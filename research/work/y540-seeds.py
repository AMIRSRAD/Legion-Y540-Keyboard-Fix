from pathlib import Path
import struct,json
root=Path('outputs/y540-research');b=(root/'samples'/'ITESHFU.exe').read_bytes();pe=struct.unpack_from('<I',b,60)[0];opt=pe+24;image=struct.unpack_from('<Q',b,opt+24)[0];n=struct.unpack_from('<H',b,pe+6)[0];table=opt+struct.unpack_from('<H',b,pe+20)[0]
rows=[]
for label,f in [('setfeature-error',0x2def64),('getfeature-error',0x2def7e),('checksum-error',0x2df19b),('enter-flash',0x2df1c7)]:
 for i in range(n):
  o=table+i*40;vs,va,size,off=struct.unpack_from('<IIII',b,o+8)
  if off<=f<off+size:
   address=hex(image+va+f-off);rows.append({'label':label,'file_offset':hex(f),'mapped_va':address});break
(root/'evidence'/'string-seeds.json').write_text(json.dumps(rows,indent=2))
for i,row in enumerate(rows,20):
 (root/'work'/'queue'/f'{i:03d}-xref-{row["label"]}.json').write_text(json.dumps({'name':'xrefs','arguments':{'address':row['mapped_va']}}))
print(json.dumps(rows,indent=2))
