$ErrorActionPreference = 'Stop'
$archiveStage = $PSScriptRoot
$verifiedLocal = Get-Content -LiteralPath (Join-Path $archiveStage 'LOCAL-VERIFICATION.json') -Raw | ConvertFrom-Json
$verifiedRemote = Get-Content -LiteralPath (Join-Path $archiveStage 'REMOTE-VERIFICATION.json') -Raw | ConvertFrom-Json
$verifiedSources = Get-Content -LiteralPath (Join-Path $archiveStage 'SOURCE-AUDIT.json') -Raw | ConvertFrom-Json
if ($verifiedLocal.status -ne 'passed' -or $verifiedRemote.status -ne 'passed' -or $verifiedSources.status -ne 'passed') { throw 'Preservation checks have not passed' }
$reaKept = 'C:\Users\a.saberi\Desktop\rea-rea-agents-6.4.0'
$expectedDirectories = @(
    'C:\Users\a.saberi\Documents\Codex\2026-10-12\https-github-com-morluto-rea-https',
    'C:\Users\a.saberi\Desktop\KeyboardFirmware-Issue',
    'C:\Users\a.saberi\Desktop\Tries',
    'C:\Users\a.saberi\Desktop\logs',
    'C:\Users\a.saberi\Desktop\Y540-keyboard-firmware-00000044'
)
$expectedFiles = @(
    'C:\Users\a.saberi\Desktop\bhcn45ww.exe',
    'C:\Users\a.saberi\Desktop\return-exp1-recording-20261013T095802730Z.zip'
)
# Resolve every target before the first deletion and require exact approved paths.
foreach ($target in ($expectedDirectories + $expectedFiles)) {
    $resolved = (Resolve-Path -LiteralPath $target).ProviderPath.TrimEnd('\')
    if (-not [string]::Equals($resolved, $target, [StringComparison]::OrdinalIgnoreCase)) { throw "Unexpected resolved target: $resolved" }
    if ($resolved.StartsWith($reaKept, [StringComparison]::OrdinalIgnoreCase)) { throw 'Would touch retained REA' }
}
foreach ($target in $expectedDirectories) {
    if (-not (Get-Item -LiteralPath $target).PSIsContainer) { throw 'Directory expected' }
}
if (-not (Test-Path -LiteralPath (Join-Path $reaKept 'ghidra\ghidraRun.bat'))) { throw 'Retained Ghidra missing' }
$beforeFree = (Get-PSDrive C).Free
$removed = @()
$emptyLockedFolders = @()
foreach ($target in $expectedDirectories) {
    Write-Output "Removing verified research copy: $target"
    try {
        Remove-Item -LiteralPath $target -Recurse -Force
    } catch {
        if ($target -eq $expectedDirectories[0] -and (Test-Path -LiteralPath $target) -and
            @(Get-ChildItem -LiteralPath $target -Force).Count -eq 0) {
            $emptyLockedFolders += $target
            Write-Output 'Only the empty active chat folder remains locked; all contents are removed.'
        } else { throw }
    }
    if ($target -notin $emptyLockedFolders) {
        if (Test-Path -LiteralPath $target) { throw "Deletion incomplete: $target" }
        $removed += $target
    }
}
foreach ($target in $expectedFiles) {
    Remove-Item -LiteralPath $target -Force
    if (Test-Path -LiteralPath $target) { throw "Deletion incomplete: $target" }
    $removed += $target
}
$receipt = [ordered]@{
    status = 'completed'
    owner_requested = $true
    completed_at = (Get-Date).ToString('o')
    removed_paths = $removed
    contents_removed_empty_folder_locked = $emptyLockedFolders
    retained_rea = $reaKept
    unrelated_desktop_and_shared_installed_tools_preserved = $true
    free_bytes_before_resume = $beforeFree
    free_bytes_after = (Get-PSDrive C).Free
    source_file_bytes_removed = 10090457183
    public_archive = 'https://github.com/AMIRSRAD/Y540-Keyboard/releases/tag/preservation-2026-10-13'
    missing_trace_explicitly_waived = 'fix9-recording-20261013T115002055Z.zip'
}
$receipt | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $archiveStage 'CLEANUP-RECEIPT.json') -Encoding utf8
Write-Output 'Research cleanup completed; staging is retained until receipt is pushed.'
