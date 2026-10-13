import json, hashlib, shutil
from pathlib import Path
from collections import Counter
from datetime import datetime, timedelta, timezone
import xml.etree.ElementTree as ET

work=Path('work/usb-trace-141255')
out=Path('outputs/usb-trace-analysis/working-recording')
out.mkdir(exist_ok=True)
ns={'e':'http://schemas.microsoft.com/win/2004/08/events/event'}
tree=ET.parse(work/'events.xml')
rows=[]
for n,event in enumerate(tree.getroot()):
    def val(path):
        node=event.find(path,ns)
        return (node.text or '').strip() if node is not None else ''
    provider=event.find('e:System/e:Provider',ns)
    time=event.find('e:System/e:TimeCreated',ns)
    rows.append({'ordinal':n,'provider':provider.get('Name',''),'id':val('e:System/e:EventID'),'version':val('e:System/e:Version'),'time':time.get('SystemTime'),'level':val('e:System/e:Level'),'task':val('e:RenderingInfo/e:Task'),'opcode':val('e:RenderingInfo/e:Opcode'),'message':val('e:RenderingInfo/e:Message'),'data':{d.get('Name',''):(d.text or '').strip() for d in event.findall('.//e:Data',ns)},'schema_error':val('e:ProcessingErrorData/e:ErrorCode')})
assert len(rows)==653
(out/'decoded.json').write_text(json.dumps(rows,indent=2),encoding='utf-8')
old=json.loads(Path('outputs/usb-trace-analysis/decoded.json').read_text(encoding='utf-8-sig'))
def summary(events):
    return {'events':len(events),'provider_counts':dict(Counter(r['provider'] or 'Trace metadata' for r in events)), 'schema_errors':[r for r in events if r['schema_error']], 'hub_enumeration_events':[r for r in events if r['provider'].endswith('USBHUB3') and r['id'] in ['60','61','62','63','64','160','197']], 'port_change_failures':[r for r in events if r['provider'].endswith('USBHUB3') and r['id']=='123'], 'control_completions':[r for r in events if r['provider'].endswith('USB-UCX') and r['id']=='24'], 'events_lost':events[0]['data']['EventsLost'],'buffers_lost':events[0]['data']['BuffersLost']}
header=rows[0]
base=datetime.fromisoformat(header['time'][:26])
start=datetime(1601,1,1,tzinfo=timezone.utc)+timedelta(microseconds=int(header['data']['StartTime'])//10)
for r in rows:
    r['relative_seconds']=(datetime.fromisoformat(r['time'][:26])-base).total_seconds()
    r['utc_reconstructed']=(start+timedelta(seconds=r['relative_seconds'])).isoformat()
interesting=[r for r in rows if r['data'].get('fid_PortNumber') in ['9','6'] or r['data'].get('fid_idProduct')=='0xC100']
retry_time=datetime(2026,10,12,14,13,49,tzinfo=timezone.utc)
near=[r for r in rows if abs((datetime.fromisoformat(r['utc_reconstructed'])-retry_time).total_seconds())<2]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
zip_path=Path(r'C:\Users\a.saberi\Desktop\recording-20261012T141255304Z.zip')
keyboard=next(r for r in rows if r['provider'].endswith('USBHUB3') and r['data'].get('fid_PortNumber')=='9' and r['data'].get('fid_idProduct')=='0xC100')
keyboard_pointer=keyboard['data']['fid_UsbDevice']
live=[r for r in rows if r['provider'].endswith('USB-UCX') and r['id']=='27' and r['data'].get('fid_UsbDevice')==keyboard_pointer]
assert len(live)==4 and all(r['data']['fid_URB_Hdr_Status']=='0x0' and r['data']['fid_IRP_NtStatus']=='0x0' and r['data']['fid_URB_TransferBufferLength']=='0x21' for r in live)
comparison={'source_zip':str(zip_path),'source_zip_sha256':sha(zip_path),'etl_sha256':sha(work/'usb_000001.etl'),'working':summary(rows),'failed':summary(old),'working_port_6_9_and_C100_records':interesting,'working_events_within_two_seconds_of_retry':near,'successful_keyboard_transfers':live,'trace_start_utc':start.isoformat(),'time_method':'FILETIME StartTime plus displayed event-to-header wall-clock differences; original rendered offset retained, not used for UTC conversion.'}
(out/'comparison.json').write_text(json.dumps(comparison,indent=2),encoding='utf-8')
for name in ['events.xml','summary.txt','capture-journal.txt','machine.json','windows.json']:
    shutil.copyfile(work/name,out/name)
print(json.dumps({'working':{k:v for k,v in summary(rows).items() if k not in ['schema_errors','control_completions','hub_enumeration_events','port_change_failures']},'schema_errors':[(r['ordinal'],r['schema_error']) for r in rows if r['schema_error']],'enumeration_events':len(summary(rows)['hub_enumeration_events']),'port_change_failures':len(summary(rows)['port_change_failures']),'control_completions':len(summary(rows)['control_completions']),'near_retry':[{'ordinal':r['ordinal'],'time':r['utc_reconstructed'],'message':r['message'],'id':r['id']} for r in near],'interesting_port_records':[{'ordinal':r['ordinal'],'message':r['message'],'data':r['data']} for r in interesting]},indent=2))
