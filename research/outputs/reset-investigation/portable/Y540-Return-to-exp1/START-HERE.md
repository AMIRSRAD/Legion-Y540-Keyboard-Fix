# Return to exp1 — not a new repair

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

