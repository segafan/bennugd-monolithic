@ECHO OFF

REM Go to the directory where this BAT file is located.
REM We need to do this when launched from the windows explorer.
CD %~d0%~p0

REM Remove any previous output before creating the new one
RMDIR /S /Q output\win32

REM Package the program
CALL c:\Python27\Scripts\cxfreeze.bat main.py --target-dir="output\win32" --base-name="Win32GUI" --include-modules="atexit,PyQt4.QtCore,PyQt4.QtGui,sqlite3,os,sys,uuid,shutil,subprocess" --icon="res/icon.ico"

REM Copy the templates to the output dir
XCOPY templates output\win32\templates /E /I
XCOPY res output\win32\res /E /I
DEL output\win32\res\icon.icns
DEL output\win32\res\BennuGD_Packager.tar.bz2
MOVE output\win32\main.exe "output\win32\BennuGD Packager.exe"