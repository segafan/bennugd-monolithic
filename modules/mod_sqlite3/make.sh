#!/bin/sh

if [ -f mod_sqlite3.o ]; then
	rm -f mod_sqlite3.o;
fi

gcc -O2 -Wall $(pkg-config --cflags bennugd-core sqlite3) -D_REENTRANT -c mod_sqlite3.c
ld -omod_sqlite3.so mod_sqlite3.o $(pkg-config --libs bennugd-core) -lpthread -shared -lc -fPic

if [ -f mod_sqlite3.so ]; then
	strip mod_sqlite3.so;
fi
