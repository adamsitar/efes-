@echo off
cd /d "%~dp0"
where dosbox-x.exe >nul 2>nul
if %errorlevel%==0 (
    dosbox-x.exe -conf dosbox-x.conf
) else (
    "C:\DOSBox-X\dosbox-x.exe" -conf dosbox-x.conf
)
