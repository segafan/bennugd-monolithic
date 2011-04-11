LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../core/

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(CORE_PATH)/include \
	$(LOCAL_PATH)/../../../3rdparty/libglob-bsd/include/ \
	$(LOCAL_PATH)/../SDL/include \
	$(LOCAL_PATH)/../SDL_image \
	$(LOCAL_PATH)/../SDL_mixer

# Add any compilation flags for your project here...
LOCAL_CFLAGS := \
	-D__BGDI__ \
	-DTARGET_ANDROID \
	-DVERSION='"1.0.0"'

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	../../../core/bgdi/src/main.c

LOCAL_SHARED_LIBRARIES  := SDL SDL_mixer
LOCAL_STATIC_LIBRARIES  := bgdrtm png
LOCAL_LDLIBS            := -lGLESv1_CM -llog -lz

include $(BUILD_SHARED_LIBRARY)
