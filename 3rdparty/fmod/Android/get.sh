#!/bin/sh
# Get the FMOD Ex binaries from their site, I won't distribute them
# directly from the repo.
#
# If you find that this script doesn't download the latest stable release
# of FMOD Ex, please drop me a line and I'll update it.
wget -c http://www.fmod.org/index.php/release/version/fmodapi44000android.tar.gz -O fmodapi.tar.gz

# Extract the things we need from the archive, dump the rest
tar xvzf fmodapi.tar.gz
cp -r "fmodapi44000android/api/inc/" .
cp -r "fmodapi44000android/api/lib/" .
rm -rf fmodapi44000android fmodapi.tar.gz
