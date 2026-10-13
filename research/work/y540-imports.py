from pathlib import Path
import struct,json,re
p=Path(r'C:/Users/a.saberi/Desktop/Y540-keyboard-firmware-00000044/extracted-IT/ITESHFU.exe');b=p.read_bytes();pe=struct.unpack_from('<I',b,60)[0];n=struct.unpack_from('<H',b,pe+6)[0];sz=struct.unpack_from('<H',b,pe+20)[0];oh=pe+24;tab=oh+sz
secs=[struct.unpack_from('<IIII',b,tab+i*40+8) for i in range(n)]
def off(r):
 for vs,va,s,o in secs:
  if va<=r<va+max(vs,s):return o+r-va
 return r
def z(o):return b[o:b.index(0,o)].decode(errors='replace')
rva=struct.unpack_from('<I',b,oh+120)[0];o=off(rva);imports={}
while any(b[o:o+20]):
 orig,_,_,name,iat=struct.unpack_from('<IIIII',b,o);dll=z(off(name)); t=off(orig or iat);names=[]
 while (a:=struct.unpack_from('<Q',b,t)[0]):
  if a>>63==0:names.append(z(off(a)+2))
  t+=8
 imports[dll]=names;o+=20
fw=Path(r'C:/Users/a.saberi/Desktop/Y540-keyboard-firmware-00000044/extracted-IT/44.bin').read_bytes()
r={'imports_relevant':{k:[v for v in vals if re.search('(?i)hid|setupdi|device|readfile|writefile|createfile',v)] for k,vals in imports.items() if re.search('(?i)hid|setup',k) or any(re.search('(?i)device|readfile|writefile|createfile',v) for v in vals)},'embedded_firmware_exact_offset':b.find(fw),'embedded_firmware_prefix_offsets':[hex(m.start()) for m in re.finditer(re.escape(fw[:64]),b)],'usb_device_descriptor':{'offset':'0x5307','vid':'048D','pid':'C100','bcdDevice':'0044'},'usb_strings':{'0x5349':'ITE Tech. Inc.','0x536b':'ITE Device(8910)','0x5391':'I8380689FA08'}}
Path('outputs/Y540-analysis/additional-facts.json').write_text(json.dumps(r,indent=2));print(json.dumps(r,indent=2))
