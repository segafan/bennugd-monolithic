@echo off
REM
REM This script will convert your music to a format supported
REM by BennuGD-Wii using VLC.
REM Copyright (C) 2010 - Joseba García Etxebarria <joseba.gar@gmail.com>
REM

REM Go to the directory where this BAT file is located.
REM We need to do this when launched from the windows explorer.
CD %~d0%~p0

REM vlc variant, cvlc is fine  if available,
REM	"vlc -I dummy" is fine, too (needed for win32)
SET VLCDIR=%ProgramFiles%\VideoLAN\VLC
IF %PROCESSOR_ARCHITECTURE% == "AMD64" SET VLCDIR=%ProgramFiles(x86)%\VideoLAN\VLC
SET VLC=vlc.exe -I dummy --ignore-config
SET PATH=%PATH%;%VLCDIR%
REM kbps, 96 is enough
SET RATE=96
REM 1 for mono, 2 for stereo
SET CHANNELS=2
REM Leave this @ 48KHz for the Wii
SET FREQ=48000
REM Output dirs for OGG & WAV MUSIC
SET OUTOGG=converted_music
SET OUTWAV=converted_wav

REM Create the output directory, if it doesn't exist
IF NOT EXIST %OUTOGG%\NUL MD %OUTOGG%
REM Try to recode OGG and transcode MP3 & WMA files
FOR %%i in (*.ogg *.mp3 *.wma) DO CALL %VLC% %%i --sout=#transcode{acodec=vorb,ab=%RATE%,channels=%CHANNELS%,samplerate=%FREQ%}:duplicate{dst=std{access=file,mux=ogg,dst='%OUTOGG%/%%i'} vlc://quit 
IF EXIST %OUTOGG%\NUL (
        CD %OUTOGG%
        REN *.* *.ogg
)

REM Create the output directory, if it doesn't exist
IF NOT EXIST %OUTWAV%\NUL MD %OUTWAV%
REM Try to recode OGG and transcode MP3 & WMA files
FOR %%i in (*.wav) DO CALL %VLC% %%i --sout=#transcode{vcodec=none,acodec=s16l,ab=%RATE%,channels=%CHANNELS%,samplerate=%FREQ%}:duplicate{dst=std{access=file,mux=wav,dst='%OUTWAV%/%%i'} vlc://quit 
IF NOT EXIST %OUTWAV%\NUL (
        CD %OUTWAV%
        REN *.* *.wav
)
