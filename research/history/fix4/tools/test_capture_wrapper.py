"""Offline launcher orchestration test; mocks logman and process launch.
No USB/device API or updater executable is invoked."""
from pathlib import Path
import hashlib,json,subprocess,tempfile,zipfile,os
root=Path(__file__).resolve().parents[1]
work=root.parent.parent/'work'
work.mkdir(exist_ok=True)
fixture=Path(tempfile.mkdtemp(prefix='fix4-wrapper-test-',dir=work))
assert fixture.resolve().is_relative_to(work.resolve())
hashes={}
for name in ['Y540Updater.exe','44-nosleep-exp1.bin','44-stock-restore.bin','SHFU.ini']:
    data=('INERT TEST FIXTURE '+name).encode()
    (fixture/name).write_bytes(data)
    hashes[name]={'sha256':hashlib.sha256(data).hexdigest()}
(fixture/'FILE-HASHES.json').write_text(json.dumps(hashes))
(fixture/'patch-manifest.json').write_text('{}')
source=(root/'FINAL-ATTEMPT.ps1').read_text()
admin='if (-not $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator))'
assert admin in source
source=source.replace(admin,'if ($false)')
native='$result = & $logman @arguments 2>&1; $code = $LASTEXITCODE'
assert native in source
source=source.replace(native,"$result = @('MOCK logman, no trace API called'); $code = 0")
assert '& $logman' not in source
prelude='''
$script:mockLaunches = 0
function Start-Process {
    param([string]$FilePath,[string]$WorkingDirectory,[string]$WindowStyle,[switch]$PassThru)
    $script:mockLaunches++
    New-Item -ItemType Directory -Path (Join-Path $WorkingDirectory 'logs') | Out-Null
    Set-Content -LiteralPath (Join-Path $WorkingDirectory 'logs/completed.log') -Value 'MOCK completed updater result'
    return [pscustomobject]@{ HasExited=$true; Id=0 }
}
'''
postlude='''
if ($script:mockLaunches -ne 1) { throw 'Expected exactly one GUI launch' }
'''
(fixture/'test.ps1').write_text(prelude+source+postlude)
environment=os.environ.copy()
# Test Windows PowerShell with its native modules, not the host pwsh7 module path.
environment['PSMODULEPATH']=str(Path(os.environ['SystemRoot'])/'System32/WindowsPowerShell/v1.0/Modules')
run=subprocess.run(['powershell.exe','-NoProfile','-ExecutionPolicy','Bypass','-File',str(fixture/'test.ps1')],capture_output=True,text=True,env=environment)
assert run.returncode==0,run.stdout+run.stderr
archives=list(fixture.glob('final-recording-*.zip'))
assert len(archives)==1
with zipfile.ZipFile(archives[0]) as z:
    assert z.testzip() is None
    names=z.namelist()
    assert any(n.endswith('updater-logs/completed.log') for n in names)
    journal=z.read(next(n for n in names if n.endswith('capture-journal.txt'))).decode('utf-8-sig')
    for token in ['logman create','logman start','logman stop','logman delete','Updater exited']:
        assert token in journal,token
result={'status':'passed','mode':'offline mocks only','real_updater_launches':0,'real_logman_calls':0,
        'verified':['package hash check','single GUI launch requested','trace start/stop/definition cleanup requested','completed log copied','ZIP readable'],
        'fixture':str(fixture),'stdout':run.stdout}
(root/'evidence/capture-wrapper-test.json').write_text(json.dumps(result,indent=2))
print('PASS: final capture wrapper offline orchestration; no updater or USB trace executed.')
