# Owner findings — 2026-10-12

This addendum records owner observations from the affected Lenovo Y540. These are owner-reported results, not hardware tests performed on the development computer. Earlier reports remain historical records; the corrections below supersede conflicting assumptions.

## Firmware installation history correction

The owner believes firmware 44 has **never successfully installed**. Every remembered attempt produced errors and was associated with the keyboard becoming unusable. Treat any earlier note describing a successful erase/write/read/compare cycle as unconfirmed and contradicted by this correction.

The observed USB revision `0044` does not establish a successful update or firmware integrity. We do not yet know whether the failed attempts stopped before writing or after some writes. An incomplete update remains a possibility, not an established finding.

## Power and boot behavior

- Holding the power button for about 10 seconds to force a complete power-off, then pressing it again, restores keyboard operation in the BIOS and boot menu.
- After a normal Windows shutdown, powering on and entering the F12 boot manager leaves the built-in keyboard unusable **in the boot manager itself**. This does not happen after the forced power-off described above.
- Windows Restart also fails to restore keyboard operation. The owner reports this behavior on both AC and battery.
- Fast Startup is already disabled.
- Earlier working-state tests showed that connecting AC after the keyboard was working did not stop it working.
- Earlier owner observations reported functioning Fn keys during the failure and a working keyboard inside Windows after a forced power-off. These observations should be retained alongside the newer Linux result, rather than assumed to apply to every boot sequence.

## Linux Mint live boot

The owner explicitly confirmed this sequence:

1. Hold the power button for about 10 seconds until fully off.
2. Power on and boot toward the Mint live USB.
3. The built-in keyboard works in the BIOS and Mint boot selector, including the menu offering Mint/compatibility options.
4. The built-in keyboard stops working inside the Mint live desktop.

Mint's message asking to remove the installation medium and press Enter appeared when leaving the live session. That message alone is not evidence of a keyboard or firmware fault.

## Interpretation and limits

Failure in the F12 boot manager after Windows shutdown establishes that, in that sequence, the fault is present before the next operating system loads. Failure inside Mint after a forced power-off also weakens a Windows-only driver explanation.

The results suggest a persistent controller/power state and a failure associated with operating-system initialization or takeover. They do **not** identify the responsible component: keyboard controller firmware, the laptop embedded controller, USB host/controller behavior, or their interaction remain possibilities. The physical power/reset effects of the long power-button hold have not been measured.

Windows captures previously showed USB device-descriptor transaction failures on the keyboard's port. No Linux logs have yet been collected to establish whether Mint experiences the same enumeration failure or instead enumerates the device successfully without receiving input. No causal link between these symptoms and the static firmware audit's vendor-response length flaw has been established.

## Next evidence requested — pending

**Update:** The owner subsequently supplied all three Mint logs. Analysis is complete in `../linux-analysis/findings.md`: Linux repeatedly fails USB enumeration on controller 00:14.0, port 9, with descriptor and address errors. The request below is retained as the historical collection procedure; it is no longer pending.

After forced power-off, boot directly into Mint without entering Windows, reproduce the failed keyboard state, and collect the following using an external keyboard. Keep AC state unchanged during the test.

```bash
mkdir -p ~/Desktop/y540-linux
lsusb > ~/Desktop/y540-linux/usb-devices.txt
lsusb -t > ~/Desktop/y540-linux/usb-tree.txt
sudo journalctl -k -b --no-pager > ~/Desktop/y540-linux/kernel-log.txt
```

Copy the `y540-linux` folder to another USB drive before leaving the live session. These commands collect device inventory and kernel logs; they do not flash or reset the keyboard. The owner plans to perform this collection. Results are pending.

No firmware modification, firmware write, or device reset was performed as part of recording this addendum.
