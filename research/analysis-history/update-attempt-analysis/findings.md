# Update attempt and fix2

Input resolved locally to C:\Users\owner\Desktop\update-ones. The user path appears inside the laptop logs. Raw input files are preserved in evidence/.

The update session at 2026-10-12 12:40 UTC ends with: "Selected HID interface does not advertise 64-byte feature reports (code 24)."

The normal keyboard 048D:C100 is present with problem zero on port 9. Its selected collection FF89:0010 advertises 17-byte feature reports. Source inspection confirms fix1 rejected this collection before sending feature reports. The log contains no HID TX/RX records. No boot-mode handoff, backup reads, erase, or firmware write occurred in this attempt. The zero-byte backup is a placeholder created before transport open, not a backup. This conclusion does not establish what happened in historical Lenovo updater attempts.

fix1 incorrectly applied the bootloader's 64-byte requirement to normal-mode communication. Firmware descriptor analysis independently identified report 5A with 16 payload bytes, 17 total. Microsoft specifies the API buffer length using HIDP_CAPS.FeatureReportByteLength:
https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/hidsdi/nf-hidsdi-hidd_setfeature
https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/hidsdi/nf-hidsdi-hidd_getfeature

fix2 passes the validated mode-specific length through the feature callback and Windows APIs. It checks payload bounds and enforces normal report ID 5A versus boot report ID zero. Required profiles: normal 048D:C100 / FF89:0010 / 17 bytes; boot 048D:89DB / FF89:00DB / 64 bytes. Physical identity, chip verification, and backup-before-erase checks remain. Bootloader capabilities have not yet been observed on this laptop; unsupported capabilities remain a stop condition.

Combined case: Windows and Mint fail initial USB enumeration on internal port 9 in the failed state, while working Windows captures show normal enumeration. Forced power-off restores boot-menu input; normal Windows shutdown can leave it broken in F12. Original firmware update success remains unconfirmed. This attempt identifies a reconstruction bug but provides no flash contents.

Original fix1 source/releases are preserved. Firmware 44 is unchanged. fix2 addresses the observed updater rejection, not a proven keyboard startup repair. Offline validation is recorded in ../fix2/evidence/fix2-build-log.txt and the release manifest; hardware validation remains outstanding.
