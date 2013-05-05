@ECHO OFF

REM Go to the directory where this BAT file is located.
REM This is needed when launched from the windows explorer.
CD %~d0%~p0

REM Remove any previous output before creating the new one
RMDIR /S /Q output\win32

REM Package the program
CALL c:\Python27\Scripts\cxfreeze.bat main.py --target-dir="output\win32" --include-modules="atexit,PyQt4.QtCore,PyQt4.QtGui,sqlite3,os,sys,uuid,shutil,subprocess" --icon="res/icon.ico"

REM Copy the templates to the output dir
COPY packager.bat "output\win32\BennuGD_Packager.bat"
XCOPY templates output\win32\templates /E /I
XCOPY res output\win32\res /E /I
DEL output\win32\res\icon.icns
DEL output\win32\res\BennuGD_Packager.tar.bz2
MOVE output\win32\main.exe "output\win32\BennuGD_Packager.exe"

REM Copy binary Java/ANT to the output folder
XCOPY 3rdparty\ant_win output\win32\ant /E /I
XCOPY 3rdparty\jdk_win output\win32\jdk /E /I