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

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modstring_strlen( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_strupper( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_strlower( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_strcasecmp( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_substr( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_substr2( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_strfind( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_strfindSSI( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_lpad( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_rpad( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_itos( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_ftos( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_stoi( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_stof( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_asc( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_chr( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_trim( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_strrev( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_formatI( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_formatF( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modstring_formatFI( INSTANCE * my, int * params );
#endif

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_string, functions_exports )[] =
{
    { "STRLEN"     , "S"   , TYPE_INT   , SYSMACRO(modstring_strlen)     },
    { "LEN"        , "S"   , TYPE_INT   , SYSMACRO(modstring_strlen)     },
    { "UCASE"      , "S"   , TYPE_STRING, SYSMACRO(modstring_strupper)   },
    { "LCASE"      , "S"   , TYPE_STRING, SYSMACRO(modstring_strlower)   },
    { "STRCASECMP" , "SS"  , TYPE_INT   , SYSMACRO(modstring_strcasecmp) },
    { "SUBSTR"     , "SII" , TYPE_STRING, SYSMACRO(modstring_substr)     },
    { "SUBSTR"     , "SI"  , TYPE_STRING, SYSMACRO(modstring_substr2)    },
    { "FIND"       , "SS"  , TYPE_INT   , SYSMACRO(modstring_strfind)    },
    { "FIND"       , "SSI" , TYPE_INT   , SYSMACRO(modstring_strfindSSI) },
    { "LPAD"       , "SI"  , TYPE_STRING, SYSMACRO(modstring_lpad)       },
    { "RPAD"       , "SI"  , TYPE_STRING, SYSMACRO(modstring_rpad)       },
    { "ITOA"       , "I"   , TYPE_STRING, SYSMACRO(modstring_itos)       },
    { "FTOA"       , "F"   , TYPE_STRING, SYSMACRO(modstring_ftos)       },
    { "ATOI"       , "S"   , TYPE_INT   , SYSMACRO(modstring_stoi)       },
    { "ATOF"       , "S"   , TYPE_FLOAT , SYSMACRO(modstring_stof)       },
    { "ASC"        , "S"   , TYPE_BYTE  , SYSMACRO(modstring_asc)        },
    { "CHR"        , "I"   , TYPE_STRING, SYSMACRO(modstring_chr)        },
    { "TRIM"       , "S"   , TYPE_STRING, SYSMACRO(modstring_trim)       },
    { "STRREV"     , "S"   , TYPE_STRING, SYSMACRO(modstring_strrev)     },
    { "FORMAT"     , "I"   , TYPE_STRING, SYSMACRO(modstring_formatI)    },
    { "FORMAT"     , "F"   , TYPE_STRING, SYSMACRO(modstring_formatF)    },
    { "FORMAT"     , "FI"  , TYPE_STRING, SYSMACRO(modstring_formatFI)   },
    { 0            , 0     , 0          , 0                    }
};

#endif
