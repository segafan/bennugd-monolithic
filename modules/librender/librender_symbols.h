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

#ifndef __RENDER_SYMBOLS_H
#define __RENDER_SYMBOLS_H

#include <bgddl.h>
#include "librender.h"

#ifdef __BGDC__
/* --------------------------------------------------------------------------- */

char * __bgdexport( librender, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "libblit",
    NULL
};

/* --------------------------------------------------------------------------- */

DLCONSTANT __bgdexport( librender, constants_def )[] =
{
    { "C_SCREEN",           TYPE_DWORD, C_SCREEN },

    { "PARTIAL_DUMP",       TYPE_DWORD, 0 },
    { "COMPLETE_DUMP",      TYPE_DWORD, 1 },
    { "NO_RESTORE",         TYPE_DWORD, -1 },
    { "PARTIAL_RESTORE",    TYPE_DWORD, 0 },
    { "COMPLETE_RESTORE",   TYPE_DWORD, 1 },

    { "BACKGROUND",         TYPE_DWORD, 0 },
    { "SCREEN",             TYPE_DWORD, -1 },

    { "SCALE_SCALE2X",      TYPE_DWORD, SCALE_SCALE2X    },
    { "SCALE_HQ2X",         TYPE_DWORD, SCALE_HQ2X       },
    { "SCALE_SCANLINE2X",   TYPE_DWORD, SCALE_SCANLINE2X },
    { "SCALE_NORMAL2X",     TYPE_DWORD, SCALE_NOFILTER   },
    { "SCALE_NOFILTER",     TYPE_DWORD, SCALE_NOFILTER   },

    { NULL          , 0         ,  0  }
} ;

/* --------------------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion) */

char __bgdexport( librender, globals_def )[] =

    /* Frame */

    "fps;\n"
    "speed_gauge = 0;\n"
    "FLOAT frame_time = 0;\n"

    /* Screen */

    "restore_type;\n"
    "dump_type;\n"

    /* Fade */

    "fading;\n"
    "alpha_steps = 16;\n"
    ;

/* --------------------------------------------------------------------------- */

char __bgdexport( librender, locals_def )[] =

    /* Render */

    "ctype;\n"
    "cnumber;\n"

    "x;\n"
    "y;\n"
    "z;\n"
    "file;\n"
    "graph;\n"
    "size=100;\n"
    "angle;\n"
    "flags;\n"
    "alpha=255;\n"
    "palette=0;\n"
    "region;\n"
    "resolution;\n"
    "size_x=100;\n"
    "size_y=100;\n"
    "blendop=0;\n"
    "pointer xgraph;\n"

    "STRUCT _render_reserved_\n"
    "object_id=0;\n"
    "graph_ptr=0;\n"
    "xgraph_flags;\n"
    "STRUCT _saved_\n"
    "x;\n"
    "y;\n"
    "z;\n"
    "file;\n"
    "graph;\n"
    "size;\n"
    "angle;\n"
    "flags;\n"
    "alpha;\n"
    "palette;\n"
    "size_x;\n"
    "size_y;\n"
    "blendop;\n"
    "pointer xgraph;\n"
    "centerx;\n"
    "centery;\n"
    "END\n"
    "END\n"
    ;
#else
extern char __bgdexport( librender, modules_dependency )[];
extern DLCONSTANT __bgdexport( librender, constants_def )[];
extern DLVARFIXUP __bgdexport( librender, globals_fixup )[];
extern DLVARFIXUP __bgdexport( librender, locals_fixup )[];
extern char __bgdexport( librender, globals_def )[];
extern char __bgdexport( librender, locals_def )[];
extern HOOK __bgdexport( librender, handler_hooks )[];
extern void __bgdexport( librender, module_initialize )();
extern void __bgdexport( librender, module_finalize )();
extern void __bgdexport( librender, instance_create_hook )( INSTANCE * r );
extern void __bgdexport( librender, instance_destroy_hook )( INSTANCE * r );
#endif

#endif
