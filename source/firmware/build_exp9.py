# Experimental exp9 generator. Hardware behavior remains to be tested.
"""Build experimental firmware exp9 = exp7 (frame-counter watchdog) + exp8 (honour every
USB bus reset). Reserve build in case exp7 alone misses a case where the PC resets the
keyboard without first going quiet for ~0.4 s (e.g. a port reset while Windows runs).
exp9 differs from exp7 only at 39EB..39EC (JNZ 3A21 -> CLR A ; NOP) and the checksum.
"""
import hashlib, json, sys

import build_exp7 as E7
import build_exp8 as E8

EXP7_SHA = 'fc0d0141e9468288f11d762f69820022e2936f7b9ccbf42cff147ea24e8a28c0'


def build(stock, upper):
    exp7, _ = E7.build(stock, upper)
    assert hashlib.sha256(exp7).hexdigest() == EXP7_SHA, 'exp7 base differs'
    img = bytearray(exp7)
    assert img[0x39E5:0x39F1] == E8.CONTEXT, 'bus-reset guard differs'
    img[E8.GUARD:E8.GUARD + 2] = E8.GUARD_NEW
    s = E7.checksum(img)
    img[0x7FFE], img[0x7FFF] = s >> 8, s & 0xFF
    return bytes(img), s


if __name__ == '__main__':
    from pathlib import Path
    if len(sys.argv) != 4:
        raise SystemExit('Usage: build_exp9.py STOCK_BIN UPPER_DUMP OUTPUT_BIN')
    stock = Path(sys.argv[1]).read_bytes()
    upper = Path(sys.argv[2]).read_bytes()
    image, s = build(stock, upper)
    out = Path(sys.argv[3])
    with out.open('xb') as f:
        f.write(image)
    manifest = {
        'experiment': 'exp9-frame-watchdog-plus-bus-reset-fix',
        'image_sha256': hashlib.sha256(image).hexdigest(), 'base_exp7_sha256': EXP7_SHA,
        'checksum': '%04X' % s, 'bytes': len(image),
        'diffs': [{'offset': hex(i), 'before': a, 'after': b}
                  for i, (a, b) in enumerate(zip(stock, image)) if a != b],
        'hardware_validated': False,
        'limits': E7.__doc__.strip().splitlines()[:1] + ['Same limits as exp7 and exp8.'],
    }
    out.with_suffix('.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf8')
    print(json.dumps(manifest, indent=2))
