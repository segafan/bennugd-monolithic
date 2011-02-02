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

#ifndef __MODWM_SYMBOLS_H
#define __MODWM_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int bgd_set_title( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int bgd_set_icon( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int bgd_minimize( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int bgd_move_window( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int bgd_get_window_pos( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int bgd_get_window_size( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int bgd_get_desktop_size( INSTANCE * my, int * params );
#endif

/* --------------------------------------------------------------------------- */

DLSYSFUNCS __bgdexport( mod_wm, functions_exports )[] =
{
    /* Funciones de ventana */
    { "SET_TITLE"           , "S"   , TYPE_INT , SYSMACRO(bgd_set_title)          },
    { "SET_ICON"            , "II"  , TYPE_INT , SYSMACRO(bgd_set_icon)           },
    { "MINIMIZE"            , ""    , TYPE_INT , SYSMACRO(bgd_minimize)           },
    { "MOVE_WINDOW"         , "II"  , TYPE_INT , SYSMACRO(bgd_move_window)        },
    { "SET_WINDOW_POS"      , "II"  , TYPE_INT , SYSMACRO(bgd_move_window)        },
    { "GET_WINDOW_POS"      , "PP"  , TYPE_INT , SYSMACRO(bgd_get_window_pos)     },
    { "GET_WINDOW_SIZE"     , "PPPP", TYPE_INT , SYSMACRO(bgd_get_window_size)    },
    { "GET_DESKTOP_SIZE"    , "PP"  , TYPE_INT , SYSMACRO(bgd_get_desktop_size)   },
    { 0                     , 0     , 0        , 0                      }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_wm, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "libwm",
    NULL
};

#endif
