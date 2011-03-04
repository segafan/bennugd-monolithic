#!/bin/sh

## -- PSPKIT SETTINGS
export DEVKITPRO=/SDKs/devkitpro
export DEVKITPPC=$DEVKITPRO/devkitPPC
export PATH=$DEVKITPPC/bin:$DEVKITPPC/psp/pspjimPSP/bin:$PATH

## Compile source
cd monolithic
make -f Makefile.wii_bgdi create_links
make -f Makefile.wii_bgdi 
#make -f Makefile.wii_bgdc create_links
#make -f Makefile.wii_bgdc 

