LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := libvideo

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL/include/ \
	$(MODULES_PATH)/libvideo/ \
	$(MODULES_PATH)/libgrbase/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \

LOCAL_SRC_FILES := \
	../../../../modules/libvideo/g_video.c \
	../../../../modules/libvideo/g_regions.c \
	../../../../modules/libvideo/g_compat.c

LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES += bgdrtm libgrbase SDL2
LOCAL_STATIC_LIBRARIES += 

include $(BUILD_SHARED_LIBRARY)
