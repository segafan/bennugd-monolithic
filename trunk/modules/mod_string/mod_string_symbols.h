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

#ifndef __MODSTRING_H
#define __MODSTRING_H

#include <bgddl.h>

#ifdef __BGDC__
DLSYSFUNCS  __bgdexport( mod_string, functions_exports )[] =
{
    { "STRLEN"     , "S"   , TYPE_INT   , 0 },
    { "LEN"        , "S"   , TYPE_INT   , 0 },
    { "UCASE"      , "S"   , TYPE_STRING, 0 },
    { "LCASE"      , "S"   , TYPE_STRING, 0 },
    { "STRCASECMP" , "SS"  , TYPE_INT   , 0 },
    { "SUBSTR"     , "SII" , TYPE_STRING, 0 },
    { "SUBSTR"     , "SI"  , TYPE_STRING, 0 },
    { "FIND"       , "SS"  , TYPE_INT   , 0 },
    { "FIND"       , "SSI" , TYPE_INT   , 0 },
    { "LPAD"       , "SI"  , TYPE_STRING, 0 },
    { "RPAD"       , "SI"  , TYPE_STRING, 0 },
    { "ITOA"       , "I"   , TYPE_STRING, 0 },
    { "FTOA"       , "F"   , TYPE_STRING, 0 },
    { "ATOI"       , "S"   , TYPE_INT   , 0 },
    { "ATOF"       , "S"   , TYPE_FLOAT , 0 },
    { "ASC"        , "S"   , TYPE_BYTE  , 0 },
    { "CHR"        , "I"   , TYPE_STRING, 0 },
    { "TRIM"       , "S"   , TYPE_STRING, 0 },
    { "STRREV"     , "S"   , TYPE_STRING, 0 },
    { "FORMAT"     , "I"   , TYPE_STRING, 0 },
    { "FORMAT"     , "F"   , TYPE_STRING, 0 },
    { "FORMAT"     , "FI"  , TYPE_STRING, 0 },
    { 0            , 0     , 0          , 0 }
};
#else
extern DLSYSFUNCS  __bgdexport( mod_string, functions_exports )[];
#endif

#endif
