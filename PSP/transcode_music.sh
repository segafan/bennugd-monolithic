#!/bin/bash

########################################################################
#                                                                      #
# This script will convert your music to a format supported            #
# by BennuGD-Wii using VLC.                                            #
# Copyright (C) 2010 - Joseba García Etxebarria <joseba.gar@gmail.com> #
#                                                                      #
########################################################################

VLC="cvlc --ignore-config";	# vlc variant, cvlc is fine  if available,
			# "vlc -I dummy" is fine, too (needed for win32)
RATE=96;		# kbps, 96 is enough
CHANNELS=2;		# 1 for mono, 2 for stereo
FREQ=48000;		# Leave this @ 48KHz
OUTOGG=converted_music;
OUTWAV=converted_wav;
NOTIFIER=$(which notify-send);
N=0;

cd $(dirname 0)

# Try to recode OGG and transcode MP3 & WMA files
for i in *.{ogg,mp3,wma}; do
	if [ -f $i ]; then
		if [ ! -f $OUTOGG/$i ]; then
		        if [ ! -d $OUTOGG ]; then
                		mkdir $OUTOGG;
		        fi
			echo
			echo Converting $i into $OUTOGG/$i
			echo ==================================================
			echo
			$VLC $i --sout="#transcode{acodec=vorb,ab=$RATE,channels=$CHANNELS,samplerate=$FREQ}:duplicate{dst=std{access=file,mux=ogg,dst='$OUTOGG/$i'}" "vlc://quit";
			N=$((N+1))
		fi
	fi
done

# Try to recode WAV files
for i in *.wav; do
	if [ -f $i ]; then
		if [ ! -f $OUTWAV/$i ]; then
			if [ ! -d $OUTWAV ]; then
				mkdir $OUTWAV;
			fi
			echo
			echo Converting $i into $OUTWAV/$i
			echo ==================================================
			echo
			$VLC $i --sout="#transcode{vcodec=none,acodec=s16l,ab=$RATE,channels=$CHANNELS,samplerate=$FREQ}:duplicate{dst=std{access=file,mux=wav,dst='$OUTWAV/$i'}" "vlc://quit";
			N=$((N+1))
			fi
        fi
done

# Try to let the user know I've finished transcoding the music
if [ -x $NOTIFIER ]; then
    if [ $N -eq 0 ]; then
		$NOTIFIER -i dialog-information "No files transcoded"
	else
		$NOTIFIER -i dialog-information "$N files transcoded"
	fi
fi

