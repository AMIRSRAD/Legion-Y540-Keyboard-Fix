"""Export available REA pseudocode/assembly strings while retaining raw evidence."""
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1];out=root/'evidence'/'decompiled';out.mkdir(exist_ok=True)
count=0
for p in sorted((root/'evidence'/'rea').glob('*.json')):
 d=json.loads(p.read_text(encoding='utf-8-sig'))
 if d.get('request',{}).get('name') not in ('procedure_pseudo_code','procedure_assembly'):continue
 e=d['response'].get('result',{}).get('structuredContent',{})
 v=e.get('normalized_result')
 if not isinstance(v,str):continue
 ext='.asm' if d['request']['name']=='procedure_assembly' else '.c'
 # Normalize redundant CRs from provider text, without editing source evidence.
 text=v.replace('\r\r\n','\n').replace('\r\n','\n')
 (out/(p.stem+ext)).write_text(text,encoding='utf8');count+=1
print(count,'derived text views written')
