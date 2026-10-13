"""Build one explicit experimental patch. Never writes the original image."""
from pathlib import Path
import hashlib,json,shutil
root=Path(__file__).resolve().parent
source=root/'44-stock-restore.bin'
if not source.exists(): source=root.parent/'fix2/samples/44.bin'
original=source.read_bytes()
expected='3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359'
assert hashlib.sha256(original).hexdigest()==expected and len(original)==0xd800
assert original[0x4c78:0x4c7b]==bytes.fromhex('ef6066')
assert original[0x4ce1]==0x22
assert original[0x7ffe:0x8000]==bytes.fromhex('5622')
patched=bytearray(original)
# 8051 JZ rel -> SJMP rel; unchanged displacement and instruction length.
patched[0x4c79]=0x80
def checksum(data):
    return sum(255 if i in (0x7ffe,0x7fff) else data[i] for i in range(0x400,0xd800))&0xffff
assert checksum(original)==0x5622
new_sum=checksum(patched)
patched[0x7ffe:0x8000]=new_sum.to_bytes(2,'big')
assert new_sum==0x5642 and checksum(patched)==int.from_bytes(patched[0x7ffe:0x8000],'big')
differences=[{'offset':hex(i),'before':f'{a:02X}','after':f'{b:02X}'} for i,(a,b) in enumerate(zip(original,patched)) if a!=b]
assert differences==[{'offset':'0x4c79','before':'60','after':'80'},{'offset':'0x7fff','before':'22','after':'42'}]
assert (0x4c79+2+patched[0x4c7a])==0x4ce1
# Exhaustive local branch test; no claim of MCU/hardware emulation.
for accumulator in range(256):
    destination=0x4c79+2+patched[0x4c7a]
    assert destination==0x4ce1 and patched[destination]==0x22
    if accumulator==0:assert original[0x4c79]==0x60
bundle=root/'portable';bundle.mkdir(exist_ok=True)
(bundle/'44-nosleep-exp1.bin').write_bytes(patched)
(bundle/'44-stock-restore.bin').write_bytes(original)
shutil.copy2(root.parent/'fix2/samples/SHFU.ini',bundle/'SHFU.ini')
manifest={'name':'Y540 firmware44 no-deep-sleep experiment1','status':'Experimental; hardware untested; not a confirmed repair',
 'scope':'Bypass entry through4BC4 at final existing sleep gate; does not disable every possible low-power mechanism',
 'original_sha256':expected,'patched_sha256':hashlib.sha256(patched).hexdigest(),'bytes':len(patched),
 'differences':differences,'checksum':{'original':'5622','patched':'5642','range':'0400-D800 exclusive','slots':'7FFE(high),7FFF(low)'},
 'branch':{'address':'4C79','original':'JZ 4CE1','patched':'SJMP 4CE1','target':'4CE1 RET','modeled_accumulator_inputs':256},
 'rollback':'Original image included; requires a usable boot/update interface. Recovery is not guaranteed if modified firmware stops enumeration.',
 'proof_limits':['Static base-zero CODE mapping','No MCU or electrical execution','No guarantee against indirect entry paths','Increased power consumption or changed suspend/wake behavior possible']}
(root/'patch-manifest.json').write_text(json.dumps(manifest,indent=2))
print(json.dumps(manifest,indent=2))
