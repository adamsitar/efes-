@echo off
REM Headless BPC build, parameterized by target program.
REM Args: %1 = subfolder under \FDP\  (e.g., OPL, EDD, FDA, S)
REM       %2 = main program file in \FDP\%1\APP\  (e.g., OPL, EDD, FDA, SERVER)
E:
cd \FDP\%1
D:\BPC.EXE APP\%2.PAS /GD > E:\COMPILE.LOG
