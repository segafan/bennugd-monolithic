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

#ifndef __MODEFFECTS_SYMBOLS_H
#define __MODEFFECTS_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
#define BLUR_NORMAL     0
#define BLUR_3x3        1
#define BLUR_5x5        2
#define BLUR_5x5_MAP    3
#define GSCALE_RGB      0
#define GSCALE_R        1
#define GSCALE_G        2
#define GSCALE_B        3
#define GSCALE_RG       4
#define GSCALE_RB       5
#define GSCALE_GB       6
#define GSCALE_OFF     -1

DLCONSTANT __bgdexport( mod_effects, constants_def )[] =
{
    { "BLUR_NORMAL" , TYPE_INT, BLUR_NORMAL     },
    { "BLUR_3x3"    , TYPE_INT, BLUR_3x3        },
    { "BLUR_5x5"    , TYPE_INT, BLUR_5x5        },
    { "BLUR_5x5_MAP", TYPE_INT, BLUR_5x5_MAP    },

    { "GSCALE_RGB"  , TYPE_INT, GSCALE_RGB      },
    { "GSCALE_R"    , TYPE_INT, GSCALE_R        },
    { "GSCALE_G"    , TYPE_INT, GSCALE_G        },
    { "GSCALE_B"    , TYPE_INT, GSCALE_B        },
    { "GSCALE_RG"   , TYPE_INT, GSCALE_RG       },
    { "GSCALE_RB"   , TYPE_INT, GSCALE_RB       },
    { "GSCALE_GB"   , TYPE_INT, GSCALE_GB       },
    { "GSCALE_OFF"  , TYPE_INT, GSCALE_OFF      },

    { NULL          , 0       , 0               }
} ;

DLSYSFUNCS  __bgdexport( mod_effects, functions_exports )[] =
{
    { "GRAYSCALE"   , "IIB"   , TYPE_INT    , 0 },
    { "RGBSCALE"    , "IIFFF" , TYPE_INT    , 0 },
    { "BLUR"        , "IIB"   , TYPE_INT    , 0 },
    { "FILTER"      , "IIP"   , TYPE_INT    , 0 },
    { NULL          , NULL    , 0           , NULL }
};

char * __bgdexport( mod_effects, modules_dependency )[] =
{
    "libgrbase",
    NULL
};
#else
extern DLCONSTANT __bgdexport( mod_effects, constants_def )[];
extern DLSYSFUNCS  __bgdexport( mod_effects, functions_exports )[];
extern char __bgdexport( mod_effects, modules_dependency )[];
#endif

#endif
