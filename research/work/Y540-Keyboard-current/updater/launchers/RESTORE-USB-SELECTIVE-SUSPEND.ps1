# Puts back the "USB selective suspend" values recorded by DISABLE-USB-SELECTIVE-SUSPEND.ps1.
$ErrorActionPreference = 'Stop'
$identity = [Security.Principal.WindowsIdentity]::GetCurrent()
if (-not (New-Object Security.Principal.WindowsPrincipal($identity)).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host 'Right-click RESTORE-USB-SELECTIVE-SUSPEND.cmd and select Run as administrator.'; exit 1
}
$sub = '2a737441-1930-4402-8d77-b2bebba308a3'; $set = '48e6b7a6-50f5-4782-a5d4-53bb8f07e226'
$state = Join-Path $PSScriptRoot 'usb-selective-suspend-previous.txt'
if (-not (Test-Path -LiteralPath $state)) { Write-Host 'Nothing recorded; nothing to restore.'; exit 0 }
$parts = (Get-Content -LiteralPath $state -Raw).Trim() -split '\s+'
if ($parts.Count -ne 3) { throw 'Recorded state file is not in the expected format.' }
$scheme = $parts[0]; $ac = [int]$parts[1]; $dc = [int]$parts[2]
powercfg /setacvalueindex $scheme $sub $set $ac
powercfg /setdcvalueindex $scheme $sub $set $dc
powercfg /setactive $scheme
Remove-Item -LiteralPath $state
Write-Host "Restored USB selective suspend in plan $scheme (AC=$ac DC=$dc)."
