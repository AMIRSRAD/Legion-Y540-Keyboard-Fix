# OFFLINE RECOVERY PROTOTYPE: corrects exp2 CPU/concurrency bugs and uses the verified C4 terminal path.
# The original undocumented detach/software jump is removed. This does not
# establish the physical reset scope or validate the original timeout triggers.
# Experimental exp3 release generator. Hardware behavior remains to be tested.
"""Build experimental firmware exp3 from exact stock and the supplied boot dump.
Uses the existing C4 terminal reset path. Main heartbeat covers the event-drain
loop; enumeration deadline survives repeated resets and ends at SET_CONFIGURATION.
This is an experiment, not a proven permanent repair. The updater must verify
bootloader dependency bytes on the actual device before erasing.
"""
import hashlib, json, sys

BASE = 0x8A00
VAR_MAIN = 0x0FF8      # word, big-endian: ticks since last main-loop kick
VAR_ARM = 0x0FFA       # byte: enumeration watch armed
VAR_ENUM = 0x0FFB      # word, big-endian: ticks since bus reset while armed
T1 = 8000
T2 = 6000

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
    # Heartbeat at the event-drain loop entry, not just outside that loop.
    # LJMP hook replaces MOV A,26h / JNZ 07CCh; both original branches replayed.
    a.label('kick')
    a.emit(0xC0, 0xA8, 0xC2, 0xAF, 0xC0, 0xE0, 0xC0, 0x82, 0xC0, 0x83)
    a.mov_dptr(VAR_MAIN); a.emit(0xE4, 0xF0, 0xA3, 0xF0)
    a.emit(0xD0, 0x83, 0xD0, 0x82, 0xD0, 0xE0, 0xD0, 0xA8)
    a.emit(0xE5, 0x26)                       # original MOV A,26h
    a.rel(0x60, 'kick_zero')
    a.a16(0x02, 0x07CC)                     # original JNZ destination
    a.label('kick_zero'); a.a16(0x02, 0x07C8) # original fall-through
    # --- arm: replaces LCALL 39DA at 35E6 (bus reset handling); keeps R7/R6.. untouched ---
    a.label('arm')
    a.emit(0xC0, 0xA8, 0xC2, 0xAF)  # REVIEW: preserve IE; exclude timer while changing shared words
    a.emit(0xC0, 0xE0, 0xC0, 0x82, 0xC0, 0x83)
    a.mov_dptr(VAR_ARM); a.emit(0xE0)
    a.rel(0x70, 'arm_done')  # Preserve the first deadline across repeated host retries.
    a.emit(0x74, 0x01, 0xF0)
    a.emit(0xA3, 0xE4, 0xF0, 0xA3, 0xF0)                  # INC DPTR; CLR A; MOVX; INC DPTR; MOVX  (enum ticks = 0)
    a.label('arm_done')
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
    a.emit(0xC0, 0xA8, 0xC2, 0xAF)  # Bound a short tick critical section.
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
    a.emit(0xD0, 0x12, 0xD0, 0xA8)  # Restore bank-2 R2 and prior IE
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
    assert img[0x07C4:0x07C8] == bytes.fromhex('e5267004')
    img[0x07C4:0x07C8] = bytes([0x02, L['kick'] >> 8, L['kick'] & 255, 0x00])
    hook(0x35E6, [0x12, 0x39, 0xDA], 'arm')        # bus reset handling: LCALL 39DA
    hook(0x4283, [0x90, 0x00, 0x02], 'disarm')     # SET_CONFIGURATION entry; SET_ADDRESS no longer disarms
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
    from pathlib import Path
    if len(sys.argv) != 4: raise SystemExit('Usage: build_exp3.py STOCK_BIN UPPER_DUMP OUTPUT_BIN')
    stock = Path(sys.argv[1]).read_bytes(); upper = Path(sys.argv[2]).read_bytes()
    image, assembler, checksum = build(stock, upper)
    destination = Path(sys.argv[3])
    with destination.open('xb') as stream: stream.write(image)
    manifest = {
        'experiment': 'exp3-c4-reset', 'image_sha256': hashlib.sha256(image).hexdigest(),
        'stock_sha256': STOCK_SHA, 'upper_dump_sha256': UPPER_SHA,
        'checksum': '%04X' % checksum, 'bytes': len(image),
        'inserted_code_bytes': len(assembler.build()),
        'labels': {k:hex(v) for k,v in assembler.labels.items()},
        'thresholds_timer_ticks_not_verified_ms': {'main':T1, 'enumeration':T2},
        'diffs': [{'offset':hex(i),'before':a,'after':b} for i,(a,b) in enumerate(zip(stock,image)) if a!=b],
        'hardware_validated': False,
        'limits': ['XRAM ownership not proven beyond bounded static scan',
                   'reset scope and timer rate not documented for exact chip',
                   'enumeration deadline can also expire while host intentionally inactive']
    }
    destination.with_suffix('.manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf8')
    print(json.dumps(manifest,indent=2))
