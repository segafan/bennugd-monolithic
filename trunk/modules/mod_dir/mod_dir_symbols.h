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

#ifndef __MODDIR_SYMBOLS_H
#define __MODDIR_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
char  __bgdexport( mod_dir, globals_def )[] =
    "STRUCT fileinfo\n"
    "    STRING path;\n"
    "    STRING name;\n"
    "    directory;\n"
    "    hidden;\n"
    "    readonly;\n"
    "    size;\n"
    "    STRING created;\n"
    "    STRING modified;\n"
    "END\n";

DLSYSFUNCS __bgdexport( mod_dir, functions_exports)[] =
    {
        /* Archivos y directorios */
        { "CD"      , ""  , TYPE_STRING , 0 },
        { "CHDIR"   , "S" , TYPE_INT    , 0 },
        { "MKDIR"   , "S" , TYPE_INT    , 0 },
        { "RMDIR"   , "S" , TYPE_INT    , 0 },
        { "GLOB"    , "S" , TYPE_STRING , 0 },
        { "CD"      , "S" , TYPE_STRING , 0 },
        { "RM"      , "S" , TYPE_INT    , 0 },
        { "DIROPEN" , "S" , TYPE_INT    , 0 },
        { "DIRCLOSE", "I" , TYPE_INT    , 0 },
        { "DIRREAD" , "I" , TYPE_STRING , 0 },
        { 0         , 0   , 0           , 0 }
    };
#else
extern char  __bgdexport( mod_dir, globals_def )[];
extern DLVARFIXUP __bgdexport( mod_dir, globals_fixup)[];
extern DLSYSFUNCS __bgdexport( mod_dir, functions_exports)[];
#endif

#endif
