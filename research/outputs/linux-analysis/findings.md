# Mint live-session findings

Analyzed the three files supplied in `C:\Users\a.saberi\Desktop\y540-linux`. Exact copies are in `evidence/`, with SHA-256 hashes in `hashes.json`. No device operations were performed on the development computer.

## Result

Linux reproduces failure during USB enumeration on internal port 9. This is the same failure stage and controller/port location implicated by the Windows recordings. It is not merely a successfully enumerated HID keyboard failing to deliver keystrokes.

## Evidence

- Kernel: Linux 6.14.0-37-generic, x86-64 (kernel-log.txt line 1).
- Intel PCI controller `0000:00:14.0` owns USB bus 1 (lines 785–787); failing device path is `1-9`.
- Four enumeration sequences fail: lines 988–1041, 1278–1296, 1297–1315, and 1321–1338.
- Across these sequences: 16 `device descriptor read/64, error -71` messages, eight address-acceptance failures, four `attempt power cycle` messages, and four final `unable to enumerate USB device` messages.
- Linux also reports `Device not responding to setup address` and subsequent xHCI context warnings. These warnings alone do not establish a host-controller defect.
- `048d:c100` is absent from the supplied lsusb inventory. Port 9 is absent from the enumerated USB tree. Because Linux never identifies this device, associating it with the keyboard relies on the previously established controller/port mapping, not a successful Linux VID/PID read.
- Camera, Bluetooth, live USB storage, and external wireless receiver enumerate. The receiver is `3554:fa09` on port 2 and must not be mistaken for the internal keyboard.
- The kernel registers an `AT Translated Set 2 keyboard` on i8042 (line 843). Registration does not demonstrate working keys or identify the role of that interface.
- Camera port 6 resets occur near two later port-9 retry sequences (lines 1285 and 1304). Cause and relationship are unproven; do not infer an operator action from these lines.
- Early journal messages share a displayed timestamp. No timezone conversion or precise duration for the initial enumeration sequence is inferred from those timestamps.

Linux error `-71` is EPROTO. The kernel USB documentation explains that this class of error can cover protocol faults or a missing response, and can arise from devices (including firmware) or physical connections. It does not identify a unique failed component: https://www.kernel.org/doc/html/v6.2/driver-api/usb/error-codes.html

The logged attempt to power-cycle a port is not proof that the keyboard's physical supply was removed, nor that it reproduces the electrical effects of holding the laptop power button.

## Combined interpretation

Owner reports establish that after a forced power-off the keyboard works in BIOS/Mint's selector but fails in Mint. After Windows shutdown, it can already fail in the F12 boot manager. The Linux logs now demonstrate an early USB communication failure in an independent operating system, consistent with Windows descriptor-transaction failures on the same port.

A Windows-only keyboard driver explanation is insufficient. Keyboard controller firmware/state, embedded-controller power/reset handling, the internal USB connection, and host/device interaction remain candidates. The data does not prove corrupt flash or a successful prior firmware update. USB revision 0044 from earlier working Windows captures is not an integrity check.

The static firmware audit's vendor-response length candidate has no demonstrated causal link: these failures concern initial standard USB enumeration, before normal HID or vendor update communication is established. The rebuilt updater cannot reach its normal HID update interface while enumeration fails. Reflashing is not yet an evidence-backed repair.

## Next investigation

Prioritize locating the original Lenovo updater's failure logs to determine whether an erase/write was ever reached. If unavailable, evaluate a controlled flash readback from the known working Windows state against the original image. That requires reviewing the device's bootloader transition first: readback can change device mode and is not equivalent to passive diagnostics. No readback or firmware write is authorized or performed by this report.

Linux collection requested in the owner-findings addendum is now complete. Additional copies of the same failed-state inventory are unnecessary unless the boot sequence or test condition changes.
