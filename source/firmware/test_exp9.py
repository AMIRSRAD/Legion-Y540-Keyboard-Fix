"""Offline checks for exp9: equals exp7 except the exp8 bus-reset guard bytes and checksum,
and the exp7 frame-watchdog ISR checks (test_exp7) pass on the exp9 image."""
import hashlib, json, pathlib, sys

import build_exp7 as E7
import build_exp9 as B
import test_exp7 as T7


def main(stock_path, upper_path):
    stock, upper = stock_path.read_bytes(), upper_path.read_bytes()
    image, s = B.build(stock, upper)
    exp7, _ = E7.build(stock, upper)
    diffs = {i for i, (a, b) in enumerate(zip(exp7, image)) if a != b}
    assert diffs <= {0x39EB, 0x39EC, 0x7FFE, 0x7FFF} and {0x39EB, 0x39EC} <= diffs, sorted(map(hex, diffs))
    assert image[0x39EB:0x39ED] == bytes.fromhex('e400')
    assert E7.checksum(image) == s == (image[0x7FFE] << 8 | image[0x7FFF])
    full = image + upper
    ram = {}
    def run(frame):
        nonlocal ram
        cpu, out = T7.isr(full, frame, ram)
        ram = dict(cpu.xram)
        return cpu, out
    for i in range(3000):                          # live bus: arms, never resets
        assert run((i * 100 // 260) & 0xFF)[1] == 'reti'
    frame = ram[E7.VAR_LAST]
    n = 0
    while True:                                    # host stops: reset after STALL_TICKS
        cpu, out = run(frame); n += 1
        if out == 'reset': break
        assert n <= E7.STALL_TICKS
    assert E7.STALL_TICKS - 3 <= n <= E7.STALL_TICKS, n      # counter may already hold 1-2 ticks
    ram = {}
    for i in range(5000):                          # after reset, host off: no further reset
        assert run(frame)[1] == 'reti'
    print(json.dumps({'reset_after_ticks': n, 'image_sha256': hashlib.sha256(image).hexdigest(), 'checksum': '%04X' % s,
                      'changed_vs_exp7': sorted(hex(d) for d in diffs)}, indent=2))


if __name__ == '__main__':
    if len(sys.argv) != 3:
        raise SystemExit('Usage: test_exp9.py STOCK_BIN UPPER_DUMP')
    main(pathlib.Path(sys.argv[1]), pathlib.Path(sys.argv[2]))
