# Introduction #

This page describes how to get BennuGD-monolithic working on your PSP. This approach is in very very alpha stage, so don't expect too much.

# Requirements #

One must have a PSP capable of running homebrews, aka unsigned code. There are several so called loaders or [PSPHomebrewEnabler](PSPHomebrewEnabler.md) in the wild and people should look for information regarding the specific PSP they own.

# Running BennuGD in PSP #

There are several combinations of PSP models, motherboard revisions and firmware versions. For each combination a different approach should be taken in order to use BennuGD.

For information on how to find your PSP model, check [PSPModelInfo](PSPModelInfo.md).
For information on how to find your PSP motherboard revision, check [PSPMotherboardRevision](PSPMotherboardRevision.md).
For information on how to find your PSP firmware version, check [PSPFirmwareVersion](PSPFirmwareVersion.md).

The following is model-specific information.

## PSP-1000 or PSP-2000 without motherboard TA88v3 ##
These are the finest. Custom firmwares works really fine and they are the easier to get BennuGD running. This needs to be 'pandorized' using a Pandora's battery. After that, custom firmware gets loaded every boot and there is nothing more to worry about. Copy the EBOOT.PBP file and the DCBs you want to run to /GAME/BENNUGD. Then go to Game -> Memory Stick and launch BennuGD.

This environment is tested by the developer and it works fine.

## PSP-2000 series with TA88v3 motherboard or PSP-3000 series ##
For now, these only works if they have firmware version older or equal than 5.03. They need some way to load unsigned code in the PSP. One possible alternative is to use the ChickHEN exploit. This is a software-only exploit and does not harm your PSP, altough it is somewhat instable and does not work correctly every time. Copy the EBOOT.PBP file and DCBs you want to run to /GAME/BENNUGD and load the exploit.

One can check if the exploit worked by looking at System Settings -> Version to see if the word "ChickHEN" is in the version string.

When the exploit gets loaded, the homebrew icon shows in the XMB Game -> Memory Stick option and you can launch BennuGD from there.

## Remaining models ##

The remaning models are:
  * PSP-2000 with motherboard TA88v3 and firmware version newer than 5.03
  * PSP-3000 with firmware version newer than 5.03
  * PSP-Go

At the time of this writing the only way to load homebrew application in these models is to use [HalfByte Loader](http://www.wololo.net/wagic/hbl/) by wololo and his team (nice job, guys). Please note that the developer does not have any of these models so they are not tested. Reports on this are welcome. For more information about running applications in the PSP, please check [PSPHomebrewEnabler](PSPHomebrewEnabler.md).

