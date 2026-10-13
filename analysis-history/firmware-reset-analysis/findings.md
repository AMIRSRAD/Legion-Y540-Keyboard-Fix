# Targeted firmware reset investigation — result

The USB-reset and power-transition audit is complete within the saved 8051 static-analysis scope. It did not identify a defensible instruction-level repair for the owner's startup failure. No modified firmware image was produced. This is an unresolved repair, not a claim that firmware 44 is correct.

## Evidence reused and checked

Original firmware 44 and the verified pre/post-update readbacks match in the measured 55,296-byte region. Existing direct-Ghidra exports were reused because REA's raw-image route had already rejected this artifact; no new REA Evidence ID is claimed. Selected assembly was checked against the original bytes: parent verification 1,528 instructions, USB audit 991, power audit 952, all zero mismatches. These are overlapping sets, not additive coverage. A bounded reset-branch model passed five assertions; it is not a microcontroller or hardware simulator.

## Findings that change the repair hypothesis

1. Reset handling exists: the event path at 35DD/39DA clears the device-address-register candidate, initializes endpoint registers, and clears protocol state. Merely adding an address reset duplicates existing behavior.
2. The main USB service path can bypass reset inspection when two low-power state flags are set. However, the caller schedules wake cleanup through 270A/510D, and a separate wake path at 4F75 handles the same reset event candidate. The proposed permanently stuck flag is not established. Moving reset handling ahead of these guards without understanding clock/power prerequisites could be incorrect.
3. Sleep entry and return are traceable: 4BC4 -> 813C -> 264B, followed by register restoration, timer restart, and scheduled cleanup. Exact ITE hardware semantics and actual execution on the failed laptop remain unknown.
4. The GET_CONFIGURATION value at context+0E is not cleared by the examined reset cleanup. This is a narrow stale-state candidate with unresolved indirect-write coverage, not an explanation for the initial descriptor failures. The standard descriptor path does not gate on this value.

Details and exact addresses: usb-reset.md and power-state.md. Raw selected assembly and verification receipts accompany them.

## Repair boundary and concrete next evidence

The existing host traces locate failure at initial USB communication but cannot show whether the MCU is asleep, its reset handler executes, its clock/power is valid, or its bus responses are electrically malformed. More of the same inventory logs will not distinguish these conditions.

A qualified board-level investigation should compare two sequences on the affected board: forced-off recovery and an ordinary reboot that fails. Establish the actual keyboard controller and circuit first. Measure its supply and reset behavior through the transition and, if available, capture the full-speed USB reset/setup/response exchange. The supplied reference boardview has AG_WRST# and AGKB_PWR_EN# strings, but they are leads only; pin connections, polarity and actual-board compatibility are unverified. Do not short pins or guess embedded-controller writes.

- If supply/reset sequencing differs improperly and recreating the correct physical sequence restores enumeration, investigate board/EC sequencing before modifying keyboard firmware.
- If power/reset are verified correct but the device stops answering USB after reset, obtain applicable ITE register documentation or internal state/debug evidence to test the identified sleep/reset branches.
- If signaling is malformed, investigate the physical USB path as well as controller behavior; a host EPROTO result alone cannot distinguish them.

The BIOS EC-update history and other flash/ROM regions remain outside this keyboard payload audit. Do not infer that changing BIOS versions or replacing a keyboard is a demonstrated repair.

## Current status

fix2 repairs the demonstrated updater transport defect and has one successful logged hardware programming sequence. It does not repair the startup symptom. Do not repeat an identical flash. Preserve the original image, complete backup, and logs. The known forced-off procedure remains a workaround after saving work, not the proposed final solution.

Open checklist: reset handler located (answered); power/wake chain located (answered); candidate state omissions assessed (partial); actual failing state and hardware register semantics (unresolved); validated firmware repair (unresolved).
