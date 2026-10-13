from pathlib import Path
import json
root=Path('outputs/y540-research');rows=[]
for p in sorted((root/'evidence'/'rea').glob('*.json')):
 d=json.loads(p.read_text())
 if 'request' not in d:continue
 e=d['response'].get('result',{}).get('structuredContent',{})
 rows.append((p.name,e.get('evidence_id')))
print('\n'.join(n+' '+str(e) for n,e in rows))
