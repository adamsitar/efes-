@echo off
E:
cd \FDP\OPL
echo Compiling OPL with debug symbols...
D:\BPC.EXE APP\OPL.PAS
echo.
if exist APP\OPL.EXE echo SUCCESS: OPL.EXE created
if not exist APP\OPL.EXE echo FAILED: check errors above
echo.
