#
# experimental CMake build system for bennugd 
# 
# based on the ScummVM CMake proposed build system 
# and the Ogre3D CMake build system
#

# This file lists the options for build menu and its presets.

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

# Add menu options and presets

option( BENNUGD_LIBBLIT "LibBlit" TRUE )
option( BENNUGD_LIBDRAW "LibDraw" TRUE )
option( BENNUGD_LIBFONT "LibFont" TRUE )
option( BENNUGD_LIBGRBASE "LibGRBase" TRUE )
option( BENNUGD_LIBJOY "LibJoy" TRUE )
option( BENNUGD_LIBKEY "LibKey" TRUE )
option( BENNUGD_LIBMOUSE "LibMouse" TRUE )
option( BENNUGD_LIBRENDER "LibRender" TRUE )
option( BENNUGD_LIBSCROLL "LibScroll" TRUE )
option( BENNUGD_LIBSDLHANDLER "LibSDLHandler" TRUE )
option( BENNUGD_LIBTEXT "LibText" TRUE )
option( BENNUGD_LIBVIDEO "LibVideo" TRUE )
option( BENNUGD_LIBWM "LibWM" TRUE )

# option(SCUMMVM_BUILD_DEVTOOLS "Build the devtools" FALSE)

# hide advanced options
# mark_as_advanced(
  # SCUMMVM_BUILD_DEVTOOLS
# )

