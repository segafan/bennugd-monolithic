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
    
    # Patch main.py to point to python.org binaries
    # THIS IS CRAP! but I cannot get cx_freeze to work on Mac
    sed -i '' 's/\/usr\/bin\/env python/\/Library\/Frameworks\/Python.framework\/Versions\/2.7\/bin\/python/g' main.py
    
    # Finally, create DMG image with the app (We have to do this many times to be able to set an icon)
    cd ../../../
    rm -rf .DS_Store
    ln -s /Applications .
    cp ../../res/icon.icns .VolumeIcon.icns
    SetFile -c icnC .VolumeIcon.icns
    cd $WORKDIR
    hdiutil create -srcfolder output/OSX/ -volname "BennuGD Packager" -format UDRW -ov "output/raw.dmg"
    rm -rf output/OSX/
    mkdir -p output/OSX/
    hdiutil attach "output/raw.dmg" -mountpoint output/OSX/
    SetFile -a C output/OSX/
    hdiutil detach output/OSX/
    rm -rf output/OSX/
    hdiutil convert "output/raw.dmg" -format UDZO -o "$OUTPUTDMG"
    rm -f "output/raw.dmg"
#hdiutil create -fs HFS+ -volname "BennuGD Packager" -srcfolder output/OSX/ "$OUTPUTDMG"
}

# Determine if we're on Linux or on Mac and set output dir
# accordingly
PLATFORM=$(uname)
if [ "$PLATFORM" = 'Darwin' ]; then
    OUTPUTDIR='output/OSX'
    OUTPUTDMG='output/BennuGD Packager.dmg'
else
    OUTPUTDIR='output/linux'
fi


# Remove any previous output before creating the new one
if [ -d "$OUTPUTDIR" ]; then
    rm -rf $OUTPUTDIR
fi

if [ -f "$OUTPUTDMG" ]; then
    rm -f "$OUTPUTDMG"
fi

# Package the program
if [ "$PLATFORM" = 'Darwin' ]; then
    package_osx
else
    package_linux
fi

