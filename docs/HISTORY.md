# How this started, and how the fix was found

## The original problem: Lenovo's keyboard firmware update 00000044

Lenovo offers Y540 owners a **"Y540 keyboard Firmware update – 10 [64] – 00000044"** (package `ite1fw11s.exe`, released 2023-03-28) through Lenovo Vantage / Lenovo support. On the author's laptop the update never completed: Lenovo's tool `ITESHFU.exe` stopped with

> **"Can not Find Device! - 1"** … *"Please shutdown Tablet PC then retry"*

From then on, the built-in keyboard stopped working after every normal Restart or Shut down. Only holding the power button ~10 seconds (fully cutting power) brought it back, until the next restart. Device Manager showed *"Unknown USB Device (Device Descriptor Request Failed)"*, code 43.

The author is not alone: Lenovo forum threads describe the same thing on other Y540s after the same 00000044 update: failed installs, a dead keyboard after reboot, recovery only after a full power-off. Lenovo never published a fix.

What is proven and what is not: the updater's original logs were not available, so it is not proven that the failed update *caused* the fault. Later analysis showed the keyboard actually held an exact, intact copy of firmware 44, and Lenovo's tool fails for a separate, explainable reason (below). What exp4 fixes is how firmware 44 behaves across restarts.

## Reverse engineering it

With no documentation from Lenovo or ITE, everything was reconstructed from the binaries:

- **Tools:** [REA (Reverse Engineer Anything)](https://github.com/morluto/rea) and NSA's [Ghidra](https://github.com/NationalSecurityAgency/ghidra) (8051 processor module), plus small custom 8051 disassembler/emulator scripts in this repo.
- **Lenovo's updater `ITESHFU.exe`** was decompiled to recover the keyboard's flash protocol (commands `C0`–`C4`, `D0`, `D1`, report sizes, write order, checksum rules). This became the open-source updater in [`source/`](../source/).
- **Firmware 44** (55,296 bytes of 8051 code for the ITE IT8176 keyboard controller) was disassembled: reset vectors, USB handling, sleep paths, bus-reset handling, start-up tables.
- **The chip's bootloader** (never included in Lenovo's package) was read straight off the keyboard with a read-only dump, which revealed its reset routine at `F455`.
- **The board**: the Y540 board view showed the keyboard chip runs from an always-on power rail, which is why only a full power cut resets it.
- **Windows and Linux USB traces** pinned the failure down: the keyboard stays attached but never answers the computer after a restart.

## Progress, attempt by attempt

| Step | What was tried | What we learned |
|---|---|---|
| fix1 | First rebuilt updater | Wrong USB report sizes; could not talk to the chip |
| fix2 | Correct report sizes | **First successful write** — rewrote stock firmware 44. Backup showed the chip already held an exact copy of 44: not corrupted. Symptom unchanged. |
| fix3–fix4 | Longer retries, different HID access | Chip never answered in update mode (120 failed queries) |
| fix5 | Contact the update-mode chip immediately | **Why Lenovo's tool fails:** it waits 6 s, Windows suspends the idle chip, and it never answers again. Fast contact fixed updating. |
| fix6 + **exp1** | First patched firmware: skip the sleep sequence (2 bytes) | Restarts 1–2 now survive; 3rd still fails. Sleep path is involved, but not the whole story. |
| fix7 | Read-only dump of the bootloader area | Found the chip's own reset routine (`F455`) and bootloader layout |
| fix8 + exp2 | Software watchdog | Worse; later found a CPU register-bank bug |
| fix9 + exp3 | Corrected watchdog using the real reset routine | Seemed better, then failed again |
| boot trace | Recorded a failing restart from early boot | Keyboard attached but silent, never recovers, and exp3's watchdog never fired: the chip is stuck in a state exp3 cannot detect |
| fix10 + **exp4** | Restart the chip at the exact moment it would have gone to sleep | **Keyboard works after every shutdown and Shift+shutdown tested.** Backlight flashes once at power-off — the restart happening. Under long-term test. |

Details of each step are preserved in [`research/`](../research/); how exp4 works is in [HOW-IT-WORKS.md](HOW-IT-WORKS.md); current test results are in [STATUS.md](STATUS.md).
