@echo off
REM Open the Borland Pascal 7 IDE with a program's main source loaded.
REM Usage: bp.bat [TARGET]   TARGET = OPL ^| EDD ^| FDA ^| SERVER  (default EDD)
REM
REM IDE keys: F9 compile, Ctrl+F8 breakpoint, Ctrl+F9 run, F7/F8 step,
REM Alt+F5 program screen, Alt+X quit.
REM After every F9 rebuild run utils\deploy.bat EDD before Ctrl+F9 -
REM the program loads EDD.OVR from C:\ and a stale one gives RTE 209.

setlocal
set TARGET=%1
if "%TARGET%"=="" set TARGET=EDD

if /i "%TARGET%"=="OPL"    set SRC=E:\FDP\OPL\APP\OPL.PAS
if /i "%TARGET%"=="EDD"    set SRC=E:\FDP\EDD\APP\EDD.PAS
if /i "%TARGET%"=="FDA"    set SRC=E:\FDP\FDA\APP\FDA.PAS
if /i "%TARGET%"=="SERVER" set SRC=E:\FDP\S\APP\SERVER.PAS
if "%SRC%"=="" echo Unknown target: %TARGET% (valid: OPL EDD FDA SERVER) & exit /b 1

cd /d "%~dp0..\.."
where dosbox-x.exe >nul 2>nul
if %errorlevel%==0 (
    dosbox-x.exe -conf dosbox-x.conf -c "D:\BP.EXE %SRC%"
) else (
    "C:\DOSBox-X\dosbox-x.exe" -conf dosbox-x.conf -c "D:\BP.EXE %SRC%"
)
