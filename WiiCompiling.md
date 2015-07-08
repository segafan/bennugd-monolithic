# Introduction #

This document describes how to compile bennugd-monolithic for the Wii on your system. The main system used for development is Linux x86, but it should work on any Devkitpro system.

# Details #

  * In order to install the SDK, follow the instructions to install devkitpro from [here](http://devkitpro.org/wiki/Getting_Started/devkitPPC).
  * Download the latest copy of my DevkitPPC directory available [here](http://code.google.com/p/bennugd-monolithic/downloads/list) -it can be used in win32, linux or OS X- and uncompress it to (following the example in the Getting Started page) _/opt/devkitpro/_ so that there you'll have threee folders: _devklitPPC_, _libogc_ & _portlibs_.
  * Now, set the _DEVKITPRO_ & _DEVKITPPC_ environment vars as described in the Devkitpro "Getting Started" page.
  * Get the latest bennugd-monolithic code as described [here](http://code.google.com/p/bennugd-monolithic/source/checkout).
  * Last, in your favorite console, and from the _bennugd-monolithic-read-only/core_ directory type make. That's it! After that, your binaries will be in _core/bgdc/bgdc.elf_ & _core/bgdi/bgdi.elf_.
  * Should you want to create a monolithic build for Linux (which should work just as fine as the normal BennuGD build, as you won't experience any endianess issues), type _make linux_ instead of _make_.