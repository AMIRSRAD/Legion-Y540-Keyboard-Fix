from pathlib import Path
import hashlib,json
p=next(Path('work/fw44-board-docs').glob('Lenovo*.tvw'))
b=p.read_bytes()
tokens=['IT8176FN-56A-BX_QFN48_6X6','IT8226E-128-BX_LQFP128_14X14','USB20_N9_AGKB','USB20_P9_AGKB','AG_WRST#','AGKB_PWR_EN#','AGKB_PWR_OCB','USB20_N9','USB20_P9']
rows=[]
for t in tokens:
    x=t.encode(); start=0; hits=[]
    while (i:=b.find(x,start))>=0:
        hits.append({'offset':i,'hex':hex(i)})
        start=i+len(x)
    rows.append({'token':t,'occurrences':hits})
out=Path('outputs/firmware44-analysis/chip-docs');out.mkdir(parents=True,exist_ok=True)
(out/'local-board-evidence.json').write_text(json.dumps({'file':str(p.resolve()),'size':len(b),'sha256':hashlib.sha256(b).hexdigest(),'evidence':rows,'limitation':'Strings only. Proprietary TVW geometry/component/net association not decoded. No physical board revision confirmed.'},indent=2))
print(json.dumps(rows,indent=2))
