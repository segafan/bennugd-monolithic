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

#ifndef __MODMATHI_SYMBOLS_H
#define __MODMATHI_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int mathi_abs( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_pow( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_sqrt( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_cos( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_sin( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_tan( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_acos( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_asin( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_atan( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_atan2( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_isinf( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_isnan( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_finite( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_get_disty( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_fget_angle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_fget_dist( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_near_angle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int mathi_get_distx( INSTANCE * my, int * params );
#endif

/* --------------------------------------------------------------------------- */

DLCONSTANT __bgdexport( mod_mathi, constants_def )[] =
{
    { "PI"  , TYPE_INT  , 180000    },
    { NULL  , 0         , 0         }
} ;

/* --------------------------------------------------------------------------- */
/* Declaracion de funciones                                                    */

DLSYSFUNCS __bgdexport( mod_mathi, functions_exports )[] =
{
    { "ABS"         , "F"       , TYPE_FLOAT    , SYSMACRO(mathi_abs)          },
    { "POW"         , "FF"      , TYPE_FLOAT    , SYSMACRO(mathi_pow)          },
    { "SQRT"        , "F"       , TYPE_FLOAT    , SYSMACRO(mathi_sqrt)         },
	
    { "COS"         , "I"       , TYPE_FLOAT    , SYSMACRO(mathi_cos)          },
    { "SIN"         , "I"       , TYPE_FLOAT    , SYSMACRO(mathi_sin)          },
    { "TAN"         , "I"       , TYPE_FLOAT    , SYSMACRO(mathi_tan)          },
    { "ACOS"        , "I"       , TYPE_FLOAT    , SYSMACRO(mathi_acos)         },
    { "ASIN"        , "I"       , TYPE_FLOAT    , SYSMACRO(mathi_asin)         },
    { "ATAN"        , "I"       , TYPE_FLOAT    , SYSMACRO(mathi_atan)         },
    { "ATAN2"       , "II"      , TYPE_FLOAT    , SYSMACRO(mathi_atan2)        },
	
    { "ISINF"       , "F"       , TYPE_INT      , SYSMACRO(mathi_isinf)        },
    { "ISNAN"       , "F"       , TYPE_INT      , SYSMACRO(mathi_isnan)        },
    { "FINITE"      , "F"       , TYPE_INT      , SYSMACRO(mathi_finite)       },
	
    { "FGET_ANGLE"  , "IIII"    , TYPE_INT      , SYSMACRO(mathi_fget_angle)   },
    { "FGET_DIST"   , "IIII"    , TYPE_INT      , SYSMACRO(mathi_fget_dist)    },
    { "NEAR_ANGLE"  , "III"     , TYPE_INT      , SYSMACRO(mathi_near_angle)   },
    { "GET_DISTX"   , "II"      , TYPE_INT      , SYSMACRO(mathi_get_distx)    },
    { "GET_DISTY"   , "II"      , TYPE_INT      , SYSMACRO(mathi_get_disty)    },
	
    { 0             , 0         , 0             , 0                 }
};

#endif
