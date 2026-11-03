"""Find polling/busy-wait loops (backward branches) and which ISR/main paths reach them."""
import re, collections
ins=[]; func=None; fa={}
for l in open('full/full-listing.asm'):
    m=re.match(r'; ===== (\S+)',l)
    if m: func=m.group(1); continue
    m=re.match(r'CODE:([0-9a-f]{4})\s+(.*)',l)
    if m:
        a=int(m.group(1),16); ins.append((a,m.group(2).strip(),func)); fa[a]=func
idx={a:i for i,(a,_,_) in enumerate(ins)}
calls=collections.defaultdict(set); entry={}
for line in open('full/functions.tsv').read().splitlines()[1:]:
    p=line.split('\t'); e=int(p[0].split(':')[1],16)
    calls[e]=set(int(x.split(':')[1],16) for x in (p[4].split() if len(p)>4 else []))
fentry={}
for a,t,f in ins: fentry.setdefault(f,a)
def reach(root):
    seen=set([root]); st=[root]
    while st:
        x=st.pop()
        for y in calls.get(x,()):
            if y not in seen: seen.add(y); st.append(y)
    return seen
R={'USB-ISR 4F75':reach(0x4f75),'T0-ISR 3300':reach(0x3300),'INT1-ISR 3400':reach(0x3400),'main 2200':reach(0x2200)}
out=[]
for i,(a,t,f) in enumerate(ins):
    m=re.match(r'(J\w+|CJNE|DJNZ|SJMP)\b.*0x([0-9a-f]{3,4})$',t)
    if not m: continue
    tgt=int(m.group(2),16)
    if not (a-40 <= tgt <= a): continue
    body=[x for x in ins[idx.get(tgt,i):i+1]]
    mm=[]
    dptr=None
    for b,tt,_ in body:
        q=re.match(r'MOV DPTR,#0x([0-9a-f]+)',tt)
        if q: dptr=int(q.group(1),16)
        if tt.startswith('MOVX A,@DPTR') and dptr is not None: mm.append('%04X'%dptr)
    polls_hw=[x for x in mm if int(x,16)>=0x1000]
    sfrpoll=any(re.search(r'JN?B 0x(8f|8d|99|98)',tt) for _,tt,_ in body)
    if not polls_hw and not sfrpoll and m.group(1)!='SJMP' : continue
    if not polls_hw and not sfrpoll: continue
    e=fentry.get(f)
    who=[k for k,s in R.items() if e in s]
    out.append('%04X  %-40s loop %04X-%04X polls %s %s  reached-from: %s'%(a,t,tgt,a,' '.join(polls_hw) or '', 'TF/RI' if sfrpoll else '', ', '.join(who) or '-'))
open('full/poll-loops.txt','w').write('\n'.join(out)+'\n')
print(len(out)); print('\n'.join(out))
