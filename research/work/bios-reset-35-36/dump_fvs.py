from pathlib import Path
import sys,json,contextlib
base=Path(__file__).parent
sys.path.insert(0,str(base.parent/'uefi-parser-deps'))
from uefi_firmware.uefi import FirmwareVolume
inv=json.loads((base/'inventory.json').read_text())
for ver in ('35','36'):
 b=(base/ver/'BIOS.fd').read_bytes()
 with (base/ver/'parse.log').open('w') as log,contextlib.redirect_stdout(log),contextlib.redirect_stderr(log):
  for d in inv[ver]['firmware_volumes']:
   o=d['offset']; fv=FirmwareVolume(b[o:o+d['length']]); print('START',hex(o),fv.valid_header)
   try:
    print('PROCESSED',fv.process());fv.dump(str(base/ver/'volumes'/f'{o:x}'))
   except Exception as e: print(type(e).__name__,str(e))
 print(ver,'done')
