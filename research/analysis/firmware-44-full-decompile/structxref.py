"""Accesses through Keil generic-pointer helpers, grouped by the pointer variable the base came from
(MOV DPTR,#ptrvar ; MOVX ; MOV R3.. R2.. R1). Usage: structxref.py PTRVAR_HEX [OFFSET_HEX]"""
import re, sys
H = {'0x857a': 'RD8', '0x85b9': 'WR8', '0x8632': 'RD16', '0x866a': 'ADD16', '0x86d6': 'WR16', '0x8561': 'RD8+0', '0x85a7': 'WR8+0', '0x88b1': 'RD16?', '0x8881': 'WR16?'}
want = int(sys.argv[1], 16); woff = int(sys.argv[2], 16) if len(sys.argv) > 2 else None
ins = []; func = None
for l in open('full/full-listing.asm'):
    m = re.match(r'; ===== (\S+)', l)
    if m: func = m.group(1); continue
    m = re.match(r'CODE:([0-9a-f]{4})\s+(.*)', l)
    if m: ins.append((int(m.group(1), 16), m.group(2).strip(), func))
base = None; pend = None; dptr = None; aval = None
for a, t, f in ins:
    q = re.match(r'MOV DPTR,#0x([0-9a-f]+)', t)
    if q:
        dptr = int(q.group(1), 16)
        if dptr in (0xde8, 0xdeb, 0x449, 0x44e, 0x43, 0x424): pend = dptr
    if t == 'MOV R1,A' and pend is not None: base = pend; pend = None
    if re.match(r'(RET|LJMP|SJMP)', t): base = None
    if t == 'CLR A': aval = 0
    q = re.match(r'MOV A,#0x([0-9a-f]+)', t)
    if q: aval = int(q.group(1), 16)
    m = re.match(r'LCALL (0x8[58][0-9a-f]{2})$', t)
    if m and m.group(1) in H and base == want:
        kind = H[m.group(1)]
        off = 0 if kind.endswith('+0') else dptr
        if woff is None or off == woff:
            print('%-6s +%02X at %04X in %-16s %s' % (kind, off if off is not None else -1, a, f, ('A=%02X' % aval) if kind.startswith('WR') and aval is not None else ''))
    if m: aval = None
