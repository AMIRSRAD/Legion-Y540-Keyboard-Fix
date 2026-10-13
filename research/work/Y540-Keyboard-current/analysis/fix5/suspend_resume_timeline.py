"""Extract the boot-mode (048D:89DB) enumerate -> idle -> suspend -> resume -> first-transfer
timeline from the fix4 final ETW recording. Read-only; takes decoded.json from
outputs/fix4-final-analysis. Usage: python -I suspend_resume_timeline.py DECODED_JSON [OUT_TXT]
"""
import json, sys

decoded = json.load(open(sys.argv[1], encoding='utf-8'))
out = []

def short(prov):
    return prov.replace('Microsoft-Windows-USB-', '')

# 1. find the boot device by its device-descriptor event (VID_048D&PID_89DB)
boot_dev = None
for e in decoded:
    d = e.get('data', {})
    if short(e['provider'].get('Name', '')) == 'USBHUB3' and e['id'] == '43' and '89DB' in d.get('fid_DeviceInterfacePath', '').upper():
        boot_dev = d.get('fid_UsbDevice')
        out.append(f"{e['ordinal']:>5} {e['time'][11:26]} HUB3 43  boot device bound: {d['fid_DeviceInterfacePath']}  port={d.get('fid_PortNumber')}  UsbDevice={boot_dev}")
        t_enum = e['ordinal']
        break
assert boot_dev, 'boot device not found in trace'

NAMES = {'51': 'D0 (resume) requested', '52': 'D0 (resume) completed', '53': 'low-power (suspend) requested',
         '54': 'low-power (suspend) completed', '96': 'idle-suspend path entered', '97': 'idle request completed/cancelled', '98': 'idle-suspend path continued'}
for e in decoded:
    if e['ordinal'] < t_enum:
        continue
    d = e.get('data', {})
    p = short(e['provider'].get('Name', ''))
    if p == 'USBHUB3' and e['id'] in NAMES and (d.get('fid_UsbDevice') == boot_dev or e['id'] in ('96', '98', '97')):
        extra = ' '.join(f"{k.replace('fid_', '')}={v}" for k, v in d.items() if k in ('fid_TargetState', 'fid_NtStatus'))
        out.append(f"{e['ordinal']:>5} {e['time'][11:26]} HUB3 {e['id']:<3} {NAMES[e['id']]} {extra}")
    elif p == 'USBHUB3' and e['id'] == '100' and d.get('fid_PortNumber') == '9':
        out.append(f"{e['ordinal']:>5} {e['time'][11:26]} HUB3 100 port 9 status={d['fid_PortStatus']} change={d['fid_PortChange']}  (change 0x4 = suspend/resume change)")
    elif p == 'UCX' and e['id'] == '21' and d.get('fid_UsbDevice') == boot_dev:
        s = (d['fid_URB_Setup_bmRequestType'], d['fid_URB_Setup_bRequest'], d['fid_URB_Setup_wValue'], d['fid_URB_Setup_wLength'])
        out.append(f"{e['ordinal']:>5} {e['time'][11:26]} UCX control completion setup={','.join(s)} status={d['fid_URB_Hdr_Status']} bytes={d['fid_URB_TransferBufferLength']}")

# Keep the first 12 failures only, summarise the rest.
fail = [l for l in out if 'status=0xC0000011' in l]
keep = []
seen_fail = 0
for l in out:
    if 'status=0xC0000011' in l:
        seen_fail += 1
        if seen_fail > 4:
            continue
    keep.append(l)
keep.append(f"... {len(fail)} control transfers on this device completed with USBD 0xC0000011 in total; none succeeded after the resume.")
text = '\n'.join(keep)
print(text)
if len(sys.argv) > 2:
    open(sys.argv[2], 'w', encoding='utf-8').write(text + '\n')
