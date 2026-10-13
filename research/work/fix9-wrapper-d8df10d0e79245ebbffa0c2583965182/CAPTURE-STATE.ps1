param(
    [ValidateSet('working','failed','unknown')][string]$Keyboard = 'unknown',
    [string]$Note = ''
)
$ErrorActionPreference = 'Stop'
if (-not $PSBoundParameters.ContainsKey('Keyboard')) {
    $reply = Read-Host 'Built-in keyboard typing: working / failed / unknown'
    if ($reply -in @('working','failed','unknown')) { $Keyboard = $reply }
}
if (-not $Note) { $Note = Read-Host 'Short note (for example: restart 1 failed, waited 30 seconds)' }
$os = Get-CimInstance Win32_OperatingSystem
$machine = Get-CimInstance Win32_ComputerSystem
$devices = @(Get-PnpDevice | Where-Object {
    $_.InstanceId -like 'USB\*' -or $_.InstanceId -match 'VID_048D' -or $_.Class -eq 'Keyboard'
} | Select-Object Status,Class,FriendlyName,InstanceId,Problem)
$folder = Join-Path $PSScriptRoot 'state-records'
New-Item -ItemType Directory -Path $folder -Force | Out-Null
$stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssfffZ')
$record = @{
    utc=(Get-Date).ToUniversalTime().ToString('o'); model=[string]$machine.Model;
    last_boot_utc=$os.LastBootUpTime.ToUniversalTime().ToString('o');
    owner_reported_keyboard=$Keyboard; owner_note=$Note; devices=$devices;
    limits='Read-only metadata snapshot. Does not measure MCU reset, timer or physical keyboard input.'
}
$path = Join-Path $folder ('state-' + $stamp + '-' + [Guid]::NewGuid().ToString('N') + '.json')
$record | ConvertTo-Json -Depth 7 | Set-Content -LiteralPath $path -Encoding UTF8
Write-Host ('Saved: ' + $path)
Write-Host 'No updater, device reset or power-setting change was performed.'
