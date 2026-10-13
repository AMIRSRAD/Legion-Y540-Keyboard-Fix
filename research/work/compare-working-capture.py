from pathlib import Path
import json

# Reuse the full log parser from the failed-state correlation, stopping before ETW handling.
parser=Path('work/correlate-fix1-recording.py').read_text(encoding='utf-8')
parser=parser.split('etl=json.loads',1)[0].replace('New folder (2)','New folder (3)')
exec(compile(parser,'correlate-fix1-recording.py','exec'))
previous=json.loads((out/'fix1-correlation.json').read_text(encoding='utf-8'))
failed=previous['logs'][2]['inventories'][0]
failed_by_id={d['instance_id']:d for d in failed['devices']}
working_by_id={d['instance_id']:d for d in inventories[0][1]['devices']}
changes=[]
for identity in sorted(failed_by_id.keys()|working_by_id.keys()):
    a,b=failed_by_id.get(identity),working_by_id.get(identity)
    if a!=b:
        fields={k:{'failed':a.get(k),'working':b.get(k)} for k in sorted(a.keys()|b.keys()) if a.get(k)!=b.get(k)} if a and b else {'record':{'failed':a,'working':b}}
        changes.append({'instance_id':identity,'changed_fields':fields})
result={'source_directory':str(source),'logs':records,'inventory_count':len(inventories),'device_record_count':sum(len(i['devices']) for _,i in inventories),'within_capture_differences':diffs,'failed_to_working_differences':changes,'owner_report':'Built-in keyboard kept typing normally after USB retry.','etw_recording_supplied_in_folder':False,'status_mapping':{'CM_Disable_DevNode_return_decimal_40':'CR_NOT_DISABLEABLE (0x28)','CR_ACCESS_DENIED':'0x33 (51), not observed here'}}
(out/'working-state-comparison.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
print(json.dumps({'inventory_count':len(inventories),'records':result['device_record_count'],'within_capture_changes':[len(x['differences']) for x in diffs],'failed_to_working_changed_devices':len(changes),'changed_devices':[{'id':x['instance_id'],'fields':list(x['changed_fields'])} for x in changes],'action_events':[e for l in records for e in l['events'] if 'restart' in e['message'].lower()]},indent=2))
