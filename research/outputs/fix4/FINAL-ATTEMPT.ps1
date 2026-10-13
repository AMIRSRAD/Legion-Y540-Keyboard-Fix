$ErrorActionPreference = 'Stop'
$identity = [Security.Principal.WindowsIdentity]::GetCurrent()
$principal = New-Object Security.Principal.WindowsPrincipal($identity)
if (-not $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host 'Right-click RUN-FINAL-ATTEMPT.cmd and select Run as administrator.'
    exit 1
}
$root = $PSScriptRoot
$manifest = Get-Content -LiteralPath (Join-Path $root 'FILE-HASHES.json') -Raw | ConvertFrom-Json
foreach ($name in @('Y540Updater.exe', '44-nosleep-exp1.bin', '44-stock-restore.bin', 'SHFU.ini')) {
    $expected = $manifest.$name.sha256
    $actual = (Get-FileHash -LiteralPath (Join-Path $root $name) -Algorithm SHA256).Hash
    if (-not $expected -or $actual -ne $expected) { throw ('Package file verification failed: ' + $name) }
}
$stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssfffZ')
$recording = Join-Path $root ('final-recording-' + $stamp)
New-Item -ItemType Directory -Path $recording | Out-Null
$journal = Join-Path $recording 'capture-journal.txt'
$session = 'Y540Fix4-' + [Guid]::NewGuid().ToString('N')
$logman = Join-Path $env:SystemRoot 'System32\logman.exe'
$created = $false
$started = $false
$process = $null
$failure = $null
function Journal([string]$text) {
    Add-Content -LiteralPath $journal -Value ((Get-Date).ToUniversalTime().ToString('o') + ' ' + $text) -Encoding UTF8
}
function TraceCommand([string[]]$arguments) {
    Journal ('logman ' + ($arguments -join ' '))
    $saved = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    try { $result = & $logman @arguments 2>&1; $code = $LASTEXITCODE }
    finally { $ErrorActionPreference = $saved }
    foreach ($line in $result) { Journal ([string]$line) }
    if ($code -ne 0) { throw ('USB recording setup/cleanup failed: ' + $code) }
}
try {
    Journal 'Final user-authorized experiment. Wrapper records USB events and launches GUI; it never clicks Write, resets a device, or flashes automatically.'
    TraceCommand -arguments @('create','trace','-n',$session,'-o',(Join-Path $recording 'usb.etl'),'-f','bincirc','-max','128','-nb','16','64','-bs','64')
    $created = $true
    foreach ($provider in @('Microsoft-Windows-USB-USBXHCI','Microsoft-Windows-USB-UCX','Microsoft-Windows-USB-USBHUB3')) {
        TraceCommand -arguments @('update','trace','-n',$session,'-p',$provider,'(Default,StateMachine,HeadersBusTrace)')
    }
    TraceCommand -arguments @('start','-n',$session)
    $started = $true
    Write-Host 'USB recording started. In fix4: Validate firmware (5642), then Advanced firmware write ONCE.'
    Write-Host 'Wait for the final result. Close the fix4 window AFTER the operation settles so logs can be packaged.'
    Write-Host 'Do not close or power off while it reports erasing/writing.'
    Journal 'TRACE STARTED; launching interactive fix4 GUI.'
    $process = Start-Process -FilePath (Join-Path $root 'Y540Updater.exe') -WorkingDirectory $root -WindowStyle Normal -PassThru
    $timer = [Diagnostics.Stopwatch]::StartNew()
    while (-not $process.HasExited -and $timer.Elapsed.TotalSeconds -lt 300) {
        Start-Sleep -Milliseconds 250
        $process.Refresh()
    }
    if (-not $process.HasExited) {
        Journal 'Five-minute trace cap reached. Updater is left running; no interruption performed.'
        TraceCommand -arguments @('stop','-n',$session)
        $started = $false
        Write-Host 'Recording cap reached. Let the updater settle, then close its window. It has NOT been stopped.'
        Wait-Process -Id $process.Id
    }
    Journal 'Updater exited; preparing completed logs.'
} catch {
    $failure = $_.Exception.Message
    Write-Host $failure
    try { Journal ('ERROR: ' + $failure) } catch {}
} finally {
    if ($started) {
        try { TraceCommand -arguments @('stop','-n',$session); $started = $false }
        catch { Write-Host ('Trace stop failed. Retain session name: ' + $session) }
    }
    if ($created -and -not $started) {
        try { TraceCommand -arguments @('delete','-n',$session) } catch { Write-Host 'Trace definition cleanup failed; see journal.' }
    }
}
if ($process -and -not $process.HasExited) {
    Write-Host 'Updater is still running. No further device operation was initiated. Wait for its result.'
    exit 1
}
$logs = Join-Path $root 'logs'
if (Test-Path -LiteralPath $logs) { Copy-Item -LiteralPath $logs -Destination (Join-Path $recording 'updater-logs') -Recurse }
Copy-Item -LiteralPath (Join-Path $root 'patch-manifest.json'),(Join-Path $root 'FILE-HASHES.json') -Destination $recording
$archive = $recording + '.zip'
Compress-Archive -LiteralPath $recording -DestinationPath $archive -CompressionLevel Optimal
Write-Host ('SEND THIS FILE: ' + $archive)
if ($failure) { Write-Host 'Capture/setup had an error; keep the ZIP and do not retry automatically.' }
