# Final fix4 result — 2026-10-13

Fix4 did not install the experimental firmware. It found the keyboard, switched it into bootloader/update mode, and stopped when every first chip-query transfer failed. No flash erase or firmware write occurred. The zero-byte before-flash file is an unfilled backup placeholder, not a successful backup.

## Evidence

- Source: final-recording-20261013T050036127Z.zip, supplied by the owner.
- Journal records a successfully started and stopped USB trace, approximately 05:00:37–05:01:47 UTC.
- tracerpt decoded 3,100 events in 19 buffers, zero events and buffers lost. One schema warning affects trace metadata record 1; no USB record has a processing/schema error.
- Bootloader USB descriptor identifies VID 048D, PID 89DB. HUB3 event ordinal 2067 binds USB device pointer 0x1AF1065D33E8 to physical port 9 and the expected device instance.
- The updater opened the bound bootloader with requested read/write access 0xC0000000. This change did not resolve the failure.
- All 120 chip-query SET_REPORT completion records on that same device return USBD 0xC0000011 (USBD_STATUS_XACT_ERROR), IRP NTSTATUS 0xC0000001, and zero transferred bytes. These match the 12 readiness rounds with 10 failed application attempts each and error 31.
- USB setup is 21 09 00 03 00 00 3F 00: feature report ID 0, 63 on-wire bytes. The application passes a 64-byte Windows HID buffer beginning with report ID 0. Record both lengths for future protocol comparison; the length difference alone is not proof of a bug.
- Update log ends at 05:01:35.128Z explicitly before erase/write. Experimental image checksum preflight succeeded, but no image contents were written.
- The numeric USBD transaction-error mapping was verified against installed MinGW usb.h. It is distinct from a USB STALL status and from Windows application error 31.

## Meaning and limits

This is a failure while communicating with the keyboard's update interface, before programming begins. It is not merely an application permission rejection: the USB stack records the attempted transfers and transaction errors. Longer waiting and read/write access did not fix this attempt. The trace does not determine whether the reason is bootloader state, protocol/framing, host/platform behavior, or electrical communication. Header tracing does not establish which payload bytes reached or were acted on by the device.

The proposed no-sleep patch remains untested on hardware because it was never installed. Previous verified stock-firmware rewriting did not cure the ordinary restart/shutdown symptom. This final result does not prove permanent keyboard damage or identify a proven firmware repair. No additional flashing attempt is proposed here.

## Time handling

tracerpt renders an inconsistent +03:29 timestamp offset. Raw strings are preserved; capture UTC times come from the journal and updater log rather than blindly converting that offset. Ordinals are zero-based XML event order.
