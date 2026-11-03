# Experimental exp8 generator. Hardware behavior remains to be tested.
"""Build experimental firmware exp8: stock 44 that honours every USB bus reset.

Full decompile (analysis/app44/full, 2026-11-03) of the bus-reset handler 39DA,
called from the USB interrupt (INT22 -> 4F75 -> 35DD) when 2F52 bit2 is set:

    if (usb_state[+3] == 0) {          // 39E5..39EB  (usb_state = *(0DE8) = 0DD5)
        reset_state(0);                // 4B29
        2F64 = 2F74 = 2F84 = 1;        // endpoint control
        2F94 = 1; 2F54 = 0; ...        // 34DF: device ADDRESS back to 0, EP0 = 21
        2F52 = 18;
        usb_state[+3] = 1;
    }                                  // else: the bus reset is ignored

usb_state[+3] is cleared only at boot (50F3) and on wake from the firmware's own
low-power sequence (4D21). So after the first reset, every later USB reset is
ignored until the firmware has slept: the device keeps its old address. When the
idle gate does not reach that sleep between BIOS enumeration and Windows (activity
vetoes), Windows' resets are ignored and every GET_DESCRIPTOR to address 0 fails
(boot trace: four resets, 0xC0000011 each) until power is cut.

exp8 replaces JNZ 3A21 at 39EB with CLR A ; NOP, so every bus reset runs the
first-reset path exactly (R7 = 0 into 4B29), as the USB specification requires.
Sleep, wake and everything else stay stock. 2 bytes + checksum.
"""
import hashlib, json, sys

STOCK_SHA = '3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359'
GUARD = 0x39EB
GUARD_ORIG = bytes.fromhex('7034')          # JNZ 3A21
GUARD_NEW = bytes.fromhex('e400')           # CLR A ; NOP
CONTEXT = bytes.fromhex('900003' '12857a' '7034' 'ff' '124b29')   # 39E5..39F0


def checksum(img):
    work = bytearray(img)
    work[0x7FFE] = work[0x7FFF] = 0xFF
    return sum(work[0x400:0xD800]) & 0xFFFF


def build(stock):
    assert hashlib.sha256(stock).hexdigest() == STOCK_SHA, 'Wrong stock image'
    img = bytearray(stock)
    assert img[0x39E5:0x39F1] == CONTEXT, 'bus-reset guard differs'
    img[GUARD:GUARD + 2] = GUARD_NEW
    s = checksum(img)
    img[0x7FFE], img[0x7FFF] = s >> 8, s & 0xFF
    return bytes(img), s


if __name__ == '__main__':
    from pathlib import Path
    if len(sys.argv) != 3:
        raise SystemExit('Usage: build_exp8.py STOCK_BIN OUTPUT_BIN')
    stock = Path(sys.argv[1]).read_bytes()
    image, s = build(stock)
    out = Path(sys.argv[2])
    with out.open('xb') as f:
        f.write(image)
    manifest = {
        'experiment': 'exp8-honour-every-bus-reset',
        'image_sha256': hashlib.sha256(image).hexdigest(), 'stock_sha256': STOCK_SHA,
        'checksum': '%04X' % s, 'bytes': len(image),
        'diffs': [{'offset': hex(i), 'before': a, 'after': b}
                  for i, (a, b) in enumerate(zip(stock, image)) if a != b],
        'hardware_validated': False,
        'limits': ['Assumes the IT8176 USB block does not itself clear the address on bus reset '
                   '(firmware 44 and the bootloader both clear 2F54 in software).',
                   'A spurious bus-reset flag would now re-initialise endpoints; the host re-enumerates.'],
    }
    out.with_suffix('.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf8')
    print(json.dumps(manifest, indent=2))
