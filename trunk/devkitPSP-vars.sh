#!/bin/sh

SDK_HOME=/SDKs/devkitpro
PSP_GCC=${SDK_HOME}/devkitPSP

## HOST and TARGET - These should be the canonical tool names of your tool.
## For the sake of this script HOST and TARGET should be the same.
## Defaults would be 'arm-PSP_GCC-linux' for a normal PSP_GCC tool-chain.

HOST=psp
TARGET=psp
BUILD=`uname -m`
PKG_CONFIG_PATH=$PSP_GCC/lib/pkgconfig

## -- END PSP_GCC USER SETTINGS

export PSP_GCC
export HOST
export TARGET
export PKG_CONFIG_PATH

PREFIX=$PSP_GCC
export PREFIX

PATH=$PSP_GCC/bin:$PATH
export PATH

ln -s `whereis -b pkg-config | sed 's/pkg-config\: //g'` $PSP_GCC/bin/pkg-config

# Do not edit below here
CC="${PSP_GCC}/bin/${HOST}-gcc"
CXX="${PSP_GCC}/bin/${HOST}-g++"
AR="${PSP_GCC}/bin/${HOST}-ar"
STRIP="${PSP_GCC}/bin/${HOST}-strip"
RANLIB="${PSP_GCC}/bin/${HOST}-ranlib"

LDFLAGS="-L${PSP_GCC}/lib -L${SDK_HOME}/sdl-libs-211006/devkitGP2X/lib -L/home/dcelso/workspace_BGD/bennugd_devkitGP2X/openssl-0.9.8q_psp"

PKG_CONFIG="${PSP_GCC}/bin/pkg-config"

export CC
export CXX
export AR
export STRIP
export RANLIB
export LDFLAGS
export PKG_CONFIG

echo Current settings.
echo
echo Install root/Working dir	= $PSP_GCC
echo Tool locations 		= $PSP_GCC/bin
echo Host/Target		= $HOST / $TARGET
echo

echo CC         = $CC
echo CXX        = $CXX
echo AR         = $AR
echo STRIP      = $STRIP
echo RANLIB     = $RANLIB

echo LDFLAGS    = $LDFLAGS
echo PKG_CONFIG = $PKG_CONFIG

CFLAGS="-DTARGET_PSP -O2"

export CFLAGS

echo CFLAGS     = $CFLAGS
echo ""
echo "Now do:"

echo "cd openssl-0.9.8q"
echo "sh ./config no-asm no-dso no-krb5 threads zlib no-shared --prefix=$PREFIX -DOPENSSL_IMPLEMENTS_strncasecmp -I${PSP_GCC}/psp/sdk/include"
