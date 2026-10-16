import json, pathlib, shutil, subprocess, time
base=pathlib.Path(__file__).resolve().parent
archive=base/'archive'
def run(*args):
    subprocess.run(list(args),check=True,cwd=base/'repo')
started=time.monotonic()
while not (archive/'ARCHIVE-SUMMARY.json').exists():
    if time.monotonic()-started>7200: raise TimeoutError('Archive not complete after two hours')
    time.sleep(5)
print('Archive build complete; verifying all reconstructed bytes',flush=True)
run('python',str(base/'verify_local.py'))
run('python',str(base/'audit_cleanup_sources.py'))
for name in ['file-index.jsonl.gz','object-index.json.gz','ARCHIVE-SHA256.json','ARCHIVE-SUMMARY.json']:
    shutil.copy2(archive/name,base/'repo'/'archive'/name)
for name in ['LOCAL-VERIFICATION.json','RESTORE-VERIFICATION.json','SOURCE-AUDIT.json']:
    shutil.copy2(base/name,base/'repo'/'archive'/name)
shutil.copy2(base/'restore_archive.py',archive/'restore_archive.py')
for name in ['LOCAL-VERIFICATION.json','RESTORE-VERIFICATION.json','SOURCE-AUDIT.json']:
    shutil.copy2(base/name,archive/name)
run('git','add','archive','ARCHIVE.md')
run('git','-c','user.name=AMIRSRAD','-c','user.email=115648246+AMIRSRAD@users.noreply.github.com',
    'commit','--quiet','-m','Index every preserved file and record full verification and recovery checks')
run('git','push','origin','main')
print('Indexes and local verification pushed; uploading and reading back remaining assets',flush=True)
while not (base/'PART-UPLOADS-COMPLETE.json').exists():
    if time.monotonic()-started>7200: raise TimeoutError('Part uploads not complete')
    time.sleep(5)
run('python',str(base/'publish_verify.py'))
shutil.copy2(base/'REMOTE-VERIFICATION.json',base/'repo'/'archive'/'REMOTE-VERIFICATION.json')
run('git','add','archive/REMOTE-VERIFICATION.json')
run('git','-c','user.name=AMIRSRAD','-c','user.email=115648246+AMIRSRAD@users.noreply.github.com',
    'commit','--quiet','-m','Record SHA-256 verification of every GitHub release asset')
run('git','push','origin','main')
run('gh','release','edit','preservation-2026-10-13','--repo','AMIRSRAD/Y540-Keyboard','--draft=false')
print('PUBLIC RELEASE VERIFIED; source deletion has not been performed',flush=True)
