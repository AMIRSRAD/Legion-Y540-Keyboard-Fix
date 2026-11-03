"""Offline checks for exp4. Executes the real stock gate, the stub and the
bootloader's F455 bytes in the in-memory 8051 model up to the terminal wait.
Does not model USB, clocks, the watchdog or electrical reset."""
import hashlib, json, pathlib, sys

import build_exp6 as B
import instruction_model as M
from test_exp3 import CPU as _CPU


class CPU(_CPU):
    """Adds JB/JNB on accumulator bits (E0..E7), used by the 16E0 suspend check."""
    def step(self):
        op = self.code[self.pc]
        if op in (0x20, 0x30) and 0xE0 <= self.code[self.pc + 1] <= 0xE7:
            bit = self.code[self.pc + 1] - 0xE0
            rel = self.code[self.pc + 2]
            self.pc += 3
            if bool(self.a >> bit & 1) == (op == 0x20):
                self.pc = (self.pc + (rel - 256 if rel > 127 else rel)) & 0xFFFF
            return
        return super().step()

ALLOWED = set(range(0x4C43, 0x4C46)) | set(range(0x4C7B, 0x4C7E)) | set(range(0x8A00, 0x8A09)) | {0x7FFE, 0x7FFF}


def main(stock_path, upper_path):
    stock, upper = stock_path.read_bytes(), upper_path.read_bytes()
    image, s = B.build(stock, upper)
    diffs = {i for i, (a, b) in enumerate(zip(stock, image)) if a != b}
    assert diffs <= ALLOWED and {0x4C7B, 0x8A00, 0x8A05} <= diffs, sorted(map(hex, diffs))
    assert B.checksum(image) == s == (image[0x7FFE] << 8 | image[0x7FFF])
    full = image + upper
    assert len(full) == 65536
    cases = []
    # activity vetoes skipped, 16E0 suspend check kept
    for v in (1, 0x55):
        for hw, expect_reset in ((0x20, True), (0x10, False), (0x00, False), (0x30, False)):
            cpu = CPU(full); cpu.setreg(7, 1)
            cpu.xram[0x0891] = v; cpu.xram[0x08AE] = v; cpu.xram[0x0800] = 0; cpu.xram[0x0902] = 0
            cpu.xram[0x16E0] = hw
            cpu.push(M.original_test.SENT & 255); cpu.push(M.original_test.SENT >> 8)
            cpu.pc = 0x4C43
            if expect_reset:
                assert cpu.run(until_pc=0xF455, limit=30) == 'sentinel', hex(hw)
            else:
                assert cpu.run(until_pc=0x4CE1, limit=30) == 'sentinel', hex(hw)
                assert not cpu.xw
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
