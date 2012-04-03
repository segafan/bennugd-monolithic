/*
 *  Copyright © 2006-2010 SplinterGU (Fenix/Bennugd)
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

#ifndef __MODVIDEO_H
#define __MODVIDEO_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modvideo_set_mode( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modvideo_set_mode_2( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modvideo_set_mode_3( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modvideo_set_mode_4( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modvideo_set_fps( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modvideo_list_modes( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modvideo_mode_is_ok( INSTANCE * my, int * params );

extern DLVARFIXUP __bgdexport( mod_video, globals_fixup )[];
#endif

/* --------------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_video, functions_exports )[] =
{
    /* Video */
    { "SET_MODE"        , "I"     , TYPE_INT        , SYSMACRO(modvideo_set_mode)         },
    { "SET_MODE"        , "II"    , TYPE_INT        , SYSMACRO(modvideo_set_mode_2)       },
    { "SET_MODE"        , "III"   , TYPE_INT        , SYSMACRO(modvideo_set_mode_3)       },
    { "SET_MODE"        , "IIII"  , TYPE_INT        , SYSMACRO(modvideo_set_mode_4)       },
    { "SET_FPS"         , "II"    , TYPE_INT        , SYSMACRO(modvideo_set_fps)          },
    { "GET_MODES"       , "II"    , TYPE_POINTER    , SYSMACRO(modvideo_list_modes)       },
    { "MODE_IS_OK"      , "IIII"  , TYPE_INT        , SYSMACRO(modvideo_mode_is_ok)       },
    { 0                 , 0       , 0               , 0                         }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_video, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "librender",
    NULL
};

#endif
