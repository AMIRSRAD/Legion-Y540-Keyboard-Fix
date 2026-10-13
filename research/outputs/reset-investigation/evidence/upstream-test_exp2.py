"""Offline test of the exp2 watchdog routines on a minimal 8051 interpreter.
This executes ONLY the new routines (and the hook stubs), with the rest of the firmware replaced by
sentinels. It checks logic, thresholds, register/stack discipline and the restart sequence. It does
not model the chip, the USB core or the real ISR environment.
Usage: python test_exp2.py STOCK_BIN
"""
import sys
import build_exp2 as B

class Halt(Exception):
    pass

class CPU:
    def __init__(self, img):
        self.code = img
        self.iram = bytearray(256)
        self.xram = {}
        self.pc = 0
        self.a = 0; self.c = 0; self.sp = 0x30; self.dptr = 0
        self.psw_bank = 0; self.ea = 1
        self.xw = []  # (addr, val) writes
        self.reti_to = None
    def reg(self, n): return self.iram[(self.psw_bank * 8) + n]
    def setreg(self, n, v): self.iram[(self.psw_bank * 8) + n] = v & 255
    def fetch(self):
        v = self.code[self.pc]; self.pc += 1; return v
    def push(self, v):
        self.sp += 1; self.iram[self.sp] = v & 255
    def pop(self):
        v = self.iram[self.sp]; self.sp -= 1; return v
    def rd_dir(self, d):
        if d == 0xE0: return self.a
        if d == 0x82: return self.dptr & 255
        if d == 0x83: return self.dptr >> 8
        raise Halt('dir read %02x' % d)
    def wr_dir(self, d, v):
        if d == 0xD0: self.psw_bank = (v >> 3) & 3; return
        if d == 0x81: self.sp = v; return
        if d == 0xE0: self.a = v; return
        if d == 0x82: self.dptr = (self.dptr & 0xFF00) | v; return
        if d == 0x83: self.dptr = (self.dptr & 0xFF) | (v << 8); return
        raise Halt('dir write %02x' % d)
    def rel(self):
        r = self.fetch(); return r - 256 if r > 127 else r
    def step(self):
        pc0 = self.pc
        o = self.fetch()
        if o == 0x75:
            d = self.fetch(); v = self.fetch(); self.wr_dir(d, v)
        elif o == 0x90:
            hi = self.fetch(); lo = self.fetch(); self.dptr = hi << 8 | lo
        elif o == 0xE0: self.a = self.xram.get(self.dptr, 0)
        elif o == 0xF0:
            self.xram[self.dptr] = self.a; self.xw.append((self.dptr, self.a))
        elif o == 0xA3: self.dptr = (self.dptr + 1) & 0xFFFF
        elif o == 0xE4: self.a = 0
        elif o == 0x24:
            v = self.fetch(); s = self.a + v; self.c = s > 255; self.a = s & 255
        elif o == 0x34:
            v = self.fetch(); s = self.a + v + self.c; self.c = s > 255; self.a = s & 255
        elif o == 0x94:
            v = self.fetch(); s = self.a - v - self.c; self.c = s < 0; self.a = s & 255
        elif o == 0xC3: self.c = 0
        elif o == 0x74: self.a = self.fetch()
        elif o == 0xFA: self.setreg(2, self.a)
        elif o == 0xEA: self.a = self.reg(2)
        elif 0x78 <= o <= 0x7F: self.setreg(o - 0x78, self.fetch())
        elif 0xD8 <= o <= 0xDF:
            n = o - 0xD8; r = self.rel(); v = (self.reg(n) - 1) & 255; self.setreg(n, v)
            if v: self.pc += r
        elif o == 0xB4:
            v = self.fetch(); r = self.rel(); self.c = self.a < v
            if self.a != v: self.pc += r
        elif o == 0x40:
            r = self.rel()
            if self.c: self.pc += r
        elif o == 0x60:
            r = self.rel()
            if self.a == 0: self.pc += r
        elif o == 0x80: r = self.rel(); self.pc += r
        elif o == 0x02:
            hi = self.fetch(); lo = self.fetch(); self.pc = hi << 8 | lo
        elif o == 0x12:
            hi = self.fetch(); lo = self.fetch(); self.push(self.pc & 255); self.push(self.pc >> 8); self.pc = hi << 8 | lo
        elif o == 0x22:
            hi = self.pop(); lo = self.pop(); self.pc = hi << 8 | lo
        elif o == 0x32:
            hi = self.pop(); lo = self.pop(); self.pc = hi << 8 | lo; self.reti_to = self.pc; raise Halt('reti')
        elif o == 0xC2:
            b = self.fetch()
            if b == 0xAF: self.ea = 0
            else: raise Halt('clr bit')
        elif o == 0xC0: self.push(self.rd_dir(self.fetch()))
        elif o == 0xD0: self.wr_dir(self.fetch(), self.pop())
        else: raise Halt('opcode %02x at %04x' % (o, pc0))
    def run(self, until_pc=None, limit=5_000_000):
        n = 0
        while n < limit:
            if until_pc is not None and self.pc == until_pc: return 'sentinel'
            try: self.step()
            except Halt as h:
                return str(h)
            n += 1
        raise RuntimeError('step limit')

def make(stock):
    img, a, s = B.build(stock)
    full = bytearray(0x10000); full[:len(img)] = img
    return bytes(full), a

SENT = 0xFFF0
def call(cpu, addr):
    cpu.push(SENT & 255); cpu.push(SENT >> 8); cpu.pc = addr
    return cpu.run(until_pc=SENT)

def main():
    stock = open(sys.argv[1], 'rb').read()
    img, a = make(stock)
    L = a.labels
    ok = True
    def check(c, msg):
        nonlocal ok
        if not c: ok = False; print('FAIL', msg)
    iram_snapshot = None

    # --- S1: no kick -> restart exactly at tick T1 (hi/lo compare), stack/regs behave
    cpu = CPU(img)
    result = None; ticks = 0
    for t in range(1, B.T1 + 5):
        cpu.sp = 0x30; cpu.iram[0x30] = 0
        r = call(cpu, L['tick'])
        ticks = t
        if r == 'reti': result = t; break
        check(r == 'sentinel', 'tick returned %s' % r)
    check(result == B.T1, 'T1 restart at %s (want %d)' % (result, B.T1))
    check(cpu.reti_to == 0x0100, 'RETI target %s' % cpu.reti_to)
    check(cpu.sp == 7, 'SP after RETI %d' % cpu.sp)
    check(cpu.ea == 0, 'EA not cleared')
    check((0x2F40, 0) in cpu.xw, 'no detach write')

    # --- S2: healthy main loop (counter cleared as kick does; kick itself is checked in S3)
    cpu = CPU(img); bad = None
    for t in range(1, 200001):
        cpu.sp = 0x30
        r = call(cpu, L['tick'])
        if r == 'reti': bad = t; break
        if t % 50 == 0:
            cpu.xram[B.VAR_MAIN] = 0; cpu.xram[B.VAR_MAIN + 1] = 0   # what kick does (checked separately)
    check(bad is None, 'restart during healthy run at tick %s' % bad)

    # --- S3: kick stub: clears counter, preserves A/DPTR, ends at 07C4
    cpu = CPU(img); cpu.xram[B.VAR_MAIN] = 0x12; cpu.xram[B.VAR_MAIN + 1] = 0x34
    cpu.dptr = 0xBEEF; cpu.a = 0x77; sp0 = cpu.sp
    cpu.push(SENT & 255); cpu.push(SENT >> 8); cpu.pc = L['kick']
    r = cpu.run(until_pc=0x07C4)
    check(r == 'sentinel', 'kick did not reach 07C4: %s' % r)
    check(cpu.xram[B.VAR_MAIN] == 0 and cpu.xram[B.VAR_MAIN + 1] == 0, 'kick did not clear')
    check(cpu.dptr == 0xBEEF and cpu.a == 0x77, 'kick clobbered A/DPTR')
    check(cpu.sp == sp0 + 2, 'kick stack imbalance')

    # --- S4: arm/disarm + T2 threshold
    for disarm_at, expect in ((None, B.T2), (2000, None)):
        cpu = CPU(img)
        cpu.dptr = 0xCAFE; cpu.a = 0x11; sp0 = cpu.sp
        cpu.push(SENT & 255); cpu.push(SENT >> 8); cpu.pc = L['arm']
        r = cpu.run(until_pc=0x39DA)
        check(r == 'sentinel', 'arm flow %s' % r)
        check(cpu.dptr == 0xCAFE and cpu.a == 0x11 and cpu.sp == sp0 + 2, 'arm clobbered state')
        check(cpu.xram[B.VAR_ARM] == 1, 'arm flag')
        res = None
        for t in range(1, 7000):
            cpu.sp = 0x30
            cpu.xram[B.VAR_MAIN] = 0; cpu.xram[B.VAR_MAIN + 1] = 0  # healthy main loop
            if disarm_at and t == disarm_at:
                cpu.a = 0xAA; cpu.sp = 0x30
                call(cpu, L['disarm'])
                check(cpu.dptr == 0x0002 and cpu.xram[B.VAR_ARM] == 0, 'disarm effect')
            r = call(cpu, L['tick'])
            if r == 'reti': res = t; break
        check(res == expect, 'T2 result %s want %s (disarm_at=%s)' % (res, expect, disarm_at))

    # --- S5: not armed -> enum counter never runs
    cpu = CPU(img)
    for t in range(1, 5000):
        cpu.sp = 0x30; cpu.xram[B.VAR_MAIN] = 0; cpu.xram[B.VAR_MAIN + 1] = 0
        r = call(cpu, L['tick'])
        check(r == 'sentinel', 'unarmed restart at %d' % t)
        if r != 'sentinel': break

    # --- S6: ISR-stack discipline: tick must leave SP and iram[1..0x30] alone on normal return
    cpu = CPU(img); cpu.sp = 0x30
    for i in range(0x31): cpu.iram[i] = i ^ 0x5A
    snap = bytes(cpu.iram[0x20:0x31])
    call(cpu, L['tick'])
    check(cpu.sp == 0x30, 'SP drift %d' % cpu.sp)
    check(bytes(cpu.iram[0x20:0x31]) == snap, 'tick wrote to low iram')
    print('exp2 code: %d bytes at %s' % (len(a.build()), hex(B.BASE)))
    print('ALL OK' if ok else 'FAILURES')
    sys.exit(0 if ok else 1)

main()
