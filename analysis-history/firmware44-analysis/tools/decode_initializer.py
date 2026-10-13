"""Decode the constant initializer using byte operations at CODE:0464..04a7.
Assumes raw CODE base0 and classic8051. No target execution or hardware access.
"""
from pathlib import Path
import json, hashlib

root=Path(__file__).resolve().parents[1]
source=root.parent/'y540-research/samples/44.bin'
raw=source.read_bytes()
cursor=0x5154
records=[]
xram=bytearray(4096) # Both observed startup loops clear XDATA 0000..0fff first.
origins={}
while True:
    begin=cursor
    header=raw[cursor]; cursor+=1
    if header==0: break
    length=header&0x3f
    if length&0x20:
        length=((header&0x1f)<<8)|raw[cursor]; cursor+=1
    mode=header&0xc0
    if mode==0xc0:
        address=None
    elif mode==0x40:
        address=int.from_bytes(raw[cursor:cursor+2],'big'); cursor+=2
    else:
        address=raw[cursor]; cursor+=1
    data_offset=cursor
    payload=raw[cursor:cursor+length]; assert len(payload)==length
    cursor+=length
    entry={'record_file_offset':hex(begin),'header':hex(header),'mode':{0:'IDATA',0x40:'XDATA',0x80:'PDATA',0xc0:'BITS'}[mode],'destination':hex(address) if address is not None else None,'length':length,'payload_file_offset':hex(data_offset),'payload_hex':payload.hex(' ')}
    records.append(entry)
    if mode==0x40:
        assert address+length<=len(xram)
        xram[address:address+length]=payload
        for i in range(length): origins[address+i]=data_offset+i
assert xram[0xa1f:0xa23]==bytes([76,0,0,0])
assert origins[0xa1f]==0x53ca
for label,addr,size in [('os_properties',0xa1f,76),('hid_report',0xaa7,161)]:
    assert len({origins[addr+i]-i for i in range(size)})==1
result={'source_sha256':hashlib.sha256(raw).hexdigest(),'initializer_start':'0x5154','initializer_terminator':hex(cursor-1),'records':records,'known_objects':{'os_properties':{'xdata':'0x0a1f','file_offset':hex(origins[0xa1f]),'size':76},'hid_report':{'xdata':'0x0aa7','file_offset':hex(origins[0xaa7]),'size':161}},'limitations':['Assumes generic8051 instruction decoding and CODE:file offsetbase0.','This is an offline replay of constant initialization, not captured device RAM.','PDATA and bit initialization are retained as records, not simulated.']}
(root/'initializer.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
(root/'initializer-xdata-model.bin').write_bytes(xram)
print(json.dumps({'records':len(records),'terminator':hex(cursor-1),'known_objects':result['known_objects']},indent=2))
