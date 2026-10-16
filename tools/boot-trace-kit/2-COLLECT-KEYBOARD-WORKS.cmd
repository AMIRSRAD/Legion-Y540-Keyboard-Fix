@echo off
rem Runs Boot-Trace.ps1 as administrator (Windows will ask for permission).
powershell.exe -NoProfile -Command "Start-Process powershell.exe -Verb RunAs -ArgumentList @('-NoProfile','-ExecutionPolicy','Bypass','-NoExit','-File','\"%~dp0Boot-Trace.ps1\"','-Action Collect -Outcome works')"
