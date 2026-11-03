"""Cross-reference the full listing: XDATA/MMIO reads+writes per function (DPTR tracked through
straight-line code), SFR writes of interest, interrupt/power/watchdog sites, call graph roots.
Usage: xref.py full/full-listing.asm full/functions.tsv OUTDIR"""
import re, sys, collections, os
lst, ftsv, out = sys.argv[1], sys.argv[2], sys.argv[3]
ins = []          # (addr, text, func)
func = None
for line in open(lst):
    m = re.match(r'; ===== (\S+)', line)
    if m: func = m.group(1); continue
    m = re.match(r'CODE:([0-9a-f]{4})\s+(.*)', line)
    if m: ins.append((int(m.group(1), 16), m.group(2).strip(), func))
entry_of = {}
for a, t, f in ins: entry_of.setdefault(f, a)
targets = set()
for a, t, f in ins:
    for x in re.findall(r'0x([0-9a-f]{3,4})\b', t):
        if re.match(r'(S?L?A?JMP|LCALL|ACALL|J\w+|CJNE|DJNZ|SJMP)', t): targets.add(int(x, 16))
xd = collections.defaultdict(lambda: {'R': set(), 'W': set()})
sfr = collections.defaultdict(set)
SFR = {'0x87': 'PCON', '0xa8': 'IE', '0xd8': 'WDCON?', '0x8e': 'CKCON', '0x89': 'TMOD', '0xb8': 'IP', '0xd0': 'PSW', '0x81': 'SP'}
BITS = {'0xaf': 'EA', '0xa9': 'ET0', '0xab': 'ET1', '0xa8': 'EX0', '0xaa': 'EX1', '0xac': 'ES', '0x8c': 'TR0', '0x8e': 'TR1'}
dptr = None
prev = None
for a, t, f in ins:
    if a in targets or (prev and prev[2] != f): dptr = None
    m = re.match(r'MOV DPTR,#0x([0-9a-f]+)', t)
    if m: dptr = int(m.group(1), 16)
    elif t == 'INC DPTR' and dptr is not None: dptr += 1
    elif t.startswith('MOVX A,@DPTR') and dptr is not None: xd[dptr]['R'].add(f)
    elif t.startswith('MOVX @DPTR,A') and dptr is not None: xd[dptr]['W'].add(f)
    elif re.match(r'(LCALL|ACALL|MOVC|MOV DPL|MOV DPH|MOV 0x8[23])', t): dptr = None
    m = re.match(r'(MOV|ORL|ANL|XRL) (0x[0-9a-f]{2}),', t)
    if m and m.group(2) in SFR: sfr['%s %s' % (SFR[m.group(2)], m.group(1))].add('%04X %s (%s)' % (a, t, f))
    m = re.match(r'(SETB|CLR) (0x[0-9a-f]{2})$', t)
    if m and m.group(2) in BITS: sfr['%s %s' % (m.group(1), BITS[m.group(2)])].add('%04X (%s)' % (a, f))
    if t.startswith('RETI'): sfr['RETI'].add('%04X (%s)' % (a, f))
    prev = (a, t, f)
os.makedirs(out, exist_ok=True)
with open(os.path.join(out, 'xdata-xref.tsv'), 'w') as w:
    w.write('addr\tkind\treaders\twriters\n')
    for k in sorted(xd):
        kind = 'RAM' if k < 0x1000 else ('MMIO' if k < 0x3000 else 'other')
        w.write('%04X\t%s\t%s\t%s\n' % (k, kind, ' '.join(sorted(xd[k]['R'])), ' '.join(sorted(xd[k]['W']))))
with open(os.path.join(out, 'sfr-sites.txt'), 'w') as w:
    for k in sorted(sfr):
        w.write('== %s (%d)\n' % (k, len(sfr[k])))
        for s in sorted(sfr[k]): w.write('   ' + s + '\n')
callers = {}
for line in open(ftsv).read().splitlines()[1:]:
    p = line.split('\t')
    callers[p[0]] = p[3] if len(p) > 3 else ''
roots = [k for k, v in callers.items() if not v]
with open(os.path.join(out, 'roots.txt'), 'w') as w:
    w.write('Functions with no static caller (vectors, indirect/table targets, heuristic):\n')
    for r in roots: w.write(r + '\n')
print(len(xd), 'xdata addrs;', sum(1 for k in xd if k >= 0x1000), 'MMIO;', len(roots), 'roots')
