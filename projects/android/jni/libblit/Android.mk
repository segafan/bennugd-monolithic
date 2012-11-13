LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := libblit

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL/include/ \
	$(MODULES_PATH)/libgrbase/ \
	$(MODULES_PATH)/libblit/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-D__LIBRENDER \
	-DWITH_GPL_CODE \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \
	-DWITH_SDLRWOPS

LOCAL_SRC_FILES := \
	../../../../modules/libblit/libblit.c \
	../../../../modules/libblit/g_blit.c \
	../../../../modules/libblit/g_pixel.c

LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES += bgdrtm libgrbase
LOCAL_STATIC_LIBRARIES +=

include $(BUILD_SHARED_LIBRARY)
