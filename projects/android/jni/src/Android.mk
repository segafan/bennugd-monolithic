LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := $(LOCAL_PATH)/../../../../3rdparty/SDL-1.3/src/

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(CORE_PATH)/include \
	$(LOCAL_PATH)/../../../3rdparty/libglob-bsd/include/ \
	$(SDL_PATH)/include \
	$(SDL_PATH)/../SDL_mixer/src

# Add any compilation flags for your project here...
LOCAL_CFLAGS := \
	-D__BGDI__ \
	-DTARGET_ANDROID \
	-DVERSION='"1.0.0"' \
	-DSDL_NO_COMPAT

# Add your application source files here...
LOCAL_SRC_FILES := ../../../../3rdparty/SDL-1.3/src/src/main/android/SDL_android_main.cpp \
	main.c

LOCAL_SHARED_LIBRARIES  := SDL SDL_mixer
LOCAL_STATIC_LIBRARIES  := bgdrtm png
LOCAL_LDLIBS            := -lGLESv1_CM -llog -lz

include $(BUILD_SHARED_LIBRARY)
