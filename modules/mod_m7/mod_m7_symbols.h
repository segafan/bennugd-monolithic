/*
 *  Copyright © 2006-2011 SplinterGU (Fenix/Bennugd)
 *  Copyright © 2002-2006 Fenix Team (Fenix)
 *  Copyright © 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

#ifndef __MODM7_SYMBOLS_H
#define __MODM7_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
#define C_M7        2

DLCONSTANT __bgdexport( mod_m7, constants_def )[] =
{
    { "C_M7", TYPE_INT, C_M7 },
    { NULL  , 0       , 0 }
} ;

/* --------------------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion) */
char __bgdexport( mod_m7, globals_def )[] =
    "STRUCT m7[9]\n"
    "camera;\n"
    "height = 32;\n"
    "distance = 64;\n"
    "horizon = 0;\n"
    "focus = 256;\n"
    "z = 256;\n"
    "color = 0;\n"
    "flags = 0;\n"
    "END\n" ;

/* --------------------------------------------------------------------------- */
/* Definicion de variables locales (usada en tiempo de compilacion)  */
char __bgdexport( mod_m7, locals_def )[] =
    "ctype;\n"
    "cnumber;\n"
    "height;\n"
    "STRUCT _m7_reserved\n"
    "  distance1;\n"
    "END;\n";

DLSYSFUNCS  __bgdexport( mod_m7, functions_exports )[] =
{
    { "MODE7_START" , "IIIIII", TYPE_INT , 0 },
    { "MODE7_STOP"  , "I"     , TYPE_INT , 0 },
    { "START_MODE7" , "IIIIII", TYPE_INT , 0 },
    { "STOP_MODE7"  , "I"     , TYPE_INT , 0 },
    { NULL          , NULL    , 0        , 0 }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_m7, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "librender",
    NULL
};
#else
extern DLCONSTANT __bgdexport( mod_m7, constants_def )[];
extern char       __bgdexport( mod_m7, globals_def )[];
extern char       __bgdexport( mod_m7, locals_def )[];
extern DLVARFIXUP __bgdexport( mod_m7, globals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_m7, locals_fixup )[];
extern void __bgdexport( mod_m7, module_initialize )();
extern DLSYSFUNCS  __bgdexport( mod_m7, functions_exports )[];
extern char * __bgdexport( mod_m7, modules_dependency )[];
#endif


#endif
