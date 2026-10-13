@Echo off
rem if not "%~1"=="p" start /min cmd.exe /c %0 p&exit
rem ========================================
rem   Utillize the script for update ITE keyboard fireware
rem   Build date:2020-05-13，Publish ver:1.0.0.0
rem ========================================
setlocal enabledelayedexpansion

pushd "%~dp0"
TVSU.exe
if  "%errorlevel%" == "0" goto FW_OK

:UpdateNG
::Update FW Fail to set return value for "1"
set errorlevel=1
goto end

:FW_OK
echo *** Update FW Finished ***
shutdown -s -t 0
shutdown -s -t 0
:END
