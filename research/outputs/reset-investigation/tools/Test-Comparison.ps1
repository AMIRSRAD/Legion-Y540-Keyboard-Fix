param([string]$Script = (Join-Path $PSScriptRoot '..\Compare-UsbPower.ps1'))
$ErrorActionPreference = 'Stop'
# A fake native provider prevents any Windows power-policy call. The script is
# copied to a fresh temporary test directory so its records are isolated.
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
namespace Y540Comparison {
 public static class Power {
  public static Guid Scheme = new Guid("11111111-2222-3333-4444-555555555555");
  public static uint AC=1, DC=1; public static int Writes=0, Apply=0;
  public static bool FailDCOnce=false;
  public static uint PowerGetActiveScheme(IntPtr root,out IntPtr p) { p=Marshal.AllocHGlobal(16); Marshal.StructureToPtr(Scheme,p,false); return 0; }
  public static uint PowerReadACValueIndex(IntPtr r,ref Guid a,ref Guid b,ref Guid c,out uint v) { v=AC; return 0; }
  public static uint PowerReadDCValueIndex(IntPtr r,ref Guid a,ref Guid b,ref Guid c,out uint v) { v=DC; return 0; }
  public static uint PowerWriteACValueIndex(IntPtr r,ref Guid a,ref Guid b,ref Guid c,uint v) { AC=v; Writes++; return 0; }
  public static uint PowerWriteDCValueIndex(IntPtr r,ref Guid a,ref Guid b,ref Guid c,uint v) { Writes++; if(FailDCOnce) { FailDCOnce=false; return 5; } DC=v; return 0; }
  public static uint PowerSetActiveScheme(IntPtr r,ref Guid a) { Apply++; return 0; }
  public static IntPtr LocalFree(IntPtr p) { Marshal.FreeHGlobal(p); return IntPtr.Zero; }
 }
}
'@
$global:y540FixtureModel = '81SX'
function Get-CimInstance([string]$ClassName) {
    switch ($ClassName) {
        'Win32_ComputerSystem' { return [pscustomobject]@{Manufacturer='LENOVO';Model=$global:y540FixtureModel} }
        'Win32_ComputerSystemProduct' { return [pscustomobject]@{Version='';UUID='aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee'} }
        'Win32_OperatingSystem' { return [pscustomobject]@{BuildNumber='fixture';LastBootUpTime=[DateTime]::UtcNow.AddHours(-1)} }
    }
}
function Get-PnpDevice { return @() }
function New-Object([string]$TypeName,[object[]]$ArgumentList) {
    if ($TypeName -eq 'Security.Principal.WindowsPrincipal') {
        $principal = [pscustomobject]@{}
        $principal | Add-Member -MemberType ScriptMethod -Name IsInRole -Value { param($Role) return $true }
        return $principal
    }
    return Microsoft.PowerShell.Utility\New-Object -TypeName $TypeName -ArgumentList $ArgumentList
}
$root = Join-Path ([IO.Path]::GetTempPath()) ('y540-policy-test-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $root | Out-Null
$copy = Join-Path $root 'Compare-UsbPower.ps1'
Copy-Item -LiteralPath $Script -Destination $copy
$cases = 0
& $copy -Action Record -Keyboard working -Note fixture
if ([Y540Comparison.Power]::Writes -ne 0) { throw 'Record changed power settings' }; $cases++
& $copy -Action Disable
if ([Y540Comparison.Power]::AC -ne 0 -or [Y540Comparison.Power]::DC -ne 0) { throw 'Disable failed' }; $cases++
$state = Join-Path $root 'comparison-records\restore-state.json'
if (-not (Test-Path -LiteralPath $state)) { throw 'Original policy not saved' }; $cases++
$blocked = $false
try { & $copy -Action Disable } catch { $blocked = $true }
if (-not $blocked) { throw 'Repeated Disable overwrote restore state' }; $cases++
& $copy -Action Restore
if ([Y540Comparison.Power]::AC -ne 1 -or [Y540Comparison.Power]::DC -ne 1 -or (Test-Path -LiteralPath $state)) { throw 'Restore failed' }; $cases++
$global:y540FixtureModel = 'Different computer'
$writes = [Y540Comparison.Power]::Writes
$blocked = $false
try { & $copy -Action Disable } catch { $blocked = $true }
if (-not $blocked -or [Y540Comparison.Power]::Writes -ne $writes) { throw 'Wrong-machine guard failed' }; $cases++
$global:y540FixtureModel = '81SX'
[Y540Comparison.Power]::FailDCOnce = $true
$blocked = $false
try { & $copy -Action Disable } catch { $blocked = $true }
if (-not $blocked -or [Y540Comparison.Power]::AC -ne 1 -or [Y540Comparison.Power]::DC -ne 1) { throw 'Partial-failure rollback failed' }; $cases++
if (-not (Test-Path -LiteralPath $state)) { throw 'Failed comparison lost restore state' }; $cases++
& $copy -Action Restore
# A different active scheme must not be activated during restoration.
& $copy -Action Disable
[Y540Comparison.Power]::Scheme = [Guid]'99999999-2222-3333-4444-555555555555'
$apply = [Y540Comparison.Power]::Apply
& $copy -Action Restore
if ([Y540Comparison.Power]::Apply -ne $apply) { throw 'Restore switched the active plan' }; $cases++
Write-Output ('PASS: ' + $cases + ' mocked power-policy checks; no native power/device APIs called. Test files: ' + $root)

