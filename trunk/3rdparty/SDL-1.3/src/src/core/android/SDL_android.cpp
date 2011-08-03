/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_config.h"
#include "SDL_stdinc.h"

#include "SDL_android.h"

extern "C" {
#include "../../events/SDL_events_c.h"
#include "../../video/android/SDL_androidkeyboard.h"
#include "../../video/android/SDL_androidtouch.h"
#include "../../video/android/SDL_androidvideo.h"

/* Impelemented in audio/android/SDL_androidaudio.c */
extern void Android_RunAudioThread();
} // C

/*******************************************************************************
 This file links the Java side of Android with libsdl
*******************************************************************************/
#include <jni.h>
#include <android/log.h>


/*******************************************************************************
                               Globals
*******************************************************************************/
static JNIEnv* mEnv = NULL;
static JNIEnv* mAudioEnv = NULL;

// Main activity
static jclass mActivityClass;

// method signatures
static jmethodID midCreateGLContext;
static jmethodID midFlipBuffers;
static jmethodID midAudioInit;
static jmethodID midAudioWriteShortBuffer;
static jmethodID midAudioWriteByteBuffer;
static jmethodID midAudioQuit;

// Accelerometer data storage
static float fLastAccelerometer[3];


/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/

// Library init
extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    return JNI_VERSION_1_4;
}

// Called before SDL_main() to initialize JNI bindings
extern "C" void SDL_Android_Init(JNIEnv* env, jclass cls)
{
    __android_log_print(ANDROID_LOG_INFO, "SDL", "SDL_Android_Init()");

    mEnv = env;
    mActivityClass = cls;

    midCreateGLContext = mEnv->GetStaticMethodID(mActivityClass,
                                "createGLContext","(II)Z");
    midFlipBuffers = mEnv->GetStaticMethodID(mActivityClass,
                                "flipBuffers","()V");
    midAudioInit = mEnv->GetStaticMethodID(mActivityClass, 
                                "audioInit", "(IZZI)Ljava/lang/Object;");
    midAudioWriteShortBuffer = mEnv->GetStaticMethodID(mActivityClass,
                                "audioWriteShortBuffer", "([S)V");
    midAudioWriteByteBuffer = mEnv->GetStaticMethodID(mActivityClass,
                                "audioWriteByteBuffer", "([B)V");
    midAudioQuit = mEnv->GetStaticMethodID(mActivityClass,
                                "audioQuit", "()V");

    if(!midCreateGLContext || !midFlipBuffers || !midAudioInit ||
       !midAudioWriteShortBuffer || !midAudioWriteByteBuffer || !midAudioQuit) {
        __android_log_print(ANDROID_LOG_WARN, "SDL", "SDL: Couldn't locate Java callbacks, check that they're named and typed correctly");
    }
}

// Resize
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeResize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height, jint format)
{
    Android_SetScreenResolution(width, height, format);
}

// Keydown
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyDown(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Android_OnKeyDown(keycode);
}

// Keyup
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyUp(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Android_OnKeyUp(keycode);
}

// Touch
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeTouch(
                                    JNIEnv* env, jclass jcls,
                                    jint action, jfloat x, jfloat y, jfloat p)
{
    Android_OnTouch(action, x, y, p);
}

// Accelerometer
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeAccel(
                                    JNIEnv* env, jclass jcls,
                                    jfloat x, jfloat y, jfloat z)
{
    fLastAccelerometer[0] = x;
    fLastAccelerometer[1] = y;
    fLastAccelerometer[2] = z;   
}

// Quit
extern "C" void Java_org_libsdl_app_SDLActivity_nativeQuit(
                                    JNIEnv* env, jclass cls)
{    
    // Inject a SDL_QUIT event
    SDL_SendQuit();
}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(
                                    JNIEnv* env, jclass cls)
{
    /* This is the audio thread, with a different environment */
    mAudioEnv = env;

    Android_RunAudioThread();
}


/*******************************************************************************
             Functions called by SDL into Java
*******************************************************************************/
extern "C" SDL_bool Android_JNI_CreateContext(int majorVersion, int minorVersion)
{
    if (mEnv->CallStaticBooleanMethod(mActivityClass, midCreateGLContext, majorVersion, minorVersion)) {
        return SDL_TRUE;
    } else {
        return SDL_FALSE;
    }
}

extern "C" void Android_JNI_SwapWindow()
{
    mEnv->CallStaticVoidMethod(mActivityClass, midFlipBuffers); 
}

extern "C" void Android_JNI_SetActivityTitle(const char *title)
{
    jmethodID mid;

    mid = mEnv->GetStaticMethodID(mActivityClass,"setActivityTitle","(Ljava/lang/String;)V");
    if (mid) {
        mEnv->CallStaticVoidMethod(mActivityClass, mid, mEnv->NewStringUTF(title));
    }
}

extern "C" void Android_JNI_GetAccelerometerValues(float values[3])
{
    int i;
    for (i = 0; i < 3; ++i) {
        values[i] = fLastAccelerometer[i];
    }
}

//
// Audio support
//
static jboolean audioBuffer16Bit = JNI_FALSE;
static jboolean audioBufferStereo = JNI_FALSE;
static jobject audioBuffer = NULL;
static void* audioBufferPinned = NULL;

extern "C" int Android_JNI_OpenAudioDevice(int sampleRate, int is16Bit, int channelCount, int desiredBufferFrames)
{
    int audioBufferFrames;

    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL audio: opening device");
    audioBuffer16Bit = is16Bit;
    audioBufferStereo = channelCount > 1;

    audioBuffer = mEnv->CallStaticObjectMethod(mActivityClass, midAudioInit, sampleRate, audioBuffer16Bit, audioBufferStereo, desiredBufferFrames);

    if (audioBuffer == NULL) {
        __android_log_print(ANDROID_LOG_WARN, "SDL", "SDL audio: didn't get back a good audio buffer!");
        return 0;
    }
    audioBuffer = mEnv->NewGlobalRef(audioBuffer);

    jboolean isCopy = JNI_FALSE;
    if (audioBuffer16Bit) {
        audioBufferPinned = mEnv->GetShortArrayElements((jshortArray)audioBuffer, &isCopy);
        audioBufferFrames = mEnv->GetArrayLength((jshortArray)audioBuffer);
    } else {
        audioBufferPinned = mEnv->GetByteArrayElements((jbyteArray)audioBuffer, &isCopy);
        audioBufferFrames = mEnv->GetArrayLength((jbyteArray)audioBuffer);
    }
    if (audioBufferStereo) {
        audioBufferFrames /= 2;
    }

    return audioBufferFrames;
}

extern "C" void * Android_JNI_GetAudioBuffer()
{
    return audioBufferPinned;
}

extern "C" void Android_JNI_WriteAudioBuffer()
{
    if (audioBuffer16Bit) {
        mAudioEnv->ReleaseShortArrayElements((jshortArray)audioBuffer, (jshort *)audioBufferPinned, JNI_COMMIT);
        mAudioEnv->CallStaticVoidMethod(mActivityClass, midAudioWriteShortBuffer, (jshortArray)audioBuffer);
    } else {
        mAudioEnv->ReleaseByteArrayElements((jbyteArray)audioBuffer, (jbyte *)audioBufferPinned, JNI_COMMIT);
        mAudioEnv->CallStaticVoidMethod(mActivityClass, midAudioWriteByteBuffer, (jbyteArray)audioBuffer);
    }

    /* JNI_COMMIT means the changes are committed to the VM but the buffer remains pinned */
}

extern "C" void Android_JNI_CloseAudioDevice()
{
    mEnv->CallStaticVoidMethod(mActivityClass, midAudioQuit); 

    if (audioBuffer) {
        mEnv->DeleteGlobalRef(audioBuffer);
        audioBuffer = NULL;
        audioBufferPinned = NULL;
    }
}

static int Android_JNI_FileOpen(SDL_RWops* ctx)
{
    jstring fileNameJString = (jstring)ctx->hidden.androidio.fileName;

    // context = SDLActivity.getContext();
    jmethodID mid = mEnv->GetStaticMethodID(mActivityClass,
            "getContext","()Landroid/content/Context;");
    jobject context = mEnv->CallStaticObjectMethod(mActivityClass, mid);

    // assetManager = context.getAssets();
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(context),
            "getAssets","()Landroid/content/res/AssetManager;");
    jobject assetManager = mEnv->CallObjectMethod(context, mid);

    // inputStream = assetManager.open(<filename>);
    mEnv->ExceptionClear();
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(assetManager),
            "open", "(Ljava/lang/String;)Ljava/io/InputStream;");
    jobject inputStream = mEnv->CallObjectMethod(assetManager, mid, fileNameJString);
    if (mEnv->ExceptionOccurred()) {
        mEnv->ExceptionDescribe();
        mEnv->ExceptionClear();
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);
        return -1;
    } else {
        ctx->hidden.androidio.inputStream = inputStream;
        ctx->hidden.androidio.inputStreamRef = mEnv->NewGlobalRef(inputStream);
    }

    // Store .skip id for seeking purposes
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
            "skip", "(J)J");
    ctx->hidden.androidio.skipMethod = mid;

    // Despite all the visible documentation on [Asset]InputStream claiming
    // that the .available() method is not guaranteed to return the entire file
    // size, comments in <sdk>/samples/<ver>/ApiDemos/src/com/example/ ...
    // android/apis/content/ReadAsset.java imply that Android's
    // AssetInputStream.available() /will/ always return the total file size

    // size = inputStream.available();
    mEnv->ExceptionClear();
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
            "available", "()I");
    ctx->hidden.androidio.size = mEnv->CallIntMethod(inputStream, mid);
    if (mEnv->ExceptionOccurred()) {
        mEnv->ExceptionDescribe();
        mEnv->ExceptionClear();
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.inputStreamRef);
        return -1;
    }

    // readableByteChannel = Channels.newChannel(inputStream);
    mEnv->ExceptionClear();
    jclass channels = mEnv->FindClass("java/nio/channels/Channels");
    mid = mEnv->GetStaticMethodID(channels,
            "newChannel",
            "(Ljava/io/InputStream;)Ljava/nio/channels/ReadableByteChannel;");
    jobject readableByteChannel = mEnv->CallStaticObjectMethod(
            channels, mid, inputStream);
    if (mEnv->ExceptionOccurred()) {
        mEnv->ExceptionDescribe();
        mEnv->ExceptionClear();
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.inputStreamRef);
        return -1;
    } else {
        ctx->hidden.androidio.readableByteChannel = readableByteChannel;
        ctx->hidden.androidio.readableByteChannelRef =
            mEnv->NewGlobalRef(readableByteChannel);
    }

    // Store .read id for reading purposes
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(readableByteChannel),
            "read", "(Ljava/nio/ByteBuffer;)I");
    ctx->hidden.androidio.readMethod = mid;

    ctx->hidden.androidio.position = 0;

    return 0;
}

extern "C" int Android_JNI_FileOpen(SDL_RWops* ctx,
        const char* fileName, const char*)
{
    if (!ctx) {
        return -1;
    }

    jstring fileNameJString = mEnv->NewStringUTF(fileName);
    ctx->hidden.androidio.fileName = fileNameJString;
    ctx->hidden.androidio.fileNameRef = mEnv->NewGlobalRef(fileNameJString);

    return Android_JNI_FileOpen(ctx);
}

extern "C" size_t Android_JNI_FileRead(SDL_RWops* ctx, void* buffer,
        size_t size, size_t maxnum)
{
    int bytesRemaining = size * maxnum;
    int bytesRead = 0;

    jobject readableByteChannel = (jobject)ctx->hidden.androidio.readableByteChannel;
    jmethodID readMethod = (jmethodID)ctx->hidden.androidio.readMethod;
    jobject byteBuffer = mEnv->NewDirectByteBuffer(buffer, bytesRemaining);

    mEnv->ExceptionClear();
    while (bytesRemaining > 0) {
        // result = readableByteChannel.read(...);
        int result = mEnv->CallIntMethod(readableByteChannel, readMethod, byteBuffer);

        if (mEnv->ExceptionOccurred()) {
            mEnv->ExceptionDescribe();
            mEnv->ExceptionClear();
            return 0;
        }

        if (result < 0) {
            break;
        }

        bytesRemaining -= result;
        bytesRead += result;
        ctx->hidden.androidio.position += result;
    }

    return bytesRead / size;
}

extern "C" size_t Android_JNI_FileWrite(SDL_RWops* ctx, const void* buffer,
        size_t size, size_t num)
{
    SDL_SetError("Cannot write to Android package filesystem");
    return 0;
}

static int Android_JNI_FileClose(SDL_RWops* ctx, bool release)
{
    int result = 0;

    if (ctx) {
        if (release) {
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);
        }

        jobject inputStream = (jobject)ctx->hidden.androidio.inputStream;

        // inputStream.close();
        mEnv->ExceptionClear();
        jmethodID mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
                "close", "()V");
        mEnv->CallVoidMethod(inputStream, mid);
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.inputStreamRef);
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.readableByteChannelRef);
        if (mEnv->ExceptionOccurred()) {
            result = -1;
            mEnv->ExceptionDescribe();
            mEnv->ExceptionClear();
        }

        if (release) {
            SDL_FreeRW(ctx);
        }
    }

    return result;
}


extern "C" long Android_JNI_FileSeek(SDL_RWops* ctx, long offset, int whence)
{
    long newPosition;

    switch (whence) {
        case RW_SEEK_SET:
            newPosition = offset;
            break;
        case RW_SEEK_CUR:
            newPosition = ctx->hidden.androidio.position + offset;
            break;
        case RW_SEEK_END:
            newPosition = ctx->hidden.androidio.size + offset;
            break;
        default:
            SDL_SetError("Unknown value for 'whence'");
            return -1;
    }
    if (newPosition < 0) {
        newPosition = 0;
    }
    if (newPosition > ctx->hidden.androidio.size) {
        newPosition = ctx->hidden.androidio.size;
    }

    long movement = newPosition - ctx->hidden.androidio.position;
    jobject inputStream = (jobject)ctx->hidden.androidio.inputStream;
    jmethodID skipMethod = (jmethodID)ctx->hidden.androidio.skipMethod;

    if (movement > 0) {
        // The easy case where we're seeking forwards
        mEnv->ExceptionClear();
        while (movement > 0) {
            // inputStream.skip(...);
            movement -= mEnv->CallLongMethod(inputStream, skipMethod, movement);
            if (mEnv->ExceptionOccurred()) {
                mEnv->ExceptionDescribe();
                mEnv->ExceptionClear();
                SDL_SetError("Exception while seeking");
                return -1;
            }
        }
    } else if (movement < 0) {
        // We can't seek backwards so we have to reopen the file and seek
        // forwards which obviously isn't very efficient
        Android_JNI_FileClose(ctx, false);
        Android_JNI_FileOpen(ctx);
        Android_JNI_FileSeek(ctx, newPosition, RW_SEEK_SET);
    }

    ctx->hidden.androidio.position = newPosition;

    return ctx->hidden.androidio.position;
}

extern "C" int Android_JNI_FileClose(SDL_RWops* ctx)
{
    return Android_JNI_FileClose(ctx, true);
}

/* vi: set ts=4 sw=4 expandtab: */
