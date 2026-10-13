import json, hashlib, shutil
from pathlib import Path
from datetime import datetime
from collections import Counter

root = Path.cwd()
work = root / 'work/usb-trace-135023'
out = root / 'outputs/usb-trace-analysis'
out.mkdir(exist_ok=True)
rows = json.loads((work / 'decoded.json').read_text(encoding='utf-8-sig'))
def seconds(row):
    # Compare displayed wall clocks only; tracerpt's rendered +03:29 offset is inconsistent.
    return (datetime.fromisoformat(row['time'][:26]) - datetime.fromisoformat(rows[0]['time'][:26])).total_seconds()
def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()
failures = [r for r in rows if r['provider'].endswith('USB-UCX') and r['id']=='24' and r['data'].get('fid_URB_Hdr_Status')=='0xC0000011']
assert len(rows)==3201 and len(failures)==4
for r in failures:
    d=r['data']
    assert (d['fid_URB_Setup_bRequest'],d['fid_URB_Setup_wValue'],d['fid_URB_Setup_wLength'],d['fid_URB_TransferBufferLength'])==('0x6','0x100','0x40','0x0')
selected_ids = {598,848,849,850,852,875,1817,1818,1819,1821,1844,1923,1924,1925,1927,1950,2057,2058,2059,2061,2084,2101,2103,2210,729,1077,2176,2509}
selected = [dict(r, relative_seconds=round(seconds(r),7)) for r in rows if r['ordinal'] in selected_ids]
source = Path(r'C:\Users\a.saberi\Desktop\recording-20261012T135023471Z.zip')
evidence = {
    'source_zip':str(source),'source_zip_sha256':sha(source),
    'etl_sha256':sha(work/'usb_000001.etl'),
    'events':len(rows),'events_lost':int(rows[0]['data']['EventsLost']),
    'buffers_lost':int(rows[0]['data']['BuffersLost']),
    'provider_counts':dict(Counter(r['provider'] or 'Trace metadata' for r in rows)),
    'schema_errors':[r for r in rows if r['schema_error']],
    'owner_action_report':'Only Diagnose and USB retry; no Device Manager changes or AC connect/disconnect during recording.',
    'time_policy':'Relative seconds computed from displayed event wall clocks; original timestamp strings preserved. Rendered offset +03:29 is inconsistent with journal UTC and expected +03:30; no absolute UTC conversion from those strings.',
    'selected_events':selected,
    'method':'Offline Windows tracerpt XML export and full 3201-event parse; ordinal is zero-based XML event order. Flattened data is a convenience; raw XML remains authoritative for nested/repeated field names.'
}
(out/'evidence.json').write_text(json.dumps(evidence,indent=2),encoding='utf-8')
for name in ['events.xml','decoded.json','summary.txt','capture-journal.txt','machine.json','windows.json']:
    shutil.copyfile(work/name,out/name)
table='\n'.join(f"| {r['ordinal']} | {seconds(r):.6f} | GET_DESCRIPTOR(Device), 64 requested | 0 | 0xC0000011 |" for r in failures)
report=f'''# USB trace: failed keyboard enumeration

The completed recording establishes repeated USB transaction failures while Windows tries to enumerate the keyboard's physical port. It does not establish a permanent repair or identify the defective component.

## Capture and provenance

- Source ZIP SHA-256: `{evidence['source_zip_sha256']}`.
- ETL SHA-256: `{evidence['etl_sha256']}`; size 1,179,648 bytes.
- LENOVO 81SX, Legion Y540-15IRH; Windows 11 Enterprise, build 26200.
- Journal: trace started 13:50:24 UTC, stopped after the 180-second capture window; stop and session deletion completed successfully.
- tracerpt processed 3,201 events and 18 buffers; zero events/buffers lost.
- One decode/schema warning affects the trace metadata PartitionInfoExtensionV2 record (ordinal 1, error 15005). No USB-provider record reports a schema error. The warning is retained; not all metadata decoded completely.
- This was offline analysis on the development computer. No local USB operation, device execution, or firmware write was performed.

## Observed keyboard failure

HUB3 event 60 (ordinal 598) starts enumeration of port 9 at +35.612689 seconds. Four UCX event 24/version 1 completions then record the same standard USB device-descriptor request. The setup packet is `80 06 00 01 00 00 40 00`. Each returns zero bytes and USBD status `0xC0000011` (`USBD_STATUS_XACT_ERROR`); the separate IRP NTSTATUS is `0xC0000001`.

| XML ordinal | Seconds from trace header | Request | Returned bytes | USBD status |
|---|---:|---|---:|---|
{table}

Each failure is followed by HUB3 event 160 (descriptor request failed), event 132 (control-transfer error), and event 75 (descriptor validation failure). Three event 62 retry notices follow the first three attempts. Event 63 at ordinal 2084 reports maximum retries reached, and event 64 at ordinal 2101 reports enumeration failed.

Event 197 at ordinal 2103 explicitly ties enumeration failure to port 9 and PCI controller 00:14.0, Intel 8086:A36D, with USBD `0xC0000011` and NTSTATUS `0xC0000001`. Event 43 at ordinal 2210 exposes the same failed device instance seen in the earlier fix1 logs: `USB\\VID_0000&PID_0002\\5&1f456139&0&9`, described as Unknown USB Device (Device Descriptor Request Failed).

That event also carries 048D:C100/revision 0044 metadata, but its descriptor length/type and USB-device pointer are zero. Those IDs are not evidence of a freshly successful descriptor read; cached identity is a possible explanation. This trace does not measure firmware integrity.

## Other USB activity and action attribution

Port 6 device 30C9:001B undergoes two port-change failures/removals near the keyboard attempts, followed by successful enumeration completions (ordinals 1077 and 2509, NTSTATUS 0). These are a different device; its errors must not be attributed to the keyboard. Successful communication with that device does not prove the keyboard port or its power supply is healthy.

The owner confirms only Diagnose and USB retry were used, without Device Manager operations or AC changes. Reviewing fix1 source shows its retry opens the exact selected instance and calls CM_Disable_DevNode / CM_Enable_DevNode on that instance; there is no explicit parent-hub/controller restart in that path. Nevertheless, the port 6 reconnections are observed and their cause is unknown. A platform/shared effect is a hypothesis, not established causality. Matching fix1 session logs are still needed to correlate API timing, selected instance, and before/after state with this ETW recording.

## Interpretation and limits

Observed: Windows makes fresh attempts at the basic device descriptor and fails before establishing a usable keyboard USB/HID interface. This is stronger evidence than a stale Device Manager entry or a refused software retry. In this recording, the updater's normal HID transport cannot communicate through the failed keyboard device. HID identification tweaks or ignoring the not-found result cannot overcome that enumeration failure.

Inference: the owner's battery cold-start recovery, continued function after subsequently attaching AC, and failure of Windows Restart to recover an already-failed keyboard are consistent with an initialization/retained-state dependency. The trace does not distinguish keyboard firmware, EC/BIOS behavior, a USB power/reset sequence, host-controller behavior, or an electrical fault. It does not prove permanent damage, prove an electrical rail power cycle occurred during retry, or prove a firmware patch would repair previously affected laptops.

This recording starts after Windows boot. It cannot show the original AC-startup transition into failure. The provider configuration includes headers/state events, not USB transfer payloads. Zero-byte failed reads give no malformed descriptor content to repair. No firmware-change conclusion is warranted from this capture.

## Next useful evidence

1. Preserve the existing failed trace. Supply the fix1 logs generated during this recording (13:50–13:53 UTC, approximately 17:20–17:23 Tehran time), particularly the USB retry session and its selected device. No repeat failed-state capture is needed yet.
2. Obtain a comparison recording after the owner's known successful battery cold start: start the same capture kit while typing works, Diagnose, use USB retry once, wait ten seconds, Diagnose again, then end capture. Record whether typing survives and whether AC was attached after startup; do not change AC during this comparison. This comparison deliberately retries the working keyboard, so it may temporarily interrupt typing; keep the already-used external input available. It writes no firmware. Its purpose is to test whether port 6 reconnections also happen in the healthy state and compare successful descriptor transfers with failed ones.
3. If healthy-state retry itself loses typing or causes wider device loss, stop retry experiments and preserve that trace. A startup trace or OS comparison can then address the remaining initialization boundary. Do not treat further flashing as the established next repair: this trace provides no new firmware bytes or validated patch.

## Decoder and references

Raw XML and all parsed event records are included beside this report. Event ordinals are zero-based XML order, not Windows event IDs. Relative timings use displayed wall-clock differences: tracerpt renders an inconsistent `+03:29` offset, so those strings were not blindly converted to UTC. Journal times remain the source for the capture's UTC window.

The numeric USBD mapping was verified in the installed MinGW-w64 usb.h (`USBD_STATUS_XACT_ERROR = 0xc0000011`). USBD and NTSTATUS are separate status namespaces.

- [Microsoft: Recovering from USB pipe errors](https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/how-to-recover-from-usb-pipe-errors) describes transaction errors and recovery mechanisms; it does not identify this laptop's root cause.
- [Microsoft: Troubleshooting an unknown USB device using ETW](https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/case-study--troubleshooting-an-unknown-usb-device-by-using-etw-and-netmon) provides the enumeration-trace interpretation method.
'''
(out/'findings.md').write_text(report,encoding='utf-8')
print(json.dumps({'output':str(out),'events':len(rows),'failures':len(failures),'failure_seconds':[round(seconds(r),6) for r in failures],'source_sha256':sha(source)},indent=2))
