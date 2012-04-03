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

#ifndef __MODMATH_H
#define __MODMATH_H

#include <bgddl.h>
#include <unistd.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int math_abs( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_pow( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_sqrt( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_cos( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_sin( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_tan( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_acos( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_asin( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_atan( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_atan2( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_isinf( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_isnan( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_finite( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_get_disty( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_fget_angle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_fget_dist( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_near_angle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int math_get_distx( INSTANCE * my, int * params );
#endif


/* --------------------------------------------------------------------------- */

DLCONSTANT __bgdexport( mod_math, constants_def )[] =
{
    { "PI"  , TYPE_INT  , 180000    },
    { NULL  , 0         , 0         }
} ;

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_math, functions_exports )[] =
{
    { "ABS"         , "F"       , TYPE_FLOAT    , SYSMACRO(math_abs)          },
    { "POW"         , "FF"      , TYPE_FLOAT    , SYSMACRO(math_pow)          },
    { "SQRT"        , "F"       , TYPE_FLOAT    , SYSMACRO(math_sqrt)         },
	
    { "COS"         , "F"       , TYPE_FLOAT    , SYSMACRO(math_cos)          },
    { "SIN"         , "F"       , TYPE_FLOAT    , SYSMACRO(math_sin)          },
    { "TAN"         , "F"       , TYPE_FLOAT    , SYSMACRO(math_tan)          },
    { "ACOS"        , "F"       , TYPE_FLOAT    , SYSMACRO(math_acos)         },
    { "ASIN"        , "F"       , TYPE_FLOAT    , SYSMACRO(math_asin)         },
    { "ATAN"        , "F"       , TYPE_FLOAT    , SYSMACRO(math_atan)         },
    { "ATAN2"       , "FF"      , TYPE_FLOAT    , SYSMACRO(math_atan2)        },
	
    { "ISINF"       , "F"       , TYPE_INT      , SYSMACRO(math_isinf)        },
    { "ISNAN"       , "F"       , TYPE_INT      , SYSMACRO(math_isnan)        },
    { "FINITE"      , "F"       , TYPE_INT      , SYSMACRO(math_finite)       },
	
    { "FGET_ANGLE"  , "IIII"    , TYPE_INT      , SYSMACRO(math_fget_angle)   },
    { "FGET_DIST"   , "IIII"    , TYPE_INT      , SYSMACRO(math_fget_dist)    },
    { "NEAR_ANGLE"  , "III"     , TYPE_INT      , SYSMACRO(math_near_angle)   },
    { "GET_DISTX"   , "II"      , TYPE_INT      , SYSMACRO(math_get_distx)    },
    { "GET_DISTY"   , "II"      , TYPE_INT      , SYSMACRO(math_get_disty)    },
	
    { 0             , 0         , 0             , 0                 }
};

#endif
