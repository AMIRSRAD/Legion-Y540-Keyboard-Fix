# Experimental exp4 generator. Hardware behavior remains to be tested.
"""Build experimental firmware exp4 ("reset instead of sleep") from exact stock 44.

Stock 44 decides at 4C79 (JZ 4CE1) whether the bus has been idle long enough
to enter its low-power sequence, which starts at 4C7B (MOV DPTR,#0DD3).
exp1 skipped that sequence (keyboard stays awake, still wedges on restart #3).
exp3 added a timeout reset but only reacted to bus resets or a stalled main
loop, which a silently wedged USB block never produces.

exp4 keeps stock's idle decision and replaces the low-power sequence with the
byte-verified bootloader C4 terminal reset path (F455): when the host goes
quiet (restart, shutdown, BIOS-to-OS handoff), the controller restarts from
power-on code, so the host always meets a freshly initialised device.

Changes: 3 bytes at 4C7B (LJMP stub), 9-byte stub at 8A00 (originally FF),
checksum at 7FFE..7FFF. Everything else is byte-identical to stock 44.
"""
import hashlib, json, sys

STOCK_SHA = '3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359'
UPPER_SHA = '6160ed916d5356c631a5e7939a55d3dae0b863199e0f33ba7e6680fe6f684d2a'
F455_BYTES = bytes.fromhex('7f057e0012f12c902f507408f07fe87e0312f12c901058e04440f0538e3f75d80280fe')
F12C_BYTES = bytes.fromhex('e4fdfcc3ed9fec9e5013e4fbe490200bf00bebb442f60dbd00010c80e622')
HOOK = 0x4C7B
STUB = 0x8A00
SLEEP_ENTRY = bytes.fromhex('900dd3')          # MOV DPTR,#0DD3 (first byte of sleep sequence)
GATE = bytes.fromhex('ef6066')                 # MOV A,R7 ; JZ 4CE1 (stock idle decision, kept)
STUB_CODE = bytes([
    0xC2, 0xAF,        # CLR EA          no interrupts during the terminal sequence
    0x75, 0xD0, 0x00,  # MOV PSW,#00h    bank 0 for the bootloader delay routine
    0x02, 0xF4, 0x55,  # LJMP F455       verified C4 terminal reset path (detach + watchdog)
    0x22,              # RET             unreachable padding
])

def checksum(img):
    work = bytearray(img)
    work[0x7FFE] = work[0x7FFF] = 0xFF
    return sum(work[0x400:0xD800]) & 0xFFFF

def build(stock, upper):
    assert hashlib.sha256(stock).hexdigest() == STOCK_SHA, 'Wrong stock image'
    assert len(upper) == 0x2800 and hashlib.sha256(upper).hexdigest() == UPPER_SHA, 'Wrong bootloader dump'
    assert upper[0xF455 - 0xD800:0xF455 - 0xD800 + len(F455_BYTES)] == F455_BYTES
    assert upper[0xF12C - 0xD800:0xF12C - 0xD800 + len(F12C_BYTES)] == F12C_BYTES
    assert checksum(stock) == (stock[0x7FFE] << 8 | stock[0x7FFF]) == 0x5622, 'checksum convention mismatch'
    img = bytearray(stock)
    assert img[0x4C78:0x4C7B] == GATE, 'idle gate differs'
    assert img[HOOK:HOOK + 3] == SLEEP_ENTRY, 'sleep entry differs'
    assert all(b == 0xFF for b in img[STUB:STUB + len(STUB_CODE)]), 'stub area not free'
    img[HOOK:HOOK + 3] = bytes([0x02, STUB >> 8, STUB & 0xFF])
    img[STUB:STUB + len(STUB_CODE)] = STUB_CODE
    s = checksum(img)
    img[0x7FFE], img[0x7FFF] = s >> 8, s & 0xFF
    return bytes(img), s

if __name__ == '__main__':
    from pathlib import Path
    if len(sys.argv) != 4:
        raise SystemExit('Usage: build_exp4.py STOCK_BIN UPPER_DUMP OUTPUT_BIN')
    stock = Path(sys.argv[1]).read_bytes()
    upper = Path(sys.argv[2]).read_bytes()
    image, s = build(stock, upper)
    out = Path(sys.argv[3])
    with out.open('xb') as f:
        f.write(image)
    manifest = {
        'experiment': 'exp4-reset-instead-of-sleep',
        'image_sha256': hashlib.sha256(image).hexdigest(),
        'stock_sha256': STOCK_SHA, 'upper_dump_sha256': UPPER_SHA,
        'checksum': '%04X' % s, 'bytes': len(image),
        'diffs': [{'offset': hex(i), 'before': a, 'after': b}
                  for i, (a, b) in enumerate(zip(stock, image)) if a != b],
        'hardware_validated': False,
        'limits': ['Fires whenever stock would have entered its idle low-power sequence, including '
                   'Windows runtime selective suspend and system sleep: the keyboard detaches and '
                   're-enumerates instead of sleeping; keyboard wake from sleep is lost.',
                   'Recovery depends on the C4 path resetting the USB block; observed for update '
                   'handoff, not yet for the wedged state.',
                   'Idle thresholds/tick rate inherited from stock and not independently timed.'],
    }
    out.with_suffix('.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf8')
    print(json.dumps(manifest, indent=2))
