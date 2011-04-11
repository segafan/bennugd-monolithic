/*
 *  Copyright � 2006-2011 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
 *
 *  This file is part of Bennu - Game Development
 *
 *  Bennu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Bennu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgddl.h"
#include "xstrings.h"

#if defined(TARGET_ANDROID)
#include <android/log.h>
#define printf(...)  __android_log_print(ANDROID_LOG_INFO, "BennuGD", __VA_ARGS__)
#define fprintf(stderr, ...) __android_log_print(ANDROID_LOG_INFO, "BennuGD Error", __VA_ARGS__)
#endif

/* ---------------------------------------------------------------------- */

static int modsay_say( INSTANCE * my, int * params )
{
    /* Show debugging info also in stdout */
    printf( "%s\n", string_get( params[0] ) );
    fflush( stdout );
    string_discard( params[0] ) ;
    return 1 ;
}

/* ---------------------------------------------------------------------- */

static int modsay_say_fast( INSTANCE * my, int * params )
{
    /* Show debugging info also in stdout */
    printf( "%s\n", string_get( params[0] ) );
    string_discard( params[0] ) ;
    return 1 ;
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_say, functions_exports )[] =
{
    { "SAY"     , "S", TYPE_UNDEFINED, modsay_say     },
    { "SAY_FAST", "S", TYPE_UNDEFINED, modsay_say_fast},
    { 0         , 0  , 0             , 0              }
};

/* ----------------------------------------------------------------- */
