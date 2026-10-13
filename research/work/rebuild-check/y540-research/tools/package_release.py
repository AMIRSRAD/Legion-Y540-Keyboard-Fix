"""Package source/test fixtures and a portable native build; no vendor EXEs bundled."""
from pathlib import Path
import hashlib,json,re,shutil,subprocess,zipfile
root=Path(__file__).resolve().parents[1]
outputs=root.parent
exe=root/'build'/'Y540Updater.exe'
if not exe.exists():raise SystemExit('Run build.ps1 first')
imports=re.findall(r'DLL Name:\s*(\S+)',subprocess.check_output(['objdump','-p',str(exe)],text=True))
receipt={'version':'0.2.0','compiler':'MinGW-w64 GCC 13.2.0','architecture':'Windows x64','exe_sha256':hashlib.sha256(exe.read_bytes()).hexdigest(),'exe_bytes':exe.stat().st_size,'imported_dlls':imports,'tests':{'core':'passed','transport_memory_backend':'passed','protocol_emulator':'passed','app_sample_verify':'passed','hidden_gui_initialization':'passed','cmake_ctest':'5/5 passed'},'hardware_validation':'not performed','original_executable_execution':'not performed','source_is_vendor_original':False}
(root/'evidence'/'build-verification.json').write_text(json.dumps(receipt,indent=2),encoding='utf8')
portable=root/'dist'/'Y540Updater-0.2.0';portable.mkdir(parents=True,exist_ok=True)
shutil.copy2(exe,portable/'Y540Updater.exe')
for n in ['44.bin','SHFU.ini']:shutil.copy2(root/'samples'/n,portable/n)
(portable/'README.txt').write_text('Y540Updater 0.2.0 - independently reconstructed native source build\n\nDouble-click Y540Updater.exe to open the GUI. Firmware/INI are beside the EXE.\nValidate firmware and inspect the plan before any deliberate update.\nUpdate keyboard / --update performs hardware writes.\nHardware behavior has NOT been validated on a keyboard. No hardware was flashed during development.\n\nSource archive: y540-research-source.zip\nRebuild: extract source archive, open PowerShell in y540-research, run .\\build.ps1\nRequires Windows MinGW-w64 GCC and windres. No vendor compiler or .NET runtime.\n\nThis is not the original vendor EXE or firmware source. The supplied 44.bin remains a prebuilt firmware input.\n',encoding='utf8')
source=outputs/'y540-research-source.zip'
manifest=json.loads((root/'samples'/'manifest.json').read_text(encoding='utf-8-sig'))
manifest['files']=[r for r in manifest['files'] if r['name'] in ['44.bin','SHFU.ini']]
manifest['scope']='Source-build test fixtures only; original installer/updater remain in the full local research project.'
with zipfile.ZipFile(source,'w',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
 for p in sorted(root.rglob('*')):
  if not p.is_file():continue
  rel=p.relative_to(root)
  if any(v in {'.git','work','build','dist','__pycache__'} for v in rel.parts):continue
  if rel.parts[0]=='samples' and p.name not in {'44.bin','SHFU.ini','manifest.json'}:continue
  if p.suffix in {'.pyc','.o','.exe'}:continue
  name='y540-research/'+rel.as_posix()
  if rel.as_posix()=='samples/manifest.json':z.writestr(name,json.dumps(manifest,indent=2))
  else:z.write(p,name)
portable_zip=outputs/'Y540Updater-0.2.0-portable.zip'
with zipfile.ZipFile(portable_zip,'w',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
 for p in sorted(portable.iterdir()):z.write(p,'Y540Updater-0.2.0/'+p.name)
release={'files':[{'name':p.name,'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in [source,portable_zip]],'exe':receipt}
(outputs/'y540-release-manifest.json').write_text(json.dumps(release,indent=2),encoding='utf8')
print(json.dumps(release,indent=2))
