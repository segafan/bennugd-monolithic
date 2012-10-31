LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := mod_string

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(MODULES_PATH)/mod_string/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \

LOCAL_SRC_FILES := \
	../../../../modules/mod_string/mod_string.c

LOCAL_LDLIBS := -llog -ldl -lz
LOCAL_SHARED_LIBRARIES += bgdrtm
LOCAL_STATIC_LIBRARIES += 

include $(BUILD_SHARED_LIBRARY)
