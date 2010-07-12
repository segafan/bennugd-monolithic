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

#ifndef __MODCD_SYMBOLS_H
#define __MODCD_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern DLVARFIXUP  __bgdexport( mod_cd, globals_fixup )[];
extern void  __bgdexport( mod_cd, module_initialize )();
extern void  __bgdexport( mod_cd, module_finalize )();

extern CONDITIONALLY_STATIC int modcd_drives( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_status( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_name( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_getinfo( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_play( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_playtracks( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_eject( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_pause( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_resume( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modcd_stop( INSTANCE * my, int * params );
#endif

/* ----------------------------------------------------------------- */
/* Definicion de constantes (usada en tiempo de compilacion)         */
DLCONSTANT  __bgdexport( mod_cd, constants_def )[] =
{
    { "CD_TRAYEMPTY", TYPE_INT, 0  },
    { "CD_STOPPED"  , TYPE_INT, 1  },
    { "CD_PLAYING"  , TYPE_INT, 2  },
    { "CD_PAUSED"   , TYPE_INT, 3  },
    { "CD_ERROR"    , TYPE_INT, -1 },
    { NULL          , 0       , 0  }
} ;

/* ----------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion) */
char __bgdexport( mod_cd, globals_def )[] =
"STRUCT cdinfo\n"
" current_track;\n"
" current_frame;\n"
" tracks;\n"
" minute;\n"
" second;\n"
" subframe;\n"
" minutes;\n"
" seconds;\n"
" subframes;\n"
" STRUCT track[99]\n"
"  audio;\n"
"  minutes;\n"
"  seconds;\n"
"  subframes;\n"
" END;\n"
"END;\n" ;

/* --------------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_cd, functions_exports )[] =
{
    /* Funciones de manejo de CD */
    { "CD_DRIVES"   , ""      , TYPE_INT    , SYSMACRO(modcd_drives)     },
    { "CD_STATUS"   , "I"     , TYPE_INT    , SYSMACRO(modcd_status)     },
    { "CD_NAME"     , "I"     , TYPE_STRING , SYSMACRO(modcd_name)       },
    { "CD_GETINFO"  , "I"     , TYPE_INT    , SYSMACRO(modcd_getinfo)    },
    { "CD_PLAY"     , "II"    , TYPE_INT    , SYSMACRO(modcd_play)       },
    { "CD_PLAY"     , "III"   , TYPE_INT    , SYSMACRO(modcd_playtracks) },
    { "CD_STOP"     , "I"     , TYPE_INT    , SYSMACRO(modcd_stop)       },
    { "CD_PAUSE"    , "I"     , TYPE_INT    , SYSMACRO(modcd_pause)      },
    { "CD_RESUME"   , "I"     , TYPE_INT    , SYSMACRO(modcd_resume)     },
    { "CD_EJECT"    , "I"     , TYPE_INT    , SYSMACRO(modcd_eject)      },
    { 0             , 0       , 0           , 0                }
};

#endif
