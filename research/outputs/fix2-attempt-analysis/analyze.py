from pathlib import Path
import re, hashlib, json
root=Path(__file__).resolve().parent
log=next((root/'evidence').glob('*-2.log'))
fw=(root.parent/'fix2/samples/44.bin').read_bytes()
backup=next((root/'evidence').glob('*.bin')).read_bytes()
passes=[]; data=bytearray(); commands={}; pending=None
for line in log.read_text().splitlines():
    m=re.search(r'HID (TX|RX) attempt=(\d+) success=(\d+).*report64=([0-9A-F]+)',line)
    if not m: continue
    direction,attempt,success,h=m.groups()
    assert success=='1',line
    b=bytes.fromhex(h)
    if direction=='TX' and b[0]==0:
        commands[f'{b[1]:02X}']=commands.get(f'{b[1]:02X}',0)+1
        pending=b if b[1]==0xd1 else None
    if direction=='RX' and b[:2]==b'\x00\xd1':
        assert pending and pending[:6]==b[:6]
        addr=int.from_bytes(b[2:5],'little'); n=b[5]
        assert addr==len(data) and 0<n<=56
        data.extend(b[6:6+n]);pending=None
        if len(data)==len(fw):
            passes.append(bytes(data));data.clear()
assert len(passes)==3 and not data
sha=lambda b:hashlib.sha256(b).hexdigest()
result={'bytes':len(fw),'original_sha256':sha(fw),'backup_sha256':sha(backup),
 'backup_matches_original':backup==fw,'read_passes':[{'pass':i+1,'sha256':sha(p),'matches_original':p==fw,'matches_backup':p==backup} for i,p in enumerate(passes)],
 'successful_boot_command_counts':commands,
 'inputs':{p.name:{'bytes':p.stat().st_size,'sha256':sha(p.read_bytes())} for p in (root/'evidence').iterdir()}}
(root/'verification.json').write_text(json.dumps(result,indent=2))
print(json.dumps({k:v for k,v in result.items() if k!='inputs'},indent=2))
