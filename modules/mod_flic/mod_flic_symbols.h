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

#ifndef __MODFLIC_SYMBOLS_H
#define __MODFLIC_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modflic_start( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_reset( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_end( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_frame( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_startx1( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_startx2( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_resetx( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_endx( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_framex( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_params( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_move( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_z( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_angle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_size( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_flags( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modflic_getinfo( INSTANCE * my, int * params );
#endif

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_flic, functions_exports )[] =
{
    /* Animaciones FLI */
    { "START_FLI"       , "SII"         , TYPE_INT , SYSMACRO(modflic_start)        },
    { "END_FLI"         , ""            , TYPE_INT , SYSMACRO(modflic_end)          },
    { "FRAME_FLI"       , ""            , TYPE_INT , SYSMACRO(modflic_frame)        },
    { "RESET_FLI"       , ""            , TYPE_INT , SYSMACRO(modflic_reset)        },
	
    { "FLI_START"       , "SII"         , TYPE_INT , SYSMACRO(modflic_startx1)      },
    { "FLI_START"       , "SIIIIII"     , TYPE_INT , SYSMACRO(modflic_startx2)      },
    { "FLI_END"         , "I"           , TYPE_INT , SYSMACRO(modflic_endx)         },
    { "FLI_FRAME"       , "I"           , TYPE_INT , SYSMACRO(modflic_framex)       },
    { "FLI_RESET"       , "I"           , TYPE_INT , SYSMACRO(modflic_resetx)       },
	
    { "FLI_PARAMS"      , "IIIIIII"     , TYPE_INT , SYSMACRO(modflic_params)       },
    { "FLI_MOVE"        , "III"         , TYPE_INT , SYSMACRO(modflic_move)         },
    { "FLI_ANGLE"       , "II"          , TYPE_INT , SYSMACRO(modflic_angle)        },
    { "FLI_SIZE"        , "II"          , TYPE_INT , SYSMACRO(modflic_size)         },
    { "FLI_FLAGS"       , "II"          , TYPE_INT , SYSMACRO(modflic_flags)        },
    { "FLI_Z"           , "II"          , TYPE_INT , SYSMACRO(modflic_z)            },
    { "FLI_GETINFO"     , "IPPPPPPPPP"  , TYPE_INT , SYSMACRO(modflic_getinfo)      },
	
    { NULL              , NULL          , 0        , NULL                 }
};

#endif
