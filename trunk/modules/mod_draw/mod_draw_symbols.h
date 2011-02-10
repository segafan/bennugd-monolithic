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

#ifndef __MODDRAW_SYMBOLS_H
#define __MODDRAW_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
DLSYSFUNCS __bgdexport( mod_draw, functions_exports )[] =
{
    /* Funciones de primitivas */
    { "DRAWING_MAP"     , "II"          , TYPE_INT  , 0 },
    { "DRAWING_COLOR"   , "I"           , TYPE_INT  , 0 },
    { "DRAW_LINE"       , "IIII"        , TYPE_INT  , 0 },
    { "DRAW_RECT"       , "IIII"        , TYPE_INT  , 0 },
    { "DRAW_BOX"        , "IIII"        , TYPE_INT  , 0 },
    { "DRAW_CIRCLE"     , "III"         , TYPE_INT  , 0 },
    { "DRAW_FCIRCLE"    , "III"         , TYPE_INT  , 0 },
    { "DRAW_CURVE"      , "IIIIIIIII"   , TYPE_INT  , 0 },
    { "DRAWING_Z"       , "I"           , TYPE_INT  , 0 },
    { "DELETE_DRAW"     , "I"           , TYPE_INT  , 0 },
    { "MOVE_DRAW"       , "III"         , TYPE_INT  , 0 },
    { "DRAWING_ALPHA"   , "I"           , TYPE_INT  , 0 },
    { "DRAWING_STIPPLE" , "I"           , TYPE_INT  , 0 },
    { "PUT_PIXEL"       , "III"         , TYPE_INT  , 0 },
    { "GET_PIXEL"       , "II"          , TYPE_INT  , 0 },
    { "MAP_GET_PIXEL"   , "IIII"        , TYPE_INT  , 0 },
    { "MAP_PUT_PIXEL"   , "IIIII"       , TYPE_INT  , 0 },
    { NULL              , NULL          , 0         , NULL }
};

char * __bgdexport( mod_draw, modules_dependency )[] =
{
    "libgrbase",
    "librender",
    "libdraw",
    NULL
};
#else
extern DLSYSFUNCS __bgdexport( mod_draw, functions_exports )[];
extern char * __bgdexport( mod_draw, modules_dependency )[];
#endif

#endif
