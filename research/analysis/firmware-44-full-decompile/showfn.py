import sys,re
src=open(sys.argv[1],encoding='utf8',errors='replace').read()
parts=re.split(r'(?m)^// ===== ',src)
want=[w.lower() for w in sys.argv[2:]]
for p in parts:
    head=p.split('\n',1)[0]
    m=re.search(r'_([0-9a-fA-F]{4})\b',head)
    if m and m.group(1).lower() in want:
        print('// =====',p[:4000])
