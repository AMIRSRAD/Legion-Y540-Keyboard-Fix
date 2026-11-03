# Y540 keyboard firmware 44 + bootloader: full map

Decompiled 2026-11-03 from `fix10/samples/44.bin` (app, CODE 0000-D7FF) and
`fix10/samples/upper-flash-dump.bin` (bootloader, D800-FFFF), combined as
`app44-full64k.bin` (cat 44.bin + upper-flash-dump.bin).

## Coverage

| | bytes |
|---|---|
| Decoded as instructions (app + bootloader) | 38,202 |
| Data (USB/HID descriptors, key tables, padding) | 3,427 |
| Undecided | 11 |
| Functions | 508 (63 marked `H_`: reached only through pointers or tables, so found by sweep) |

Pipeline (re-runnable): `run_all.sh`. It runs Ghidra headless with `DecompileAll.java`,
which follows Keil switch tables (890A, 8930, F35A) to a fixpoint and has Ghidra's
non-returning-function guess turned off (`DisableNoReturn.java`). After that, `classify_unreached.py`
and `filter_seeds.py` repeat until no new code turns up.

Outputs in `full/`:

- `full-decompiled.c`: every function as C. For hardware polling loops, trust the listing over the C.
- `full-listing.asm`: complete disassembly.
- `functions.tsv`: each function's entry, size, callers and callees.
- `xdata-xref.tsv`: who reads and writes each RAM and hardware-register address.
- `sfr-sites.txt`: every write to interrupt, power, timer and watchdog registers.
- `poll-loops.txt`: every busy-wait loop on hardware.
- `coverage-log.txt`, `full/regions.tsv`: what was not decoded as code, and why.

Helpers: `rng.py` (listing by address range), `showfn.py` (C by function address),
`structxref.py` (fields reached through Keil generic pointers).

## Memory

| Range | What |
|---|---|
| XDATA 0000-0FFF | RAM. Zeroed by the app entry (0400 / 0100) on every start. |
| 0DD5.. | USB state record (pointer at 0DE8). `+1` control-transfer state, `+3` **"bus reset handled"**, `+0F` idle counter, `+11` activity flag. |
| 0E00-0EFF | Settings copy, loaded from flash D800 at boot (806D → 7F65). Defaults are rewritten only if invalid (7F40). |
| 1000-103F | Flash controller. The app's flash routines are copied to RAM and run with interrupts off. |
| 1100-1130 | Interrupt controller: 1110 = pending vector, 1100-1106 = status and enable. |
| 16E0 | USB line state: bit5 = D+, bit4 = D-. 0x20 = J (idle). |
| 1E00-1E43 | Clock and power control. |
| 2F40-2F9F | USB device block: 2F50 connect, 2F52 interrupt status (bit0 setup, bit2 **bus reset**, bit3 SOF), **2F54 device address**, **2F55:2F56 frame number**, 2F64/74/84/94 endpoint control. |
| D800 (flash) | Settings block, 256 bytes. |
| E000-F9FF | Bootloader. USB descriptors for 048D:89DB "ITE Upgrade Mode" at F90A. |

## Start-up

1. Reset → bootloader E000 → (normal) app entry 0400.
2. 0400:
   1. Clears IRAM and XDATA 0000-0FFF.
   2. Saves the reset source from 2006 into 0082.
   3. Runs the C start-up at 0464, then jumps to **main 2200**.
3. main 2200, init:
   1. 0EC1 loads the settings.
   2. 8000 starts USB.
   3. 50AC → 4B29 + 4B88: `0DD2 = 1`, USB state record cleared.
   4. 05A7 enables interrupts.
4. Main loop:
   1. Waits until 6FA8 returns FF.
   2. Event dispatcher 07C4 handles IRAM 26h flags:
      - bit0 → 0946 timer task (→ 26B7 → 26E2 idle gate)
      - bit1 → 0950
      - bit5 → 07F1
      - bit7 → 2260 key scan
   3. With no events, PCON = 1 (idle until the next interrupt).

## Interrupts

- **Timer 0** (vector 000B → 3300) ticks every ~384 µs and sets 26h.0 / 26h.5.
  - It is stopped in only one place: 813F, inside the stock sleep sequence, which exp4/exp7 replace.
- **INT1** (vector 0013 → 3400) is the dispatcher for the interrupt controller. It reads vector 1110 and looks it up in the table at 05C4. Live sources:

| Source | Handler | Role |
|---|---|---|
| INT5 | 04AE → 841D / 80DB | |
| INT9 | 04B9 | Sets 26h.7 → key scan |
| INT21 | 04D4 | |
| **INT22** | 04E2 → 21FC → **4F75 USB service, runs in interrupt context** | USB |
| INT33-35 | 04EF / 04F2 / 04FF → 7FFC | |
| INT39 | 050D → 7FF9 | |
| INT54 / 55 | 267E / 26A5 | |
| INT56-63 | 8131 | Key-row wake |

- No interrupt priorities are set, so the USB service and the timer cannot interrupt each other.
- The main firmware has **no wait loop on USB hardware**. All its hardware waits are bounded by timer 1, and every unbounded USB wait is in the bootloader.
- Interrupts are turned off only through 059D/05A4, in short pairs: flash operations, short delays, init, the wake path.
- **The main firmware never touches the watchdog.** The only watchdog write is in the bootloader's C4 restart path at F455. A wedged state never recovers by itself.

## USB service (4F75, interrupt context)

- **2F52 bit2, bus reset** → 35DD → **39DA**:

  ```
  if (usb_state[+3] == 0) {            // 39E5..39EB
      4B29 reset state; 2F64/74/84 = 1; 2F94 = 1;
      2F54 = 0 (address 0); 2F44 = 21; 2F52 = 18;
      usb_state[+3] = 1;
  }                                    // otherwise ignored; 35DD only clears 2F52 bit2
  ```

  `usb_state[+3]` is written in exactly three other places:

  | Address | Value | When |
  |---|---|---|
  | 3A1B | 1 | Above, after handling a reset |
  | 4B29 | 0 | Called from boot (50F3) and from the wake-from-sleep path (4D21) |
  | 4DE5 | 0 | Only before USB is enabled |

  The bootloader's handler (F7A0) has the same once-only shape.
- **2F52 bit0, setup** → standard and HID requests. SET_ADDRESS writes 2F54 at 505D.

## Sleep and power

- **Idle gate 4BC4**, run from the main-loop timer task:
  - It counts ticks without an SOF, with 2F52 bit3 as the SOF flag. The limit is 8 ticks after activity has been seen, or 5000 ticks if none has.
  - It is vetoed by 0891/0800 and 08AE/0902.
  - It also requires 16E0 to show J (idle).
- **Sleep sequence 4C7B** (stock): sets 0DD3, then the 1Bxx/111C/1E20 writes, then 813C.
  - 813C stops timer 0 and enters deep sleep (PCON = 2 via 2633/264B/2665).
  - On wake, 8180 restarts timer 0 and sets a 300-tick grace period in 00F4/00F5.
  - After wake, the path at 4D21 calls 4B29, which **clears `usb_state[+3]`**.
- 0966-0983 also contains a deep-sleep routine, but nothing references it (dead code).

## Diagnosis this map gives

- After power-on, the keyboard obeys the first USB bus reset and then **ignores every later one until it has been through its own sleep and wake**.
- An ignored reset leaves the old device address in 2F54. Windows' enumeration then asks address 0 for the device descriptor and gets no answer. This matches the boot trace: port 9 connected, four resets, `0xC0000011` after each.
- Whether the sleep happens between BIOS and Windows depends on the idle gate's activity vetoes, which explains "dies after normal use, fine after a cold start".
- A power cut (10 s hold, battery drain) clears RAM, which also clears the flag.
- **exp8** (`source/firmware/build_exp8.py`): stock 44 with 39EB `JNZ 3A21` replaced by `CLR A; NOP`, so every bus reset takes the first-reset path. Image sha256 `5d0312a6…`, sum 5662.
  - It assumes the USB block does not clear 2F54 by itself. Both the firmware and the bootloader clear it in software, which supports that assumption.
- **exp7** (frame watchdog) stays as the fallback.
- exp4, exp6 and exp7 only worked around the bug by restarting the chip. exp8 targets the cause.
