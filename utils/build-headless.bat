@echo off
REM Compile a target with BPC under DOSBox-X (window flashes briefly).
REM Usage: build-headless.bat [TARGET]   TARGET = OPL ^| EDD ^| FDA ^| SERVER
REM Output: fdp.source\FDP\^<folder^>\APP\^<NAME^>.EXE (+.OVR, /V symbols)
REM Log:    fdp.source\COMPILE.LOG

setlocal
set TARGET=%1
if "%TARGET%"=="" set TARGET=EDD

set FOLDER=
if /i "%TARGET%"=="OPL"    set FOLDER=OPL& set PROGRAM=OPL
if /i "%TARGET%"=="EDD"    set FOLDER=EDD& set PROGRAM=EDD
if /i "%TARGET%"=="FDA"    set FOLDER=FDA& set PROGRAM=FDA
if /i "%TARGET%"=="SERVER" set FOLDER=S&   set PROGRAM=SERVER
if "%FOLDER%"=="" echo Unknown target: %TARGET% (valid: OPL EDD FDA SERVER) & exit /b 1

cd /d "%~dp0.."
del /q fdp.source\COMPILE.LOG 2>nul

where dosbox-x.exe >nul 2>nul
if %errorlevel%==0 (
    dosbox-x.exe -conf dosbox-x.conf -c "E:\BUILD.BAT %FOLDER% %PROGRAM%" -exit
) else (
    "C:\DOSBox-X\dosbox-x.exe" -conf dosbox-x.conf -c "E:\BUILD.BAT %FOLDER% %PROGRAM%" -exit
)

if exist "fdp.source\FDP\%FOLDER%\APP\%PROGRAM%.EXE" (
    echo SUCCESS: fdp.source\FDP\%FOLDER%\APP\%PROGRAM%.EXE produced.
    echo Now deploy it: utils\deploy.bat %TARGET%
) else (
    echo FAILED - check fdp.source\COMPILE.LOG
)
