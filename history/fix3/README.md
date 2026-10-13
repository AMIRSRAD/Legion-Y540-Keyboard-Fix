# Y540 updater fix3

An independent, compilable Windows updater with USB diagnosis, a targeted USB restart attempt, and corrected failure handling. The original `outputs/y540-research` source and previous release archives are preserved. This separate folder is version `0.3.2-fix3`.

**Updater changes pass offline tests. A permanent cure for the AC-dependent keyboard fault has not been established.** Your captures show a USB descriptor failure on the keyboard's historical port before Windows exposes its HID interfaces. The supplied `44.bin` is unchanged.

## First run

1. Extract `Y540Updater-fix3-portable.zip` to a writable folder and open `Y540Updater.exe`. Close other keyboard updaters first.
2. Select the power condition **at the last complete startup** in the dropdown. Current AC status is measured separately.
3. Click **Diagnose + save log** while the keyboard is failing. It reads PnP/power metadata without firmware commands.
4. Optionally click **Retry USB (no flash)** and confirm the displayed exact target. If permissions are denied, reopen as administrator and repeat diagnosis/retry. It refuses an ambiguous or changed target and excludes hubs/controllers. A successful Windows API result does not prove typing recovered.
5. Click **Open logs folder** and retain both diagnostic/restart logs. Also capture diagnosis when typing works after startup on battery. Report whether typing resumed and whether failure returns at the next AC startup.

Logs are beside the executable in `logs`; if that folder cannot be created, the app tries `%LOCALAPPDATA%\Y540Updater-fix3\logs`. Logs contain hardware identifiers; review before public sharing. Nothing is uploaded. Advanced firmware actions additionally record transmitted/received feature reports. A full pre-erase flash backup is saved in the same directory.

The failed-device restart is specific to this case: `USB\VID_0000&PID_0002\5&1F456139&0&9`, parent `USB\ROOT_HUB30\4&15ed8360&0&0`, location `Port_#0009.Hub_#0002`, USB class, descriptor-failure hardware ID, present/problem43. This is a topology match, not an authenticated firmware interface. If these change, collect new evidence instead of broadening the selector.

## Changes

- Failed custom-command/boot handoff attempts normal-mode cleanup and preserves the initiating error.
- Boot selection follows the same physical USB parent/port; unhealthy, missing or ambiguous HID targets fail closed.
- A consistent 54 KiB backup must be read twice, saved to a new file and flushed before erase.
- Final compare failure no longer causes an extra erase or an unverified reset. Chip qualification cannot be disabled through the INI.
- Speculative report-ID fallback and D1 response-echo requirements were removed to follow recovered vendor routines.
- Device changes share a cross-process guard. Close vendor updaters, which do not share it.

See [fix3-changes.md](docs/fix3-changes.md) for evidence and [case-evidence.md](docs/case-evidence.md) for the supplied case analysis.

## Build

In PowerShell from this folder:

```powershell
.\build.ps1
```

Requires Windows x64 MinGW-w64 GCC and `windres`; available here in `C:\Strawberry\c\bin`. Use `-Compiler C:\path\to\gcc.exe` to select another toolchain. Output: `build/Y540Updater.exe`. No vendor EXE, .NET, REA, Java or Ghidra is needed to compile. The build runs only offline emulators/file fixtures and hidden GUI initialization. Alternate CMake instructions: [build-and-test.md](docs/build-and-test.md).

## Advanced firmware writing

The firmware button and `--update FIRMWARE INI` perform real writes, separately from USB recovery. An unknown device with failed descriptors cannot receive HID firmware commands. A fresh consistent backup is required even in boot mode. On programming failure, fix3 leaves boot mode rather than blindly resetting into an unverified image; retain the log and backup.

This is a Windows source reconstruction, not recovered proprietary source or a byte-identical vendor build. Boot09's formerly undefined second byte is deterministically zero. Hardware compatibility and the AC fault remain unverified. We can compile this Windows EXE; the supplied MCU `44.bin` remains prebuilt and its source has not been recovered. No keyboard was flashed or restarted during development.
