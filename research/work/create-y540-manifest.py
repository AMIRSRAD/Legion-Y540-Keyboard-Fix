from pathlib import Path
import json,hashlib
root=Path('outputs/y540-research');files=[]
for p in sorted((root/'samples').iterdir()):
 if p.name=='manifest.json':continue
 b=p.read_bytes();files.append({'name':p.name,'size':len(b),'sha256':hashlib.sha256(b).hexdigest()})
(root/'samples'/'manifest.json').write_text(json.dumps({'source_directory':r'C:\Users\a.saberi\Desktop\Y540-keyboard-firmware-00000044','captured_date':'2026-10-12','files':files},indent=2),encoding='utf8')
