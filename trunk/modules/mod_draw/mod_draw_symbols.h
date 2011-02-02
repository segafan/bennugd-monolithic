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

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int moddraw_drawing_map( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_drawing_at( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_drawing_stipple( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_delete_drawing( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_move_drawing( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_drawing_color( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_drawing_alpha( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_box( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_rect( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_line( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_circle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_fcircle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_bezier( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_get_pixel( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_put_pixel( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_map_get_pixel( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int moddraw_map_put_pixel( INSTANCE * my, int * params );
#endif

/* --------------------------------------------------------------------------- */
/* Declaracion de funciones                                                    */

DLSYSFUNCS __bgdexport( mod_draw, functions_exports )[] =
{
    /* Funciones de primitivas */
    { "DRAWING_MAP"     , "II"          , TYPE_INT  , SYSMACRO(moddraw_drawing_map)       },
    { "DRAWING_COLOR"   , "I"           , TYPE_INT  , SYSMACRO(moddraw_drawing_color)     },
    { "DRAW_LINE"       , "IIII"        , TYPE_INT  , SYSMACRO(moddraw_line)              },
    { "DRAW_RECT"       , "IIII"        , TYPE_INT  , SYSMACRO(moddraw_rect)              },
    { "DRAW_BOX"        , "IIII"        , TYPE_INT  , SYSMACRO(moddraw_box)               },
    { "DRAW_CIRCLE"     , "III"         , TYPE_INT  , SYSMACRO(moddraw_circle)            },
    { "DRAW_FCIRCLE"    , "III"         , TYPE_INT  , SYSMACRO(moddraw_fcircle)           },
    { "DRAW_CURVE"      , "IIIIIIIII"   , TYPE_INT  , SYSMACRO(moddraw_bezier)            },
    { "DRAWING_Z"       , "I"           , TYPE_INT  , SYSMACRO(moddraw_drawing_at)        },
    { "DELETE_DRAW"     , "I"           , TYPE_INT  , SYSMACRO(moddraw_delete_drawing)    },
    { "MOVE_DRAW"       , "III"         , TYPE_INT  , SYSMACRO(moddraw_move_drawing)      },
    { "DRAWING_ALPHA"   , "I"           , TYPE_INT  , SYSMACRO(moddraw_drawing_alpha)     },
    { "DRAWING_STIPPLE" , "I"           , TYPE_INT  , SYSMACRO(moddraw_drawing_stipple)   },
    { "PUT_PIXEL"       , "III"         , TYPE_INT  , SYSMACRO(moddraw_put_pixel)         },
    { "GET_PIXEL"       , "II"          , TYPE_INT  , SYSMACRO(moddraw_get_pixel)         },
    { "MAP_GET_PIXEL"   , "IIII"        , TYPE_INT  , SYSMACRO(moddraw_map_get_pixel)     },
    { "MAP_PUT_PIXEL"   , "IIIII"       , TYPE_INT  , SYSMACRO(moddraw_map_put_pixel)     },
    { NULL              , NULL          , 0         , NULL                      }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_draw, modules_dependency )[] =
{
    "libgrbase",
    "librender",
    "libdraw",
    NULL
};

#endif
