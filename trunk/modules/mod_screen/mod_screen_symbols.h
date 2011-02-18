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

#ifndef __MODSCREEN_SYMBOLS_H
#define __MODSCREEN_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
DLSYSFUNCS  __bgdexport( mod_screen, functions_exports )[] =
{
    { "REGION_DEFINE"        , "IIIII"      , TYPE_INT      , 0 },
    { "REGION_OUT"           , "II"         , TYPE_INT      , 0 },
    { "PUT"                  , "IIII"       , TYPE_INT      , 0 },
    { "XPUT"                 , "IIIIIIII"   , TYPE_INT      , 0 },
    { "SCREEN_PUT"           , "II"         , TYPE_INT      , 0 },
    { "SCREEN_CLEAR"         , ""           , TYPE_INT      , 0 },
    { "SCREEN_GET"           , ""           , TYPE_INT      , 0 },
    { "DEFINE_REGION"        , "IIIII"      , TYPE_INT      , 0 },
    { "OUT_REGION"           , "II"         , TYPE_INT      , 0 },
    { "PUT_SCREEN"           , "II"         , TYPE_INT      , 0 },
    { "CLEAR_SCREEN"         , ""           , TYPE_INT      , 0 },
    { "GET_SCREEN"           , ""           , TYPE_INT      , 0 },
    { 0                     , 0             , 0             , 0 }
};

char * __bgdexport( mod_screen, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "libblit",
    "librender",
    NULL
};
#else
extern DLVARFIXUP __bgdexport( mod_screen, locals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_screen, globals_fixup )[];
extern DLSYSFUNCS  __bgdexport( mod_screen, functions_exports )[];
extern char * __bgdexport( mod_screen, modules_dependency )[];
#endif

#endif
