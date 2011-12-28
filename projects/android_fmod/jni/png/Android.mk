LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

common_SRC_FILES := \
	/../../../../3rdparty/libpng/src/png.c \
    /../../../../3rdparty/libpng/src/pngerror.c \
    /../../../../3rdparty/libpng/src/pngget.c \
    /../../../../3rdparty/libpng/src/pngmem.c \
    /../../../../3rdparty/libpng/src/pngpread.c \
    /../../../../3rdparty/libpng/src/pngread.c \
    /../../../../3rdparty/libpng/src/pngrio.c \
    /../../../../3rdparty/libpng/src/pngrtran.c \
    /../../../../3rdparty/libpng/src/pngwio.c \
    /../../../../3rdparty/libpng/src/pngwrite.c \
    /../../../../3rdparty/libpng/src/pngwtran.c \
    /../../../../3rdparty/libpng/src/pngwutil.c \
    /../../../../3rdparty/libpng/src/pngrutil.c \
    /../../../../3rdparty/libpng/src/pngset.c \
    /../../../../3rdparty/libpng/src/pngtrans.c

common_CFLAGS := ## -fomit-frame-pointer

common_C_INCLUDES += $(LOCAL_PATH)/../../../../3rdparty/libpng/src/\

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_MODULE:= png

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

LOCAL_LDLIBS := -lz

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)

