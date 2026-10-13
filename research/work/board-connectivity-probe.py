import sys,json,dataclasses,struct
from pathlib import Path
sys.path.insert(0,'work/tvw-parser-source')
from src import tvw_compal as t
p=next(Path('work/fw44-board-docs').glob('Lenovo*.tvw'));b=p.read_bytes()
def netscan(data):
 for i in range(0x1170000,0x1190000):
  a,c=struct.unpack_from('<II',data,i)
  if a!=c or not 100<a<20000:continue
  pos=i+8;names=[]
  for _ in range(a):
   n=data[pos];txt=data[pos+1:pos+1+n]
   if n>200 or any(v<32 or v>126 for v in txt):break
   names.append(txt.decode());pos+=1+n
  if len(names)==a:
   print('NETS',hex(i),a,hex(pos));return names
 raise ValueError('no table')
t._MASTER_POOL_START_HINT=0x124087f
t._R3_SEARCH_START=0x1185000;t._R3_SEARCH_END=0x124087f
t._scan_net_names=netscan
t._TEST_POINT_FP_IDS=frozenset()
m=t.parse(p,b)
print('COUNTS',len(m.components),len(m.signals),m.warnings)
wanted=['AG_WRST#','AGKB_PWR_EN#','AGKB_PWR_OCB','USB20_N9_AGKB','USB20_P9_AGKB','AGKB_INT','AVCC3.3V_AG']
result={'components':{k:dataclasses.asdict(v) for k,v in m.components.items()},'signals':m.signals,'warnings':m.warnings}
Path('work/board-connectivity-model.json').write_text(json.dumps(result,indent=2))
for name in wanted: print(name,[(ref,pin,m.components[ref].device) for ref,pin in m.signals.get(name,[])])
print('U22',[(net,pin) for net,pins in m.signals.items() for ref,pin in pins if ref=='U22'])
