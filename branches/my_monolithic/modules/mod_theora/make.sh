#!/bin/sh

DEPS="bennugd-core bennugd-module-mod_video sdl"
MODULE="mod_theora"

# Clean previous module files
if [ -f $MODULE.so ]; then
	rm $MODULE.so
fi

# Compile the source code
gcc -c -Wall $(pkg-config --cflags $DEPS) $MODULE.c theoraplay.c

# Link the module
if [ -f $MODULE.o ]; then
	gcc -o$MODULE.so $MODULE.o theoraplay.o -shared $(pkg-config --libs $DEPS) -Wl,-soname -Wl,$MODULE.so
fi

# Strip and remove compilation files
if [ -f $MODULE.so ]; then
	rm $MODULE.o
    rm theoraplay.o
	strip $MODULE.so
fi

