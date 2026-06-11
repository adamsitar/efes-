@echo off
REM Headless BPC build, parameterized by target program.
REM Args: %1 = subfolder under \FDP\  (e.g., OPL, EDD, FDA, S)
REM       %2 = main program file in \FDP\%1\APP\  (e.g., OPL, EDD, FDA, SERVER)
REM
REM Flags:
REM   /V    embed debug symbol table in EXE (required for source-level TD)
REM   /GD   write a detailed .MAP file (linker map)
REM   /$Y+  emit symbol-reference (Browser) info
REM   /$D+ and /$L+ are default-on per BPC -- left implicit
E:
cd \FDP\%1
D:\BPC.EXE E:\FDP\%1\APP\%2.PAS /V /GD /$Y+ > E:\COMPILE.LOG
