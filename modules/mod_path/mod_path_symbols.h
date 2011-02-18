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

#ifndef __MODPATH_SYMBOLS_H
#define __MODPATH_SYMBOLS_H

#include <bgddl.h>

#define PF_NODIAG       1
#define PF_REVERSE      2

#ifdef __BGDC__
DLCONSTANT __bgdexport( mod_path, constants_def )[] =
{
    { "PF_NODIAG"   , TYPE_INT, PF_NODIAG   },
    { "PF_REVERSE"  , TYPE_INT, PF_REVERSE  },
    { NULL          , 0       , 0           }
} ;

DLSYSFUNCS __bgdexport( mod_path, functions_exports )[] =
{
    /* Path finding */
    { "PATH_FIND"   , "IIIIIII", TYPE_INT   , 0 },
    { "PATH_GETXY"  , "PP"     , TYPE_INT   , 0 },
    { "PATH_WALL"   , "I"      , TYPE_INT   , 0 },
    { 0             , 0        , 0          , 0 }
};

char * __bgdexport( mod_path, modules_dependency )[] =
{
    "libgrbase",
    NULL
};
#else
extern DLCONSTANT __bgdexport( mod_path, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_path, functions_exports )[];
extern char * __bgdexport( mod_path, modules_dependency )[];
#endif

#endif
