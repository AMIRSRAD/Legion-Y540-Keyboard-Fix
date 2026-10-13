$env:JAVA_HOME='C:\Program Files\Java\jdk-23'
$firmwareRoot=Join-Path (Get-Location) 'outputs\firmware44-analysis'
$projectRoot=Join-Path (Get-Location) 'work\fw44-ghidra-project'
New-Item -ItemType Directory -Force -Path $projectRoot | Out-Null
& 'C:\Users\a.saberi\Documents\Codex\tools\ghidra_12.1.4_PUBLIC\support\analyzeHeadless.bat' $projectRoot fw44 -import (Join-Path (Get-Location) 'outputs\y540-research\samples\44.bin') -loader BinaryLoader -processor '8051:BE:16:default' -cspec default -scriptPath (Join-Path (Get-Location) 'work\fw44-ghidra') -postScript ExportFirmware.java (Join-Path $firmwareRoot 'ghidra-static.json') -analysisTimeoutPerFile 180 -log (Join-Path $firmwareRoot 'ghidra.log') -scriptlog (Join-Path $firmwareRoot 'ghidra-script.log')
exit $LASTEXITCODE
