# Installing the Y540 keyboard fix (exp4) — step by step

Time needed: about 5 minutes. No programming knowledge needed.

## What you need

- A Lenovo Legion Y540 with the problem described in the [README](../README.md).
- The charger plugged in.
- An external USB keyboard or mouse, just in case.
- A Windows account that can approve "Run as administrator".

## 1. Download

Download [**Y540-Keyboard-Fix.zip**](https://github.com/AMIRSRAD/Y540-Keyboard/raw/main/download/Y540-Keyboard-Fix.zip).
Right-click it → **Extract All…** → **Extract**. Open the extracted `Y540-Keyboard-Fix` folder.

> Windows SmartScreen may warn that the program is unrecognised, because it is not signed by a company.
> Click **More info → Run anyway** only if you downloaded it from this GitHub page.

## 2. Get the keyboard working first

The updater needs to talk to the keyboard, so it must be in its **working** state:
hold the **power button for about 10 seconds** until the laptop is completely off, then turn it on and log in.
Check that the built-in keyboard types.

## 3. Open the updater

Double-click **`INSTALL THE FIX.cmd`** and click **Yes** on the Windows prompt.
Check the window title reads **`Y540 fix10 - Reset-instead-of-sleep exp4 (506A)`** and the firmware box shows `44-reset-exp4.bin`.

## 4. Validate

Click **Validate firmware**. The log must show:

```
Validated 55296 bytes. Sum=506A stored=506A residual=0000.
```

## 5. Write

Click **Advanced firmware write** and then **Yes**. Do not close the window, close the lid, or unplug the charger until it finishes (about 1–2 minutes). You will see, in order:

| Message | Meaning |
|---|---|
| `Find keyboard boot interface` / `Enter keyboard boot mode` | The keyboard switches to its update mode. It stops typing for a moment — that is expected. |
| `Verify existing bootloader reset dependency` | Checks that your chip's recovery code matches the tested chip. If not, it stops here without changing anything. |
| `Read complete update region for backup` / `Firmware backup saved and flushed` | Your current keyboard firmware is saved to the `logs` folder (`before-flash-….bin`). |
| `Erase image region`, `Write firmware`, `Read back and compare` | Writing and checking every byte. |
| **`Firmware readback matched; reset command accepted.`** | **Success.** The keyboard restarts and types again within a few seconds. |

Close the window. You are done.

## 6. Check it

- Restart normally a few times and check the keyboard each time.
- Shut down normally, wait 30 seconds, turn on, check.
- You may see the keyboard backlight **flash once** as the laptop powers off. That is the fix restarting the keyboard chip.

Please report your result in a GitHub issue — it helps others.

If anything unexpected happens, see [TROUBLESHOOTING.md](TROUBLESHOOTING.md).
