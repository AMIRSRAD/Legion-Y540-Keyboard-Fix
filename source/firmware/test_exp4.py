"""Offline checks for exp4. Executes the real stock gate, the stub and the
bootloader's F455 bytes in the in-memory 8051 model up to the terminal wait.
Does not model USB, clocks, the watchdog or electrical reset."""
import hashlib, json, pathlib, sys

import build_exp4 as B
import instruction_model as M
from test_exp3 import CPU

ALLOWED = set(range(0x4C7B, 0x4C7E)) | set(range(0x8A00, 0x8A09)) | {0x7FFE, 0x7FFF}


def main(stock_path, upper_path):
    stock, upper = stock_path.read_bytes(), upper_path.read_bytes()
    image, s = B.build(stock, upper)
    diffs = {i for i, (a, b) in enumerate(zip(stock, image)) if a != b}
    assert diffs <= ALLOWED and {0x4C7B, 0x8A00, 0x8A05} <= diffs, sorted(map(hex, diffs))
    assert B.checksum(image) == s == (image[0x7FFE] << 8 | image[0x7FFF])
    full = image + upper
    assert len(full) == 65536
    cases = []
    for r7 in range(256):
        for bank in (0, 1, 2, 3):
            for ea in (False, True):
                cpu = CPU(full)
                cpu.xram[0x1058] = 0x85
                cpu.psw_bank, cpu.ea = bank, ea
                cpu.setreg(7, r7)
                cpu.push(M.original_test.SENT & 255)
                cpu.push(M.original_test.SENT >> 8)
                cpu.pc = 0x4C78
                if r7 == 0:
                    # Stock "not idle" branch: plain RET, no MMIO at all.
                    assert cpu.run(until_pc=0x4CE1, limit=10) == 'sentinel'
                    assert not cpu.xw
                    continue
                assert cpu.run(until_pc=0xF455, limit=10) == 'sentinel'
                assert not cpu.ea and cpu.psw_bank == 0
                assert not cpu.xw, 'no MMIO before the bootloader path'
                assert cpu.run(until_pc=0xF476) == 'sentinel'
                assert cpu.xram[0x2F50] == 8 and cpu.xram[0x1058] == 0xC5
                assert cpu.sfr[0xD8] == 2
                assert all(a not in (0x0DD3, 0x08AD, 0x1E20, 0x1E03) for a, _ in cpu.xw)
                cases.append((r7, bank, ea))
    result = {'image_sha256': hashlib.sha256(image).hexdigest(), 'checksum': '%04X' % s,
              'changed_offsets': sorted(hex(d) for d in diffs),
              'reset_cases_to_terminal_wait': len(cases), 'not_idle_cases_plain_ret': 8,
              'physical_reset_modeled': False}
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    if len(sys.argv) != 3:
        raise SystemExit('Usage: test_exp4.py STOCK_BIN UPPER_DUMP')
    main(pathlib.Path(sys.argv[1]), pathlib.Path(sys.argv[2]))
