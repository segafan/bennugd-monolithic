#!/bin/bash
WORKDIR=$(dirname $0)
cd "$WORKDIR"
WORKDIR=$(pwd)

function package_osx {
    mkdir -p $OUTPUTDIR
    cd $OUTPUTDIR
    tar xvjf ../../res/BennuGD_Packager.tar.bz2
    cd "BennuGD Packager.app/Contents/MacOS/"
    mkdir res
    cp $WORKDIR/*.py .
    cp -r $WORKDIR/templates .
    cp $WORKDIR/res/icon.png res
    
    for i in $(find * | grep svn); do
        if [ -d $i ]; then
            rm -rf $i
        fi
    done
    
    # Finally, patch main.py to point to python.org binaries
    # This is CRAP! but I cannot get cx_freeze to work on Mac
    sed -i '' 's/\/usr\/bin\/env python/\/Library\/Frameworks\/Python.framework\/Versions\/2.7\/bin\/python/g' main.py
    
    cd $WORKDIR
}

# Determine if we're on Linux or on Mac and set output dir
# accordingly
PLATFORM=$(uname)
if [ "$PLATFORM" = 'Darwin' ]; then
    OUTPUTDIR='output/OSX'
else
    OUTPUTDIR='output/linux'
fi


# Remove any previous output before creating the new one
if [ -d "$OUTPUTDIR" ]; then
    rm -rf $OUTPUTDIR
fi

# Package the program
if [ "$PLATFORM" = 'Darwin' ]; then
    package_osx
else
    package_linux
fi

