from pathlib import Path
import sys,re,struct,json,hashlib
sys.path.insert(0,str(Path('work/uefi-parser-deps').resolve()))
from uefi_firmware.uefi import FirmwareVolume
path=Path('work/bios-reset-45/payload/BIOS.fd');b=path.read_bytes()
out=Path('work/bios-reset-45/volumes');out.mkdir(exist_ok=True)
records=[]; end=0
for m in re.finditer(b'_FVH',b):
 p=m.start()-40
 if p<0 or p<end:continue
 length=struct.unpack_from('<Q',b,p+32)[0]; hlen=struct.unpack_from('<H',b,p+48)[0]
 if not(56<=hlen<4096 and hlen%2==0 and 0<length<=len(b)-p):continue
 if sum(struct.unpack('<'+'H'*(hlen//2),b[p:p+hlen]))&65535:continue
 rec={'offset':hex(p),'length':length}
 try:
  fv=FirmwareVolume(b[p:p+length]); rec['processed']=fv.process()
  fv.dump(str(out/hex(p)))
 except Exception as e:rec['error']=repr(e)
 records.append(rec);end=p+length
Path('work/bios-reset-45/volume-index.json').write_text(json.dumps(records,indent=2))
print(records)
