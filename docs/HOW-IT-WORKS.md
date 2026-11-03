# How the fix works, and the evidence behind it

## Current fix: exp7 (frame-counter watchdog)

While a host is talking to a USB device it sends a Start-of-Frame every 1 ms. The IT8176 latches the frame number in `2F55:2F56` (found with a read-only probe: two reads 866 ms apart advanced exactly 866). exp7 hooks the chip's timer-0 interrupt (`330A`, ticks every ~384 µs, runs whatever the main loop is doing) with a 64-byte routine at `8A10`:

- frame changed → remember it; after 16 changes the watchdog is armed; stall counter = 0
- frame unchanged while armed → stall counter + 1; at 1024 ticks (~0.4 s) → `F455`, the bootloader's own detach-and-watchdog restart

Arming needs real frames since power-on, so with the PC off it can't loop; 0.4 s is far above a USB bus reset (10–50 ms). exp7 keeps exp4's change too. Generator and model test: [`build_exp7.py`](../source/firmware/build_exp7.py), [`test_exp7.py`](../source/firmware/test_exp7.py).

Why exp4 was not enough: it restarted the chip only when the firmware's own sleep check passed, and after normal use that check is often vetoed (activity locks) so nothing happened at shutdown.

Also found in the [full decompile](../research/analysis/firmware-44-full-decompile/README.md): the stock bus-reset handler (`39DA`) only re-initialises USB (including clearing the device address) on the first reset after power-on, until the chip has slept. **exp8** removes that check (2 bytes); on its own it did not fix the keyboard. **exp9** = exp7 + exp8 is kept as an untested spare.

## Earlier fix: exp4

## The hardware

- Keyboard controller: ITE IT8176 (USB `048D:C100`, update mode `048D:89DB`), an 8051 microcontroller on internal USB port 9 (`HS09`).
- It is powered from an always-on rail (`+3VALW_AG` via switch U23, enable shared with `PCH_PWR_EN`) with a simple RC reset. A normal Restart or Shut down does **not** remove that power; the ~10 s power-button hold does. See [research/analysis-history/platform-reset-analysis/board-connectivity.md](../research/analysis-history/platform-reset-analysis/board-connectivity.md).

## What fails

Boot trace on the failing laptop (exp3 installed), ordinary restart — [boot-trace-1-findings.md](boot-trace-1-findings.md):

- When Windows' USB driver starts, port 9 is **connected** (the chip's pull-up is on).
- Windows resets the port four times; every reset completes, and every time the chip **never answers** the first setup request (`USBD 0xC0000011`). Windows gives up after 2 s.
- For the next 33 s the chip never disconnects or re-attaches, although exp3's watchdog would have done so within seconds. So in this state the chip is either halted or running but deaf to the bus, and it stays that way until power is removed.

The same failure stage appears in Linux (`device descriptor read/64, error -71`) and in every earlier Windows capture.

## The firmware change

Firmware 44 decides at `CODE 4C79` (`JZ 4CE1`) whether the bus has been idle long enough to enter its low-power sequence, which starts at `4C7B`. Earlier experiments:

| | Change | Result |
|---|---|---|
| exp1 | skip the low-power sequence | better (restarts 1–2 survive), still fails ~3rd restart |
| exp2 | software watchdog with a guessed detach | worse; later found to have a CPU register-bank bug |
| exp3 | timeout reset on bus-reset-without-configuration or stalled main loop | did not hold; the trace shows it never fired in the failure |
| **exp4** | **at `4C7B`, instead of sleeping, jump to the chip's own C4 reset routine (`F455`)** | **working so far** |

exp4 bytes: `4C7B: 02 8A 00` (LJMP 8A00); `8A00: C2 AF 75 D0 00 02 F4 55 22` (CLR EA; MOV PSW,#0; LJMP F455); checksum `7FFE..7FFF = 50 6A`. Everything else is byte-identical to Lenovo's firmware 44. `F455` is the routine the bootloader already uses to leave update mode: it detaches from USB, then lets the chip's watchdog restart it, which is how the chip normally returns from a firmware update.

Effect: whenever the host goes quiet — restart, shutdown, BIOS-to-Windows hand-over — the chip restarts itself instead of sleeping, so the host always meets a freshly started keyboard. The single backlight flash at power-off is that restart.

## Verification done

- Generator [`source/firmware/build_exp4.py`](../source/firmware/build_exp4.py) checks the stock image hash, every byte it replaces, the free space and the bootloader bytes it depends on.
- [`source/firmware/test_exp4.py`](../source/firmware/test_exp4.py) runs the real stock gate, the stub and the real bootloader bytes in an 8051 model: all 2,040 "idle" cases reach the reset point; all "not idle" cases return untouched.
- The updater (fix10) refuses to install exp3/exp4 unless the chip's own `F12C`/`F455` bytes match, and its offline protocol tests cover install, interrupted-write resume and rollback.
- On hardware: installed and verified on the author's Y540-15IRH (BIOS BHCN35WW); boot traces after a normal shutdown and a Shift+shutdown show port 9 enumerating on the first attempt.

Not proven: the chip's exact reset scope and register meanings (no ITE documentation), and long-term reliability.
