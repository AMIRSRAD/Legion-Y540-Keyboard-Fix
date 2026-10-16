param(
    [Parameter(Mandatory = $true)][ValidateSet('Arm', 'Collect', 'Remove')][string]$Action,
    [ValidateSet('dead', 'works', 'unsure')][string]$Outcome = 'unsure'
)
# Y540 boot-time USB trace. Records Windows USB driver events (USBXHCI, UCX,
# USBHUB3; Default, StateMachine, HeadersBusTrace, USBError, Power, PnP, Enumeration
# keywords only - never PartialDataBusTrace or FullDataBusTrace, so no transfer
# payloads) from early boot. No firmware, device, BIOS or power setting is changed.
$ErrorActionPreference = 'Stop'
$BootSession = 'Y540UsbBoot'
$ShutdownSession = 'Y540UsbShutdown'
$Work = Join-Path $env:ProgramData 'Y540BootTrace'
$StateFile = Join-Path $Work 'state.json'
$Journal = Join-Path $Work 'capture-journal.txt'
$Logman = Join-Path $env:SystemRoot 'System32\logman.exe'
$Providers = @('Microsoft-Windows-USB-USBXHCI', 'Microsoft-Windows-USB-UCX', 'Microsoft-Windows-USB-USBHUB3')
$Keywords = @('Default', 'StateMachine', 'HeadersBusTrace', 'USBError', 'Power', 'PnP', 'Enumeration')

function Write-Journal([string]$Text) {
    $line = (Get-Date).ToUniversalTime().ToString('o') + ' ' + $Text
    try { Add-Content -LiteralPath $Journal -Value $line -Encoding UTF8 } catch { }
    Write-Host $Text
}

function Invoke-Logman([string[]]$Arguments, [switch]$AllowFailure) {
    Write-Journal ('logman ' + ($Arguments -join ' '))
    $saved = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    try { $out = & $Logman @Arguments 2>&1; $code = $LASTEXITCODE } finally { $ErrorActionPreference = $saved }
    foreach ($l in $out) { Write-Journal ('  ' + [string]$l) }
    Write-Journal ('  exit_code=' + $code)
    if ($code -ne 0 -and -not $AllowFailure) { throw ('logman failed (' + $code + '); see ' + $Journal) }
    return $code
}

# Resolve provider GUIDs and the exact keyword bits on THIS machine, so no
# unlisted keyword (for example a data-payload keyword) is ever enabled.
function Get-ProviderLines {
    $lines = @()
    foreach ($name in $Providers) {
        $out = & $Logman query providers $name 2>&1 | ForEach-Object { [string]$_ }
        $guid = $null; $mask = [UInt64]0; $found = @()
        foreach ($l in $out) {
            if (-not $guid -and $l -match ('^\s*' + [regex]::Escape($name) + '\s+(\{[0-9A-Fa-f-]{36}\})')) { $guid = $Matches[1] }
            if ($l -match '^\s*0x([0-9A-Fa-f]{1,16})\s+(\S+)') {
                if ($Keywords -contains $Matches[2]) {
                    $mask = $mask -bor [Convert]::ToUInt64($Matches[1], 16); $found += $Matches[2]
                }
            }
        }
        if (-not $guid) { throw ('Provider not found on this Windows: ' + $name) }
        if ($mask -eq 0) { throw ('None of the keywords ' + ($Keywords -join ',') + ' found for ' + $name) }
        Write-Journal ($name + ' ' + $guid + ' keywords=' + ($found -join ',') + (' mask=0x{0:X}' -f $mask))
        $lines += ('{0} 0x{1:X} 0xFF' -f $guid, $mask)
    }
    return $lines
}

function Save-Inventory([string]$Path) {
    $rows = @()
    try {
        $devs = Get-PnpDevice -ErrorAction SilentlyContinue | Where-Object {
            $_.InstanceId -match 'VID_048D|VID_0000&PID_0002|DEVICE_DESCRIPTOR_FAILURE|ROOT_HUB30|VID_30C9' }
        foreach ($d in $devs) {
            $problem = $null; $loc = $null
            try { $problem = (Get-PnpDeviceProperty -InstanceId $d.InstanceId -KeyName DEVPKEY_Device_ProblemCode -ErrorAction Stop).Data } catch { }
            try { $loc = (Get-PnpDeviceProperty -InstanceId $d.InstanceId -KeyName DEVPKEY_Device_LocationPaths -ErrorAction Stop).Data } catch { }
            $rows += [pscustomobject]@{ InstanceId = $d.InstanceId; Name = $d.FriendlyName; Class = $d.Class;
                Status = [string]$d.Status; Present = $d.Present; ProblemCode = $problem; LocationPaths = $loc }
        }
    } catch { Write-Journal ('Inventory error: ' + $_.Exception.Message) }
    $rows | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $Path -Encoding UTF8
    $kb = $rows | Where-Object { $_.InstanceId -match 'VID_048D&PID_C100' -and $_.Present }
    $bad = $rows | Where-Object { $_.InstanceId -match 'VID_0000&PID_0002|DEVICE_DESCRIPTOR_FAILURE' -and $_.Present }
    Write-Journal ('Inventory ' + (Split-Path -Leaf $Path) + ': keyboard C100 present=' + [bool]$kb + ', descriptor-failure placeholder present=' + [bool]$bad)
}

function Save-Platform([string]$Dir) {
    try {
        Get-CimInstance Win32_OperatingSystem | Select-Object Caption, Version, BuildNumber, LastBootUpTime |
            ConvertTo-Json | Set-Content -LiteralPath (Join-Path $Dir 'windows.json') -Encoding UTF8
        Get-CimInstance Win32_ComputerSystem | Select-Object Manufacturer, Model, SystemFamily |
            ConvertTo-Json | Set-Content -LiteralPath (Join-Path $Dir 'machine.json') -Encoding UTF8
        Get-CimInstance Win32_BIOS | Select-Object SMBIOSBIOSVersion, ReleaseDate |
            ConvertTo-Json | Set-Content -LiteralPath (Join-Path $Dir 'bios.json') -Encoding UTF8
        $hb = (Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Power' -ErrorAction SilentlyContinue).HiberbootEnabled
        Write-Journal ('Fast Startup (HiberbootEnabled)=' + $hb)
    } catch { Write-Journal ('Platform metadata unavailable: ' + $_.Exception.Message) }
}

$principal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
if (-not $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host 'Administrator access is required. Close this window and run the .cmd file again, choosing Yes at the prompt.'
    exit 1
}
New-Item -ItemType Directory -Path $Work -Force | Out-Null

try {
    if ($Action -eq 'Arm') {
        $existing = & $Logman query "autosession\$BootSession" 2>&1
        if ($LASTEXITCODE -eq 0) { throw 'A boot trace is already armed. Run 2-COLLECT (after restarting) or 3-REMOVE-BOOT-TRACE first.' }
        Get-ChildItem -LiteralPath $Work -File -ErrorAction SilentlyContinue | Remove-Item -Force
        Write-Journal 'ARM: boot-time USB trace. No firmware/device/BIOS/power change is made.'
        Save-Platform $Work
        Save-Inventory (Join-Path $Work 'inventory-before-restart.json')
        $pf = Join-Path $Work 'providers.txt'
        Get-ProviderLines | Set-Content -LiteralPath $pf -Encoding ASCII
        # 1) Boot logger: starts automatically on the next boot, before the USB stack loads.
        Invoke-Logman @('create', 'trace', "autosession\$BootSession", '-o', (Join-Path $Work 'boot.etl'),
            '-pf', $pf, '-f', 'bincirc', '-max', '256', '-nb', '16', '64', '-bs', '64', '-ft', '1') | Out-Null
        # 2) Shutdown-side trace: runs now until Windows stops it while restarting (best effort).
        Invoke-Logman @('start', $ShutdownSession, '-o', (Join-Path $Work 'shutdown.etl'),
            '-pf', $pf, '-f', 'bincirc', '-max', '128', '-nb', '16', '64', '-bs', '64', '-ft', '1', '-ets') -AllowFailure | Out-Null
        @{ armed_utc = (Get-Date).ToUniversalTime().ToString('o'); boot_session = $BootSession } |
            ConvertTo-Json | Set-Content -LiteralPath $StateFile -Encoding UTF8
        Write-Journal 'ARMED.'
        Write-Host ''
        Write-Host '=== BOOT TRACE ARMED ==='
        Write-Host 'Now do ONE ordinary restart: Start > Power > Restart.'
        Write-Host 'Do not hold the power button. Do not use Shift.'
        Write-Host 'After Windows is back, use an external keyboard/mouse to run'
        Write-Host '2-COLLECT-KEYBOARD-DEAD.cmd or 2-COLLECT-KEYBOARD-WORKS.cmd.'
        Write-Host 'Note where the built-in keyboard stopped working, if it did (F2/BIOS, PIN screen, desktop).'
        exit 0
    }

    if ($Action -eq 'Collect') {
        if (-not (Test-Path -LiteralPath $StateFile)) { throw 'Nothing armed. Run 1-ARM-BOOT-TRACE.cmd first.' }
        Write-Journal ('COLLECT: owner-reported outcome=' + $Outcome)
        Save-Inventory (Join-Path $Work 'inventory-after-restart.json')
        Save-Platform $Work
        Invoke-Logman @('stop', $BootSession, '-ets') -AllowFailure | Out-Null
        Invoke-Logman @('delete', "autosession\$BootSession") -AllowFailure | Out-Null
        Invoke-Logman @('stop', $ShutdownSession, '-ets') -AllowFailure | Out-Null
        $lastTwoHours = '/q:*[System[TimeCreated[timediff(@SystemTime) <= 7200000]]]'
        foreach ($log in @('System', 'Microsoft-Windows-Kernel-PnP/Configuration', 'Microsoft-Windows-Kernel-Boot/Operational')) {
            $file = Join-Path $Work (($log -replace '[\\/]', '_') + '.evtx')
            & wevtutil.exe epl $log $file $lastTwoHours 2>&1 | Out-Null
            Write-Journal ('export ' + $log + ' exit=' + $LASTEXITCODE)
        }
        & powercfg.exe /a 2>&1 | Set-Content -LiteralPath (Join-Path $Work 'powercfg-a.txt') -Encoding UTF8
        $etls = @(Get-ChildItem -LiteralPath $Work -Filter '*.etl' -File)
        Write-Journal ('ETL files: ' + (($etls | ForEach-Object { $_.Name + '=' + $_.Length }) -join ', '))
        $stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssZ')
        $desktop = [Environment]::GetFolderPath('Desktop')
        $zip = Join-Path $desktop ('Y540-boot-trace-' + $stamp + '-keyboard-' + $Outcome + '.zip')
        Compress-Archive -Path (Join-Path $Work '*') -DestinationPath $zip -CompressionLevel Optimal
        Remove-Item -LiteralPath $StateFile -Force
        Get-ChildItem -LiteralPath $Work -File | Remove-Item -Force -ErrorAction SilentlyContinue
        Write-Host ''
        Write-Host ('=== DONE. SEND THIS FILE: ' + $zip + ' ===')
        if ($etls.Count -eq 0) { Write-Host 'WARNING: no trace file was produced; send the ZIP anyway (it has the journal).' }
        Write-Host 'The boot trace is removed and will not run again.'
        exit 0
    }

    if ($Action -eq 'Remove') {
        Invoke-Logman @('stop', $BootSession, '-ets') -AllowFailure | Out-Null
        Invoke-Logman @('delete', "autosession\$BootSession") -AllowFailure | Out-Null
        Invoke-Logman @('stop', $ShutdownSession, '-ets') -AllowFailure | Out-Null
        Remove-Item -LiteralPath $StateFile -Force -ErrorAction SilentlyContinue
        Write-Host 'Boot trace removed. Nothing will record on the next boot.'
        exit 0
    }
} catch {
    Write-Journal ('ERROR: ' + $_.Exception.Message)
    Write-Host ''
    Write-Host ('FAILED: ' + $_.Exception.Message)
    Write-Host ('Journal: ' + $Journal)
    exit 1
}
