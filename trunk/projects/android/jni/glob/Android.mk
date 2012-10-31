LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := glob

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../3rdparty/libglob-bsd/include/

LOCAL_CFLAGS := 


LOCAL_SRC_FILES := ../../../../3rdparty/libglob-bsd/src/glob.c

LOCAL_LDLIBS :=
LOCAL_SHARED_LIBRARIES += 
LOCAL_STATIC_LIBRARIES += 

include $(BUILD_SHARED_LIBRARY)
