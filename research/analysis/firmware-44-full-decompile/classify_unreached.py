"""Pick extra code seeds for regions Ghidra did not reach (indirect calls, jump tables).
Writes seeds.txt (hex addr + reason) and regions.tsv (every unreached region with its verdict).
Usage: classify_unreached.py full/coverage-log.txt"""
import re, sys
d = open('app44-full64k.bin', 'rb').read()

# 8051 instruction lengths
L = [1] * 256
for op in range(256):
    if op & 0x1F in (0x01, 0x11): L[op] = 2                       # AJMP/ACALL
for op in (0x02, 0x12, 0x10, 0x20, 0x30, 0x43, 0x53, 0x63, 0x75, 0x85, 0x90, 0xB4, 0xB5, 0xB6, 0xB7,
           0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xD5):
    L[op] = 3
for op in (0x05, 0x15, 0x24, 0x25, 0x34, 0x35, 0x40, 0x42, 0x44, 0x45, 0x50, 0x52, 0x54, 0x55, 0x60, 0x62,
           0x64, 0x65, 0x70, 0x72, 0x74, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80,
           0x82, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x92, 0x94, 0x95, 0xA0, 0xA2,
           0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB2, 0xC0, 0xC2, 0xC5, 0xD0,
           0xD2, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE5, 0xF5):
    L[op] = 2

# data evidence: addresses loaded into DPTR right before MOVC in non-heuristic code
dptr_data = set()
cur = None; last_dptr = None
for line in open('full/full-listing.asm'):
    m = re.match(r'; ===== (\S+)', line)
    if m: cur = m.group(1); last_dptr = None; continue
    m = re.match(r'CODE:([0-9a-f]{4})\s+(.*)', line)
    if not m or (cur or '').startswith('H_'): continue
    t = m.group(2)
    q = re.match(r'MOV DPTR,#0x([0-9a-f]+)', t)
    if q: last_dptr = int(q.group(1), 16); continue
    if t.startswith('MOVC') and last_dptr is not None: dptr_data.add(last_dptr)
    if t.startswith(('LCALL', 'RET', 'LJMP', 'SJMP', 'MOV DPL', 'MOV DPH', 'MOV 0x82', 'MOV 0x83', 'XCH A,DP', 'INC DPTR')): last_dptr = None


def descriptor_like(blk):
    for i in range(min(len(blk), 64)):
        if blk[i:i + 2] in (b'\x12\x01', b'\x09\x02', b'\x09\x04', b'\x09\x21') and len(blk) > i + 8:
            return True
        if (i + 4 < len(blk) and blk[i + 1] == 0x03 and blk[i] >= 4 and blk[i] % 2 == 0
                and blk[i + 3] == 0 and 0x20 <= blk[i + 2] < 0x7F):
            return True
    return False


def decode_ok(start, end):
    """Linear decode start..end; plausible code if it ends on a boundary with a flow-ending op."""
    a, enders, zeros, n = start, 0, 0, 0
    while a <= end:
        op = d[a]
        if op == 0xA5: return False, 'invalid opcode A5'
        if op == 0x00:
            zeros += 1
            if zeros > 3: return False, 'NOP run'
        else: zeros = 0
        if op in (0x22, 0x32, 0x02, 0x80) or (op & 0x1F) == 0x01: enders += 1
        a += L[op]; n += 1
    if n < 3: return False, 'too short'
    if not enders and not (a == end + 1 and ins_start(a)): return False, 'no RET/JMP'
    if not enders: return True, 'falls through into code at %04X (%d instructions)' % (a, n)
    return True, 'decodes as %d instructions' % n


starts = set()
for line in open('full/full-listing.asm'):
    m = re.match(r'CODE:([0-9a-f]{4})', line)
    if m: starts.add(int(m.group(1), 16))
def ins_start(a): return a in starts

regions = []
for line in open(sys.argv[1]):
    m = re.match(r'unreached (\w+)-(\w+)', line)
    if m: regions.append((int(m.group(1), 16), int(m.group(2), 16)))
seeds = []
with open('regions.tsv', 'w') as out:
    out.write('start\tend\tbytes\tverdict\twhy\tfirst bytes\n')
    for s, e in regions:
        blk = d[s:e + 1]
        verdict, why = 'data', ''
        if re.search(rb'(\x05[\x01\x0c\x07\x08]|\x06.\xff)\x09.\xa1', blk[:16]):
            why = 'HID report descriptor pattern'
        elif all(blk[i] == 0x02 for i in range(0, min(len(blk), 12), 3)) and len(blk) >= 6:
            verdict, why = 'ljmp-table', 'LJMP jump table'
            for i in range(0, len(blk) - 2, 3):
                if blk[i] != 0x02: break
                t = blk[i + 1] << 8 | blk[i + 2]
                seeds.append((s + i, 'ljmp-table entry')); seeds.append((t, 'ljmp-table target from %04X' % (s + i)))
        elif any(s <= x <= e for x in dptr_data):
            why = 'MOVC table referenced by code (DPTR=%04X)' % min(x for x in dptr_data if s <= x <= e)
        elif descriptor_like(blk):
            why = 'USB descriptor/string pattern'
        elif 0xD800 <= s < 0xE000:
            why = 'bootloader data area D800-DFFF'
        else:
            ok, why = decode_ok(s, e)
            if ok:
                verdict = 'code?'
                seeds.append((s, 'heuristic END=%04X: %s' % (e, why)))
        out.write('%04X\t%04X\t%d\t%s\t%s\t%s\n' % (s, e, e - s + 1, verdict, why, blk[:16].hex()))
with open('seeds.txt', 'w') as f:
    for a, why in seeds:
        f.write('%04X %s\n' % (a, why))
print(len(regions), 'regions;', len(seeds), 'seeds')
