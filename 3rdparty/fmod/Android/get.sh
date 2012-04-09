#!/bin/sh
# Get the FMOD Ex binaries from their site, I won't distribute them
# directly from the repo.
#
# If you find that this script doesn't download the latest stable release
# of FMOD Ex, please drop me a line and I'll update it.
wget -c http://www.fmod.org/index.php/release/version/fmodapi44004android.tar.gz -O fmodapi.tar.gz

# Extract the things we need from the archive, dump the rest
tar xvzf fmodapi.tar.gz
cp -r fmodapi44004android/api/inc .
cp -r fmodapi44004android/api/lib .
cp -r fmodapi44004android/api/lib/* ../../../projects/android_fmod/libs/
rm -rf fmodapi44004android fmodapi.tar.gz
