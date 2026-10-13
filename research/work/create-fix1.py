from pathlib import Path
import shutil,json,hashlib,subprocess
base=Path('outputs/y540-research');dest=Path('outputs/fix1')
if dest.exists():raise SystemExit('fix1 already exists; inspect before replacing')
shutil.copytree(base,dest,ignore=shutil.ignore_patterns('.git','build','dist','work','__pycache__'))
(dest/'work').mkdir();(dest/'evidence'/'case-inputs').mkdir()
case=Path(r'C:/Users/a.saberi/Desktop/KeyboardFirmware-Issue')
for p in case.iterdir():
 if p.is_file() and p.suffix.lower() in ('.md','.json','.ps1'):shutil.copy2(p,dest/'evidence'/'case-inputs'/p.name)
receipt={'baseline_git_commit':subprocess.check_output(['git','-C',str(base),'rev-parse','HEAD'],text=True).strip(),'files':[]}
for p in sorted((base/'src').rglob('*')):
 if p.is_file():receipt['files'].append({'path':p.relative_to(base).as_posix(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
(dest/'evidence'/'baseline-preservation.json').write_text(json.dumps(receipt,indent=2))
print('Created separate fix1; baseline source preserved.')
