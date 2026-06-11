@echo off
REM Launch DOSBox-X interactively (Windows). The conf mounts drives via
REM relative paths, so run from the repo root (two levels up from here).
cd /d "%~dp0..\.."
where dosbox-x.exe >nul 2>nul
if %errorlevel%==0 (
    dosbox-x.exe -conf dosbox-x.conf
) else (
    "C:\DOSBox-X\dosbox-x.exe" -conf dosbox-x.conf
)
