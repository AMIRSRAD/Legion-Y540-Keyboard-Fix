from pathlib import Path
import re,struct,hashlib,json
base=Path(__file__).parent
out={}
for ver in ('35','36'):
 tables={}; ec=[]
 for p in (base/ver/'volumes').rglob('*'):
  if not p.is_file():continue
  b=p.read_bytes()
  for m in re.finditer(b'DSDT|SSDT',b):
   o=m.start()
   if o+36>len(b):continue
   l=struct.unpack_from('<I',b,o+4)[0]
   if not 36<=l<=1000000 or o+l>len(b) or sum(b[o:o+l])%256:continue
   tb=b[o:o+l]; sha=hashlib.sha256(tb).hexdigest()
   if sha in tables:continue
   dest=base/ver/'acpi'/f'{tb[:4].decode()}-{sha[:12]}.aml';dest.parent.mkdir(exist_ok=True);dest.write_bytes(tb)
   tables[sha]={'source':str(p),'offset':o,'length':l,'oem_table_id':tb[16:24].decode(errors='replace'),'file':str(dest),'sha256':sha}
  if p.name.startswith('section'):
   hits=[]
   for m in re.finditer(rb'[ -~]{5,}',b):
    if any(t in m.group().lower() for t in (b'8226',b'bhec',b'ecfw',b'ec version',b'ec firmware',b'agkb',b'ag_wr',b'agkb_pwr')):hits.append({'offset':m.start(),'text':m.group().decode()[:200]})
   if hits:ec.append({'file':str(p),'length':len(b),'sha256':hashlib.sha256(b).hexdigest(),'hits':hits[:40]})
 out[ver]={'tables':list(tables.values()),'ec_candidates':ec}
(base/'scan.json').write_text(json.dumps(out,indent=2));print(json.dumps({v:{'tables':len(o['tables']),'ec_candidates':len(o['ec_candidates'])} for v,o in out.items()}))
