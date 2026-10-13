from pathlib import Path
import json
root=Path('outputs/y540-research')
for name in ['050-checksum-validation','051-hidrequests-assembly']:
 e=json.loads((root/'evidence'/'rea'/(name+'.json')).read_text())['response']['result']['structuredContent'];v=e['normalized_result'];print(name,e['evidence_id']);
 if isinstance(v,str):
  (root/'evidence'/'decompiled'/(name+'.txt')).write_text(v,encoding='utf8')
  if name.startswith('050'):print(v[:13000])
  else:
   lines=v.splitlines();print('\n'.join(line for i,line in enumerate(lines) if 'memcpy' in line or 'HidD_' in line or '0x40' in line))
 else:print(str(v)[:15000])
