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

#ifndef __SCROLL_SYMBOLS_H
#define __SCROLL_SYMBOLS_H

#include <bgddl.h>
#include "libscroll.h"

#ifndef __BGDC__
extern DLVARFIXUP __bgdexport( libscroll, locals_fixup )[];
extern DLVARFIXUP __bgdexport( libscroll, globals_fixup )[];
#endif

/* --------------------------------------------------------------------------- */

DLCONSTANT __bgdexport( libscroll, constants_def )[] =
{
    { "C_SCROLL",   TYPE_DWORD,     C_SCROLL    },

    { "C_0",        TYPE_DWORD,     0x0001      },
    { "C_1",        TYPE_DWORD,     0x0002      },
    { "C_2",        TYPE_DWORD,     0x0004      },
    { "C_3",        TYPE_DWORD,     0x0008      },
    { "C_4",        TYPE_DWORD,     0x0010      },
    { "C_5",        TYPE_DWORD,     0x0020      },
    { "C_6",        TYPE_DWORD,     0x0040      },
    { "C_7",        TYPE_DWORD,     0x0080      },
    { "C_8",        TYPE_DWORD,     0x0100      },
    { "C_9",        TYPE_DWORD,     0x0200      },

    { NULL,         0,              0           }
};

/* --------------------------------------------------------------------------- */

char __bgdexport( libscroll, locals_def )[] =
    "ctype;\n"
    "cnumber;\n";

/* --------------------------------------------------------------------------- */

char __bgdexport( libscroll, globals_def )[] =
    "STRUCT scroll[9]\n"
    "x0, y0;\n"
    "x1, y1;\n"
    "z = 512;\n"
    "camera;\n"
    "ratio = 200;\n"
    "speed;\n"
    "region1 = -1;\n"
    "region2 = -1;\n"
    "flags1;\n"
    "flags2;\n"
    "follow = -1;\n"
    "reserved[6];\n"  /* size: 20 dwords */
    "END \n";

/* --------------------------------------------------------------------------- */

char * __bgdexport( libscroll, modules_dependency )[] =
{
    "libgrbase",
    "libblit",
    "librender",
    "libvideo",
    NULL
};

#endif
