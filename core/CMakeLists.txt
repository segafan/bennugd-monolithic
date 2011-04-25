cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0001 NEW) # don't use MAKE_BACKWARDS_COMPATIBILITY but policies instead

project(bennugd)

# to change the prefix, run cmake with the parameter:
#   -D CMAKE_INSTALL_PREFIX=/my/prefix

# to change the build type, run cmake with the parameter:
#   -D CMAKE_BUILD_TYPE=<build-type>
# run "cmake --help-variable CMAKE_BUILD_TYPE" for details
set(CMAKE_BUILD_TYPE Release)

# other options for the build, you can i.e. activate the ruby bindings by passing
#   -D BUILD_NORMAL=ON
# to cmake. Other options analog
option(BUILD_NORMAL "Build a normal (non-monolithic) version of BennuGD" OFF)
option(BUILD_MONOLITHIC "Build a monolithic version of BennuGD" ON)
option(TARGET_WII "Build the Wii Homebrew version of BennuGD" ON)
option(TARGET_IOS "Build the iOS version of BennuGD" OFF)

# sanity checks...
if(INSTALL_DEMOS)
  set(BUILD_DEMOS ON FORCE)
endif(INSTALL_DEMOS)
# thse need the static lib too
if(BUILD_DEMOS OR BUILD_RUBY_EXT OR INSTALL_STATIC)
  set(BUILD_STATIC ON FORCE)
endif(BUILD_DEMOS OR BUILD_RUBY_EXT OR INSTALL_STATIC)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") # allways use gnu99
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math") # extend release-profile with fast-math
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall") # extend debug-profile with -Wall

add_subdirectory(bgdrtm)

if(BUILD_DEMOS)
  add_subdirectory(Demo)
endif(BUILD_DEMOS)
