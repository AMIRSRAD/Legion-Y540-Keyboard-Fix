from pathlib import Path
import json, hashlib
root=Path(__file__).resolve().parents[1]
base=root.parent
fw=(base/'fix2/samples/44.bin').read_bytes()
export_path=base/'firmware44-analysis/ghidra-static-inline-aware.json'
p=json.loads(export_path.read_text())
ranges=[(0x07c4,0x09a0),(0x26e2,0x2718),(0x3185,0x3195),(0x32d3,0x3500),(0x35dd,0x35f0),(0x36eb,0x36fc),(0x39da,0x3a24),(0x4b29,0x5154),(0x80fc,0x81a0)]
items=[]
for i in p['instructions']:
 a=int(i['address'].split(':')[1],16)
 if any(lo<=a<hi for lo,hi in ranges):
  b=bytes.fromhex(i['bytes'])
  assert fw[a:a+len(b)]==b,(i['address'],'mismatch')
  items.append(i)
(root/'selected-assembly.txt').write_text('\n'.join(f"{i['address']} {i['bytes']:12} {i['text']}" for i in items))
result={'firmware_sha256':hashlib.sha256(fw).hexdigest(),'export_sha256':hashlib.sha256(export_path.read_bytes()).hexdigest(),'selected_instruction_count':len(items),'byte_mismatches':0,'method':'Byte verification of saved direct-Ghidra export; not execution or proof of hardware register semantics. Raw file offsets assumed CODE addresses.'}
(root/'verification.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result,indent=2))
