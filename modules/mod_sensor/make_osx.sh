#!/bin/sh

gcc -O2 -m32 -Wall -I../../core/include/ -I/usr/local/include/ -I../../core/bgdrtm/include/ -D_REENTRANT -DFAKE -c mod_sensor.c
if [ -f mod_sensor.o ]; then
        gcc mod_sensor.o -O2 -dynamiclib -m32 -o mod_sensor.dylib -L../../../../bennugd_bin/lib/ -lbgdrtm -lcurl -L/opt/local/lib -install_name mod_sensor.dylib -Wl,-single_module
fi

if [ -f mod_sensor.dylib ]; then
        rm mod_sensor.o
fi
