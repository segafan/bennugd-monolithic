LOCAL_PATH := $(call my-dir)

#
# FMOD Ex Shared Library
# 
include $(CLEAR_VARS)

LOCAL_MODULE            := fmodex
LOCAL_SRC_FILES		:= ../../../../3rdparty/fmod/Android/lib/$(TARGET_ARCH_ABI)/libfmodex.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../../3rdparty/fmod/Android/

include $(PREBUILT_SHARED_LIBRARY)
