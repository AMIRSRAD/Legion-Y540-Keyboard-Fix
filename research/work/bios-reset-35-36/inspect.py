from pathlib import Path
import re,struct,json,hashlib
base=Path(__file__).parent
out={}
for ver in ('35','36'):
 p=base/ver/'BIOS.fd'; b=p.read_bytes()
 u16=lambda o:struct.unpack_from('<H',b,o)[0]
 u32=lambda o:struct.unpack_from('<I',b,o)[0]
 pe=u32(0x3c); n=u16(pe+6); sec=pe+24+u16(pe+20)
 sections=[]
 for k in range(n):
  o=sec+k*40; sections.append({'name':b[o:o+8].rstrip(b'\0').decode(),'raw_offset':u32(o+20),'raw_size':u32(o+16)})
 fvs=[]
 for m in re.finditer(b'_FVH',b):
  o=m.start()-40
  if o<0:continue
  length=struct.unpack_from('<Q',b,o+32)[0]; hl=u16(o+48)
  if hl>=56 and hl<4096 and length>=hl and o+length<=len(b):
   fvs.append({'offset':o,'length':length,'header_length':hl,'checksum_ok':sum(struct.unpack('<'+'H'*(hl//2),b[o:o+hl]))%65536==0})
 strings=[]
 for m in re.finditer(rb'[ -~]{4,}',b):
  if any(x in m.group().lower() for x in [b'ecfw',b'8226',b'bhcn',b'bhec',b'ecrom',b'ec_ver',b'ec version',b'$ec',b'$_iflash']):strings.append({'offset':m.start(),'text':m.group().decode()[:256]})
 acpi=[]
 for sig in (b'DSDT',b'SSDT'):
  for m in re.finditer(sig,b):
   o=m.start()
   if o+36>len(b):continue
   l=u32(o+4)
   if 36<=l<=0x100000 and o+l<=len(b) and sum(b[o:o+l])%256==0:
    t=base/ver/f'{sig.decode()}-{o:x}.aml';t.write_bytes(b[o:o+l]);acpi.append({'offset':o,'length':l,'path':str(t)})
 out[ver]={'sha256':hashlib.sha256(b).hexdigest(),'size':len(b),'pe_offset':pe,'sections':sections,'firmware_volumes':fvs,'strings':strings,'uncompressed_acpi':acpi}
(base/'inventory.json').write_text(json.dumps(out,indent=2))
print(json.dumps(out,indent=2))
