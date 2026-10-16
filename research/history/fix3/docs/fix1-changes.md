# fix1 implementation and evidence

Baseline commit: `9904e54eb613679c96de074f3b4abb0b6c4e34ae` in the separately preserved `y540-research`. Original source hashes: `evidence/baseline-preservation.json`. Vendor binaries, firmware44 and BIOS packages are not patched.

## Case diagnosis

Both complete snapshots and all supplied root notes were read. Working C100 and failed descriptor nodes share recorded parent/port/suffix. Normal HID collections become historical/nonpresent in the failed snapshot; no boot89DB node is recorded. This establishes an enumeration failure before normal HID input, without identifying the electrical/platform/firmware cause. Owner-reported BIOS/Fn/battery behavior and previous successful flash comparison remain separate from snapshot facts. See `case-evidence.md` and `evidence/case-comparison.json`.

Microsoft's [USB troubleshooting case study](https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/case-study--troubleshooting-an-unknown-usb-device-by-using-etw-and-netmon) supports interpreting unknown USB descriptor failures as enumeration failures; it does not identify a fault in this keyboard's firmware.

## Corrected updater paths

| Change | Evidence or rationale | Offline verification |
|---|---|---|
| Restore custom mode after failed handshake/handoff | `HidCustomCmdInit`, VA `0x40A280`, REA `ev_fd5cef455511f38958e586f0c63ecf627ff68d3d1ca88e0a045f3270e297dd99`: key toggle with report5A, up to two attempts | Initial-on/off, failed reads/09/cleanup; primary error retained |
| Remove guessed D1 response-echo requirement | `cmd_read_from_flash`, VA `0x40AA50`, REA `ev_e5ac5178d378672969e09416dbbbcda0173562cb5834abefa27305664b20cfa3`: data copied from payload+5 | Full flash with absent D1 echo |
| Require durable backup before erase | New protection | Two matching full reads; new file only; write+flush; unavailable/existing file/read failure/inconsistent reads stop before C2 |
| Remove final-failure erase/reset | Additional erase after exhausting retries has no next write | Exhausted comparison failures cause no final extra C2 or C4 |
| Correlate boot to normal USB topology | New identity protection | Parent/port/path fixtures; native health gates compiled, hardware-unqualified |
| Require known chip profile | Zero previously bypassed chip qualification | Zero/unknown IDs fail before feature I/O |
| Serialize device changes | Named Windows mutex across update and recovery | Code review; no hardware concurrency test |

Health is revalidated before erase, commit and verified reset. Failed handoff attempts normal-mode cleanup. After confirmed boot handoff, errors do not blindly reset. Backups are evidence/potential recovery inputs; automatic backup restoration is not implemented.

Deterministic padding and boot09's zero second byte differ from undefined original contents and need physical qualification. Broader ITE modes, parameter-only writes, docking and TVSU wrapper automation are unsupported. Unchanged44 cannot establish a fix to internal firmware USB initialization.

## Separate USB recovery experiment

The metadata collector includes historical entries, missing-property markers and current AC status without feature reports. Optional restart re-reads exact current identity. It accepts an identified physical ITE keyboard or the tightly bounded descriptor-failure candidate from this case, excludes hubs/controllers, and refuses ambiguity. [CM_Disable_DevNode](https://learn.microsoft.com/en-us/windows/win32/api/cfgmgr32/nf-cfgmgr32-cm_disable_devnode) is used without `CM_DISABLE_PERSIST`, followed immediately by enable with bounded retries. Failed enable is reported explicitly. Permissions are not bypassed and elevation is not automatic.

No driver package, forced class driver, BIOS or power-policy change is performed. The after-state is captured after a bounded wait; actual typing must be observed by the owner. A permanent cure is unresolved until runtime evidence supports it.

## Qualification boundary

Compilation, file fixtures, protocol emulation and hidden controls are verified. No live inventory, feature command, device restart, flash or vendor updater execution was performed during fix1 development. GUI visual layout and real timing remain unverified. Next evidence: paired AC-failed/battery-working logs, typing result after optional targeted restart, and behavior on the next complete AC startup.
