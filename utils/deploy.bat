@echo off
REM Deploy a built EXE+OVR pair (matched, from one compile) into the demo
REM dir. Run after EVERY rebuild (IDE F9 or build-headless) before running
REM the program - it loads its OVR from C:\ and a stale one gives
REM "Overlay manager error (-1)" or RTE 209.
REM
REM Usage: deploy.bat EDD            deploy the self-built pair
REM        deploy.bat EDD shipped    restore the shipped 1999 pair

setlocal
set TARGET=%1
if "%TARGET%"=="" set TARGET=EDD

set INST=
if /i "%TARGET%"=="EDD" set INST=IDD
if /i "%TARGET%"=="OPL" set INST=OPL
if "%INST%"=="" echo Unknown target: %TARGET% (valid: EDD OPL) & exit /b 1

cd /d "%~dp0.."

if /i "%2"=="shipped" (
    set SRC=fdp.demo\idd\INST\%INST%
) else (
    set SRC=fdp.source\FDP\%TARGET%\APP
)

if not exist "%SRC%\%TARGET%.EXE" echo Missing %SRC%\%TARGET%.EXE - build first & exit /b 1
if not exist "%SRC%\%TARGET%.OVR" echo Missing %SRC%\%TARGET%.OVR - build first & exit /b 1

copy /y "%SRC%\%TARGET%.EXE" fdp.demo\idd\ >nul
copy /y "%SRC%\%TARGET%.OVR" fdp.demo\idd\ >nul
echo Deployed %TARGET% pair from %SRC% to fdp.demo\idd\
