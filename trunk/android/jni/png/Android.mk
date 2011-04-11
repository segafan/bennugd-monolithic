LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

common_SRC_FILES := \
	png.c \
	pngset.c \
	pngget.c \
	pngrutil.c \
	pngtrans.c \
	pngwutil.c \
	pngread.c \
	pngrio.c \
	pngwio.c \
	pngwrite.c \
	pngrtran.c \
	pngtrans.c \
	pngwtran.c \
	pngmem.c \
	pngerror.c \
	pngpread.c

common_CFLAGS := ## -fomit-frame-pointer

common_C_INCLUDES += \

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_MODULE:= png

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)

