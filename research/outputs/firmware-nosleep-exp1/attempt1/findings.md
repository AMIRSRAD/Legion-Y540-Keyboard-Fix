# Experimental image attempt1 — 2026-10-13

The selected image validated as55296bytes, checksum5642, consistent with experiment1 (checksum alone is not a SHA-256 identity check).

The normal device was healthy on internalport9. Normal17-byte report5A handshake and boot-handoff command0900 succeeded. After roughly7seconds, boot device048D:89DB / FF89:00DB / feature64 was enumerated and opened on the same port.

The first bootloader command,070020F003 (chip qualification), failed HidD_SetFeature with Win32error31 on all10attempts over approximately1second. No successful boot command, backup read, erase, programming, or final reset appears. Source control flow gates boot_program behind successful chip qualification. The backup placeholder is0bytes.

Therefore the experimental image was NOT installed by this session and no erase/write was reached. Earlier verified stock44 remains the last known flash contents; this failed session supplies no new readback. The device may remain in boot mode after the failed handoff attempt; later enumeration/typing state is unknown.

Win32error31 is generic and does not establish a firmware checksum rejection, a bad experimental patch, or a specific readiness/timing cause. The payload bytes were not sent to flash at this stage. The same chip-check transaction succeeded in the prior stock44 update; the reason for this difference is unresolved.

Do not interpret post-attempt restart behavior as an experimental firmware result. Do not repeat flashing blindly. First establish whether normal keyboard input returns using the previously known forced-off recovery, saving work with an external keyboard before any forced-off action. If it does not recover, stop further firmware operations and report the observed state.

Owner follow-up: forced-off recovery restored the working keyboard state. No further flash occurred in that confirmation. fix3 separately addresses bounded qualification retries without changing the experimental firmware bytes.
