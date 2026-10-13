from pathlib import Path
import struct,hashlib,re,json,math,collections
root=Path(r'C:\Users\a.saberi\Desktop\Y540-keyboard-firmware-00000044')
results={}
for p in root.rglob('*'):
 if p.suffix.lower() not in ('.exe','.bin'): continue
 b=p.read_bytes(); r={'size':len(b),'sha256':hashlib.sha256(b).hexdigest(),'header_hex':b[:64].hex()}
 ss=[(m.start(),m.group().decode('ascii')) for m in re.finditer(rb'[\x20-\x7e]{6,}',b)]
 if b[:2]==b'MZ':
  pe=struct.unpack_from('<I',b,60)[0];machine,n=struct.unpack_from('<HH',b,pe+4); opt=struct.unpack_from('<H',b,pe+20)[0]; tab=pe+24+opt
  sections=[]; end=0
  for i in range(n):
   o=tab+40*i; name=b[o:o+8].rstrip(b'\0').decode(errors='replace'); vs,va,sz,off=struct.unpack_from('<IIII',b,o+8);end=max(end,off+sz);sections.append({'name':name,'virtual_size':vs,'raw_size':sz,'offset':off})
  r.update(machine=hex(machine),sections=sections,overlay_size=len(b)-end)
  r['relevant_strings']=[{'offset':hex(o),'text':s} for o,s in ss if re.search(r'(?i)hid|firmware|flash|checksum|SHFU|\.bin|VID_|PID_|boot|8171|version|ite tech',s)][:150]
 else:
  c=collections.Counter(b);r['entropy']=-sum(v/len(b)*math.log2(v/len(b)) for v in c.values());r['strings']=[{'offset':hex(o),'text':s} for o,s in ss][:80];r['version_bytes_at_3100']=b[0x3100:0x3120].hex();r['sum16_0400_d800_exclusive']=hex(sum(b[0x400:0xd800])&65535);r['zero_bytes']=c[0];r['ff_bytes']=c[255]
 results[str(p.relative_to(root))]=r
out=Path('outputs/Y540-analysis/file-facts.json');out.write_text(json.dumps(results,indent=2))
print(json.dumps(results,indent=2)[:18000])
