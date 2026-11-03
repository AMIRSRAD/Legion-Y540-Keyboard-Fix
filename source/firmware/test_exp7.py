"""Offline checks for exp7. Runs the real timer-0 ISR (3300) with the frame
watchdog hook, and the bootloader's F455 bytes, in the in-memory 8051 model.
Does not model USB, clocks, the watchdog or electrical reset."""
import hashlib, json, pathlib, sys

import build_exp7 as B
import instruction_model as M
from test_exp6 import CPU as _CPU


class CPU(_CPU):
    """Adds register B, low IRAM as direct addresses, and the few ISR opcodes the base lacks."""
    def __init__(self, image):
        super().__init__(image)
        self.sfr.update({0xF0: 0, 0x8A: 0, 0x8C: 0})

    def rd_dir(self, d):
        if d < 0x80:
            return self.iram[d]
        return super().rd_dir(d)

    def wr_dir(self, d, value):
        if d < 0x80:
            self.iram[d] = value & 255
            return
        return super().wr_dir(d, value)

    def step(self):
        c = self.code
        op = c[self.pc]
        if op == 0xB5:                      # CJNE A,direct,rel
            v = self.rd_dir(c[self.pc + 1]); r = c[self.pc + 2]; self.pc += 3
            self.c = self.a < v
            if self.a != v:
                self.pc = (self.pc + (r - 256 if r > 127 else r)) & 0xFFFF
            return
        if op == 0xE5:                      # MOV A,direct
            self.a = self.rd_dir(c[self.pc + 1]); self.pc += 2; return
        if op == 0xF5:                      # MOV direct,A
            self.wr_dir(c[self.pc + 1], self.a); self.pc += 2; return
        if op == 0x04:                      # INC A
            self.a = (self.a + 1) & 255; self.pc += 1; return
        if op == 0x32:                      # RETI
            hi = self.pop(); lo = self.pop(); self.pc = hi << 8 | lo; return
        if op == 0xD2 and c[self.pc + 1] in (0x30, 0x35):   # SETB bit in IRAM 26h
            b = c[self.pc + 1]; self.iram[0x20 + (b >> 3)] |= 1 << (b & 7); self.pc += 2; return
        if op in (0xC2, 0xD2) and c[self.pc + 1] == 0x8D:   # CLR/SETB TF0
            self.pc += 2; return
        if op == 0xD3:                      # SETB C
            self.c = True; self.pc += 1; return
        if op == 0x94:                      # SUBB A,#imm
            v = c[self.pc + 1]; r = self.a - v - self.c; self.c = r < 0; self.a = r & 255
            self.pc += 2; return
        if op == 0x40:                      # JC rel
            r = c[self.pc + 1]; self.pc += 2
            if self.c: self.pc = (self.pc + (r - 256 if r > 127 else r)) & 0xFFFF
            return
        if op == 0xD5:                      # DJNZ direct,rel
            d = c[self.pc + 1]; r = c[self.pc + 2]; self.pc += 3
            v = (self.rd_dir(d) - 1) & 255; self.wr_dir(d, v)
            if v: self.pc = (self.pc + (r - 256 if r > 127 else r)) & 0xFFFF
            return
        return super().step()


def isr(full, frame, xram=None, bank=0, ea=True):
    """Enter the timer-0 ISR once; return (cpu, outcome) with outcome 'reti' or 'reset'."""
    cpu = CPU(full)
    if xram:
        cpu.xram = dict(xram)
    cpu.xram[B.FRAME_LO] = frame
    cpu.psw_bank, cpu.ea = bank, ea
    cpu.a = 0x5A
    cpu.push(M.original_test.SENT & 255); cpu.push(M.original_test.SENT >> 8)
    cpu.pc = 0x3300
    for _ in range(400):
        if cpu.pc == 0xF455:
            return cpu, 'reset'
        if cpu.pc == M.original_test.SENT:
            return cpu, 'reti'
        cpu.step()
    raise AssertionError('ISR did not finish')


def main(stock_path, upper_path):
    stock, upper = stock_path.read_bytes(), upper_path.read_bytes()
    image, s = B.build(stock, upper)
    exp4, _ = B.E4.build(stock, upper)
    diffs = {i for i, (a, b) in enumerate(zip(exp4, image)) if a != b}
    code_len = len(B.program().build())
    allowed = set(range(0x330A, 0x330D)) | set(range(B.TICK, B.TICK + code_len)) | {0x7FFE, 0x7FFF}
    assert diffs <= allowed, sorted(map(hex, diffs - allowed))
    assert B.checksum(image) == s == (image[0x7FFE] << 8 | image[0x7FFF])
    full = image + upper
    ram = None

    def run(frame, bank=0):
        nonlocal ram
        cpu, out = isr(full, frame, ram, bank)
        ram = dict(cpu.xram)
        return cpu, out

    # 1. power-on with a static (garbage) frame value: one change, never arms, never resets
    ram = None
    for i in range(5000):
        cpu, out = run(0x77)
        assert out == 'reti'
    assert ram.get(B.VAR_ARM) == 1 and ram[0x00CF] == 1
    # 2. live bus: frame advances every ~2.6 ticks -> arms, stall counter keeps clearing
    frame = 0
    for i in range(20000):
        frame = (i * 100 // 260) & 0xFF
        cpu, out = run(frame, bank=i & 3)
        assert out == 'reti', i
        assert cpu.psw_bank == (i & 3), 'PSW restored'
        assert cpu.a == 0x5A, 'ACC restored'
    assert ram[B.VAR_ARM] == B.ARM_CHANGES
    assert ram.get(B.VAR_STALL, 0) == 0 and ram.get(B.VAR_STALL + 1, 0) <= 3
    # 3. bus reset (SE0, no frames) for 50 ms ~= 130 ticks: no reset, then frames resume
    for i in range(130):
        assert run(frame)[1] == 'reti'
    frame = (frame + 1) & 0xFF
    assert run(frame)[1] == 'reti' and ram[B.VAR_STALL] == ram[B.VAR_STALL + 1] == 0
    # 4. host stops (shutdown/handover): reset exactly at STALL_TICKS unchanged ticks
    n = 0
    while True:
        cpu, out = run(frame)
        n += 1
        if out == 'reset':
            break
        assert n < B.STALL_TICKS + 5
    assert n == B.STALL_TICKS, n
    assert not cpu.ea and cpu.psw_bank == 0
    assert cpu.run(until_pc=0xF476) == 'sentinel'
    assert cpu.xram[0x2F50] == 8 and cpu.sfr[0xD8] == 2
    # 5. after the watchdog reset, startup zeroes 0000-0FFF: host still off -> no second reset
    ram = {}
    for i in range(20000):
        assert run(frame)[1] == 'reti'
    # 6. fewer than ARM_CHANGES frame changes never arm
    ram = {}
    for k in range(B.ARM_CHANGES - 1):
        run(k + 1)
    for i in range(B.STALL_TICKS * 3):
        assert run(B.ARM_CHANGES - 1)[1] == 'reti'
    result = {'image_sha256': hashlib.sha256(image).hexdigest(), 'checksum': '%04X' % s,
              'changed_vs_exp4': sorted(hex(d) for d in diffs), 'tick_code_bytes': code_len,
              'reset_after_ticks': n, 'physical_reset_modeled': False}
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    if len(sys.argv) != 3:
        raise SystemExit('Usage: test_exp7.py STOCK_BIN UPPER_DUMP')
    main(pathlib.Path(sys.argv[1]), pathlib.Path(sys.argv[2]))
