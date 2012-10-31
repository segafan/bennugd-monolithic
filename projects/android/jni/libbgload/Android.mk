LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := bgload

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL/include/ \
	$(MODULES_PATH)/libbgload/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-DTARGET_LINUX \
	-DTARGET_ANDROID

LOCAL_SRC_FILES := \
	../../../../modules/libbgload/bgload.c

LOCAL_LDLIBS :=
LOCAL_SHARED_LIBRARIES += bgdrtm SDL2
LOCAL_STATIC_LIBRARIES += 

include $(BUILD_SHARED_LIBRARY)
