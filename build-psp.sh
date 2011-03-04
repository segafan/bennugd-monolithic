#!/bin/sh

## -- PSPKIT SETTINGS
export PSPDEV=/SDKs/pspdev
export PSPSDK=$PSPDEV/psp/sdk
export PATH=$PSPDEV/bin:$PATH

## Compile source
cd monolithic
make -f Makefile.psp_bgdi create_links
make -f Makefile.psp_bgdi all
make -f Makefile.psp_bgdc create_links
make -f Makefile.psp_bgdc all

