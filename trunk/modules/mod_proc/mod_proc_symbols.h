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

#ifndef __MODPROC_SYMBOLS_H
#define __MODPROC_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
#define ALL_PROCESS         0
#define S_KILL              0
#define S_WAKEUP            1
#define S_SLEEP             2
#define S_FREEZE            3
#define S_FORCE             50
#define S_TREE              100
#define S_KILL_TREE         (S_TREE + S_KILL  )
#define S_WAKEUP_TREE       (S_TREE + S_WAKEUP)
#define S_SLEEP_TREE        (S_TREE + S_SLEEP )
#define S_FREEZE_TREE       (S_TREE + S_FREEZE)
#define S_KILL_FORCE        (S_FORCE + S_KILL  )
#define S_WAKEUP_FORCE      (S_FORCE + S_WAKEUP)
#define S_SLEEP_FORCE       (S_FORCE + S_SLEEP )
#define S_FREEZE_FORCE      (S_FORCE + S_FREEZE)
#define S_KILL_TREE_FORCE   (S_FORCE + S_KILL_TREE  )
#define S_WAKEUP_TREE_FORCE (S_FORCE + S_WAKEUP_TREE)
#define S_SLEEP_TREE_FORCE  (S_FORCE + S_SLEEP_TREE )
#define S_FREEZE_TREE_FORCE (S_FORCE + S_FREEZE_TREE)
#define S_DFL               0
#define S_IGN               1

DLCONSTANT __bgdexport( mod_proc, constants_def )[] =
{
    { "S_KILL"              , TYPE_INT, S_KILL              },
    { "S_WAKEUP"            , TYPE_INT, S_WAKEUP            },
    { "S_SLEEP"             , TYPE_INT, S_SLEEP             },
    { "S_FREEZE"            , TYPE_INT, S_FREEZE            },
    { "S_FORCE"             , TYPE_INT, S_FORCE             },
    { "S_TREE"              , TYPE_INT, S_TREE              },
    { "S_KILL_TREE"         , TYPE_INT, S_KILL_TREE         },
    { "S_WAKEUP_TREE"       , TYPE_INT, S_WAKEUP_TREE       },
    { "S_SLEEP_TREE"        , TYPE_INT, S_SLEEP_TREE        },
    { "S_FREEZE_TREE"       , TYPE_INT, S_FREEZE_TREE       },
    { "S_KILL_FORCE"        , TYPE_INT, S_KILL_FORCE        },
    { "S_WAKEUP_FORCE"      , TYPE_INT, S_WAKEUP_FORCE      },
    { "S_SLEEP_FORCE"       , TYPE_INT, S_SLEEP_FORCE       },
    { "S_FREEZE_FORCE"      , TYPE_INT, S_FREEZE_FORCE      },
    { "S_KILL_TREE_FORCE"   , TYPE_INT, S_KILL_TREE_FORCE   },
    { "S_WAKEUP_TREE_FORCE" , TYPE_INT, S_WAKEUP_TREE_FORCE },
    { "S_SLEEP_TREE_FORCE"  , TYPE_INT, S_SLEEP_TREE_FORCE  },
    { "S_FREEZE_TREE_FORCE" , TYPE_INT, S_FREEZE_TREE_FORCE },
    { "S_DFL"               , TYPE_INT, S_DFL               },
    { "S_IGN"               , TYPE_INT, S_IGN               },
    { "ALL_PROCESS"         , TYPE_INT, ALL_PROCESS         },
    { NULL                  , 0       , 0                   }
} ;

char __bgdexport( mod_proc, locals_def )[] =
    "STRUCT mod_proc_reserved\n"
    "   int type_scan;\n"
    "   int id_scan;\n"
    "   int context;\n"
    "   dword signal_action;\n"
    "END\n";

DLSYSFUNCS __bgdexport( mod_proc, functions_exports )[] =
{
    /* Interacción entre procesos */
    { "GET_ID"          , "I"   , TYPE_INT , 0 },
    { "GET_STATUS"      , "I"   , TYPE_INT , 0 },
    { "SIGNAL"          , "II"  , TYPE_INT , 0 },
    { "SIGNAL_ACTION"   , "II"  , TYPE_INT , 0 },
    { "SIGNAL_ACTION"   , "III" , TYPE_INT , 0 },
    { "LET_ME_ALONE"    , ""    , TYPE_INT , 0 },
    { "EXIT"            , "SI"  , TYPE_INT , 0 },
    { "EXIT"            , "S"   , TYPE_INT , 0 },
    { "EXIT"            , ""    , TYPE_INT , 0 },
    { "EXISTS"          , "I"   , TYPE_INT , 0 },
    { 0                 , 0     , 0        , 0 }
};
#else
extern DLCONSTANT __bgdexport( mod_proc, constants_def )[];
extern char __bgdexport( mod_proc, locals_def )[];
extern DLVARFIXUP __bgdexport( mod_proc, locals_fixup )[];
extern void __bgdexport( mod_proc, process_exec_hook )( INSTANCE * r );
extern DLSYSFUNCS __bgdexport( mod_proc, functions_exports )[];
#endif

#endif
