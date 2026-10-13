"""Queue a static REA tool request using the connected server's tool schemas.
Run: python tools/queue_request.py 020-xrefs xrefs '{"address":"0x1234"}'
Use unique labels; complete responses land in evidence/rea.
"""
from pathlib import Path
import argparse,json,re
root=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('label');p.add_argument('tool');p.add_argument('arguments');a=p.parse_args()
allowed={'open_binary','close_binary','binary_session','search_procedures','search_strings','list_procedures','procedure_pseudo_code','procedure_assembly','procedure_callers','procedure_callees','procedure_info','resolve_containing_procedure','procedure_references','analyze_function','xrefs','binary_overview','read_bytes','address_to_file_offset','get_evidence_bundle','export_evidence_bundle'}
if a.tool not in allowed:raise SystemExit('Tool outside static research scope')
if not re.fullmatch(r'[0-9]{3}-[a-z0-9-]+',a.label):raise SystemExit('Use label 020-description')
args=json.loads(a.arguments)
if not isinstance(args,dict):raise SystemExit('Arguments must be an object')
q=root/'work'/'queue';q.mkdir(parents=True,exist_ok=True);dest=q/(a.label+'.json')
if dest.exists() or (root/'evidence'/'rea'/dest.name).exists():raise SystemExit('Label already used; choose a new one')
tmp=dest.with_suffix('.tmp');tmp.write_text(json.dumps({'name':a.tool,'arguments':args},indent=2),encoding='utf8');tmp.rename(dest);print(dest)

