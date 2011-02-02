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

#ifndef __VIDEO_SYMBOLS_H
#define __VIDEO_SYMBOLS_H

#include <bgddl.h>
#include "g_video.h"

#ifdef __BGDC__
/* --------------------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion) */

char __bgdexport( libvideo, globals_def )[] =
    "graph_mode = 0;\n"
    "scale_mode = 0;\n"
    "full_screen = 0;\n"
    "scale_resolution = 0;\n"
    "scale_resolution_aspectratio = 0;\n"
    "scale_resolution_orientation = 0;\n"
    ;

/* --------------------------------------------------------------------------- */

char *__bgdexport( libvideo, modules_dependency )[] =
{
    "libgrbase",
    NULL
};

/* --------------------------------------------------------------------------- */

DLCONSTANT  __bgdexport( libvideo, constants_def )[] =
{
    { "M320X200",           TYPE_DWORD, 3200200             },
    { "M320X240",           TYPE_DWORD, 3200240             },
    { "M320X400",           TYPE_DWORD, 3200400             },
    { "M360X240",           TYPE_DWORD, 3600240             },
    { "M376X282",           TYPE_DWORD, 3760282             },
    { "M400X300",           TYPE_DWORD, 4000300             },
    { "M512X384",           TYPE_DWORD, 5120384             },
    { "M640X400",           TYPE_DWORD, 6400400             },
    { "M640X480",           TYPE_DWORD, 6400480             },
    { "M800X600",           TYPE_DWORD, 8000600             },
    { "M1024X768",          TYPE_DWORD, 10240768            },
    { "M1280X1024",         TYPE_DWORD, 12801024            },

    { "MODE_WINDOW",        TYPE_DWORD, MODE_WINDOW         },
    { "MODE_2XSCALE",       TYPE_DWORD, MODE_2XSCALE        },
    { "MODE_FULLSCREEN",    TYPE_DWORD, MODE_FULLSCREEN     },
    { "MODE_DOUBLEBUFFER",  TYPE_DWORD, MODE_DOUBLEBUFFER   },
    { "MODE_HARDWARE",      TYPE_DWORD, MODE_HARDWARE       },

    { "MODE_WAITVSYNC",     TYPE_DWORD, MODE_WAITVSYNC      },
    { "WAITVSYNC",          TYPE_DWORD, MODE_WAITVSYNC      },

    { "DOUBLE_BUFFER",      TYPE_DWORD, MODE_DOUBLEBUFFER   },  /* Obsolete */
    { "HW_SURFACE",         TYPE_DWORD, MODE_HARDWARE       },  /* Obsolete */

    { "MODE_8BITS",         TYPE_DWORD, 8                   },
    { "MODE_16BITS",        TYPE_DWORD, 16                  },
    { "MODE_32BITS",        TYPE_DWORD, 32                  },

    { "MODE_8BPP",          TYPE_DWORD, 8                   },
    { "MODE_16BPP",         TYPE_DWORD, 16                  },
    { "MODE_32BPP",         TYPE_DWORD, 32                  },

    { "MODE_MODAL",         TYPE_DWORD, MODE_MODAL          },  /* GRAB INPU */
    { "MODE_FRAMELESS",     TYPE_DWORD, MODE_FRAMELESS      },  /* FRAMELESS window */

    { "SCALE_NONE",         TYPE_DWORD, SCALE_NONE          },

    { NULL          , 0         ,  0  }
} ;
#else
extern char __bgdexport( libvideo, globals_def )[];
extern char __bgdexport( libvideo, modules_dependency )[];
extern DLCONSTANT  __bgdexport( libvideo, constants_def )[];
extern DLVARFIXUP __bgdexport( libvideo, globals_fixup )[];
extern void __bgdexport( libvideo, module_initialize )();
extern void __bgdexport( libvideo, module_finalize )();
#endif

#endif
