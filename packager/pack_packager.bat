@ECHO OFF

REM Go to the directory where this BAT file is located.
REM We need to do this when launched from the windows explorer.
CD %~d0%~p0

REM Remove any previous output before creating the new one
RMDIR /S /Q output\win32

REM Package the program
CALL c:\Python27_x32\Scripts\cxfreeze.bat main.py --target-dir output\win32 --base-name Win32GUI --include-modules atexit,PyQt4.QtCore,PyQt4.QtGui,sqlite3,os,sys,uuid,shutil

REM Copy the templates to the output dir
xcopy templates output\win32\templates /s /i
