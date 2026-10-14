import json,pathlib,subprocess,time
base=pathlib.Path(__file__).resolve().parent
archive=base/'archive'
assets=json.loads(subprocess.check_output(['gh','release','view','preservation-2026-10-13',
    '--repo','AMIRSRAD/Y540-Keyboard','--json','assets'],text=True))['assets']
uploaded={a['name'] for a in assets}
started=time.monotonic()
while True:
    complete=(archive/'ARCHIVE-SUMMARY.json').exists()
    parts=sorted(archive.glob('archive-part-*.zip'))
    closed=parts if complete else parts[:-1]
    todo=[p for p in closed if p.name not in uploaded]
    if todo:
        print('Uploading closed parts:',*[p.name for p in todo],flush=True)
        subprocess.run(['gh','release','upload','preservation-2026-10-13',
            *[str(p) for p in todo],'--repo','AMIRSRAD/Y540-Keyboard'],check=True)
        uploaded.update(p.name for p in todo)
    if complete:
        (base/'PART-UPLOADS-COMPLETE.json').write_text(json.dumps(sorted(uploaded)),encoding='utf8')
        print('All closed parts uploaded',flush=True)
        break
    if time.monotonic()-started>7200: raise TimeoutError('Archive build/upload exceeded two hours')
    time.sleep(5)
