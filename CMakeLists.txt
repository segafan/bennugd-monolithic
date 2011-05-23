#
# experimental CMake build system for bennugd
#

# minimal CMake version required for build
cmake_minimum_required( VERSION 2.8 ) 

# project name
project( bennugd C )

# set the build type (Debug for now, but can change as the build system evolves)
set( CMAKE_BUILD_TYPE "Debug" )

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
	message( "DEBUG build..." )
elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
	message( "RELEASE build..." )
else()
	message( FATAL_ERROR "Build type not set." )
endif()

# choose whether to build the monolithic version or the tradicional (dynamic linking based) version
option(BUILD_NORMAL "Build a normal (non-monolithic, DLL/SO based) version of BennuGD." OFF)
option(BUILD_MONOLITHIC "Build a monolithic version of BennuGD (targeted mostly for embedded plataforms)." ON)

# choose what plataform to build for
if( BUILD_NORMAL )
	option( BUILD_LINUX "Build the Linux version of BennuGD." OFF )
	option( BUILD_WIN32 "Build the Win32 version of BennuGD." ON )
	option( BUILD_MACOS "Build the MACOS version of BennuGD." OFF )

elseif( BUILD_MONOLITHIC ) 	
	option( BUILD_PSP "Build the PSP version of BennuGD." ON )
	option( BUILD_WII "Build the Wii version of BennuGD." OFF )
	option( BUILD_XBOX "Build the XBOX version of BennuGD." OFF )
endif( BUILD_NORMAL )

# add modules subdirectory
add_subdirectory( modules )

# add core subdir to build
# add_subdirectory( core )




