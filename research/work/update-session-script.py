from pathlib import Path
p=Path('outputs/y540-research/tools/rea_session.py')
s=p.read_text(encoding='utf-8-sig')
s=s.replace("p=argparse.ArgumentParser();p.add_argument('--rea-root'", "p=argparse.ArgumentParser();p.add_argument('--queue',default='work/queue');p.add_argument('--rea-root'")
s=s.replace("qdir=ROOT/'work'/'queue'", "qdir=ROOT/a.queue")
s=s.replace("if request.name in done:continue", "if request.name in done:continue\n   if (out/request.name).exists():\n    done.add(request.name);print('Existing response preserved: '+request.name,flush=True);continue")
s=s.replace("if call['name']=='close_binary':raise SystemExit(0)", "if call['name']=='close_binary' and not result.get('error') and not result.get('result',{}).get('isError'):raise SystemExit(0)")
p.write_text(s,encoding='utf8')
