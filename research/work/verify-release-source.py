from pathlib import Path
import hashlib,json,zipfile
root=Path('outputs/y540-research');rebuilt=Path('work/rebuild-check/y540-research')
inputs=[p.relative_to(root) for folder in ['src','tests'] for p in (root/folder).rglob('*') if p.is_file()]+[Path('build.ps1'),Path('CMakeLists.txt'),Path('samples/44.bin'),Path('samples/SHFU.ini')]
for rel in inputs:
 if (root/rel).read_bytes()!=(rebuilt/rel).read_bytes():raise SystemExit('Rebuild input differs: '+str(rel))
h=hashlib.sha256()
for rel in sorted(inputs):h.update(rel.as_posix().encode());h.update(b'\0');h.update((root/rel).read_bytes())
p=root/'evidence'/'source-rebuild-verification.json';d=json.loads(p.read_text(encoding='utf-8-sig'));d['compilation_inputs_sha256']=h.hexdigest();d['release_compilation_inputs_equal_independently_rebuilt_inputs']=True;p.write_text(json.dumps(d,indent=2))
with zipfile.ZipFile('outputs/y540-research-source.zip') as z:
 for rel in inputs:
  if z.read('y540-research/'+rel.as_posix())!=(root/rel).read_bytes():raise SystemExit('Archive source differs: '+str(rel))
 print('Release archive compilation inputs exactly match independently rebuilt source.')
print(h.hexdigest())
