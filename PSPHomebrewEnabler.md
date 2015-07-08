# Homebrew enabler #

## Disclaimer ##

The developers of this software does not endorse piracy in any form. This is just an informative page.

## Introduction ##

PSP does have a complex protection scheme. It is designed to not allow people to run unsigned code: code that was not digitally signed by Sony.

People have created ways to bypass this copy protection scheme. One of these ways is a homebrew enabler: a piece of software that enables people to run unsigned code on their PSP. This can be used to load and run applications which are neither written using an official Sony Development Kit nor digitally signed by Sony.

## Homebrew ##

Homebrew is the name given to a software written using the unoffical PSPSDK. For most people, which cannot afford an official development kit from Sony, this is the way they can write code to run in their PSP.

## Why I need a Homebrew Enabler? ##

Simply because even tough the PSPSDK is capable of producing a correct binary (executable code) to be run in PSP, the protection scheme will not let you do that.

## What about custom firmwares? ##

A custom firmware (CFW, for short) is a software which adds several capabilities to the PSP operating system (aka kernel). Among these capabilities is the one that allows one to run iso files directly from the memory stick, not using the UMD media to play games. Custom firmwares are not directly related to homebrew enablers but apart from Pandora's battery, one needs to load a HEN BEFORE loading a custom firmware. Custom firmware needs to install itself in memory and they are, in the sense of an ordinary application, not digitally signed. Also note that when one shuts down the PSP, the HEN, as well as the CFW gets unloaded (they go to RAM) so it is needed to reload these after turning on again to run your applications/games.

Pandora's battery is a special case because people were able to create a so called IPL (Inital Program Loader) for use with it. The IPL is a piece of software that loads automatically everytime the PSP boots and loads the homebrew enabler/custom firmware capabilities. Unfortunately, few PSP models (mostly 1000/2000-no-TA88v3 series) supports being _pandorized_. For information about how to discover your PSP model, please goto [PSPModelInfo](PSPModelInfo.md).

## And what is a homebrew enabler anyway? ##

A homebrew enabler (HEN) is a piece of software which takes advantage from a exploitable bug in an official game, demo or internal PSP software library to allow people to run unsigned code in their PSP. The most famous of these is [ChickHEN](http://davee.x-fusion.co.uk/) created by Davee, a HEN which uses an exploit in the PSP's library for the graphical format tiff.

The HEN works by exploiting the bug, whose internals are out of scope right now, and then rebooting the PSP in a HEN environment. Please note that no apparent visual changes happens after the reboot but you can check if the exploit worked by looking at the XMB menu Settings -> System Settings -> System Information.