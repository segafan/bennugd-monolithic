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

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modscreen_define_region( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modscreen_out_region( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modscreen_put( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modscreen_xput( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modscreen_put_screen( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modscreen_clear_screen( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modscreen_get_screen( INSTANCE * my, int * params );

extern DLVARFIXUP __bgdexport( mod_screen, globals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_screen, locals_fixup )[];
#endif

/* --------------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_screen, functions_exports )[] =
{
    /* Regiones */
    { "REGION_DEFINE"        , "IIIII"  , TYPE_INT      , SYSMACRO(modscreen_define_region)   },
    { "REGION_OUT"           , "II"     , TYPE_INT      , SYSMACRO(modscreen_out_region)      },
    /* Fondo de pantalla */
    { "PUT"                  , "IIII"   , TYPE_INT      , SYSMACRO(modscreen_put)             },
    { "XPUT"                 ,"IIIIIIII", TYPE_INT      , SYSMACRO(modscreen_xput)            },
    { "SCREEN_PUT"           , "II"     , TYPE_INT      , SYSMACRO(modscreen_put_screen)      },
    { "SCREEN_CLEAR"         , ""       , TYPE_INT      , SYSMACRO(modscreen_clear_screen)    },
    /* Video */
    { "SCREEN_GET"           , ""       , TYPE_INT      , SYSMACRO(modscreen_get_screen)      },
    /* ------------ Compatibility ------------ */
    /* Regiones */
    { "DEFINE_REGION"        , "IIIII"  , TYPE_INT      , SYSMACRO(modscreen_define_region)   },
    { "OUT_REGION"           , "II"     , TYPE_INT      , SYSMACRO(modscreen_out_region)      },
    /* Fondo de pantalla */
    { "PUT_SCREEN"           , "II"     , TYPE_INT      , SYSMACRO(modscreen_put_screen)      },
    { "CLEAR_SCREEN"         , ""       , TYPE_INT      , SYSMACRO(modscreen_clear_screen)    },
    /* Video */
    { "GET_SCREEN"           , ""       , TYPE_INT      , SYSMACRO(modscreen_get_screen)      },
    { 0                     , 0         , 0             , 0                         }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_screen, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "libblit",
    "librender",
    NULL
};

#endif
