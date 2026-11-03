import sys,re
lo,hi=int(sys.argv[2],16),int(sys.argv[3],16)
for l in open(sys.argv[1]):
    m=re.match(r'CODE:([0-9a-f]{4})',l)
    if m and lo<=int(m.group(1),16)<=hi: print(l.rstrip())
    elif l.startswith('; =====') : pass
