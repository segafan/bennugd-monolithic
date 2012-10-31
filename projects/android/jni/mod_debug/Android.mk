LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := mod_debug

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL/include/ \
	$(MODULES_PATH)/libgrbase/ \
	$(MODULES_PATH)/librender/ \
	$(MODULES_PATH)/libvideo/ \
	$(MODULES_PATH)/libkey/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-D__STATIC__ \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \
	-DWITH_SDLRWOPS

LOCAL_SRC_FILES := \
	../../../../modules/mod_debug/mod_debug.c \
	../../../../modules/mod_debug/systexts.c

LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES += 
LOCAL_STATIC_LIBRARIES +=

include $(BUILD_SHARED_LIBRARY)
