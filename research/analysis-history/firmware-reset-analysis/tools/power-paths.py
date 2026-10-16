"""Export byte-checked power-path evidence from the retained Ghidra export."""
import hashlib
import json
from pathlib import Path

root = Path(__file__).resolve().parents[2]
blob = (root / 'fix2/samples/44.bin').read_bytes()
data = json.loads((root / 'firmware44-analysis/ghidra-static-inline-aware.json').read_text())
ranges = [(0x100,0x20b),(0x400,0x42c),(0x59d,0x5e4),(0xc33,0xc47),
          (0xe30,0xe97),(0x2200,0x2260),(0x2633,0x267e),(0x26e2,0x2718),
          (0x3185,0x31ff),(0x4bc4,0x4dda),(0x4f65,0x4fa0),(0x510d,0x512d),
          (0x7c4,0x7f1),(0x946,0x966),(0x80e3,0x81a6)]
selected=[]
for ins in data['instructions']:
    addr=int(ins['address'].split(':')[1],16)
    if any(lo<=addr<hi for lo,hi in ranges):
        raw=bytes.fromhex(ins['bytes'])
        assert blob[addr:addr+len(raw)] == raw, ins
        selected.append(ins)
out=Path(__file__).resolve().parents[1]
(out/'power-state-assembly.txt').write_text('\n'.join(f"{i['address']} {i['bytes']:12} {i['text']}" for i in selected))
facts={'input_sha256':hashlib.sha256(blob).hexdigest(),'verified_instructions':len(selected),
       'byte_mismatches':0,'ranges_half_open':[[hex(a),hex(b)] for a,b in ranges],
       'scope':'Static exported instructions, not execution trace or silicon register validation.'}
(out/'power-state-evidence.json').write_text(json.dumps(facts,indent=2))
print(json.dumps(facts,indent=2))
