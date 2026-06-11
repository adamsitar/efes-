@echo off
REM Kill every running DOSBox-X instance (hung session, frozen window...).
taskkill /f /im dosbox-x.exe 2>nul
if %errorlevel%==0 (echo Killed DOSBox-X.) else (echo No DOSBox-X instances running.)
