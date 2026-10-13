ConvertTo-Json -InputObject @($args) -Compress | Set-Content -LiteralPath (Join-Path $PSScriptRoot 'arguments.json') -Encoding UTF8
if ($args -contains 'simulate-failure') { $global:LASTEXITCODE = 7 } else { $global:LASTEXITCODE = 0 }
Write-Output 'Fake tool; no trace or hardware APIs invoked.'
