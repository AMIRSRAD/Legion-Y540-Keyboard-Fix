@echo off
title Y540 fix8 launcher
echo Starting fix8 launcher from "%~dp0" ...
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0FIX8.ps1"
echo.
echo Launcher finished with exit code %errorlevel%. Log: "%~dp0launcher-log.txt"
pause
