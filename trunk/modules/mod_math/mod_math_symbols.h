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

#ifndef __MODMATH_H
#define __MODMATH_H

#include <bgddl.h>

#ifdef __BGDC__
DLCONSTANT __bgdexport( mod_math, constants_def )[] =
{
    { "PI"  , TYPE_INT  , 180000    },
    { NULL  , 0         , 0         }
} ;

DLSYSFUNCS __bgdexport( mod_math, functions_exports )[] =
{
    { "ABS"         , "F"       , TYPE_FLOAT    , 0 },
    { "POW"         , "FF"      , TYPE_FLOAT    , 0 },
    { "SQRT"        , "F"       , TYPE_FLOAT    , 0 },
    { "COS"         , "F"       , TYPE_FLOAT    , 0 },
    { "SIN"         , "F"       , TYPE_FLOAT    , 0 },
    { "TAN"         , "F"       , TYPE_FLOAT    , 0 },
    { "ACOS"        , "F"       , TYPE_FLOAT    , 0 },
    { "ASIN"        , "F"       , TYPE_FLOAT    , 0 },
    { "ATAN"        , "F"       , TYPE_FLOAT    , 0 },
    { "ATAN2"       , "FF"      , TYPE_FLOAT    , 0 },
    { "ISINF"       , "F"       , TYPE_INT      , 0 },
    { "ISNAN"       , "F"       , TYPE_INT      , 0 },
    { "FINITE"      , "F"       , TYPE_INT      , 0 },
    { "FGET_ANGLE"  , "IIII"    , TYPE_INT      , 0 },
    { "FGET_DIST"   , "IIII"    , TYPE_INT      , 0 },
    { "NEAR_ANGLE"  , "III"     , TYPE_INT      , 0 },
    { "GET_DISTX"   , "II"      , TYPE_INT      , 0 },
    { "GET_DISTY"   , "II"      , TYPE_INT      , 0 },
    { 0             , 0         , 0             , 0 }
};
#else
extern DLCONSTANT __bgdexport( mod_math, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_math, functions_exports )[];
#endif

#endif
