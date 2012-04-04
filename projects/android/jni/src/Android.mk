LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := $(LOCAL_PATH)/../../../../3rdparty/SDL2

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(CORE_PATH)/include \
	$(LOCAL_PATH)/../../../3rdparty/libglob-bsd/include/ \
	$(SDL_PATH)/include \
	$(SDL_PATH)/../SDL_mixer

# Add any compilation flags for your project here...
LOCAL_CFLAGS := \
	-D__BGDI__ \
	-DTARGET_ANDROID \
	-DWITH_SDLRWOPS \
	-DVERSION='"1.0.0"'

# Add your application source files here...
LOCAL_SRC_FILES := /../../../../3rdparty/SDL2/src/main/android/SDL_android_main.cpp \
	main.c

LOCAL_SHARED_LIBRARIES  += bgdrtm SDL2
LOCAL_STATIC_LIBRARY    +=
LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
