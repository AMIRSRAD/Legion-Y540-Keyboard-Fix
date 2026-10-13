# OFFLINE RECOVERY PROTOTYPE: corrects exp2 CPU/concurrency bugs and uses the verified C4 terminal path.
# The original undocumented detach/software jump is removed. This does not
# establish the physical reset scope or validate the original timeout triggers.
# Do not deploy this as a repair. No flashable image is shipped by this review.
"""In-memory exp2 recovery candidate. Retains the original timeout triggers for
controlled model comparison, fixes atomic updates and scratch preservation, and
replaces the pseudo-restart with the observed bootloader C4 reset-request path.
It is NOT a deployable firmware release. The caller must supply exact stock and
upper-dump bytes; no command-line image output is implemented.
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
    a.emit(0xC0, 0xA8, 0xC2, 0xAF)  # REVIEW: preserve IE; exclude timer while changing shared words
    a.emit(0xC0, 0xE0, 0xC0, 0x82, 0xC0, 0x83)          # PUSH ACC, DPL, DPH
    a.mov_dptr(VAR_MAIN); a.emit(0xE4, 0xF0, 0xA3, 0xF0)  # CLR A; MOVX @DPTR,A; INC DPTR; MOVX @DPTR,A
    a.emit(0xD0, 0x83, 0xD0, 0x82, 0xD0, 0xE0, 0xD0, 0xA8)           # POP DPH, DPL, ACC
    a.a16(0x02, 0x07C4)                                   # LJMP 07C4 (its RET returns to 224C)
    # --- arm: replaces LCALL 39DA at 35E6 (bus reset handling); keeps R7/R6.. untouched ---
    a.label('arm')
    a.emit(0xC0, 0xA8, 0xC2, 0xAF)  # REVIEW: preserve IE; exclude timer while changing shared words
    a.emit(0xC0, 0xE0, 0xC0, 0x82, 0xC0, 0x83)
    a.mov_dptr(VAR_ARM); a.emit(0x74, 0x01, 0xF0)         # MOV A,#1; MOVX @DPTR,A
    a.emit(0xA3, 0xE4, 0xF0, 0xA3, 0xF0)                  # INC DPTR; CLR A; MOVX; INC DPTR; MOVX  (enum ticks = 0)
    a.emit(0xD0, 0x83, 0xD0, 0x82, 0xD0, 0xE0, 0xD0, 0xA8)
    a.a16(0x02, 0x39DA)                                   # LJMP 39DA
    # --- disarm: replaces 'MOV DPTR,#0002' at 4034; A is dead there ---
    a.label('disarm')
    a.emit(0xC0, 0xA8, 0xC2, 0xAF)  # REVIEW: atomic disarm
    a.mov_dptr(VAR_ARM); a.emit(0xE4, 0xF0)               # CLR A; MOVX @DPTR,A
    a.emit(0xD0, 0xA8)  # REVIEW: restore prior interrupt enables
    a.mov_dptr(0x0002)                                    # the replaced instruction
    a.emit(0x22)                                          # RET
    # --- tick: replaces MOV PSW,#10 at 330A inside the timer-0 ISR ---
    a.label('tick')
    a.emit(0x75, 0xD0, 0x10)                              # MOV PSW,#10h (replaced instruction)
    a.emit(0xC0, 0x12)  # REVIEW: save bank-2 R2 used as scratch
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
    a.emit(0xC2, 0xAF)              # Exclude interrupt nesting during terminal reset request.
    a.emit(0x75, 0xD0, 0x00)        # Select bank 0 for the bootloader's own delay routine.
    a.a16(0x02, 0xF455)             # Tail-enter the byte-verified C4 terminal reset path.
    a.label('done')
    a.emit(0xD0, 0x12)  # REVIEW: restore bank-2 R2
    a.emit(0x22)                                          # RET
    return a

HOOKS = []  # (address, expected_original_bytes, label, opcode(LCALL=0x12), description)

def _build(stock):
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

STOCK_SHA = '3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359'
UPPER_SHA = '6160ed916d5356c631a5e7939a55d3dae0b863199e0f33ba7e6680fe6f684d2a'

def build(stock, upper_flash):
    assert hashlib.sha256(stock).hexdigest() == STOCK_SHA, 'Wrong stock image'
    assert len(upper_flash) == 0x2800 and hashlib.sha256(upper_flash).hexdigest() == UPPER_SHA, 'Wrong bootloader dump'
    # This offline qualification does NOT substitute for a fresh same-device
    # read of these bytes immediately before any future programming operation.
    assert upper_flash[0xF455-0xD800:0xF478-0xD800] == bytes.fromhex(
        '7f057e0012f12c902f507408f07fe87e0312f12c901058e04440f0538e3f75d80280fe')
    return _build(stock)

if __name__ == '__main__':
    raise SystemExit('Offline recovery prototype only; no firmware image is emitted. Run test_candidate.py STOCK_BIN UPPER_DUMP. Triggers, scratch RAM, reset scope and clock behavior remain unverified on hardware.')
