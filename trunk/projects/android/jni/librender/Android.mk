LOCAL_PATH := $(call my-dir)
CORE_PATH := $(LOCAL_PATH)/../../../../core/
MODULES_PATH := $(LOCAL_PATH)/../../../../modules/

include $(CLEAR_VARS)

LOCAL_MODULE := render

LOCAL_C_INCLUDES := $(CORE_PATH)/include \
	$(CORE_PATH)/bgdrtm/include/ \
	$(LOCAL_PATH)/../../../../3rdparty/SDL/include/ \
	$(MODULES_PATH)/libgrbase/ \
	$(MODULES_PATH)/libvideo/ \
	$(MODULES_PATH)/libblit/ \
	$(MODULES_PATH)/librender/

LOCAL_CFLAGS := -DVERSION='"1.0.0"' \
	-D__STATIC__ \
	-D__LIBRENDER \
	-DWITH_GPL_CODE \
	-DTARGET_LINUX \
	-DTARGET_ANDROID \
	-DWITH_SDLRWOPS

LOCAL_SRC_FILES := \
	../../../../modules/librender/g_fade.c \
	../../../../modules/librender/g_frame.c \
	../../../../modules/librender/g_instance.c \
	../../../../modules/librender/g_object.c \
	../../../../modules/librender/g_rects.c \
	../../../../modules/librender/g_screen.c \
	../../../../modules/librender/librender.c \
	../../../../modules/librender/scaler_hq2x.c \
	../../../../modules/librender/scaler_normal.c \
	../../../../modules/librender/scaler_scale2x.c \
	../../../../modules/librender/scaler_scanline.c

LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES += modules SDL2
LOCAL_STATIC_LIBRARIES +=

include $(BUILD_SHARED_LIBRARY)
