Because of the lack or a refusal to allow usage of [dlopen](http://en.wikipedia.org/wiki/Dynamic_loading) or similar functionality in some systems, a direct recompile of [BennuGD](http://www.bennugd.org) for the Wii, PSP, iOS and other embedded systems is not possible.

This project aims to create a version of BennuGD (and the required dependencies) that implements all the functionality offered by the official modules of BennuGD in one single binary but keeping the number of required source code changes to the BennuGD base as low as possible. The project also aims to implement all the needed features for correct integration with such platforms. It is also a good starting point for ports to other platforms that require static linking.

Please note that although the code in this project works just as expected in most platforms, BennuGD still suffers from unresolved endianess issues in bigendian systems. Most of these can be workarounded, though.
You can get a quick intro on how to get my own flavour of BennuGD up and running at the [Getting Started](http://code.google.com/p/bennugd-monolithic/wiki/GettingStarted) wiki page.

This project superseeds bennugd-wii in that its architecture is much cleaner, more stable, well thought and compatible with the official BennuGD base. For example, DCB created with this version can be run in the official BennuGD version (endianes issues aside), and vice-versa.

The code is licensed as [Zlib](http://en.wikipedia.org/wiki/Zlib_License) but it was previously licensed as GNU GPLv2 or over. If you find any reference in the code to the GNU GPL license, please file a bug.

As a final note, this used to be the home of my BennuGD Packager project. It has now a house it can call its own here: https://code.google.com/p/bennugd-packager/
Sources and binary downloads for the packager have been removed from this repo.