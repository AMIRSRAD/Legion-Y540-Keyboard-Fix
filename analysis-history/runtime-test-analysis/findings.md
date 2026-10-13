# First fix1 hardware test: result and next evidence

All eight supplied logs in `Desktop/workingstate` and `Desktop/nonworking` were read in full. Five inventories contain 34 records each (170 records compared). File identities, complete parsed inventories, events and field-level differences are preserved in `comparison.json`. These are logs from the affected laptop supplied by the owner; no hardware operation was run on the development computer.

**Result: fix1's tested USB devnode restart did not produce a recovered keyboard device.** Windows accepted the operation, but both the immediate after-state and a later diagnosis still show present descriptor failure/problem43 and absent normal C100/HID devices. No firmware update action appears in the supplied logs. This does not invalidate the corrected updater failure paths, but those corrections are not a demonstrated repair of the existing startup fault.

## Captured comparison

| Observation | Nonworking capture | Working capture |
|---|---|---|
| Measured AC line | Connected, battery95% | Battery,89% |
| Owner-selected startup power | AC connected | Battery only |
| Physical normal ITE USB device | Nonpresent; CM/presence result0xD | Present/problem0,048D:C100,REV0044 |
| Five C100 HID collections | All nonpresent | All present/problem0 |
| Descriptor-failure placeholder | Present/problem43 | Nonpresent |
| Boot device048D:89DB | No record | No record |
| Intel root hub/controller | Present/problem0 | Present/problem0 |

Normal instance: `USB\VID_048D&PID_C100\5&1F456139&0&9`. Failed instance: `USB\VID_0000&PID_0002\5&1F456139&0&9`, hardware ID `USB\DEVICE_DESCRIPTOR_FAILURE`. Parent: `USB\ROOT_HUB30\4&15ED8360&0&0`; display location `Port_#0009.Hub_#0002`.

Unlike the earlier case captures, these logs include location paths. The normal device and failed placeholder share the exact ACPI path:

```text
ACPI(_SB_)#ACPI(PCI0)#ACPI(XHC_)#ACPI(RHUB)#ACPI(HS09)
```

The normal record additionally contains `PCIROOT(0)#PCI(1400)#USBROOT(0)#USB(9)`. The failed placeholder lacks that additional path. The common ACPI path strengthens the physical-port correlation; it is not authentication of a firmware command interface.

Nine records differ between the initial failed and working inventories: the two physical USB records, five HID children, Intel controller and root hub. The latter two differ only by status bit0x2000, defined as `DN_DISABLEABLE` in the installed MinGW-w64 cfg.h; neither acquires a nonzero problem code. All other recorded properties are unchanged. A healthy parent does not prove its individual port or downstream device is electrically healthy.

## Recovery timeline

Raw source timestamps are UTC; local times below use Asia/Tehran (UTC+03:30),12 October2026.

| Local time | Event |
|---|---|
| 16:56:58 | Before-restart inventory: failed descriptor,Code43 |
| 16:57:24 | One nonpersistent devnode restart attempted; Windows accepted it |
| 16:57:27 | After-state still failed; no normal/boot device |
| 16:57:49 | Later independent diagnosis still failed |
| 17:02:36 | Working-state inventory on battery: normal device and five HID collections present |

Every recorded device state/property is identical before/after the restart, and between the after-state and later failed diagnosis. This establishes no captured recovery; it does not establish whether a transient unobserved change occurred. An accepted configuration-manager operation alone does not prove the electrical keyboard supply was interrupted or identify which USB transfers were retried.

The working capture is from a later startup, not a successful result of the logged USB restart. There is no erase/program/readback log or firmware backup in these supplied files. REV0044 is an enumerated version field, not a complete flash-integrity measurement.

## Owner observations supplied after review

These remain owner reports, separate from instrumented log facts:

- After successful battery startup, connecting AC without restarting leaves typing working.
- From the failed state, Windows Restart while on battery does not restore typing.
- Forced shutdown followed by a battery-powered start with the laptop power button restores typing.
- Previously reported: AC-connected startup fails; typing works in BIOS and Fn functions survive.

Battery power alone is therefore not the reported recovery condition. The power-off/start sequence matters. These observations suggest a startup/initialization or retained-state dependency rather than an immediate failure whenever AC is attached. They do not identify the state-holding component, prove an actual rail power cycle, distinguish forced-off reset from off-duration, or establish firmware versus platform/host responsibility. A Windows restart has not been shown to break an already-working keyboard; the owner says it fails to recover an already-failed one.

## Important interpretation limits

Nonpresent historical records show problem0 with CM0xD because the status query did not obtain a live devnode. That problem0 is not a healthy-device result. Cached descriptions/IDs on those records do not mean the device responded during the failed capture. Empty service data on the descriptor placeholder does not prove that installing a keyboard driver will fix enumeration.

No USB enumeration control-transfer trace, actual power-rail measurement or execution trace of keyboard firmware is present. Firmware USB initialization, BIOS/EC handoff, Windows host/controller behavior and electrical power sequencing remain hypotheses. The data does not justify a random firmware patch or claiming a permanent repair.

## Next technical step

Capture USB enumeration/reset events to learn whether the attempted recovery causes fresh descriptor requests and which stage fails. Microsoft documents [USB ETW capture with Logman](https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/how-to-capture-a-usb-event-trace). Its `Default`, `StateMachine` and `HeadersBusTrace` keyword categories can supply state transitions and transfer headers without requesting transfer payloads. A post-startup recording cannot retroactively capture the initial boot failure; startup/handoff investigation requires an appropriately configured boot trace if no runtime reproduction is available.

A separately implemented exact-port cycle is a possible next recovery experiment; Microsoft documents [IOCTL_USB_HUB_CYCLE_PORT](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/usbioctl/ni-usbioctl-ioctl_usb_hub_cycle_port). It requires fresh hub-interface/port validation and explicit action, and cannot be assumed to interrupt a motherboard-wired supply or repair this keyboard. Do not infer success from an API result. No such action or boot tracing was installed or performed in this review.

Original source, fix1 source, firmware inputs and all release packages remain unchanged by this analysis.
