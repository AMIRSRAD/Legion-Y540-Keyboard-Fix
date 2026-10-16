"""Build experimental firmware 2 (self-recovery) from the stock 44 image.

exp2 = exp1 (no deep-sleep gate, 4C79) + a small software watchdog in free flash at 0x8A00:

  T1  main-loop stall   : the 1 ms timer-0 ISR counts ticks; the main loop clears the count each
                          iteration (hook at 2249). >= 8000 ticks without a clear -> restart.
  T2  enumeration stall : the bus-reset handler (hook at 35E6) arms a counter; SET_ADDRESS (hook at
                          4034) disarms it. >= 3000 ticks armed -> restart.
  restart               : disable interrupts, write 0 to 2F40 (USB control, written 01/03 by the
                          firmware's own init; used here as 'detach', semantic unverified), busy-wait
                          ~0.4 s so the host sees a disconnect, then RETI to 0100, the firmware's own
                          cold-start vector (RETI clears the interrupt-in-service latch).

All new variables live in XRAM 0FF8..0FFC (cleared by the cold start). Nothing else is changed.
Usage: python build_exp2.py STOCK_BIN OUT_BIN
"""
import hashlib, json, sys

BASE = 0x8A00
VAR_MAIN = 0x0FF8      # word, big-endian: ticks since last main-loop kick
VAR_ARM = 0x0FFA       # byte: enumeration watch armed
VAR_ENUM = 0x0FFB      # word, big-endian: ticks since bus reset while armed
T1 = 8000
T2 = 3000

# ---- tiny assembler -------------------------------------------------------
class Asm:
    def __init__(self, base):
        self.base = base
        self.items = []
        self.labels = {}
        self.pos = 0
    def label(self, n):
        self.labels[n] = self.base + self.pos
    def emit(self, *bs):
        self.items.append(('b', bytes(bs), self.pos)); self.pos += len(bs)
    def rel(self, op, target, extra=b''):
        # op [extra] rel8
        self.items.append(('rel', op, extra, target, self.pos)); self.pos += 2 + len(extra)
    def a16(self, op, target):
        self.items.append(('a16', op, target, self.pos)); self.pos += 3
    def mov_dptr(self, v): self.emit(0x90, v >> 8, v & 255)
    def build(self):
        out = bytearray()
        for it in self.items:
            if it[0] == 'b':
                out += it[1]
            elif it[0] == 'rel':
                _, op, extra, tgt, p = it
                end = self.base + p + 2 + len(extra)
                tv = tgt if isinstance(tgt, int) else self.labels[tgt]
                d = tv - end
                assert -128 <= d <= 127, (tgt, d)
                out += bytes([op]) + extra + bytes([d & 255])
            else:
                _, op, tgt, p = it
                tv = tgt if isinstance(tgt, int) else self.labels[tgt]
                out += bytes([op, tv >> 8, tv & 255])
        return bytes(out)

def program():
    a = Asm(BASE)
    # --- kick: replaces LCALL 07C4 at 2249; preserves A, DPTR; then continues into 07C4 ---
    a.label('kick')
    a.emit(0xC0, 0xE0, 0xC0, 0x82, 0xC0, 0x83)          # PUSH ACC, DPL, DPH
    a.mov_dptr(VAR_MAIN); a.emit(0xE4, 0xF0, 0xA3, 0xF0)  # CLR A; MOVX @DPTR,A; INC DPTR; MOVX @DPTR,A
    a.emit(0xD0, 0x83, 0xD0, 0x82, 0xD0, 0xE0)           # POP DPH, DPL, ACC
    a.a16(0x02, 0x07C4)                                   # LJMP 07C4 (its RET returns to 224C)
    # --- arm: replaces LCALL 39DA at 35E6 (bus reset handling); keeps R7/R6.. untouched ---
    a.label('arm')
    a.emit(0xC0, 0xE0, 0xC0, 0x82, 0xC0, 0x83)
    a.mov_dptr(VAR_ARM); a.emit(0x74, 0x01, 0xF0)         # MOV A,#1; MOVX @DPTR,A
    a.emit(0xA3, 0xE4, 0xF0, 0xA3, 0xF0)                  # INC DPTR; CLR A; MOVX; INC DPTR; MOVX  (enum ticks = 0)
    a.emit(0xD0, 0x83, 0xD0, 0x82, 0xD0, 0xE0)
    a.a16(0x02, 0x39DA)                                   # LJMP 39DA
    # --- disarm: replaces 'MOV DPTR,#0002' at 4034; A is dead there ---
    a.label('disarm')
    a.mov_dptr(VAR_ARM); a.emit(0xE4, 0xF0)               # CLR A; MOVX @DPTR,A
    a.mov_dptr(0x0002)                                    # the replaced instruction
    a.emit(0x22)                                          # RET
    # --- tick: replaces MOV PSW,#10 at 330A inside the timer-0 ISR ---
    a.label('tick')
    a.emit(0x75, 0xD0, 0x10)                              # MOV PSW,#10h (replaced instruction)
    # main stall counter++
    a.mov_dptr(VAR_MAIN + 1); a.emit(0xE0, 0x24, 0x01, 0xF0, 0xFA)   # MOVX A; ADD A,#1; MOVX @DPTR,A; MOV R2,A
    a.mov_dptr(VAR_MAIN); a.emit(0xE0, 0x34, 0x00, 0xF0)             # MOVX A; ADDC A,#0; MOVX @DPTR,A
    a.rel(0xB4, 'cmp1_ne', bytes([T1 >> 8]))              # CJNE A,#hi,cmp1_ne
    a.emit(0xEA, 0xC3, 0x94, T1 & 255)                    # MOV A,R2; CLR C; SUBB A,#lo
    a.rel(0x40, 'enum_part')                              # JC enum_part   (below limit)
    a.rel(0x80, 'restart')                                # SJMP restart   (>= limit)
    a.label('cmp1_ne')
    a.rel(0x40, 'enum_part')                              # JC: A < hi -> below limit
    a.rel(0x80, 'restart')
    a.label('enum_part')
    a.mov_dptr(VAR_ARM); a.emit(0xE0)                     # MOVX A,@DPTR
    a.rel(0x60, 'done')                                   # JZ done (not armed)
    a.mov_dptr(VAR_ENUM + 1); a.emit(0xE0, 0x24, 0x01, 0xF0, 0xFA)
    a.mov_dptr(VAR_ENUM); a.emit(0xE0, 0x34, 0x00, 0xF0)
    a.rel(0xB4, 'cmp2_ne', bytes([T2 >> 8]))
    a.emit(0xEA, 0xC3, 0x94, T2 & 255)
    a.rel(0x40, 'done')
    a.rel(0x80, 'restart')
    a.label('cmp2_ne')
    a.rel(0x40, 'done')
    a.label('restart')
    a.emit(0xC2, 0xAF)                                    # CLR EA
    a.mov_dptr(0x2F40); a.emit(0xE4, 0xF0)                # detach: MOV DPTR,#2F40; CLR A; MOVX @DPTR,A
    a.emit(0x7F, 0x03)                                    # MOV R7,#3
    a.label('d_o'); a.emit(0x7E, 0x00)                    # MOV R6,#0
    a.label('d_m'); a.emit(0x7D, 0x00)                    # MOV R5,#0
    a.label('d_i'); a.rel(0xDD, 'd_i')                    # DJNZ R5,d_i
    a.rel(0xDE, 'd_m')                                    # DJNZ R6,d_m
    a.rel(0xDF, 'd_o')                                    # DJNZ R7,d_o
    a.emit(0x75, 0x81, 0x07)                              # MOV SP,#07h
    a.emit(0x74, 0x00, 0xC0, 0xE0)                        # MOV A,#00; PUSH ACC  (PCL)
    a.emit(0x74, 0x01, 0xC0, 0xE0)                        # MOV A,#01; PUSH ACC  (PCH)
    a.emit(0x32)                                          # RETI -> 0100
    a.label('done')
    a.emit(0x22)                                          # RET
    return a

HOOKS = []  # (address, expected_original_bytes, label, opcode(LCALL=0x12), description)

def build(stock):
    img = bytearray(stock)
    assert len(img) == 0xD800
    a = program()
    code = a.build()
    assert all(x == 0xFF for x in img[BASE:BASE + len(code)]), 'target area not free'
    assert BASE + len(code) < 0xD700
    img[BASE:BASE + len(code)] = code
    L = a.labels
    def hook(addr, orig, label):
        assert bytes(img[addr:addr + 3]) == bytes(orig), hex(addr)
        img[addr:addr + 3] = bytes([0x12, L[label] >> 8, L[label] & 255])
    hook(0x2249, [0x12, 0x07, 0xC4], 'kick')       # main loop: LCALL 07C4
    hook(0x35E6, [0x12, 0x39, 0xDA], 'arm')        # bus reset handling: LCALL 39DA
    hook(0x4034, [0x90, 0x00, 0x02], 'disarm')     # SET_ADDRESS: MOV DPTR,#0002
    hook(0x330A, [0x75, 0xD0, 0x10], 'tick')       # timer-0 ISR: MOV PSW,#10h
    # exp1 sleep-gate patch (JZ -> SJMP at 4C79)
    assert img[0x4C79:0x4C7B] == bytes([0x60, 0x66])
    img[0x4C79] = 0x80
    # checksum: 16-bit sum of 0400..D7FF with the two checksum slots read as FF (matches stock/exp1 convention)
    img[0x7FFE] = img[0x7FFF] = 0xFF
    s = sum(img[0x400:0xD800]) & 0xFFFF
    img[0x7FFE], img[0x7FFF] = s >> 8, s & 255
    return bytes(img), a, s

if __name__ == '__main__':
    stock = open(sys.argv[1], 'rb').read()
    out, a, s = build(stock)
    open(sys.argv[2], 'wb').write(out)
    diffs = [(hex(i), stock[i], out[i]) for i in range(len(stock)) if stock[i] != out[i]]
    manifest = {
        'stock_sha256': hashlib.sha256(stock).hexdigest(),
        'exp2_sha256': hashlib.sha256(out).hexdigest(),
        'checksum_stored': '%04X' % s,
        'new_code': {'base': hex(BASE), 'bytes': len(a.build()), 'labels': {k: hex(v) for k, v in a.labels.items()}},
        'changed_bytes_outside_new_code': [d for d in diffs if not (BASE <= int(d[0], 16) < BASE + len(a.build()))],
    }
    print(json.dumps(manifest, indent=2))
