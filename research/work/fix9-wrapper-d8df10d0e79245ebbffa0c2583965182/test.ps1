$env:PSModulePath = (Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\Modules')
$script:mockLaunches=0
function Get-CimInstance([string]$ClassName) { return [pscustomobject]@{Manufacturer='LENOVO';Model='81SX';Version='Legion Y540-15IRH'} }
function Start-Process {
 param([string]$FilePath,[string]$WorkingDirectory,[string]$WindowStyle,[switch]$PassThru)
 $script:mockLaunches++
 New-Item -ItemType Directory -Path (Join-Path $WorkingDirectory 'logs') -Force | Out-Null
 Set-Content -LiteralPath (Join-Path $WorkingDirectory 'logs\completed.log') -Value 'MOCK no updater execution'
 return [pscustomobject]@{HasExited=$true;Id=0}
}
try { Start-Transcript -LiteralPath (Join-Path $PSScriptRoot 'launcher-log.txt') -Force | Out-Null } catch {}
Write-Host 'fix9 launcher: checking administrator rights...'
$ErrorActionPreference = 'Stop'
$identity = [Security.Principal.WindowsIdentity]::GetCurrent()
$principal = New-Object Security.Principal.WindowsPrincipal($identity)
if ($false) {
    Write-Host 'Right-click RUN-FIX8.cmd and select Run as administrator.'
    exit 1
}
$root = $PSScriptRoot
$machine = Get-CimInstance Win32_ComputerSystem
$product = Get-CimInstance Win32_ComputerSystemProduct
if (([string]$machine.Manufacturer -notmatch 'LENOVO') -or
    (([string]$machine.Model -notmatch '^81SX') -and ([string]$product.Version -notmatch 'Y540'))) {
    throw 'Use this return package only on the affected Lenovo Y540; not the development computer.'
}
Write-Host ('fix9 launcher: folder ' + $root)
$manifest = Get-Content -LiteralPath (Join-Path $root 'FILE-HASHES.json') -Raw | ConvertFrom-Json
foreach ($name in @('Y540Updater.exe', '44-recovery-exp3.bin', '44-nosleep-exp1.bin', 'SHFU.ini')) {
    $expected = $manifest.$name.sha256
    $actual = (Get-FileHash -LiteralPath (Join-Path $root $name) -Algorithm SHA256).Hash
    if (-not $expected -or $actual -ne $expected) { throw ('Package file verification failed: ' + $name) }
}
Write-Host 'fix9 launcher: package hashes OK'
$stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssfffZ')
$recording = Join-Path $root ('fix9-recording-' + $stamp)
New-Item -ItemType Directory -Path $recording | Out-Null
$journal = Join-Path $recording 'capture-journal.txt'
$session = 'Y540Fix9-' + [Guid]::NewGuid().ToString('N')
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
    try { $result = @('MOCK; no native trace API'); $code = 0 }
    finally { $ErrorActionPreference = $saved }
    foreach ($line in $result) { Journal ([string]$line) }
    if ($code -ne 0) { throw ('USB recording setup/cleanup failed: ' + $code) }
}
try {
    Journal 'fix9 session. Wrapper records USB events and launches the GUI; it never clicks Write, resets a device, or flashes automatically.'
    TraceCommand -arguments @('create','trace','-n',$session,'-o',(Join-Path $recording 'usb.etl'),'-f','bincirc','-max','128','-nb','16','64','-bs','64')
    $created = $true
    foreach ($provider in @('Microsoft-Windows-USB-USBXHCI','Microsoft-Windows-USB-UCX','Microsoft-Windows-USB-USBHUB3')) {
        TraceCommand -arguments @('update','trace','-n',$session,'-p',$provider,'(Default,StateMachine,HeadersBusTrace)')
    }
    TraceCommand -arguments @('start','-n',$session)
    $started = $true
    Write-Host 'USB recording started. In fix9: Validate firmware (0699), then Advanced firmware write ONCE.'
    Write-Host 'Wait for the final result. Close the fix9 window AFTER the operation settles so logs can be packaged.'
    Write-Host 'Do not close or power off while it reports erasing/writing.'
    Journal 'TRACE STARTED; launching interactive fix9 GUI.'
    $process = Start-Process -FilePath (Join-Path $root 'Y540Updater.exe') -WorkingDirectory $root -WindowStyle Normal -PassThru
    $timer = [Diagnostics.Stopwatch]::StartNew()
    while (-not $process.HasExited -and $timer.Elapsed.TotalSeconds -lt 1200) {
        Start-Sleep -Milliseconds 250
        $process.Refresh()
    }
    if (-not $process.HasExited) {
        Journal 'Twenty-minute trace cap reached. Updater is left running; no interruption performed.'
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

if ($script:mockLaunches -ne 1) { throw 'Wrong mock GUI launch count' }; Write-Output 'MOCK WRAPPER PASS'
