param(
    [ValidateRange(30, 300)][int]$Seconds = 180
)
$ErrorActionPreference = 'Stop'
$identity = [Security.Principal.WindowsIdentity]::GetCurrent()
$principal = New-Object Security.Principal.WindowsPrincipal($identity)
if (-not $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host 'Administrator access is needed to record Windows USB events.'
    Write-Host 'Close this window, then right-click CAPTURE-USB.cmd and choose Run as administrator.'
    exit 1
}

$session = 'Y540Diag-' + [Guid]::NewGuid().ToString('N')
$stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssfffZ')
$recording = Join-Path $PSScriptRoot ('recording-' + $stamp)
New-Item -ItemType Directory -Path $recording -ErrorAction Stop | Out-Null
$journal = Join-Path $recording 'capture-journal.txt'
$logman = Join-Path $env:SystemRoot 'System32\logman.exe'
$created = $false
$started = $false
$finished = $false
$failure = $null

function Write-Journal([string]$Text) {
    $line = (Get-Date).ToUniversalTime().ToString('o') + ' ' + $Text
    try { Add-Content -LiteralPath $journal -Value $line -Encoding UTF8 -ErrorAction Stop }
    catch { Write-Warning ('Journal write failed; trace cleanup will still be attempted: ' + $_.Exception.Message) }
}

function Invoke-TraceCommand([string[]]$Arguments) {
    Write-Journal ('logman ' + ($Arguments -join ' '))
    $savedPreference = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    try {
        $result = & $logman @Arguments 2>&1
        $resultCode = $LASTEXITCODE
    } finally {
        $ErrorActionPreference = $savedPreference
    }
    foreach ($line in $result) { Write-Journal ([string]$line) }
    Write-Journal ('exit_code=' + $resultCode)
    if ($resultCode -ne 0) { throw ('logman failed with exit code ' + $resultCode + '; see capture-journal.txt') }
}

try {
    Write-Journal 'USB diagnosis only: no device restart, HID feature report, firmware write, or power-policy change is performed by this script.'
    Write-Journal 'Operator scenario: keyboard already failing; observe one manually confirmed fix1 USB retry.'
    try {
        Get-CimInstance Win32_OperatingSystem | Select-Object Caption, Version, BuildNumber, LastBootUpTime |
            ConvertTo-Json | Set-Content -LiteralPath (Join-Path $recording 'windows.json') -Encoding UTF8
        Get-CimInstance Win32_ComputerSystem | Select-Object Manufacturer, Model, SystemFamily |
            ConvertTo-Json | Set-Content -LiteralPath (Join-Path $recording 'machine.json') -Encoding UTF8
    } catch { Write-Journal ('Optional platform metadata unavailable: ' + $_.Exception.Message) }

    Invoke-TraceCommand -Arguments @('create', 'trace', '-n', $session, '-o', (Join-Path $recording 'usb.etl'), '-f', 'bincirc', '-max', '128', '-nb', '16', '64', '-bs', '64')
    $created = $true
    foreach ($provider in @('Microsoft-Windows-USB-USBXHCI', 'Microsoft-Windows-USB-UCX', 'Microsoft-Windows-USB-USBHUB3')) {
        Invoke-TraceCommand -Arguments @('update', 'trace', '-n', $session, '-p', $provider, '(Default,StateMachine,HeadersBusTrace)')
    }
    Invoke-TraceCommand -Arguments @('start', '-n', $session)
    $started = $true
    Write-Journal 'TRACE STARTED. Events before this moment are not recorded.'
    Write-Host ''
    Write-Host 'USB RECORDING IS RUNNING (maximum 3 minutes by default).'
    Write-Host 'In fix1: Diagnose + save log, Retry USB (no flash) ONCE, wait 10 seconds, Diagnose again.'
    Write-Host 'Then return to THIS window and press ENTER. Do not restart Windows during this capture.'
    Write-Host 'Recording stops automatically at the time limit. No firmware update is needed.'
    Write-Host ''
    $timer = [Diagnostics.Stopwatch]::StartNew()
    while ($timer.Elapsed.TotalSeconds -lt $Seconds) {
        if ([Console]::KeyAvailable) {
            $key = [Console]::ReadKey($true)
            if ($key.Key -eq [ConsoleKey]::Enter) { break }
        }
        Start-Sleep -Milliseconds 250
    }
    Write-Journal ('Capture wait ended at ' + [Math]::Round($timer.Elapsed.TotalSeconds, 1) + ' seconds.')
    $finished = $true
} catch {
    $failure = $_.Exception.Message
    Write-Host ('Capture failed: ' + $failure)
    Write-Journal ('ERROR: ' + $failure)
} finally {
    if ($started) {
        try {
            Invoke-TraceCommand -Arguments @('stop', '-n', $session)
            $started = $false
            Write-Journal 'TRACE STOPPED.'
        } catch {
            $finished = $false
            Write-Journal ('STOP FAILED: ' + $_.Exception.Message)
            Write-Host ('Stop failed. In an administrator terminal run: logman stop -n ' + $session)
        }
    }
    if ($created) {
        try { Invoke-TraceCommand -Arguments @('delete', '-n', $session) }
        catch {
            Write-Journal ('DELETE FAILED: ' + $_.Exception.Message)
            Write-Host ('Session definition cleanup failed: logman delete -n ' + $session)
        }
    }
}

Write-Host ''
Write-Host ('Saved recording folder: ' + $recording)
$traces = @(Get-ChildItem -LiteralPath $recording -Filter '*.etl' -File)
if ($finished -and $traces.Count -gt 0) {
    $archive = $recording + '.zip'
    try {
        Compress-Archive -LiteralPath $recording -DestinationPath $archive -CompressionLevel Optimal
        Write-Host ('SEND THIS FILE: ' + $archive)
        Write-Host 'Also send the new fix1 Diagnose / USB retry logs from its Open logs folder button.'
        Write-Host 'Tell us whether typing changed. Windows accepting a reset is not proof of recovery.'
    } catch {
        Write-Host ('ZIP creation failed; retain the recording folder: ' + $_.Exception.Message)
        exit 1
    }
} else {
    Write-Host 'Capture did not finish successfully. Send capture-journal.txt so the failure can be diagnosed.'
    exit 1
}
