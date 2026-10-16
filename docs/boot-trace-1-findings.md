# Boot trace 1 — ordinary restart on exp3, keyboard dead (2026-10-16)

Source: `Y540-boot-trace-20261016T154124Z-keyboard-dead.zip` (boot.etl 7.5 MB, shutdown.etl 0.3 MB).
Firmware on the keyboard: exp3 (backup taken minutes later hashes to exp3 `e0a959a6…`).
Times are laptop local (UTC+03:30).

## Port 9 (internal keyboard, HS09)

| Time | Event |
|---|---|
| 19:10:41.400 | USBHUB3 root hub prepare-hardware; port 9 listed as USB 2.0/1.1 |
| 19:10:41.501 | Port 9 status `0x101` change `0x1`: **powered + connected** (device pull-up present when Windows takes over) |
| 19:10:41.602 | Enumeration start, port 9 |
| 19:10:41.755 | Port reset completes: status `0x103` (connected, enabled, full speed), change `0x10` |
| 19:10:41.788 | GET_DESCRIPTOR(device) to address 0 fails, USBD `0xC0000011` (transaction error, no handshake), ~33 ms |
| 19:10:42.345 / 42.446 | Reset OK, descriptor request fails again |
| 19:10:43.002 / 43.103 | Same |
| 19:10:43.659 / 43.760 | Same; "Maximum Enumeration Retry Count Reached"; enumeration failed |
| 19:10:43.76 → 19:11:17 | **No further port-9 status change** (no disconnect, no re-attach) for 33 s until collection |

Port 6 (camera) and port 14 enumerate normally in the same window. The port-14 device-qualifier
stall (`0xC0000004`) is unrelated.

## Interpretation

- Same failure stage as every earlier capture and the Linux log: the keyboard is electrically
  attached, the port reset succeeds, and the device never answers a SETUP packet.
- exp3 was installed. Its watchdog would have detached the keyboard (2F50=08) and re-attached it
  after a timeout of 6,000/8,000 timer ticks (well under the 33 s observed). No detach occurred.
  So during the failure the firmware either is not running its timer interrupt (MCU halted or
  clock stopped) or is running but never sees the bus resets (USB block deaf). exp3 cannot
  catch either case.
- The shutdown-side trace contains only the session start rundown (19:10:03); the events up to the
  restart were not flushed. The shutdown side of the failure is still unrecorded.
- The unreferenced power-down routine at 0966 (`CLR EA; PCON=02`) has no direct, indirect
  (address constant) or table reference in the image; it is dead code, not the cause.

## Consequence for the next experiment

exp4 resets the chip from inside the firmware's own bus-idle decision (4C79/4C7B), which keeps
running in the "running but deaf" case and fires before the host comes back in the halted case.
That is the gap this trace shows exp3 had.
