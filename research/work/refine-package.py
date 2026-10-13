from pathlib import Path
p=Path('outputs/y540-research/tools/package_release.py');s=p.read_text(encoding='utf-8-sig')
needle="imports=re.findall"
addition="""test_commands={
 'core':['core-tests.exe','samples'],
 'transport_memory_backend':['hid-transport-tests.exe'],
 'protocol_emulator':['protocol-tests.exe','samples'],
 'app_sample_verify':['Y540Updater.exe','--verify','samples/44.bin','samples/SHFU.ini'],
 'hidden_gui_initialization':['Y540Updater.exe','--gui-smoke']}
test_results={}
for name,args in test_commands.items():
 result=subprocess.run([str(root/'build'/args[0]),*args[1:]],cwd=root,text=True,capture_output=True)
 if result.returncode:raise SystemExit(name+' failed: '+result.stdout+result.stderr)
 test_results[name]={'status':'passed','output':result.stdout.strip()}
"""
s=s.replace(needle,addition+needle)
old="'tests':{'core':'passed','transport_memory_backend':'passed','protocol_emulator':'passed','app_sample_verify':'passed','hidden_gui_initialization':'passed','cmake_ctest':'5/5 passed'}"
s=s.replace(old,"'tests':test_results")
p.write_text(s,encoding='utf8')
