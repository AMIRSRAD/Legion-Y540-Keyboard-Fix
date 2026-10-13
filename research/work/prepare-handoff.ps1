$ErrorActionPreference = 'Stop'
$workspace = (Get-Location).Path
$bundle = Join-Path $workspace 'outputs\handoff'
$toolkit = Join-Path $bundle '01-REA-Toolkit'
$dev = Join-Path $bundle '02-Y540-Development'
New-Item -ItemType Directory -Path $toolkit,$dev,(Join-Path $bundle '_copy-records') -Force | Out-Null
$script:copyRecords = @()
function Copy-Tree([string]$Source,[string]$Destination,[string[]]$ExcludeDirectories=@()) {
    $absoluteDestination = [IO.Path]::GetFullPath($Destination)
    if (-not $absoluteDestination.StartsWith($bundle + '\',[StringComparison]::OrdinalIgnoreCase)) { throw 'Copy destination outside handoff' }
    $log = Join-Path $bundle ('_copy-records\copy-' + $script:copyRecords.Count + '.log')
    $copyArguments = @($Source,$Destination,'/E','/COPY:DAT','/DCOPY:DAT','/R:1','/W:1','/XJ','/NFL','/NDL','/NP','/NJH','/NJS',('/LOG:'+$log),'/XF','*.lock')
    if ($ExcludeDirectories.Count) { $copyArguments += '/XD'; $copyArguments += $ExcludeDirectories }
    & robocopy.exe @copyArguments | Out-Null
    $code = $LASTEXITCODE
    $script:copyRecords += [pscustomobject]@{source=$Source;destination=$Destination;robocopy_exit=$code;log=$log}
    if ($code -ge 8) { throw ('Copy failed: '+$Source+' code='+$code) }
    Write-Output ('Copied '+$Source)
}
Copy-Tree 'C:\Users\a.saberi\Desktop\rea-rea-agents-6.4.0' (Join-Path $toolkit 'rea-rea-agents-6.4.0') @('C:\Users\a.saberi\Desktop\rea-rea-agents-6.4.0\.cache','C:\Users\a.saberi\Desktop\rea-rea-agents-6.4.0\.turbo')
Copy-Tree 'C:\Users\a.saberi\Documents\Codex\tools\ghidra_12.1.4_PUBLIC' (Join-Path $toolkit 'ghidra')
Copy-Tree 'C:\Program Files\Java\jdk-23' (Join-Path $toolkit 'java')
Copy-Tree 'C:\Program Files\nodejs' (Join-Path $toolkit 'node')
Copy-Tree 'C:\Users\a.saberi\.agents\skills\reverse-engineer-anything' (Join-Path $toolkit 'skills\reverse-engineer-anything')
# Critical: exclude the entire destination root while copying its outputs parent.
Copy-Tree (Join-Path $workspace 'outputs') (Join-Path $dev 'outputs') @($bundle)
Copy-Tree (Join-Path $workspace 'work') (Join-Path $dev 'work')
Copy-Tree 'C:\Users\a.saberi\Desktop\KeyboardFirmware-Issue' (Join-Path $dev 'original-case')
Copy-Tree 'C:\Strawberry\c' (Join-Path $dev 'toolchain\mingw')
Copy-Tree 'C:\Users\a.saberi\AppData\Local\Programs\Python\Python313' (Join-Path $dev 'toolchain\python')
$incoming = Join-Path $dev 'incoming-originals'
foreach ($name in @('workingstate','nonworking','update-ones','New folder (2)','New folder (3)','New folder (4)','y540-linux','logs','Y540-keyboard-firmware-00000044','recording-20261012T135023471Z','recording-20261012T141255304Z')) {
    $source = Join-Path 'C:\Users\a.saberi\Desktop' $name
    if (Test-Path -LiteralPath $source -PathType Container) { Copy-Tree $source (Join-Path $incoming $name) }
}
foreach ($name in @('recording-20261012T135023471Z.zip','recording-20261012T141255304Z.zip')) {
    $source = Join-Path 'C:\Users\a.saberi\Desktop' $name
    if (Test-Path -LiteralPath $source -PathType Leaf) { Copy-Item -LiteralPath $source -Destination $incoming }
}
$script:copyRecords | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $bundle 'copy-records.json') -Encoding UTF8
Write-Output 'Handoff copy complete.'
