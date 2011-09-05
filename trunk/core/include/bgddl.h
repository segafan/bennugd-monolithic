/*
 *  Copyright � 2006-2011 SplinterGU (Fenix/Bennugd)
 *
 *  This file is part of Bennu - Game Development
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */

#ifndef __BGDDL_H
#define __BGDDL_H

#if defined(TARGET_ANDROID)
#include <android/log.h>
#define _printf(...)  __android_log_print(ANDROID_LOG_INFO, "BennuGD", __VA_ARGS__)
#define _fprintf(stderr, ...) __android_log_print(ANDROID_LOG_INFO, "BennuGD Error", __VA_ARGS__)
#elif defined(TARGET_IOS)
#define _printf(...) NSLog(@__VA_ARGS__)
#elif defined(TARGET_PSP)
#define _printf(...) pspDebugScreenPrintf(__VA_ARGS__)
#else
#define _printf(...) printf(__VA_ARGS__)
#define _fprintf(...) fprintf(__VA_ARGS__)
#endif

/* --------------------------------------------------------------------------- */

#ifndef __BGDC__

#ifdef WIN32
#define DLLEXPORT   __declspec(dllexport)
#define DLLIMPORT   __declspec(dllimport)
#else
#define DLLEXPORT
#define DLLIMPORT
#endif

/* --------------------------------------------------------------------------- */
/*
 *  ENDIANESS TRICKS
 */

#include "arrange.h"

#include <typedef_st.h>
#include <sysprocs_st.h>

#include <commons_defs.h>

#endif

/* --------------------------------------------------------------------------- */
#include <instance_st.h>
#ifdef __MONOLITHIC__
#include <typedef_st.h>
#endif

/* --------------------------------------------------------------------------- */

#define __bgdexport(m,a)    m##_##a

/* --------------------------------------------------------------------------- */

typedef struct
{
    char * var;
    void * data_offset;
    int size;
    int elements;
} DLVARFIXUP;

typedef struct
{
    char * name;
    char * paramtypes;
    int type;
    void * func;
} DLSYSFUNCS;

typedef struct
{
    char * name;
    BASETYPE type;
    int code;
} DLCONSTANT;

/* --------------------------------------------------------------------------- */

#endif
