# Exp1 power-policy comparison

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

