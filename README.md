# Lenovo Legion Y540 — built-in keyboard dies after Restart/Shut down: a fix

**Symptom:** after a normal Windows **Restart** or **Shut down**, the Y540's built-in keyboard stops typing (Fn keys may still work). Holding the power button for about **10 seconds** until the laptop is fully off, then turning it on, brings it back — until the next restart. Device Manager shows **"Unknown USB Device (Device Descriptor Request Failed)"**. Many owners report this after Lenovo's *"Y540 keyboard Firmware update – 00000044"*.

**Status (2026-10-16): experimental fix `exp4`, working so far.** On the author's laptop the keyboard has worked after every shutdown and Shift+shutdown since installing it, after nine earlier attempts (fix1–fix9) that did not hold. Long-term testing is still running; see [docs/STATUS.md](docs/STATUS.md). If it is still holding after about a week, it will be declared the fix.

---

## ⬇️ Download and install (no programming needed)

1. **Download:** [**Y540-Keyboard-Fix.zip**](https://github.com/AMIRSRAD/Y540-Keyboard/raw/main/download/Y540-Keyboard-Fix.zip) (140 KB)
2. Right-click the ZIP → **Extract All**, open the folder, read **`READ ME FIRST.txt`**.
3. Plug in the charger. Make the keyboard **work** first: hold power ~10 s until off, turn on.
4. Double-click **`INSTALL THE FIX.cmd`** → **Yes**.
5. Click **Validate firmware** (should say `Sum=506A`), then **Advanced firmware write** → **Yes**.
6. Wait for **"Firmware readback matched; reset command accepted."** Done.

Full step-by-step guide with what each message means: **[docs/INSTALL.md](docs/INSTALL.md)**
Something went wrong / want to undo: **[docs/TROUBLESHOOTING.md](docs/TROUBLESHOOTING.md)**

**Is it safe?** The updater only talks to the Y540 keyboard chip, accepts only known firmware files, checks your chip's built-in recovery code before erasing anything, always saves a backup of your current keyboard firmware first, never touches the chip's recovery (bootloader) area, and verifies every byte after writing. If your chip differs from the tested one it stops before changing anything. It is still an experimental, community-made tool — not from Lenovo — and you use it at your own risk.

**Side effects:** the keyboard backlight may flash once when the laptop powers off (that is the fix working), and the built-in keyboard can no longer wake the laptop from Sleep (use the power button or lid).

---

## What the fix does (short version)

The keyboard is a small separate chip (ITE IT8176) that stays powered even when the laptop is "off" — only a 10-second power hold really cuts its power. When Windows shuts down or restarts, the keyboard's firmware notices that the computer went quiet and puts the chip into a low-power state. On this laptop the chip often never comes back from that state until its power is removed, so the next boot finds a keyboard that is plugged in but silent.

`exp4` changes 14 bytes of Lenovo's firmware 44 (3-byte jump, 9-byte routine, 2-byte checksum): at the exact moment the firmware would put the chip to sleep, it **restarts the chip instead**, using the chip's own existing restart routine. The next boot then always meets a freshly started keyboard — the same thing the 10-second power hold achieves. Details and evidence: [docs/HOW-IT-WORKS.md](docs/HOW-IT-WORKS.md).

## Help testing

If you try it, please report back (GitHub issue): your model, what you tested (restart / shutdown / sleep) and whether it held. If it fails, the [boot trace kit](https://github.com/AMIRSRAD/Y540-Keyboard/raw/main/download/Y540-boot-trace-kit.zip) records what the USB system saw during one restart, without recording what you type ([tools/boot-trace-kit/READ-ME.txt](tools/boot-trace-kit/READ-ME.txt)).

## Repository layout

| Folder | What is in it |
|---|---|
| [`download/`](download/) | Ready-to-use ZIPs: the fix and the boot trace kit |
| [`docs/`](docs/) | Install guide, troubleshooting, how it works, test status, trace findings |
| [`source/`](source/) | Updater C source, firmware generators (`build_exp4.py`) and tests — see [source/BUILD.md](source/BUILD.md) |
| [`tools/boot-trace-kit/`](tools/boot-trace-kit/) | The boot-time USB trace scripts |
| [`research/`](research/) | The full earlier investigation (fix1–fix9, exp1–exp3, firmware/BIOS/board analysis, preservation archive) — see [research/README.md](research/README.md) |

Not affiliated with Lenovo or ITE. Firmware images in the download are Lenovo's firmware 44 and small patches of it; the original is Lenovo's public package `ite1fw11s.exe`.
