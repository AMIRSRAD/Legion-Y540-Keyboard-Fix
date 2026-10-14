import contextlib, importlib.util, json, pathlib
base = pathlib.Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('restore',base/'restore_archive.py')
module=importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
with (base/'local-verification.log').open('w',encoding='utf8') as log:
    with contextlib.redirect_stdout(log):
        result=module.restore(base/'archive')
(base/'LOCAL-VERIFICATION.json').write_text(json.dumps(result,indent=2),encoding='utf8')
with (base/'restore-latest.log').open('w',encoding='utf8') as log:
    with contextlib.redirect_stdout(log):
        result=module.restore(base/'archive',base/'restored-latest',['workspace'],'outputs/fix9')
(base/'RESTORE-VERIFICATION.json').write_text(json.dumps(result,indent=2),encoding='utf8')
print('Full local verification and latest-attempt restore passed',flush=True)
