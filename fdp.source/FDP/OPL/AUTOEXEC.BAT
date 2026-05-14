@ECHO OFF
VERIFY OFF
PROMPT $P$G


:COMMON

PATH C:\BAT;C:\DOS;C:\NWLITE;C:\UTIL;
set TMP=D:\
set RECORDS=ARC

C:\DOS\mode con: RATE=32 DELAY=1

rem call C:\BAT\rasterex.bat
rem call C:\BAT\sysmenu.bat

call C:\UTIL\PCTCP\pctcp.bat
rem call C:\UTIL\PCTCP\ppp.bat
rem call C:\UTIL\PCTCP\snmp.bat

rem call C:\BAT\cache.bat 4096

rem call C:\BAT\spea.bat
rem call C:\BAT\tigasp.bat
rem call C:\BAT\rasterex.bat
rem call C:\BAT\mcrystal.bat
rem call C:\BAT\miro40.bat
call C:\BAT\video40e.bat

rem C:\UTIL\RASTEREX\rxinit.exe


C:\DOS\MSCDEX /d:MSCD001

C:\UTIL\MOUSE\mouse.exe

goto %CONFIG%


:OPL

smartdrv C+ /N
cd \OPL
call letvis.bat
goto X



:TCPIP

cd \LETVIS.UDP
call letvis.bat %CONFIG%
rem fall down to ADMIN mode
goto X



:UP3

cd \LETVIS.UP3
call letvis.bat %CONFIG%
rem fall down to ADMIN mode
goto X



:ADMIN

smartdrv C+ /N
cd \ADMIN
call letvis.bat
goto X


:X
