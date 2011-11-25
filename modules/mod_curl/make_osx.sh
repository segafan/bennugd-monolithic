#!/bin/sh

gcc -O2 -m32 -Wall -I../bennugd/base/core/include/ -I/usr/local/include/ -I/opt/local/include/SDL/ -D_REENTRANT -c main.c
if [ -f main.o ]; then
        gcc main.o -O2 -dynamiclib -m32 -o mod_curl.dylib -L../bennugd_bin/lib/ -lbgdrtm -lcurl -L/opt/local/lib -lSDL -install_name mod_curl.dylib -Wl,-single_module
fi

if [ -f mod_curl.dylib ]; then
        rm main.o
fi
