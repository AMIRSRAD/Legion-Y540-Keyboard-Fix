import json, re, hashlib
from pathlib import Path
from datetime import datetime, timedelta, timezone

root=Path.cwd()
source=Path(r'C:\Users\a.saberi\Desktop\New folder (2)')
out=root/'outputs/usb-trace-analysis'
records=[]
for path in sorted(source.glob('*.log')):
    raw=path.read_bytes()
    text=raw.decode('utf-8-sig')
    log={'name':path.name,'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'inventories':[],'events':[]}
    inv=None
    dev=None
    for line in text.splitlines():
        m=re.match(r'(\S+Z) tick=(\d+) (.*)',line)
        if not m:
            continue
        time,tick,msg=m.groups()
        if 'PnP metadata inventory UTC=' in msg:
            inv={'time':time,'header':msg,'devices':[]}
            log['inventories'].append(inv)
            dev=None
        elif re.match(r'device\[\d+\]',msg):
            assert inv is not None
            dev={'index':int(re.search(r'\[(\d+)\]',msg)[1]),'status_fields':dict(re.findall(r'(\w+)=(\S+)',msg))}
            inv['devices'].append(dev)
        elif msg.startswith('  ') and dev is not None and '=' in msg:
            key,value=msg.strip().split('=',1)
            dev[key]=value
        else:
            log['events'].append({'time':time,'tick':int(tick),'message':msg})
    for i in log['inventories']:
        assert len(i['devices'])==int(re.search(r'count=(\d+)',i['header'])[1])
    records.append(log)
inventories=[(l['name'],i) for l in records for i in l['inventories']]
assert len(inventories)==3
base={d['instance_id']:d for d in inventories[0][1]['devices']}
diffs=[]
for name,inv in inventories[1:]:
    current={d['instance_id']:d for d in inv['devices']}
    changed=[]
    for identity in sorted(base.keys()|current.keys()):
        a,b=base.get(identity),current.get(identity)
        if a!=b: changed.append({'instance_id':identity,'before':a,'after':b})
    diffs.append({'name':name,'time':inv['time'],'differences':changed})
etl=json.loads((out/'decoded.json').read_text(encoding='utf-8-sig'))
trace_start=datetime(1601,1,1,tzinfo=timezone.utc)+timedelta(microseconds=int(etl[0]['data']['StartTime'])//10)
naive_base=datetime.fromisoformat(etl[0]['time'][:26])
timeline=[]
for row in etl:
    if row['ordinal'] in {598,848,1817,1923,2057,2103,2210,729,1077,2176,2509}:
        delta=datetime.fromisoformat(row['time'][:26])-naive_base
        utc=trace_start+delta
        timeline.append({'ordinal':row['ordinal'],'utc_reconstructed':utc.isoformat(),'message':row['message'],'data':row['data']})
result={'source_directory':str(source),'logs':records,'inventory_count':len(inventories),'device_record_count':sum(len(i['devices']) for _,i in inventories),'inventory_differences':diffs,'trace_start_utc_from_header_FILETIME':trace_start.isoformat(),'time_method':'Header StartTime FILETIME plus event-to-header displayed wall-clock difference, avoiding tracerpt offset string. Precision truncated to microseconds; fix1 logs are milliseconds.','correlated_trace_events':timeline}
(out/'fix1-correlation.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
retry=next(l for l in records if any('session action=usb-restart-no-flash' in e['message'] for e in l['events']))
events=[e for e in retry['events'] if any(s in e['message'] for s in ['Attempting one','Windows accepted','Before USB','After USB'])]
print(json.dumps({'logs':[(l['name'],l['bytes'],len(l['inventories'])) for l in records],'devices':result['device_record_count'],'differences':[len(d['differences']) for d in diffs],'retry_events':events,'trace_events':[{k:v for k,v in t.items() if k!='data'} for t in timeline]},indent=2))
