import json
from pathlib import Path
root=Path('outputs/y540-research')
for p in sorted((root/'evidence'/'rea').glob('04*.json')):
 e=json.loads(p.read_text())['response']['result']['structuredContent'];v=e.get('normalized_result');print(p.name,e.get('evidence_id'));print(v)
 if isinstance(v,str):(root/'evidence'/'decompiled'/(p.stem+'.c')).write_text(v,encoding='utf8')
