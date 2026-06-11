@echo off
REM Open Turbo Debugger on the binary currently deployed in the demo dir.
REM Usage: td.bat [TARGET]   TARGET = OPL ^| EDD   (default EDD)
REM
REM Deploy a fresh BPC build first (utils\deploy.bat EDD). MEMORY WARNING:
REM real-mode TD + symbol table share 640 KB with the program; EDD's full
REM startup dies with exit code 203 - use the BP IDE (open\bp.bat) for
REM whole-program debugging. TD keys: F2 bkpt, F9 run, F7/F8 step, Alt+X quit.

setlocal
set TARGET=%1
if "%TARGET%"=="" set TARGET=EDD
if /i not "%TARGET%"=="EDD" if /i not "%TARGET%"=="OPL" echo Unknown target: %TARGET% (valid: EDD OPL) & exit /b 1

set SD=-sdE:\FDP\%TARGET%\APP -sdL:\UNIT -sdL:\OOP -sdL:\NET -sdL:\L4 -sdL:\FDP -sdL:\FRM

cd /d "%~dp0..\.."
where dosbox-x.exe >nul 2>nul
if %errorlevel%==0 (
    dosbox-x.exe -conf dosbox-x.conf -c "D:\TD.EXE %SD% C:\%TARGET%.EXE"
) else (
    "C:\DOSBox-X\dosbox-x.exe" -conf dosbox-x.conf -c "D:\TD.EXE %SD% C:\%TARGET%.EXE"
)
