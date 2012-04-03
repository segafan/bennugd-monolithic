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

#ifndef __MODBLENDOP_SYMBOLS_H
#define __MODBLENDOP_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modblendop_create_blendop( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_apply( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_assign( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_free( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_identity( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_grayscale( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_translucency( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_intensity( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_swap( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modblendop_tint( INSTANCE * my, int * params );
#endif

/* ---------------------------------------------------------------------- */

DLSYSFUNCS __bgdexport( mod_blendop, functions_exports)[] =
{
    /* Blendops */
    { "BLENDOP_NEW"          , ""      , TYPE_INT   , SYSMACRO(modblendop_create_blendop) },
    { "BLENDOP_IDENTITY"     , "I"     , TYPE_INT   , SYSMACRO(modblendop_identity)       },
    { "BLENDOP_TINT"         , "IFIII" , TYPE_INT   , SYSMACRO(modblendop_tint)           },
    { "BLENDOP_TRANSLUCENCY" , "IF"    , TYPE_INT   , SYSMACRO(modblendop_translucency)   },
    { "BLENDOP_INTENSITY"    , "IF"    , TYPE_INT   , SYSMACRO(modblendop_intensity)      },
    { "BLENDOP_SWAP"         , "I"     , TYPE_INT   , SYSMACRO(modblendop_swap)           },
    { "BLENDOP_ASSIGN"       , "III"   , TYPE_INT   , SYSMACRO(modblendop_assign)         },
    { "BLENDOP_APPLY"        , "III"   , TYPE_INT   , SYSMACRO(modblendop_apply)          },
    { "BLENDOP_FREE"         , "I"     , TYPE_INT   , SYSMACRO(modblendop_free)           },
    { "BLENDOP_GRAYSCALE"    , "II"    , TYPE_INT   , SYSMACRO(modblendop_grayscale)      },

    { 0                      , 0       , 0          , 0                                 }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_blendop, modules_dependency )[] =
{
    "libgrbase",
    NULL
};

#endif
