LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := libgrbase

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(MODULES_PATH)/libgrbase/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \

LOCAL_SRC_FILES := \
	../../../../modules/libgrbase/g_bitmap.c \
	../../../../modules/libgrbase/g_clear.c \
	../../../../modules/libgrbase/g_grlib.c \
	../../../../modules/libgrbase/g_pal.c \
	../../../../modules/libgrbase/g_blendop.c \
	../../../../modules/libgrbase/g_conversion.c \
	../../../../modules/libgrbase/libgrbase.c

LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES += bgdrtm
LOCAL_STATIC_LIBRARIES += 

include $(BUILD_SHARED_LIBRARY)
