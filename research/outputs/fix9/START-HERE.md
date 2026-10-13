# Y540 fix9 — install experimental recovery firmware exp3

**Firmware:** `44-recovery-exp3.bin` — 55,296 bytes, checksum **0699**.

This revision replaces exp2's jump into startup with the keyboard bootloader's existing reset sequence. It fixes the register-bank startup bug, protects the counters, and improves the recovery heartbeat. It is a new hardware experiment, not a demonstrated permanent repair.

## Install on the affected Lenovo

1. Extract the complete ZIP into a new folder on the affected laptop. Keep external input available.
2. If necessary, use the previously effective approximately 10-second power-button shutdown and power on again to get a working keyboard. Connect AC. Do this before launching the updater, never during a write.
3. Right-click **RUN-FIX9.cmd** and select **Run as administrator**. It records USB events and opens the updater. It does not click Write or flash automatically.
4. Check the window title says **Y540 fix9 — Recovery exp3 (0699)** and the selected file is **44-recovery-exp3.bin**. Click **Validate firmware**. Expect **55296 bytes; Sum=0699; stored=0699; residual=0000**.
5. Click **Advanced firmware write** once and confirm. Wait for **Firmware readback matched; reset command accepted**. Do not close the window or interrupt power while erase/write is active.
6. Wait ten seconds and check typing. Close the updater after it settles. Keep the recording ZIP printed by the launcher.

Before erase, fix9 reads and compares the actual controller's reset-routine bytes. A mismatch or unreadable routine stops the update. Do not bypass that check. A complete, flushed backup is still required; exact known-image hashes need one full read, unknown contents need two matching reads. The bootloader region is never erased or written.

## Check the result

Keep AC state and Windows settings unchanged for this firmware test.

- Check typing, then use an ordinary Windows Restart.
- If typing fails, wait **30 seconds** before using the power button. Note whether it recovers by itself and approximately how long that takes. The firmware thresholds count timer ticks; their exact duration on this chip is not established.
- If that restart works, try up to six ordinary restarts, stopping at the first failure. Then try one ordinary shutdown, wait 30 seconds, and power on.
- After each relevant result, run **CAPTURE-STATE.cmd**, enter whether typing works and a short note such as `restart 1 failed, still failed after 30 seconds`.

Send the recording ZIP, the `logs` folder and the `state-records` folder. The flashing recording ends when you close the updater; state records document subsequent boots but do not trace the MCU internally.

If the update fails, stop and keep its logs. The failure message will say whether programming started; do not repeat blindly or interrupt an active write.

## Return to exp1 if exp3 is worse

After recovering a usable update interface with the known power-button procedure if possible, run RUN-FIX9.cmd again. Use the firmware **Browse...** button to select **44-nosleep-exp1.bin**. Validate **5642**, then perform one write and wait for readback/reset success. Returning to exp1 does not need the new upper-flash dependency check. It still needs a functioning update interface; recovery is not guaranteed if that interface cannot be reached.

## Limits

Exp3 can still reset when a host leaves enumeration unfinished intentionally. It cannot guarantee recovery if the MCU timer/clock stops or the fault produces no detectable condition. Scratch-RAM ownership and the physical scope of the chip reset remain incompletely documented. Do not use the package on another model or interpret successful flashing as proof the keyboard fault is fixed.
