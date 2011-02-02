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

#ifndef __MODREGEX_SYMBOLS_H
#define __MODREGEX_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modregex_regex (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modregex_regex_replace (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modregex_split (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modregex_join (INSTANCE * my, int * params);

extern DLVARFIXUP __bgdexport( mod_regex, globals_fixup) [];
#endif

/* ----------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion) */

char __bgdexport( mod_regex, globals_def )[] = "STRING regex_reg[15];\n";

/* ---------------------------------------------------------------------- */

DLSYSFUNCS __bgdexport( mod_regex, functions_exports) [] = {
    /* Regex */
    { "REGEX"                , "SS"    , TYPE_INT    , SYSMACRO(modregex_regex)           },
    { "REGEX_REPLACE"        , "SSS"   , TYPE_STRING , SYSMACRO(modregex_regex_replace)   },
    { "SPLIT"                , "SSPI"  , TYPE_INT    , SYSMACRO(modregex_split)           },
    { "JOIN"                 , "SPI"   , TYPE_STRING , SYSMACRO(modregex_join)            },
    { 0                      , 0       , 0           , 0                        }
};

#endif
