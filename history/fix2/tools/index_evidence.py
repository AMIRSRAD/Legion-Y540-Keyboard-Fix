"""Index complete saved MCP responses without replacing their source records."""
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1];rows=[]
for p in sorted((root/'evidence'/'rea').glob('*.json')):
 d=json.loads(p.read_text(encoding='utf-8-sig'))
 if 'request' not in d:continue
 r=d['response'];v=r.get('result',{});e=v.get('structuredContent')
 if e is None:
  for block in v.get('content',[]):
   if block.get('type')=='text':
    try:e=json.loads(block['text']);break
    except ValueError:pass
 rows.append({'file':str(p.relative_to(root)).replace('\\','/'),'tool':d['request']['name'],'arguments':d['request'].get('arguments',{}),'evidence_id':e.get('evidence_id') if isinstance(e,dict) else None,'error':r.get('error') or v.get('isError',False)})
(root/'evidence'/'index.json').write_text(json.dumps(rows,indent=2),encoding='utf8');print(str(len(rows))+' records indexed')
