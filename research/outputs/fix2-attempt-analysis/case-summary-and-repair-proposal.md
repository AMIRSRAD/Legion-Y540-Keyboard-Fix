# Consolidated case and proposed repair — 2026-10-12

## Latest owner result after fix2

Keyboard continued typing immediately after the completed update. Ordinary Windows Restart still causes failure. Ordinary Windows Shut down followed by power-on still causes failure. Holding the power button for approximately ten seconds to force full power-off, then powering on, still restores the working state. The successful flash did not repair the startup symptom.

## Established evidence

- fix1 had a reconstruction bug: it rejected the normal-mode 17-byte feature collection by requiring 64 bytes. It stopped before feature I/O, erase or programming.
- fix2 corrects mode-specific report sizing. The supplied hardware log shows bootloader entry, chip response 8176, two matching backup reads, one erase, programming, full matching readback and an accepted reset command.
- The saved 55,296-byte pre-erase backup and both independently reconstructed pre-erase reads match original firmware 44 byte for byte. The post-write read also matches. Thus reinstalling replaced the measured update region with identical contents.
- This is strong evidence against missing/corrupted bytes in addresses 0000–D7FF at the time of this test. It does not establish the history of earlier installations, integrity of regions outside that range, or correctness of firmware 44's logic.
- Windows and Linux fail initial USB enumeration on the keyboard's controller/port. Mint reports descriptor read errors and address-setup failures, not merely missing keystrokes from a healthy HID interface.
- The keyboard can already be unusable in F12 following ordinary Windows shutdown. Forced power-off restores boot-menu operation. Mint can then fail during boot despite keyboard operation in its selector.
- Fast Startup is off. i8042prt was running in both working and failed Windows states; changing its startup setting did not repair the symptom.

## Working diagnosis, with limits

A persistent initialization/reset/power-state failure in the internal keyboard USB path is the best current working hypothesis. Possible locations include the keyboard controller, embedded-controller handling of its power/reset, physical power/USB circuitry, and host/device interaction. No evidence yet isolates one of those components. The forced-off recovery is not proof of exactly which rail, reset signal or register changes.

The previously found vendor descriptor response-length flaw has no demonstrated causal connection to these initial standard descriptor failures. Patching it alone is not an evidence-backed repair for this case.

## Proposed repair direction

Target recovery and reinitialization of the keyboard USB controller across ordinary reset/power transitions, rather than repeating an identical firmware install.

Software path: trace firmware 44's USB bus-reset handling, endpoint-zero initialization and low-power exit paths. A candidate patch would make relevant controller/endpoint state reliably reinitialize on the transition that fails. This is a design hypothesis, not an identified instruction-level fix. Applicable register semantics and the failing transition must be established before selecting bytes to patch. Current evidence is insufficient to ship a repair image.

Board/EC path: determine whether ordinary restart/shutdown and forced power-off produce different keyboard supply/reset behavior. The reference boardview contains AG_WRST# and AGKB_PWR_EN# strings, but connectivity, polarity, timing and the affected board revision are not verified. A qualified technician would first establish the actual circuit, then compare transitions. This could support a power/reset sequencing repair if a fault is demonstrated. No pins should be shorted or EC registers guessed from net names.

An ordinary updater cannot communicate through the current HID interface while USB enumeration is failing. Sending additional normal HID commands or repeating device-manager retry does not establish a real keyboard power reset. A host-side recovery tool becomes justified only if an accessible, verified reset mechanism is identified.

## Current recommendation

Do not reflash identical 44 again or treat fix2 as a startup repair. Preserve the backup and completed update log. Continue targeted controller reset/power investigation using the existing evidence; no repeat of the same Diagnose, Mint inventory, or flash test is needed. The existing forced-off procedure is a recovery workaround, not a repair; save work before using it.

Success criterion for any proposed fix: typing after ordinary restart and shutdown/power-on, followed by repeated confirmation across AC/battery conditions and normal USB enumeration. An accepted reset command or successful flash alone does not meet that criterion.
