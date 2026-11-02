#!/usr/bin/env python3
"""Y540 keyboard rescue for Linux (run from a live USB as root).

Catches a keyboard controller that restarts in a loop (exp5), switches it to
its bootloader before the loop can reset it, then writes a known firmware image
with the same steps as the Windows updater (fix11): chip ID check, bootloader
reset-routine check, full backup, erase, block writes with device checksum,
block 0 last, full readback compare, C4 reset.

Standard library only. Talks to the device through usbfs (/dev/bus/usb).
Usage:
    sudo python3 y540_linux_rescue.py 44-reset-exp4.bin
    python3 y540_linux_rescue.py --selftest 44-reset-exp4.bin
"""
import ctypes, glob, hashlib, os, struct, sys, time
try:
    import fcntl
except ImportError:          # Windows: only --selftest is usable
    fcntl = None

VID = 0x048D
PID_NORMAL, PID_BOOT = 0xC100, 0x89DB
IMAGE_SIZE, BLOCK, CHUNK, READ_CHUNK = 0xD800, 1024, 57, 56
KNOWN = {
    '3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359': 'stock 44',
    '2b34b6d59db8443831a7e0387ae65970307f516e816dd481f1ba513d3f9de773': 'exp1',
    '82c94fd50191a3ad8b4f9760ebf588b911b193450dd7edeeec06bacba338e1b8': 'exp2',
    'e0a959a63dceada1f5fad6846451372271e266ec176cfd25bb322a69199b5457': 'exp3',
    '27438bf439766926420047b4cb65fcfca2417c7d6a36f7802d824f1f7f27ca34': 'exp4',
    '393158db2365d3c987922069e796e4431703660fb63fb7b536e1a302596b1620': 'exp5',
}
WRITABLE = {'stock 44', 'exp1', 'exp3', 'exp4'}          # exp2/exp5 never written
NEEDS_RESET_DEPS = {'exp3', 'exp4'}
DEP_F12C = bytes.fromhex('e4fdfcc3ed9fec9e5013e4fbe490200bf00bebb442f60dbd00010c80e622')
DEP_F455 = bytes.fromhex('7f057e0012f12c902f507408f07fe87e0312f12c901058e04440f0538e3f75d80280fe')
ITE_KEY = b'ITE Tech. Inc.\x00'                          # 15 bytes, as the Windows updater
COMMAND_DELAY = 0.005                                    # SHFU.ini ALLHIDCOMMANDDELAY=5
ATTEMPTS = 3

LOG = None
def log(msg):
    line = time.strftime('%H:%M:%S ') + msg
    print(line, flush=True)
    if LOG:
        LOG.write(line + '\n'); LOG.flush()

class Fail(Exception):
    pass

# ---------------------------------------------------------------- usbfs ------
def _ioc(d, t, nr, size):
    return (d << 30) | (size << 16) | (ord(t) << 8) | nr

class CtrlTransfer(ctypes.Structure):
    _fields_ = [('bRequestType', ctypes.c_uint8), ('bRequest', ctypes.c_uint8),
                ('wValue', ctypes.c_uint16), ('wIndex', ctypes.c_uint16),
                ('wLength', ctypes.c_uint16), ('timeout', ctypes.c_uint32),
                ('data', ctypes.c_void_p)]

class DisconnectClaim(ctypes.Structure):
    _fields_ = [('interface', ctypes.c_uint), ('flags', ctypes.c_uint),
                ('driver', ctypes.c_char * 256)]

USBDEVFS_CONTROL = _ioc(3, 'U', 0, ctypes.sizeof(CtrlTransfer))
USBDEVFS_RELEASEINTERFACE = _ioc(2, 'U', 16, 4)
USBDEVFS_DISCONNECT_CLAIM = _ioc(2, 'U', 27, ctypes.sizeof(DisconnectClaim))

FAST_PATHS = ['/sys/bus/usb/devices/1-9']   # internal keyboard port (HS09) on the Y540

def find(pid, full=True):
    for d in FAST_PATHS + (glob.glob('/sys/bus/usb/devices/*') if full else []):
        try:
            if int(open(d + '/idVendor').read(), 16) == VID and int(open(d + '/idProduct').read(), 16) == pid:
                bus = int(open(d + '/busnum').read()); dev = int(open(d + '/devnum').read())
                return d, '/dev/bus/usb/%03d/%03d' % (bus, dev)
        except (OSError, ValueError):
            pass
    return None, None

class Usb:
    def __init__(self, node):
        self.fd = os.open(node, os.O_RDWR)
    def close(self):
        try: os.close(self.fd)
        except OSError: pass
    def control(self, rtype, req, value, index, data_or_len, timeout=1000):
        if isinstance(data_or_len, int):
            buf = ctypes.create_string_buffer(data_or_len); n = data_or_len
        else:
            buf = ctypes.create_string_buffer(bytes(data_or_len), len(data_or_len)); n = len(data_or_len)
        x = CtrlTransfer(rtype, req, value, index, n, timeout, ctypes.cast(buf, ctypes.c_void_p))
        got = fcntl.ioctl(self.fd, USBDEVFS_CONTROL, x)
        return buf.raw[:got] if rtype & 0x80 else got
    def claim0(self):
        fcntl.ioctl(self.fd, USBDEVFS_DISCONNECT_CLAIM, DisconnectClaim(0, 0, b''))
    def get_status(self):
        return self.control(0x80, 0x00, 0, 0, 2, timeout=100)
    def set_feature(self, report_id, data):
        return self.control(0x21, 0x09, 0x0300 | report_id, 0, data)
    def get_feature(self, report_id, length):
        return self.control(0xA1, 0x01, 0x0300 | report_id, 0, length)


class KernelWatch:
    """Collects kernel messages about the keyboard port while the rescue runs."""
    def __init__(self):
        self.fd = None; self.lines = []; self.counts = {}
        try:
            self.fd = os.open('/dev/kmsg', os.O_RDONLY | os.O_NONBLOCK)
            os.lseek(self.fd, 0, os.SEEK_END)
        except OSError:
            self.fd = None
    def poll(self):
        if self.fd is None: return
        while True:
            try: rec = os.read(self.fd, 8192).decode('utf-8', 'replace')
            except BlockingIOError: return
            except OSError: return
            msg = rec.split(';', 1)[-1].strip()
            if 'usb 1-9' in msg or '1-9:' in msg or '1-9 ' in msg:
                key = msg.split(':', 1)[-1].strip()
                for token in ('new full-speed', 'device descriptor read', 'not accepting address',
                              'unable to enumerate', 'New USB device found', 'USB disconnect',
                              'error -71', 'error -110', 'Cannot enable', 'reset full-speed'):
                    if token in msg: self.counts[token] = self.counts.get(token, 0) + 1
                self.lines.append(msg); self.lines = self.lines[-12:]
    def summary(self):
        self.poll()
        if self.fd is None: return 'kernel messages unavailable'
        return 'kernel port 1-9 events: %s\n  last: %s' % (self.counts or 'none', '\n  last: '.join(self.lines[-8:]) or 'none')

def quick_enumeration():
    for name in ('old_scheme_first',):
        try:
            open('/sys/module/usbcore/parameters/' + name, 'w').write('Y')
            log('Linux USB setup: %s=Y (shorter enumeration).' % name)
        except OSError as e:
            log('Could not set %s: %s' % (name, e))

# --------------------------------------------------- normal-mode handoff ----
def normal_report(payload):                 # report 5A, 17 bytes incl. ID
    r = bytearray(17); r[0] = 0x5A; r[1:1 + len(payload)] = payload
    return bytes(r)

def handoff(u):
    """ITE key handshake then 5A/09, sent back to back (no pauses)."""
    for _ in range(2):
        u.set_feature(0x5A, normal_report(ITE_KEY))
        echo = u.get_feature(0x5A, 17)
        if echo[1:16] == ITE_KEY:
            break
    else:
        raise Fail('ITE key not echoed')
    u.set_feature(0x5A, normal_report(b'\x09\x00'))

def catch(seconds=180):
    log('Waiting for the keyboard (048D:C100) or update mode (048D:89DB)...')
    kw = KernelWatch()
    end = time.time() + seconds; seen = tries = 0; n = 0; note = time.time()
    while time.time() < end:
        n += 1; full = (n % 200 == 0)
        if full: kw.poll()
        if time.time() - note > 15:
            note = time.time(); log('...still waiting. ' + kw.summary().split('\n')[0])
        sysd, node = find(PID_BOOT, full)
        if node:
            log('Keyboard is in update mode.')
            return sysd, node
        sysd, node = find(PID_NORMAL, full)
        if not node:
            continue
        seen += 1
        try:
            u = Usb(node)
        except OSError:
            continue
        try:
            t0 = time.time()
            while time.time() - t0 < 0.3:          # keep it busy until we own it
                try: u.get_status()
                except OSError: pass
                try:
                    u.claim0(); break
                except OSError:
                    time.sleep(0.002)
            handoff(u); tries += 1
            log('Handoff sent (catch %d).' % seen)
        except (OSError, Fail) as e:
            log('Catch %d lost: %s' % (seen, e))
        finally:
            u.close()
        t1 = time.time()
        while time.time() - t1 < 3:
            sysd, node = find(PID_BOOT)
            if node:
                log('Keyboard is in update mode.')
                return sysd, node
            time.sleep(0.01)
    raise Fail('Timed out: keyboard seen %d times, handoff sent %d times\n%s' % (seen, tries, kw.summary()))

# ------------------------------------------------------- boot protocol ------
class BootLink:
    """63-byte feature report, no report ID, interface 0 (bootloader descriptor)."""
    def __init__(self, dev):
        self.dev = dev
    def _io(self, fn):
        err = None
        for _ in range(ATTEMPTS):
            time.sleep(COMMAND_DELAY)
            try:
                return fn()
            except OSError as e:
                err = e; time.sleep(0.1)
        raise Fail('bootloader stopped answering: %s' % err)
    def send(self, payload):
        data = bytes(payload) + bytes(63 - len(payload))
        self._io(lambda: self.dev.set_feature(0, data))
    def recv(self, n):
        return self._io(lambda: self.dev.get_feature(0, 63))[:n]

def chip_id(b):
    chip = []
    for j in range(2):
        b.send(bytes([7, j, 0x20, 0xF0, 3]))
        p = b.recv(8)
        if p[1] != j or p[2] != 0x20 or p[3] != 0xF0 or p[4] != 3:
            raise Fail('chip response address mismatch')
        chip.append(p[5])
    return chip[0] << 8 | chip[1]

def read_flash(b, addr, size, label=None):
    out = bytearray()
    while len(out) < size:
        n = min(READ_CHUNK, size - len(out)); a = addr + len(out)
        b.send(bytes([0xD1, a & 255, a >> 8 & 255, a >> 16 & 255, n]) + bytes(n))
        out += b.recv(n + 5)[5:5 + n]
        if label and len(out) % 0x2000 < READ_CHUNK:
            log('%s %d/%d' % (label, len(out), size))
    return bytes(out)

def write_block(b, fw, index):
    off = index * BLOCK
    data = fw[off:off + BLOCK] + b'\xff' * (BLOCK - len(fw[off:off + BLOCK]))
    if data == b'\xff' * BLOCK:
        return
    b.send(b'\xc0')
    src = fw[off:off + BLOCK]
    for i in range(0, len(src), CHUNK):
        part = src[i:i + CHUNK]
        b.send(bytes([0xC1, i & 255, i >> 8, len(part)]) + part)
    b.send(b'\xd0')
    p = b.recv(3)
    if (p[1] | p[2] << 8) != sum(data) & 0xFFFF:
        raise Fail('device staging checksum differs at block 0x%04X' % off)
    b.send(bytes([0xC3, off & 255, off >> 8 & 255, off >> 16 & 255, 0, 4]))
    time.sleep(0.005)

def interrupted_write_of(fw, flash):
    ff = b'\xff' * BLOCK
    if flash[:BLOCK] != ff:
        return False
    written = 0
    for o in range(BLOCK, IMAGE_SIZE, BLOCK):
        if flash[o:o + BLOCK] == fw[o:o + BLOCK]:
            written += fw[o:o + BLOCK] != ff
        elif flash[o:o + BLOCK] != ff:
            return False
    return written > 0

def program(b, fw, name, backup_path):
    got = None
    for r in range(12):
        try:
            got = chip_id(b); break
        except Fail as e:
            log('Bootloader not ready (%s), retry %d/12' % (e, r + 1)); time.sleep(0.5)
    if got not in (0x8171, 0x8176):
        raise Fail('boot chip ID %r is not 8171/8176; nothing erased' % got)
    log('Bootloader chip %04X answered.' % got)
    if name in NEEDS_RESET_DEPS:
        if read_flash(b, 0xF12C, len(DEP_F12C)) != DEP_F12C or read_flash(b, 0xF455, len(DEP_F455)) != DEP_F455:
            raise Fail('bootloader reset routine differs; nothing erased')
        log('Bootloader reset routine matches.')
    cur = read_flash(b, 0, IMAGE_SIZE, 'Backup read')
    h = hashlib.sha256(cur).hexdigest()
    if h in KNOWN:
        log('Current firmware is exactly %s.' % KNOWN[h])
    elif interrupted_write_of(fw, cur):
        log('Current firmware is an interrupted write of the selected image.')
    else:
        if read_flash(b, 0, IMAGE_SIZE, 'Confirm read') != cur:
            raise Fail('firmware changed between backup reads; nothing erased')
    with open(backup_path, 'wb') as f:
        f.write(cur); f.flush(); os.fsync(f.fileno())
    log('Backup saved: %s (sha256 %s)' % (backup_path, h))
    blocks = IMAGE_SIZE // BLOCK
    for attempt in range(2):                                  # PROGRAMFAILRETRY=1
        log('Erase (attempt %d)' % (attempt + 1))
        b.send(bytes([0xC2, 0, 0, 0, blocks & 255, blocks >> 8])); time.sleep(0.005)
        for i in range(1, blocks + 1):
            write_block(b, fw, 0 if i == blocks else i)       # block 0 last
            if i % 9 == 0 or i == blocks:
                log('Write %d/%d' % (i, blocks))
        if read_flash(b, 0, IMAGE_SIZE, 'Readback') == fw:
            b.send(b'\xc4')
            log('SUCCESS: readback matches %s; reset sent. The keyboard restarts in a few seconds.' % name)
            return
        log('Readback differs from selected firmware.')
    raise Fail('readback differs after retries; left in update mode, no reset')

def load_image(path):
    fw = open(path, 'rb').read()
    name = KNOWN.get(hashlib.sha256(fw).hexdigest())
    if len(fw) != IMAGE_SIZE or name not in WRITABLE:
        raise Fail('%s is not an allowed image (stock 44, exp1, exp3, exp4)' % path)
    return fw, name

# ------------------------------------------------------------- selftest ----
class FakeBoot:
    """In-memory bootloader model for --selftest (no hardware)."""
    def __init__(self, flash, upper):
        self.flash = bytearray(flash); self.upper = upper
        self.stage = bytearray(b'\xff' * BLOCK); self.reply = bytes(63)
        self.order = []; self.reset = False
    def set_feature(self, rid, d):
        assert rid == 0 and len(d) == 63
        c = d[0]
        if c == 7:
            j = d[1]; self.reply = bytes([7, j, 0x20, 0xF0, 3, (0x81, 0x71)[j]]) + bytes(57)
        elif c == 0xD1:
            a = d[1] | d[2] << 8 | d[3] << 16; n = d[4]
            mem = bytes(self.flash) + self.upper
            self.reply = bytes(d[:5]) + mem[a:a + n] + bytes(58 - n)
        elif c == 0xC2:
            self.flash[:] = b'\xff' * IMAGE_SIZE
        elif c == 0xC0:
            self.stage[:] = b'\xff' * BLOCK
        elif c == 0xC1:
            o = d[1] | d[2] << 8; n = d[3]; self.stage[o:o + n] = d[4:4 + n]
        elif c == 0xD0:
            s = sum(self.stage) & 0xFFFF; self.reply = bytes([0xD0, s & 255, s >> 8]) + bytes(60)
        elif c == 0xC3:
            a = d[1] | d[2] << 8 | d[3] << 16
            assert self.flash[a:a + BLOCK] == b'\xff' * BLOCK
            self.flash[a:a + BLOCK] = self.stage; self.order.append(a)
        elif c == 0xC4:
            self.reset = True
        return 63
    def get_feature(self, rid, n):
        return self.reply[:n]

def selftest(image_path):
    global COMMAND_DELAY
    import tempfile
    COMMAND_DELAY = 0
    scratch = os.path.join(tempfile.gettempdir(), 'y540-selftest-backup.bin')
    fw, name = load_image(image_path)
    upper = bytearray(b'\xff' * 0x2800)
    upper[0xF12C - 0xD800:0xF12C - 0xD800 + len(DEP_F12C)] = DEP_F12C
    upper[0xF455 - 0xD800:0xF455 - 0xD800 + len(DEP_F455)] = DEP_F455
    stock = bytearray(fw); stock[0x4C7B:0x4C7E] = b'\x90\x0d\xd3'       # not a known image
    for start, label in [(bytes(stock), 'unknown content'), (b'\xff' * IMAGE_SIZE, 'blank')]:
        dev = FakeBoot(start, bytes(upper))
        program(BootLink(dev), fw, name, scratch)
        assert bytes(dev.flash) == fw and dev.reset and dev.order[-1] == 0 and dev.order[0] == BLOCK
    bad = bytearray(upper); bad[0xF455 - 0xD800] ^= 1
    dev = FakeBoot(bytes(stock), bytes(bad))
    try:
        program(BootLink(dev), fw, name, scratch); raise AssertionError('dependency check missed')
    except Fail:
        assert bytes(dev.flash) == bytes(stock) and not dev.reset
    log('SELFTEST PASSED for %s: writes verified, block 0 last, dependency mismatch stops before erase.' % name)

# ----------------------------------------------------------------- main -----
def main():
    global LOG
    args = sys.argv[1:]
    if len(args) == 2 and args[0] == '--selftest':
        selftest(args[1]); return 0
    if len(args) != 1:
        print(__doc__); return 2
    if os.geteuid() != 0:
        print('Run with sudo: sudo python3 %s %s' % (sys.argv[0], args[0])); return 2
    fw, name = load_image(args[0])
    here = os.path.dirname(os.path.abspath(args[0]))
    stamp = time.strftime('%Y%m%dT%H%M%S')
    if not os.access(here, os.W_OK):
        here = '/tmp'
    LOG = open(os.path.join(here, 'rescue-%s.log' % stamp), 'w')
    log('Y540 Linux rescue. Target firmware: %s. Keep the charger plugged in.' % name)
    quick_enumeration()
    sysd, node = catch()
    try:
        open(sysd + '/power/control', 'w').write('on')        # no autosuspend in update mode
    except OSError:
        pass
    dev = Usb(node)
    try:
        dev.claim0()
        program(BootLink(dev), fw, name, os.path.join(here, 'before-rescue-%s.bin' % stamp))
    finally:
        dev.close()
    return 0

if __name__ == '__main__':
    try:
        sys.exit(main())
    except Fail as e:
        log('STOPPED: %s' % e); sys.exit(1)
