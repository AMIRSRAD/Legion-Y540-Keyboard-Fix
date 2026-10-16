# Working-state fix1 logs

All four logs in `Desktop/New folder (3)` were read in full. Three contain data; the fourth is empty. Three complete inventories contain 34 devices each, for 102 device records. Full parsed records, input hashes, events, and field comparisons are preserved in `working-state-comparison.json`.

**The keyboard remained healthy, but Windows refused the requested USB disable. This is not evidence of a successful working-state reset.** The owner separately confirms that typing continued normally.

## Recorded result

- AC=0 (battery), battery 95% in all three inventories.
- Normal physical device `USB\VID_048D&PID_C100\5&1F456139&0&9`, revision 0044, is present with problem 0; all five C100 HID collections are also present with problem 0.
- The descriptor-failure placeholder is nonpresent. Its problem 0 is not a live healthy-device status: presence/status queries return CM 0xD.
- At 17:43:49.046 Tehran time on 12 October 2026, fix1 logs the restart attempt.
- At 17:43:49.074, it logs that the per-device disable failed with decimal code 40.
- At 17:43:49.252, the after-state inventory is recorded. Every recorded device field is identical across the diagnosis, before-state, and after-state inventories.
- No firmware write is recorded. The empty fourth log is not evidence of a completed later diagnosis.

Decimal 40 is CONFIGRET `CR_NOT_DISABLEABLE` (0x28), verified in the installed MinGW-w64 cfgmgr32.h. It is distinct from `CR_ACCESS_DENIED` (0x33, decimal 51). The result does not establish missing administrator rights. [Microsoft's CM_Disable_DevNode documentation](https://learn.microsoft.com/en-us/windows/win32/api/cfgmgr32/nf-cfgmgr32-cm_disable_devnode) specifies CR-prefixed return codes; it is not appropriate to interpret this as a generic Win32 error 40.

The reviewed source returns immediately after a failed CM_Disable_DevNode call, before its CM_Enable_DevNode loop. Therefore the log records a refused disable, not a completed disable/enable cycle. The working normal device lacks DN_DISABLEABLE (status 0x0180000A). The app's generic message suggesting elevation is misleading for this particular result and should be corrected in a future source revision. No build was changed as part of this log analysis.

## Comparison with the failed capture

Nine device records differ: the normal C100 device, its five HID children, the failed placeholder, the Intel USB controller, and its root hub. The controller/root hub differ only by DN_DISABLEABLE (0x2000); both remain present with problem 0. These differences reproduce the earlier working/failed inventory pattern and do not establish a controller fault.

In the failed capture, Windows accepted retry of the descriptor-failure placeholder and fresh port 9 descriptor reads failed four times. In this working capture, retry of the normal C100 devnode is refused. Although both identify the same physical keyboard port, the operations target different Windows devnodes and have different outcomes. Continued typing here cannot prove the keyboard survives a real reset or rule out reset-dependent firmware/platform behavior.

This folder contains no ETL or recording ZIP. The already supplied failed-state recording is not a working-state trace. The next step is to obtain the completed recording ZIP from this working-state session, if it exists, rather than ask the owner to repeat the test. It can show whether any USB activity occurred around the refused disable and whether port 6 reconnections also appear. It may not include fresh successful keyboard descriptor requests, since the requested restart was refused.

The cause of the startup fault remains unproven. These logs do not justify another flash or a broader hub/controller reset.
