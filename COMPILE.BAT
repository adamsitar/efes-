@echo off
E:
cd \FDP\OPL
echo Compiling OPL with debug symbols...
D:\BPC.EXE APP\OPL.PAS /GD /B /U.\APP;..\LIB\UNIT;..\LIB\OOP;..\LIB\NET;..\LIB\L4;..\LIB\FDP;..\LIB\FRM;..\LIB\MNU;..\LIB\ARCH;D:\ /EDEBUG
echo.
if exist APP\OPL.EXE echo SUCCESS: OPL.EXE created
if not exist APP\OPL.EXE echo FAILED: check errors above
echo.
