$env:JAVA_HOME='C:\Program Files\Java\jdk-23'
$firmwareRoot=Join-Path (Get-Location) 'outputs\firmware44-analysis'
$projectRoot=Join-Path (Get-Location) 'work\fw44-ghidra-project'
& 'C:\Users\a.saberi\Documents\Codex\tools\ghidra_12.1.4_PUBLIC\support\analyzeHeadless.bat' $projectRoot fw44 -process '44.bin' -scriptPath (Join-Path (Get-Location) 'work\fw44-ghidra') -postScript ExportFirmware.java (Join-Path $firmwareRoot 'ghidra-static-expanded.json') -analysisTimeoutPerFile 180 -log (Join-Path $firmwareRoot 'ghidra-expanded.log') -scriptlog (Join-Path $firmwareRoot 'ghidra-expanded-script.log')
exit $LASTEXITCODE
