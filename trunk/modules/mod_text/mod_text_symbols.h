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

#ifndef __MODTEXT_SYMBOLS_H
#define __MODTEXT_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
#define ALIGN_TOP_LEFT      0
#define ALIGN_TOP           1
#define ALIGN_TOP_RIGHT     2
#define ALIGN_CENTER_LEFT   3
#define ALIGN_CENTER        4
#define ALIGN_CENTER_RIGHT  5
#define ALIGN_BOTTOM_LEFT   6
#define ALIGN_BOTTOM        7
#define ALIGN_BOTTOM_RIGHT  8

DLCONSTANT __bgdexport( mod_text, constants_def)[] =
{
    { "ALL_TEXT"            , TYPE_INT  , 0                     },
    { "ALIGN_TOP_LEFT"      , TYPE_INT  , ALIGN_TOP_LEFT        },
    { "ALIGN_TOP"           , TYPE_INT  , ALIGN_TOP             },
    { "ALIGN_TOP_RIGHT"     , TYPE_INT  , ALIGN_TOP_RIGHT       },
    { "ALIGN_CENTER_LEFT"   , TYPE_INT  , ALIGN_CENTER_LEFT     },
    { "ALIGN_CENTER"        , TYPE_INT  , ALIGN_CENTER          },
    { "ALIGN_CENTER_RIGHT"  , TYPE_INT  , ALIGN_CENTER_RIGHT    },
    { "ALIGN_BOTTOM_LEFT"   , TYPE_INT  , ALIGN_BOTTOM_LEFT     },
    { "ALIGN_BOTTOM"        , TYPE_INT  , ALIGN_BOTTOM          },
    { "ALIGN_BOTTOM_RIGHT"  , TYPE_INT  , ALIGN_BOTTOM_RIGHT    },
    { NULL                  , 0         , 0                     }
} ;

DLSYSFUNCS  __bgdexport( mod_text, functions_exports)[] = {
    { "WRITE"               , "IIIIS"   , TYPE_INT  , 0 },
    { "WRITE_INT"           , "IIIIP"   , TYPE_INT  , 0 },
    { "MOVE_TEXT"           , "III"     , TYPE_INT  , 0 },
    { "DELETE_TEXT"         , "I"       , TYPE_INT  , 0 },
    { "WRITE_IN_MAP"        , "ISI"     , TYPE_INT  , 0 },
    { "TEXT_WIDTH"          , "IS"      , TYPE_INT  , 0 },
    { "TEXT_HEIGHT"         , "IS"      , TYPE_INT  , 0 },
    { "GET_TEXT_COLOR"      , ""        , TYPE_INT  , 0 },
    { "SET_TEXT_COLOR"      , "I"       , TYPE_INT  , 0 },
    { "WRITE_VAR"           , "IIIIV++" , TYPE_INT  , 0 },
    { "WRITE_FLOAT"         , "IIIIP"   , TYPE_INT  , 0 },
    { "WRITE_STRING"        , "IIIIP"   , TYPE_INT  , 0 },
    { 0                     , 0         , 0         , 0 }
};

char * __bgdexport( mod_text, modules_dependency)[] =
{
    "libgrbase",
    "libblit",
    "libtext",
    "libfont",
    NULL
};
#else
extern DLCONSTANT __bgdexport( mod_text, constants_def)[];
extern DLSYSFUNCS __bgdexport( mod_text, functions_exports)[];
extern char *     __bgdexport( mod_text, modules_dependency)[];
#endif

#endif
