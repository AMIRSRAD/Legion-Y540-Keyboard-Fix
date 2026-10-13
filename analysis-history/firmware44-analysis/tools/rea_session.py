"""Local REA MCP session runner. Consumes numbered JSON requests from work/queue.
Only local static analysis is intended. Every response is saved unchanged.
"""
import subprocess, threading, queue, json, os, time, pathlib, argparse
ROOT=pathlib.Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--queue',default='work/queue');p.add_argument('--rea-root',default=r'C:\Users\owner\Desktop\rea-rea-agents-6.4.0');p.add_argument('--ghidra',default=r'C:\Users\owner\Documents\Codex\tools\ghidra_12.1.4_PUBLIC');p.add_argument('--java',default=r'C:\Program Files\Java\jdk-23');a=p.parse_args()
env=dict(os.environ,GHIDRA_INSTALL_DIR=a.ghidra,JAVA_HOME=a.java,REA_GHIDRA_LANGUAGE_ID='8051:BE:16:default')
out=ROOT/'evidence'/'rea';out.mkdir(parents=True,exist_ok=True);qdir=ROOT/a.queue;qdir.mkdir(parents=True,exist_ok=True)
log=open(ROOT/'work'/'rea-stderr.log','w',encoding='utf8')
proc=subprocess.Popen(['node',str(pathlib.Path(a.rea_root)/'scripts'/'rea.mjs'),'mcp'],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=log,text=True,encoding='utf8',env=env)
responses=queue.Queue()
def reader():
 for line in proc.stdout:
  try: responses.put(json.loads(line))
  except ValueError: pass
threading.Thread(target=reader,daemon=True).start();ident=0
def rpc(method,params):
 global ident
 ident+=1;rid=ident;proc.stdin.write(json.dumps({'jsonrpc':'2.0','id':rid,'method':method,'params':params})+'\n');proc.stdin.flush();end=time.monotonic()+900
 while time.monotonic()<end:
  try:r=responses.get(timeout=1)
  except queue.Empty:
   if proc.poll() is not None:raise RuntimeError('REA exited: '+str(proc.returncode))
   continue
  if r.get('id')==rid:return r
 raise TimeoutError(method)
try:
 init=rpc('initialize',{'protocolVersion':'2025-11-25','capabilities':{},'clientInfo':{'name':'y540-research','version':'0.1'}});(out/'initialize.json').write_text(json.dumps(init,indent=2),encoding='utf8')
 proc.stdin.write(json.dumps({'jsonrpc':'2.0','method':'notifications/initialized'})+'\n');proc.stdin.flush()
 catalog=rpc('tools/list',{});(out/'tool-catalog.json').write_text(json.dumps(catalog,indent=2),encoding='utf8');print('Catalog saved',flush=True)
 done=set()
 while True:
  for request in sorted(qdir.glob('*.json')):
   if request.name in done:continue
   if (out/request.name).exists():
    done.add(request.name);print('Existing response preserved: '+request.name,flush=True);continue
   call=json.loads(request.read_text(encoding='utf-8-sig'))
   result=rpc('tools/call',{'name':call['name'],'arguments':call.get('arguments',{})})
   (out/request.name).write_text(json.dumps({'request':call,'response':result},indent=2),encoding='utf8');done.add(request.name);print('Saved '+request.name,flush=True)
   if call['name']=='close_binary' and not result.get('error') and not result.get('result',{}).get('isError'):raise SystemExit(0)
  if proc.poll() is not None:raise RuntimeError('REA exited')
  time.sleep(1)
finally:
 proc.stdin.close()
 try:proc.wait(timeout=15)
 except subprocess.TimeoutExpired:proc.terminate();proc.wait(timeout=10)
 log.close()
