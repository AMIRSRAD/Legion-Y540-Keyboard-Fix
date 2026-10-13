"""Read-only descriptor extraction for this exact firmware. Offsets are file offsets.
This is a bounded HID item parser, not a USB/HID certification suite.
"""
from pathlib import Path
import hashlib, json, collections

ROOT = Path(__file__).resolve().parents[2]
IMAGE = ROOT / 'y540-research/samples/44.bin'
OUT = Path(__file__).resolve().parent

def hid(blob, base):
    i=0; state={}; stack=[]; collections_stack=[]; items=[]; fields=[]; errors=[]; local={}
    global_names={0:'UsagePage',1:'LogicalMinimum',2:'LogicalMaximum',3:'PhysicalMinimum',4:'PhysicalMaximum',5:'UnitExponent',6:'Unit',7:'ReportSize',8:'ReportID',9:'ReportCount',10:'Push',11:'Pop'}
    local_names={0:'Usage',1:'UsageMinimum',2:'UsageMaximum'}
    main_names={8:'Input',9:'Output',10:'Collection',11:'Feature',12:'EndCollection'}
    while i<len(blob):
        start=i; prefix=blob[i]; i+=1
        if prefix==0xfe:
            errors.append({'offset':hex(base+start),'error':'Long item outside parser coverage'}); break
        size=(0,1,2,4)[prefix&3]; typ=(prefix>>2)&3; tag=prefix>>4
        if i+size>len(blob): errors.append({'offset':hex(base+start),'error':'Truncated item'}); break
        payload=blob[i:i+size]; i+=size; value=int.from_bytes(payload,'little')
        signed=int.from_bytes(payload,'little',signed=True) if size else 0
        name=({0:main_names,1:global_names,2:local_names}.get(typ,{})).get(tag,'Unknown')
        items.append({'offset':hex(base+start),'bytes':blob[start:i].hex(' '),'type':typ,'tag':tag,'name':name,'value':value})
        if typ==1:
            if tag==10: stack.append(state.copy())
            elif tag==11:
                if stack: state=stack.pop()
                else: errors.append({'offset':hex(base+start),'error':'Global pop underflow'})
            else:
                state[name]=signed if tag in (1,3) or (tag==2 and state.get('LogicalMinimum',0)<0) or (tag==4 and state.get('PhysicalMinimum',0)<0) else value
                if tag==8 and (not value or value>255): errors.append({'offset':hex(base+start),'error':'Invalid report ID'})
        elif typ==2:
            if tag==0: local.setdefault('Usage',[]).append(value)
            else: local[name]=value
        elif typ==0:
            if tag==10:
                collections_stack.append({'type':value,'page':state.get('UsagePage'),'usage':local.get('Usage',[])[-1:]})
            elif tag==12:
                if collections_stack: collections_stack.pop()
                else: errors.append({'offset':hex(base+start),'error':'Collection underflow'})
            elif tag in (8,9,11):
                field={'offset':hex(base+start),'kind':name,'flags':value,'report_id':state.get('ReportID',0),'size_bits':state.get('ReportSize',0),'count':state.get('ReportCount',0),'global':state.copy(),'local':local.copy(),'collections':list(collections_stack)}
                field['bits']=field['size_bits']*field['count']; fields.append(field)
                if not field['bits']: errors.append({'offset':hex(base+start),'error':'Missing/zero report size or count'})
                if state.get('LogicalMinimum',0)>state.get('LogicalMaximum',0): errors.append({'offset':hex(base+start),'error':'Inverted logical range'})
            local={}
        else: errors.append({'offset':hex(base+start),'error':'Reserved item type'})
        if name=='Unknown': errors.append({'offset':hex(base+start),'error':'Unknown item tag'})
    if collections_stack: errors.append({'error':'Unclosed collections'})
    if stack: errors.append({'error':'Unbalanced global push/pop'})
    totals=collections.defaultdict(int)
    for f in fields: totals[f['kind'],f['report_id']]+=f['bits']
    reports=[{'kind':k[0],'report_id':k[1],'payload_bits':v,'payload_bytes':(v+7)//8,'wire_bytes_including_id':(v+7)//8+bool(k[1])} for k,v in totals.items()]
    return {'file_offset':hex(base),'length':len(blob),'sha256':hashlib.sha256(blob).hexdigest(),'hex':blob.hex(' '),'items':items,'fields':fields,'reports':reports,'bounded_parser_errors':errors}

def run():
    b=IMAGE.read_bytes(); dev=b[0x5307:0x5319]; cfg=b[0x531d:0x533f]
    nodes=[]; i=0
    while i<len(cfg):
        length=cfg[i]; assert length>=2 and i+length<=len(cfg)
        nodes.append({'offset':hex(0x531d+i),'length':length,'type':cfg[i+1],'hex':cfg[i:i+length].hex(' ')}); i+=length
    primary=hid(b[0x5184:0x5225],0x5184)
    alternate=hid(b[0x5229:0x527b],0x5229)
    result={'image':str(IMAGE),'image_bytes':len(b),'image_sha256':hashlib.sha256(b).hexdigest(),'device_descriptor':{'offset':'0x5307','hex':dev.hex(' '),'bcdUSB':hex(int.from_bytes(dev[2:4],'little')),'max_packet_ep0':dev[7],'VID':hex(int.from_bytes(dev[8:10],'little')),'PID':hex(int.from_bytes(dev[10:12],'little')),'bcdDevice':hex(int.from_bytes(dev[12:14],'little')),'manufacturer_index':dev[14],'product_index':dev[15],'serial_index':dev[16],'configurations':dev[17]},'configuration':{'offset':'0x531d','total_length':int.from_bytes(cfg[2:4],'little'),'parsed_length':i,'interfaces':cfg[4],'attributes':hex(cfg[7]),'max_power_ma':cfg[8]*2,'nodes':nodes},'primary_report_descriptor':primary,'additional_consumer_report_candidate':alternate,'strings':[],'limits':['File offsets are not established execution addresses.','Storage and descriptor equality do not establish actual runtime selection or RAM contents.','No full USB/HID protocol certification or control-request handler analysis.','Additional 82-byte consumer descriptor has no proven active interface binding.']}
    os_blob=b[0x53ca:0x5416]
    result['microsoft_extended_properties_candidate']={'offset':'0x53ca','hex':os_blob.hex(' '),'dwLength':int.from_bytes(os_blob[:4],'little'),'bcdVersion':hex(int.from_bytes(os_blob[4:6],'little')),'wIndex':int.from_bytes(os_blob[6:8],'little'),'wCount':int.from_bytes(os_blob[8:10],'little'),'property':{'offset':'0x53d4','dwSize':int.from_bytes(os_blob[10:14],'little'),'dwPropertyDataType':int.from_bytes(os_blob[14:18],'little'),'wPropertyNameLength':int.from_bytes(os_blob[18:20],'little'),'name':os_blob[20:68].decode('utf-16le'),'dwPropertyDataLength':int.from_bytes(os_blob[68:72],'little'),'DWORD':int.from_bytes(os_blob[72:76],'little')}}
    for off in (0x5342,0x5349,0x536b,0x5391,0x53b4):
        length=b[off]; raw=b[off:off+length]
        entry={'offset':hex(off),'length':length,'type':raw[1],'hex':raw.hex(' ')}
        if off==0x5342: entry['LANGIDs']=[hex(int.from_bytes(raw[j:j+2],'little')) for j in range(2,length,2)]
        elif off==0x53b4: entry.update({'OS_signature':raw[2:16].decode('utf-16le'),'vendor_code':raw[16],'padding':raw[17]})
        else: entry['decoded_utf16le']=raw[2:].decode('utf-16le',errors='replace')
        result['strings'].append(entry)
    (OUT/'evidence.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
    print(json.dumps({'image_sha256':result['image_sha256'],'primary':primary['reports'],'primary_errors':primary['bounded_parser_errors'],'additional':alternate['reports'],'additional_errors':alternate['bounded_parser_errors'],'strings':result['strings']},indent=2))

if __name__=='__main__': run()
