# OPTIONAL extra margin for the update. Turns "USB selective suspend" OFF in the ACTIVE Windows power plan
# (AC and battery) and records the previous values so RESTORE-USB-SELECTIVE-SUSPEND.cmd can put them back.
# Only the power plan value is changed. No device, driver, BIOS or firmware is touched.
$ErrorActionPreference = 'Stop'
$identity = [Security.Principal.WindowsIdentity]::GetCurrent()
if (-not (New-Object Security.Principal.WindowsPrincipal($identity)).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host 'Right-click DISABLE-USB-SELECTIVE-SUSPEND.cmd and select Run as administrator.'; exit 1
}
$sub = '2a737441-1930-4402-8d77-b2bebba308a3'; $set = '48e6b7a6-50f5-4782-a5d4-53bb8f07e226'
$active = (powercfg /getactivescheme) -join ' '
if ($active -notmatch '([0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12})') { throw 'Cannot read the active power plan.' }
$scheme = $Matches[1]
$q = (powercfg /query $scheme $sub $set) -join "`n"
if ($q -notmatch 'Current AC Power Setting Index:\s*0x([0-9a-fA-F]+)') { throw 'Cannot read the current AC value.' }
$ac = [Convert]::ToInt32($Matches[1], 16)
if ($q -notmatch 'Current DC Power Setting Index:\s*0x([0-9a-fA-F]+)') { throw 'Cannot read the current DC value.' }
$dc = [Convert]::ToInt32($Matches[1], 16)
$state = Join-Path $PSScriptRoot 'usb-selective-suspend-previous.txt'
if (-not (Test-Path -LiteralPath $state)) { "$scheme $ac $dc" | Set-Content -LiteralPath $state -Encoding ASCII }
powercfg /setacvalueindex $scheme $sub $set 0
powercfg /setdcvalueindex $scheme $sub $set 0
powercfg /setactive $scheme
Write-Host "USB selective suspend is now OFF in plan $scheme (was AC=$ac DC=$dc)."
Write-Host 'Run RESTORE-USB-SELECTIVE-SUSPEND.cmd after the update to put the previous values back.'
