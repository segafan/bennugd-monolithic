#!/bin/sh
# Get the FMOD Ex binaries from their site, I won't distribute them
# directly from the repo.
#
# If you find that this script doesn't download the latest stable release
# of FMOD Ex, please drop me a line and I'll update it.
wget -c http://www.fmod.org/index.php/release/version/fmodapi44000iphone-installer.dmg -O /tmp/fmodapi.dmg

# Mount the image and extract the things we need from it
hdiutil attach /tmp/fmodapi.dmg 
cp -r "/Volumes/FMOD Programmers API iPhone/FMOD Programmers API/api/inc" .
cp -r "/Volumes/FMOD Programmers API iPhone/FMOD Programmers API/api/lib" .
diskutil unmount "/Volumes/FMOD Programmers API iPhone"
rm /tmp/fmodapi.dmg
