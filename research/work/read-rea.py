import json
from pathlib import Path
for p in sorted(Path('outputs/y540-research/evidence/rea').glob('0*.json')):
 if p.name.startswith('001'):continue
 d=json.loads(p.read_text());r=d['response']['result'];e=r.get('structuredContent')
 if e is None:e=json.loads(r['content'][0]['text'])
 print(p.name,'ID',e.get('evidence_id'),'RESULT',json.dumps(e.get('normalized_result',e))[:14000])
