all: 
	cd bgdc; $(MAKE) -f Makefile
	cd bgdrtm; $(MAKE) -f Makefile
	cd bgdi; $(MAKE) -f Makefile

linux:
	cd bgdc; $(MAKE) -f Makefile.linux
	cd bgdrtm; $(MAKE) -f Makefile.linux
	cd bgdi; $(MAKE) -f Makefile.linux

psp:
	cd ../3rdparty/dietlibc-glob/; $(MAKE) -f Makefile.psp
	cd bgdi; $(MAKE) -f Makefile.psp

OSX:
	cd bgdc; $(MAKE) -f Makefile.OSX
	cd bgdrtm; $(MAKE) -f Makefile.OSX
	cd bgdi; $(MAKE) -f Makefile.OSX

clean:
	./clean
