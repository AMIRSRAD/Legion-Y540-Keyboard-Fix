"""Verify the preserved samples against their recorded SHA-256 identities."""
from pathlib import Path
import hashlib,json,sys
root=Path(__file__).resolve().parents[1]
manifest=json.loads((root/'samples'/'manifest.json').read_text())
errors=[]
for item in manifest['files']:
 p=root/'samples'/item['name'];data=p.read_bytes()
 ok=len(data)==item['size'] and hashlib.sha256(data).hexdigest()==item['sha256']
 print(('OK ' if ok else 'MISMATCH ')+item['name'])
 if not ok:errors.append(item['name'])
sys.exit(bool(errors))
