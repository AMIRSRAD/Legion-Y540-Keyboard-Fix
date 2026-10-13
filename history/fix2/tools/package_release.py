"""Package fix2 only. Never overwrites the preserved baseline releases."""
from pathlib import Path
import hashlib
import json
import re
import shutil
import subprocess
import zipfile

root = Path(__file__).resolve().parents[1]
if root.name != 'fix2':
    raise SystemExit('This packager is restricted to the fix2 folder')
outputs = root.parent
exe = root / 'build/Y540Updater.exe'
if not exe.exists():
    raise SystemExit('Run build.ps1 first')
markers = {
    'core': 'PASS: real firmware',
    'transport_memory_backend': 'HID transport offline tests passed',
    'protocol_emulator': 'PASS: offline protocol model',
    'device_state_fixtures': 'Device-state offline fixtures passed',
    'session_log_files': 'Session log file/UTF-8/unique-path tests passed',
    'app_sample_verify': 'Validated 55296 bytes.',
    'hidden_gui_initialization': 'GUI controls initialized (hidden; no device access)',
}
log_path = root/'evidence/fix2-build-log.txt'
build_log = log_path.read_text(encoding='utf-8-sig')
if log_path.stat().st_mtime < exe.stat().st_mtime or 'Built: ' not in build_log:
    raise SystemExit('Need a fresh complete build receipt: .\\build.ps1 | Tee-Object evidence\\fix2-build-log.txt')
results = {}
for name, marker in markers.items():
    if marker not in build_log:
        raise SystemExit('Missing successful build check: '+name)
    results[name] = {'status': 'passed', 'evidence': 'evidence/fix2-build-log.txt', 'marker': marker}
imports = re.findall(r'DLL Name:\s*(\S+)', subprocess.check_output(['objdump', '-p', str(exe)], text=True))
receipt = {
    'version': '0.3.1-fix2', 'compiler': subprocess.check_output(['gcc', '--version'], text=True).splitlines()[0],
    'architecture': 'Windows x64', 'exe_sha256': hashlib.sha256(exe.read_bytes()).hexdigest(),
    'exe_bytes': exe.stat().st_size, 'imported_dlls': imports, 'tests': results,
    'hardware_validation': 'not performed', 'original_executable_execution': 'not performed',
    'source_is_vendor_original': False, 'firmware_modified': False,
}
(root/'evidence/build-verification.json').write_text(json.dumps(receipt, indent=2), encoding='utf8')
portable = root/'dist/Y540Updater-fix2'
portable.mkdir(parents=True, exist_ok=True)
shutil.copy2(exe, portable/'Y540Updater.exe')
for name in ['44.bin', 'SHFU.ini']:
    shutil.copy2(root/'samples'/name, portable/name)
shutil.copy2(root/'START-HERE.txt', portable/'START-HERE.txt')
source = outputs/'fix2-source.zip'
manifest = json.loads((root/'samples/manifest.json').read_text(encoding='utf-8-sig'))
manifest['files'] = [f for f in manifest['files'] if f['name'] in ['44.bin', 'SHFU.ini']]
manifest['scope'] = 'Unchanged source-build fixtures only; vendor EXEs excluded.'
with zipfile.ZipFile(source, 'w', zipfile.ZIP_DEFLATED, compresslevel=6) as archive:
    for path in sorted(root.rglob('*')):
        if not path.is_file():
            continue
        rel = path.relative_to(root)
        if any(p in {'.git', 'work', 'build', 'dist', '__pycache__', 'case-inputs'} for p in rel.parts):
            continue
        if rel.parts[0] == 'samples' and path.name not in {'44.bin', 'SHFU.ini', 'manifest.json'}:
            continue
        if path.suffix.lower() in {'.pyc', '.o', '.exe', '.zip'}:
            continue
        name = 'fix2/'+rel.as_posix()
        if rel.as_posix() == 'samples/manifest.json':
            archive.writestr(name, json.dumps(manifest, indent=2))
        else:
            archive.write(path, name)
portable_zip = outputs/'Y540Updater-fix2-portable.zip'
with zipfile.ZipFile(portable_zip, 'w', zipfile.ZIP_DEFLATED, compresslevel=6) as archive:
    for name in ['Y540Updater.exe', '44.bin', 'SHFU.ini', 'START-HERE.txt']:
        archive.write(portable/name, 'Y540Updater-fix2/'+name)
release = {'files': [{'name': p.name, 'bytes': p.stat().st_size,
                      'sha256': hashlib.sha256(p.read_bytes()).hexdigest()}
                     for p in [source, portable_zip]], 'exe': receipt}
(outputs/'fix2-release-manifest.json').write_text(json.dumps(release, indent=2), encoding='utf8')
print(json.dumps({'files': release['files'], 'tests': {k:v['status'] for k,v in results.items()},
                  'exe_sha256': receipt['exe_sha256']}, indent=2))
