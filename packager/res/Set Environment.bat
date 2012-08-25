@ECHO OFF

REM Go to the directory where this BAT file is located.
REM We need to do this when launched from the windows explorer.
CD %~d0%~p0

REM Read the current value for the user's PATH from the registry
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "HKCU\Environment" /v PATH') DO SET REGPATH=%%B
CALL REG add HKCU\Environment /v PATH /d "%REGPATH%;%CD%\ant_win\bin" /f
CALL REG add HKCU\Environment /v ANT_HOME /d "%CD%\ant_win" /f
