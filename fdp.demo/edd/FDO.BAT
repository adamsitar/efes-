@echo off
echo ÿ
echo Heslo pre ukoncenie programu je "UKBB".
echo ÿ
pause
echo Initialize files...
copy .\inst\fdo\*.* *.* > Null
echo Done.
savedate
server
readdate
copy *.kod .\inst\fdo\*.kod > Null

