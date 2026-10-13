param(
    [string]$Compiler = '',
    [switch]$SkipTests
)
$ErrorActionPreference = 'Stop'
$projectRoot = $PSScriptRoot
if (-not $Compiler) {
    $foundCompiler = Get-Command gcc -ErrorAction SilentlyContinue
    if ($foundCompiler) { $Compiler = $foundCompiler.Source }
    elseif (Test-Path -LiteralPath 'C:\Strawberry\c\bin\gcc.exe') { $Compiler = 'C:\Strawberry\c\bin\gcc.exe' }
    else { throw 'Install a Windows MinGW-w64 GCC toolchain, or pass -Compiler C:\path\to\gcc.exe.' }
}
$toolDirectory = Split-Path -Parent (Get-Item -LiteralPath $Compiler).FullName
$resourceCompiler = Join-Path $toolDirectory 'windres.exe'
if (-not (Test-Path -LiteralPath $resourceCompiler)) { throw "windres.exe missing beside GCC: $toolDirectory" }
$buildDirectory = Join-Path $projectRoot 'build'
New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null
$env:PATH = "$toolDirectory;$env:PATH"
Push-Location $projectRoot
try {
    & $resourceCompiler src/app.rc -O coff -o build/app-res.o
    if ($LASTEXITCODE -ne 0) { throw 'Resource compilation failed.' }
    & $Compiler -std=c11 -O2 -Wall -Wextra -Werror -D_WIN32_WINNT=0x0601 src/app.c src/core.c src/hid_transport.c src/protocol.c build/app-res.o -o build/Y540Updater.exe -lsetupapi -lhid -lcomdlg32 -lgdi32 -luser32
    if ($LASTEXITCODE -ne 0) { throw 'Application compilation failed.' }
    if (-not $SkipTests) {
        & $Compiler -std=c11 -O2 -Wall -Wextra -Werror src/core.c src/core_tests.c -o build/core-tests.exe
        if ($LASTEXITCODE -ne 0) { throw 'Core test compilation failed.' }
        & ./build/core-tests.exe samples
        if ($LASTEXITCODE -ne 0) { throw 'Core tests failed.' }
        if (Test-Path -LiteralPath tests/test_hid_transport.c) {
            & $Compiler -std=c11 -O2 -Wall -Wextra -Werror -D_WIN32_WINNT=0x0601 -Isrc src/hid_transport.c tests/test_hid_transport.c -o build/hid-transport-tests.exe -lsetupapi -lhid
            if ($LASTEXITCODE -ne 0) { throw 'Transport test compilation failed.' }
            & ./build/hid-transport-tests.exe
            if ($LASTEXITCODE -ne 0) { throw 'Transport tests failed.' }
        }
        & $Compiler -std=c11 -O2 -Wall -Wextra -Werror -D_WIN32_WINNT=0x0601 src/core.c src/hid_transport.c src/protocol.c tests/test_protocol.c -o build/protocol-tests.exe -lsetupapi -lhid
        if ($LASTEXITCODE -ne 0) { throw 'Protocol test compilation failed.' }
        & ./build/protocol-tests.exe samples
        if ($LASTEXITCODE -ne 0) { throw 'Protocol emulator tests failed.' }
        & ./build/Y540Updater.exe --verify samples/44.bin samples/SHFU.ini
        if ($LASTEXITCODE -ne 0) { throw 'Compiled application sample verification failed.' }
        & ./build/Y540Updater.exe --gui-smoke
        if ($LASTEXITCODE -ne 0) { throw 'GUI initialization failed.' }
    }
    Write-Output "Built: $(Join-Path $buildDirectory 'Y540Updater.exe')"
} finally { Pop-Location }
