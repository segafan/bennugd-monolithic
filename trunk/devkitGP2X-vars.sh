#!/bin/sh

## -- ARM_GP2X USER SETTINGS

## ARM_GP2X - This should point to the root of your tool-chain {i.e. folder above the BIN dir}
SDK_HOME=/SDKs/devkitpro/devkitGP2X
ARM_GP2X=${SDK_HOME}/arm-linux

## HOST and TARGET - These should be the canonical tool names of your tool.
## For the sake of this script HOST and TARGET should be the same.
## Defaults would be 'arm-ARM_GP2X-linux' for a normal ARM_GP2X tool-chain.

HOST=arm-linux
TARGET=arm-linux
BUILD=`uname -m`
PKG_CONFIG_PATH=$ARM_GP2X/lib/pkgconfig

## -- END ARM_GP2X USER SETTINGS

export ARM_GP2X
export HOST
export TARGET
export PKG_CONFIG_PATH

PREFIX=$ARM_GP2X
export PREFIX

PATH=$ARM_GP2X/bin:$PATH
export PATH

ln -s `whereis -b pkg-config | sed 's/pkg-config\: //g'` $ARM_GP2X/bin/pkg-config

# Do not edit below here
CC="${ARM_GP2X}/../bin/${HOST}-gcc"
CXX="${ARM_GP2X}/../bin/${HOST}-g++"
AR="${ARM_GP2X}/../bin/${HOST}-ar"
STRIP="${ARM_GP2X}/../bin/${HOST}-strip"
RANLIB="${ARM_GP2X}/../bin/${HOST}-ranlib"

LDFLAGS="-L${ARM_GP2X}/lib -L${SDK_HOME}/sdl-libs-211006/devkitGP2X/lib -L/home/dcelso/workspace_BGD/bennugd_devkitGP2X/openssl-0.9.8q "

PKG_CONFIG="${ARM_GP2X}/bin/pkg-config"

export CC
export CXX
export AR
export STRIP
export RANLIB
export LDFLAGS
export PKG_CONFIG

echo Current settings.
echo
echo Install root/Working dir	= $ARM_GP2X
echo Tool locations 		= $ARM_GP2X/bin
echo Host/Target		= $HOST / $TARGET
echo

echo CC         = $CC
echo CXX        = $CXX
echo AR         = $AR
echo STRIP      = $STRIP
echo RANLIB     = $RANLIB

echo LDFLAGS    = $LDFLAGS
echo PKG_CONFIG = $PKG_CONFIG



ARM_GPH_INCLUDES="-I${ARM_GPH}/include -I${SDK_HOME}/include -I${SDK_HOME}/sdl-libs-211006/devkitGP2X/include -I${SDK_HOME}/sdl-libs-211006/devkitGP2X/include/SDL"

CFLAGS="-DTARGET_GP2X -O3 -DARM -D_ARM_ASSEM_ ${ARM_GPH_INCLUDES}"

export CFLAGS

echo CFLAGS     = $CFLAGS
echo ""
echo "Now do:"

echo "cd core"
echo 'sh ./configure --prefix=${PREFIX} --target=${TARGET} --host=${HOST} --build=${BUILD} --enable-shared'
echo ""
echo "cd modules"
