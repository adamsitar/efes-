@echo off
echo ÿ
echo Heslo pre ukoncenie programu je "UKBB".
echo ÿ
pause
echo Initialize files...
copy .\inst\edd\*.* *.* > Null
echo Done.
savedate
edd
readdate
copy *.kod .\inst\edd\*.kod > Null

