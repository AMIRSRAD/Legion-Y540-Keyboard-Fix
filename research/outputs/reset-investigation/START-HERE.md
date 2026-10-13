# Next step: return to exp1, then compare power policy

The current image is exp2 or uncertain. A confirmed exp2 restart bug makes it unsuitable as the comparison baseline. This package does not contain a new firmware repair.

## 1. Return to the previous exp1 image

Use `Y540-Return-to-exp1.zip` on the affected Lenovo, extracted into a new folder. Keep external input available.

1. Use the previously effective approximately 10-second power-button shutdown and start the laptop. Confirm the built-in keyboard works. Do this only when no update is running.
2. Connect AC. Right-click `RUN-RETURN.cmd` and run as administrator. The launcher records USB events and opens the updater; it does not click Write.
3. Confirm the window says **Return to exp1 (5642)** and the selected file is `44-nosleep-exp1.bin`.
4. Click **Validate firmware**. Expected: 55,296 bytes, sum/stored **5642**, residual **0000**.
5. Click **Advanced firmware write** once and confirm the write. Let it settle; do not close or interrupt while erase/write is active.
6. After **Firmware readback matched; reset command accepted**, wait ten seconds and check typing. Close the updater after it settles. Keep the recording ZIP shown by the launcher.

If the write does not complete, keep its logs and stop at that result. Do not continue the comparison using uncertain firmware. A backup whose contents match exact exp2 can be verified with one full read; unknown contents still require two matching full reads before erase.

Exp1 is the unchanged earlier experiment with better reported behavior. Returning to it withdraws exp2; it is not a claim that the original problem is repaired.

## 2. Comparison without another firmware change

Only do this after confirming exp1. If this exact comparison was already completed, supply its result instead of repeating it.

Copy the `Y540-Power-Comparison` folder to the affected laptop. Open an administrator PowerShell in that folder. The scripts do not reboot the laptop, reset devices or run an updater.

Begin from a working forced-off start. Record the current policy and baseline:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\Compare-UsbPower.ps1 -Action Record -Keyboard working -Note "exp1 5642; forced-off start; baseline"
```

Do the usual restart sequence under the original policy, stopping at the first failure or after six ordinary restarts. After each boot, run Record again with `working` or `not-working` and a note containing the restart number. Do not run the updater between boots.

Recover using the known forced-off start if needed, then disable selective suspend for this comparison:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\Compare-UsbPower.ps1 -Action Disable -Keyboard working -Note "exp1 5642; begin suspend-off comparison"
```

Repeat the same ordinary restart sequence, up to six or the first failure, recording each result. Keep AC state the same between comparisons. A Record invocation is:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\Compare-UsbPower.ps1 -Action Record -Keyboard working -Note "exp1 5642; suspend off; normal restart 1"
```

If the active scheme or recorded policy changes unexpectedly, stop the comparison and note it. If all six restarts work, also try one ordinary shutdown, wait 30 seconds, and power on; record that separately. If a restart fails, no additional failure repetitions are needed.

Restore the saved policy values afterwards:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\Compare-UsbPower.ps1 -Action Restore -Keyboard unknown -Note "comparison finished"
```

Send the `comparison-records` folder and return-updater recording ZIP. The records include device identifiers, so keep them private unless you choose to share them. They are metadata snapshots, not a USB trace across boot.

If disabling suspend changes the restart behavior, that gives us a useful software-workaround lead. If it does not, it does not rule out shutdown power/reset interactions. Either way, keep the installed firmware unchanged during this comparison.

## For a developer

Read FINDINGS.md. `source-review` contains reproducible corrections and tests for exp2's CPU/concurrency defects, not a deployable watchdog. `tools/verify_reset_path.py` verifies the bootloader reset path against the supplied dump. No exp3 image or automatic flashing script is included.
