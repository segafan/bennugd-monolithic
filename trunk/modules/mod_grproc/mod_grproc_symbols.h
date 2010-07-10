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

#ifndef __MODGRPROC_SYMBOLS_H
#define __MODGRPROC_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern DLVARFIXUP __bgdexport( mod_grproc, locals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_grproc, globals_fixup )[];
extern void __bgdexport( mod_grproc, module_initialize )();
extern void __bgdexport( mod_grproc, process_exec_hook )( INSTANCE * r );

extern CONDITIONALLY_STATIC int grproc_advance( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int grproc_xadvance( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int grproc_get_angle( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int grproc_get_dist( INSTANCE * a, int * params );
extern CONDITIONALLY_STATIC int grproc_get_real_point( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int grproc_collision( INSTANCE * my, int * params );
#endif

/* ----------------------------------------------------------------- */

char __bgdexport( mod_grproc, locals_def )[] =
    "STRUCT _mod_grproc_reserved\n"
    "int type_scan;\n"
    "int id_scan;\n"
    "int context;\n"
    "END\n";

/* ---------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_grproc, functions_exports )[] =
{
    { "ADVANCE"         , "I"   , TYPE_INT  , SYSMACRO(grproc_advance)        },
    { "XADVANCE"        , "II"  , TYPE_INT  , SYSMACRO(grproc_xadvance)       },
    { "GET_ANGLE"       , "I"   , TYPE_INT  , SYSMACRO(grproc_get_angle)      },
    { "GET_DIST"        , "I"   , TYPE_INT  , SYSMACRO(grproc_get_dist)       },
    { "COLLISION"       , "I"   , TYPE_INT  , SYSMACRO(grproc_collision)      },
    { "GET_REAL_POINT"  , "IPP" , TYPE_INT  , SYSMACRO(grproc_get_real_point) },

    { 0                 , 0     , 0         , 0                     }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_grproc, modules_dependency )[] =
{
    "libmouse",
    "libgrbase",
    "libvideo",
    "librender",
    "libblit",
    NULL
};

#endif
