@ECHO OFF

REM Go to the directory where this BAT file is located.
REM This is needed when launched from the windows explorer.
CD %~d0%~p0

CD > tmp
SET /p dirbase= < tmp
DEL /f tmp
SET java_home=%dirbase%\jdk
SET path=%path%;%dirbase%\ant\bin;%dirbase%\jdk;%dirbase%\jdk\bin;%dirbase%\jdk\jre;%dirbase%\jdk\jre\bin;%dirbase%
SET ant_home=%dirbase%\ant
SET java_exe=%dirbase%\jdk\jre\bin\java.exe
SET javacmd=%dirbase%\jdk\jre\bin\java.exe

%dirbase%\BennuGD_Packager.exe