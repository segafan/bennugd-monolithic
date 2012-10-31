LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := bgdrtm

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL_mixer/ \
	$(LOCAL_PATH)/../../../../3rdparty/libpng/ \
	$(LOCAL_PATH)/../../../../3rdparty/libglob-bsd/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/curl-7.23.1/include/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-D__BGDRTM__ \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \
	-DWITH_SDLRWOPS


LOCAL_SRC_FILES := \
	../../../../core/bgdrtm/src/copy.c \
	../../../../core/bgdrtm/src/dcbr.c \
	../../../../core/bgdrtm/src/dirs.c \
	../../../../core/bgdrtm/src/instance.c \
	../../../../core/bgdrtm/src/interpreter.c \
	../../../../core/bgdrtm/src/misc.c \
	../../../../core/bgdrtm/src/strings.c \
	../../../../core/bgdrtm/src/sysprocs.c \
	../../../../core/bgdrtm/src/varspace_file.c \
	../../../../core/common/debug.c \
	../../../../core/common/files.c \
	../../../../core/common/xctype.c

LOCAL_LDLIBS := -llog -ldl -lz
LOCAL_SHARED_LIBRARIES += SDL2 glob
LOCAL_STATIC_LIBRARIES += 

include $(BUILD_SHARED_LIBRARY)
