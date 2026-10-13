param(
    [ValidateSet('Record','Disable','Restore')][string]$Action = 'Record',
    [ValidateSet('working','not-working','unknown')][string]$Keyboard = 'unknown',
    [string]$Note = ''
)
$ErrorActionPreference = 'Stop'
# This script records metadata and optionally changes one Windows power-plan
# setting. It contains no firmware commands, device restart or reboot commands.
if (-not ('Y540Comparison.Power' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
namespace Y540Comparison {
 public static class Power {
  [DllImport("powrprof.dll")] public static extern uint PowerGetActiveScheme(IntPtr root, out IntPtr scheme);
  [DllImport("powrprof.dll")] public static extern uint PowerReadACValueIndex(IntPtr root, ref Guid scheme, ref Guid subgroup, ref Guid setting, out uint value);
  [DllImport("powrprof.dll")] public static extern uint PowerReadDCValueIndex(IntPtr root, ref Guid scheme, ref Guid subgroup, ref Guid setting, out uint value);
  [DllImport("powrprof.dll")] public static extern uint PowerWriteACValueIndex(IntPtr root, ref Guid scheme, ref Guid subgroup, ref Guid setting, uint value);
  [DllImport("powrprof.dll")] public static extern uint PowerWriteDCValueIndex(IntPtr root, ref Guid scheme, ref Guid subgroup, ref Guid setting, uint value);
  [DllImport("powrprof.dll")] public static extern uint PowerSetActiveScheme(IntPtr root, ref Guid scheme);
  [DllImport("kernel32.dll")] public static extern IntPtr LocalFree(IntPtr memory);
 }
}
'@
}
$subgroup = [Guid]'2a737441-1930-4402-8d77-b2bebba308a3'
$setting = [Guid]'48e6b7a6-50f5-4782-a5d4-53bb8f07e226'
function Check-Code([uint32]$Code, [string]$Operation) {
    if ($Code -ne 0) { throw ($Operation + ' failed: Win32 ' + $Code) }
}
function Read-Policy([Guid]$Scheme) {
    [uint32]$ac = 0; [uint32]$dc = 0
    Check-Code ([Y540Comparison.Power]::PowerReadACValueIndex([IntPtr]::Zero,[ref]$Scheme,[ref]$subgroup,[ref]$setting,[ref]$ac)) 'Read AC policy'
    Check-Code ([Y540Comparison.Power]::PowerReadDCValueIndex([IntPtr]::Zero,[ref]$Scheme,[ref]$subgroup,[ref]$setting,[ref]$dc)) 'Read DC policy'
    return @{ scheme=$Scheme.ToString(); ac=$ac; dc=$dc }
}
function Write-Policy([Guid]$Scheme,[uint32]$AC,[uint32]$DC,[bool]$Activate) {
    Check-Code ([Y540Comparison.Power]::PowerWriteACValueIndex([IntPtr]::Zero,[ref]$Scheme,[ref]$subgroup,[ref]$setting,$AC)) 'Write AC policy'
    Check-Code ([Y540Comparison.Power]::PowerWriteDCValueIndex([IntPtr]::Zero,[ref]$Scheme,[ref]$subgroup,[ref]$setting,$DC)) 'Write DC policy'
    if ($Activate) { Check-Code ([Y540Comparison.Power]::PowerSetActiveScheme([IntPtr]::Zero,[ref]$Scheme)) 'Apply active policy' }
    $check = Read-Policy $Scheme
    if ($check.ac -ne $AC -or $check.dc -ne $DC) { throw 'Policy readback differs from requested values' }
}
[IntPtr]$schemePointer = [IntPtr]::Zero
Check-Code ([Y540Comparison.Power]::PowerGetActiveScheme([IntPtr]::Zero,[ref]$schemePointer)) 'Read active scheme'
try { $active = [Guid][Runtime.InteropServices.Marshal]::PtrToStructure($schemePointer,[type][Guid]) }
finally { [void][Y540Comparison.Power]::LocalFree($schemePointer) }
$machine = Get-CimInstance Win32_ComputerSystem
$product = Get-CimInstance Win32_ComputerSystemProduct
$os = Get-CimInstance Win32_OperatingSystem
$identity = [string]$product.UUID
$folder = Join-Path $PSScriptRoot 'comparison-records'
New-Item -ItemType Directory -Path $folder -Force | Out-Null
$statePath = Join-Path $folder 'restore-state.json'
$before = Read-Policy $active
if ($Action -ne 'Record') {
    $principal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
    if (-not $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) { throw 'Use an administrator PowerShell on the affected Lenovo for Disable or Restore.' }
    if (([string]$machine.Manufacturer -notmatch 'LENOVO') -or
        (([string]$machine.Model -notmatch '^81SX') -and ([string]$product.Version -notmatch 'Y540'))) {
        throw 'Policy changes are restricted to the affected Lenovo Y540. This development computer must not run them.'
    }
    if (-not $identity -or $identity -match '^0{8}-') { throw 'Cannot bind restore state to a valid machine UUID' }
}
if ($Action -eq 'Disable') {
    if (Test-Path -LiteralPath $statePath) { throw 'Restore state already exists. Keep it and use Restore before starting another comparison.' }
    $state = @{ machine=$identity; policy=$before; created_utc=(Get-Date).ToUniversalTime().ToString('o') }
    $bytes = [Text.Encoding]::UTF8.GetBytes(($state | ConvertTo-Json -Depth 5))
    $stream = [IO.File]::Open($statePath,[IO.FileMode]::CreateNew,[IO.FileAccess]::Write,[IO.FileShare]::None)
    try { $stream.Write($bytes,0,$bytes.Length); $stream.Flush($true) } finally { $stream.Dispose() }
    try { Write-Policy $active 0 0 $true }
    catch {
        $primary = $_
        try { Write-Policy $active ([uint32]$before.ac) ([uint32]$before.dc) $true }
        catch { Write-Warning ('Automatic rollback failed; keep restore-state.json: ' + $_.Exception.Message) }
        throw $primary
    }
    Write-Host 'USB selective suspend is disabled for AC and battery in this power plan. Original values are saved.'
}
if ($Action -eq 'Restore') {
    if (-not (Test-Path -LiteralPath $statePath)) { throw 'No restore state exists in this package.' }
    $state = Get-Content -LiteralPath $statePath -Raw | ConvertFrom-Json
    if ($state.machine -ne $identity) { throw 'Restore state belongs to another computer' }
    $savedScheme = [Guid]$state.policy.scheme
    $current = Read-Policy $savedScheme
    if (($current.ac -ne 0 -or $current.dc -ne 0) -and
        ($current.ac -ne $state.policy.ac -or $current.dc -ne $state.policy.dc)) {
        throw 'The policy changed outside this comparison. Restore manually from restore-state.json rather than overwriting that change.'
    }
    Write-Policy $savedScheme ([uint32]$state.policy.ac) ([uint32]$state.policy.dc) ($savedScheme -eq $active)
    $stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssfffZ')
    Move-Item -LiteralPath $statePath -Destination (Join-Path $folder ('restored-state-' + $stamp + '.json'))
    Write-Host 'Original values restored. A different active power plan, if selected, was left active.'
}
$devices = @(Get-PnpDevice -ErrorAction Stop | Where-Object {
    $_.InstanceId -match 'VID_048D&PID_(C100|89DB)' -or $_.Class -eq 'Keyboard'
} | Select-Object Status,Class,FriendlyName,InstanceId,Problem)
$record = @{
    utc=(Get-Date).ToUniversalTime().ToString('o'); action=$Action;
    owner_reported_keyboard=$Keyboard; owner_note=$Note;
    model=[string]$machine.Model; product=[string]$product.Version;
    windows_build=[string]$os.BuildNumber; last_boot_utc=$os.LastBootUpTime.ToUniversalTime().ToString('o');
    active_scheme=$active.ToString(); policy_before=$before; policy_after=(Read-Policy $active);
    devices=$devices;
    limits='PnP inventory is not a USB transfer trace. Owner typing result is self-reported; this script does not test the built-in keyboard or measure USB suspend.'
}
$stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssfffZ')
$path = Join-Path $folder ('record-' + $stamp + '-' + [Guid]::NewGuid().ToString('N') + '.json')
$record | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $path -Encoding UTF8
Write-Host ('Saved: ' + $path)
Write-Host 'No firmware operation, device reset, shutdown or restart was performed.'
