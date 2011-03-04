#!/bin/sh

## -- devkitGP2X SETTINGS
export DEVKITPRO=/SDKs/devkitpro
export DEVKITGP2X=$DEVKITPRO/devkitGP2X
export PATH=$DEVKITGP2X/bin:$DEVKITGP2X/sdl-libsdevkitGP2X/bin:$PATH

cd monolithic
make -f Makefile.devkitGP2X create_links
make -f Makefile.devkitGP2X all
