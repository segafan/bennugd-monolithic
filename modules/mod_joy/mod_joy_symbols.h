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

#ifndef __MODJOY_SYMBOLS_H
#define __MODJOY_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modjoy_num( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_name( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_select( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_buttons( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_axes( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_button( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_position( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_hats( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_balls( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_hat( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_ball( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_accel( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_buttons_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_axes_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_button_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_position_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_hats_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_balls_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_hat_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_ball_specific( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modjoy_get_accel_specific( INSTANCE * my, int * params );
#endif

/* ---------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_joy, functions_exports )[] =
{
    { "JOY_AXES"            , ""      , TYPE_INT    , SYSMACRO(modjoy_axes)                  },
    { "JOY_AXES"            , "I"     , TYPE_INT    , SYSMACRO(modjoy_axes_specific)         },
    { "JOY_NUMAXES"         , ""      , TYPE_INT    , SYSMACRO(modjoy_axes)                  },
    { "JOY_NUMAXES"         , "I"     , TYPE_INT    , SYSMACRO(modjoy_axes_specific)         },
    { "JOY_GETAXIS"         , "I"     , TYPE_INT    , SYSMACRO(modjoy_get_position)          },
    { "JOY_GETAXIS"         , "II"    , TYPE_INT    , SYSMACRO(modjoy_get_position_specific) },
	
    { "JOY_BUTTONS"         , ""      , TYPE_INT    , SYSMACRO(modjoy_buttons)               },
    { "JOY_BUTTONS"         , "I"     , TYPE_INT    , SYSMACRO(modjoy_buttons_specific)      },
	
    { "JOY_NAME"            , "I"     , TYPE_STRING , SYSMACRO(modjoy_name)                  },
	
    { "JOY_NUMBUTTONS"      , ""      , TYPE_INT    , SYSMACRO(modjoy_buttons)               },
    { "JOY_NUMBUTTONS"      , "I"     , TYPE_INT    , SYSMACRO(modjoy_buttons_specific)      },
	
    { "JOY_NUMBER"          , ""      , TYPE_INT    , SYSMACRO(modjoy_num)                   },
    { "JOY_NUMJOYSTICKS"    , ""      , TYPE_INT    , SYSMACRO(modjoy_num)                   },
	
    { "JOY_SELECT"          , "I"     , TYPE_INT    , SYSMACRO(modjoy_select)                },
	
    { "JOY_GETBUTTON"       , "I"     , TYPE_INT    , SYSMACRO(modjoy_get_button)            },
    { "JOY_GETBUTTON"       , "II"    , TYPE_INT    , SYSMACRO(modjoy_get_button_specific)   },
    { "JOY_GETPOSITION"     , "I"     , TYPE_INT    , SYSMACRO(modjoy_get_position)          },
    { "JOY_GETPOSITION"     , "II"    , TYPE_INT    , SYSMACRO(modjoy_get_position_specific) },

    { "JOY_NUMHATS"         , ""      , TYPE_INT    , SYSMACRO(modjoy_hats)                  },
    { "JOY_NUMHATS"         , "I"     , TYPE_INT    , SYSMACRO(modjoy_hats_specific)         },   /* Added by Sandman */
    { "JOY_NUMBALLS"        , ""      , TYPE_INT    , SYSMACRO(modjoy_balls)                 },
    { "JOY_NUMBALLS"        , "I"     , TYPE_INT    , SYSMACRO(modjoy_balls_specific)        },   /* Added by Sandman */
    { "JOY_GETHAT"          , "I"     , TYPE_INT    , SYSMACRO(modjoy_get_hat)               },
    { "JOY_GETHAT"          , "II"    , TYPE_INT    , SYSMACRO(modjoy_get_hat_specific)      },   /* Added by Sandman */
    { "JOY_GETBALL"         , "IPP"   , TYPE_INT    , SYSMACRO(modjoy_get_ball)              },
    { "JOY_GETBALL"         , "IIPP"  , TYPE_INT    , SYSMACRO(modjoy_get_ball_specific)     },   /* Added by Sandman */

    { "JOY_GETACCEL"        , "PPP"   , TYPE_INT    , SYSMACRO(modjoy_get_accel)             },
    { "JOY_GETACCEL"        , "IPPP"  , TYPE_INT    , SYSMACRO(modjoy_get_accel_specific)    },
	
    /* Compatibility */
	
    { "NUMBER_JOY"          , ""      , TYPE_INT    , SYSMACRO(modjoy_num)                   },
    { "SELECT_JOY"          , "I"     , TYPE_INT    , SYSMACRO(modjoy_select)                },
    { "GET_JOY_BUTTON"      , "I"     , TYPE_INT    , SYSMACRO(modjoy_get_button)            },
    { "GET_JOY_BUTTON"      , "II"    , TYPE_INT    , SYSMACRO(modjoy_get_button_specific)   },
    { "GET_JOY_POSITION"    , "I"     , TYPE_INT    , SYSMACRO(modjoy_get_position)          },
    { "GET_JOY_POSITION"    , "II"    , TYPE_INT    , SYSMACRO(modjoy_get_position_specific) },
    { 0                     , 0       , 0           , 0                             }
};

/* ----------------------------------------------------------------- */

char * __bgdexport( mod_joy, modules_dependency )[] =
{
    "libjoy",
    NULL
};

/* ----------------------------------------------------------------- */

#endif
