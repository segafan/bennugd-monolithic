/*
 *  Copyright � 2006-2010 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
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

#include <stdlib.h>
#include <stdio.h>

#include "bgdrtm.h"

#include "bgddl.h"
#include "dlvaracc.h"
#include "instance.h"

#include "xstrings.h"

#ifndef __MONOLITHIC__
#include "mod_proc_symbols.h"
#endif

/* ----------------------------------------------------------------- */

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

#define SMASK_KILL          0x0001
#define SMASK_WAKEUP        0x0002
#define SMASK_SLEEP         0x0004
#define SMASK_FREEZE        0x0008
#define SMASK_KILL_TREE     0x0100
#define SMASK_WAKEUP_TREE   0x0200
#define SMASK_SLEEP_TREE    0x0400
#define SMASK_FREEZE_TREE   0x0800

/* ----------------------------------------------------------------- */

enum
{
    PROCESS_ID = 0,
    PROCESS_TYPE,
    STATUS,
    ID_SCAN,
    TYPE_SCAN,
    CONTEXT,
    SIGNAL_ACTION
} ;

/* ----------------------------------------------------------------- */
/* Son las variables que se desea acceder.                           */
/* El interprete completa esta estructura, si la variable existe.    */
/* (usada en tiempo de ejecucion)                                    */
DLVARFIXUP __bgdexport( mod_proc, locals_fixup )[]  =
{
    /* Nombre de variable local, offset al dato, tama�o del elemento, cantidad de elementos */
    { "id", NULL, -1, -1 },
    { "reserved.process_type", NULL, -1, -1 },
    { "reserved.status", NULL, -1, -1 },
    { "mod_proc_reserved.id_scan", NULL, -1, -1 },
    { "mod_proc_reserved.type_scan", NULL, -1, -1 },
    { "mod_proc_reserved.context", NULL, -1, -1 },
    { "mod_proc_reserved.signal_action", NULL, -1, -1 },
    { NULL, NULL, -1, -1 }
};

/* ----------------------------------------------------------------- */

void __bgdexport( mod_proc, process_exec_hook )( INSTANCE * r )
{
    LOCDWORD( mod_proc, r, TYPE_SCAN ) = 0;
    LOCDWORD( mod_proc, r, ID_SCAN ) = 0;
    LOCDWORD( mod_proc, r, CONTEXT ) = 0;
}

/* ----------------------------------------------------------------- */
/* Interacci�n entre procesos */

static void _modproc_kill_all()
{
    INSTANCE * i = first_instance ;
    while ( i )
    {
        LOCDWORD( mod_proc, i, STATUS ) = STATUS_KILLED ;
        i = i->next ;
    }
}

/* --------------------------------------------------------------------------- */
/** EXIT ()
 *  Leaves the program at next frame
 */

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_exit_0( INSTANCE * my, int * params )
{
    exit_value = 0;
    must_exit = 1 ;

    return 1 ;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_exit_1( INSTANCE * my, int * params )
{
    printf( string_get( params[0] ) );
    printf( "\n" );
    fflush( stdout );
    string_discard( params[0] );

    exit_value = 0;
    must_exit = 1 ;

    return 1 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_exit( INSTANCE * my, int * params )
{
    _modproc_kill_all();

    printf( string_get( params[0] ) );
    printf( "\n" );
    fflush( stdout );
    string_discard( params[0] );

    exit_value = params[1];
    must_exit = 1 ;

    return 1 ;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_running( INSTANCE * my, int * params )
{
    INSTANCE * i, * ctx;

    if ( params[0] == 0 ) return 0;

    if ( params[0] >= FIRST_INSTANCE_ID )
    {
        i = instance_get( params[0] ) ;
        if ( i && ( LOCDWORD( mod_proc, i, STATUS ) & ~STATUS_WAITING_MASK ) >= STATUS_RUNNING ) return 1;
        return 0;
    }

    ctx = NULL;
    while ( ( i = instance_get_by_type( params[0], &ctx ) ) )
    {
        if ( ( LOCDWORD( mod_proc, i, STATUS ) & ~STATUS_WAITING_MASK ) >= STATUS_RUNNING ) return 1;
    }

    return 0;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_signal( INSTANCE * my, int * params )
{
    INSTANCE * i, * ctx;
    int fake_params[2] ;

    if ( params[0] == ALL_PROCESS )
    {
        /* Signal all process but my */
        fake_params[1] = ( params[1] >= S_TREE ) ? params[1] - S_TREE : params[1] ;
        i = first_instance ;
        while ( i )
        {
            if ( LOCDWORD( mod_proc, i, PROCESS_ID ) != LOCDWORD( mod_proc, my, PROCESS_ID ) )
            {
                fake_params[0] = LOCDWORD( mod_proc, i, PROCESS_ID ) ;
                modproc_signal( my, fake_params ) ;
            }
            i = i->next ;
        }
        return 0 ;
    }
    else if ( params[0] < FIRST_INSTANCE_ID )
    {
        /* Signal by type */
        fake_params[1] = params[1] ;

        ctx = NULL;
        while ( ( i = instance_get_by_type( params[0], &ctx ) ) )
        {
            fake_params[0] = LOCDWORD( mod_proc, i, PROCESS_ID ) ;
            modproc_signal( my, fake_params ) ;
        }
        return 0 ;
    }

    i = instance_get( params[0] ) ;
    if ( i )
    {
        if (( LOCDWORD( mod_proc, i, STATUS ) & ~STATUS_WAITING_MASK ) != STATUS_DEAD )
        {
            switch ( params[1] )
            {
                case S_KILL:
                case S_KILL_FORCE:
                    if ( params[1] == S_KILL_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_KILL ) )
                        LOCDWORD( mod_proc, i, STATUS ) = STATUS_KILLED ;
                    break ;

                case S_WAKEUP:
                case S_WAKEUP_FORCE:
                    if ( params[1] == S_WAKEUP_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_WAKEUP ) )
                        LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_RUNNING ;
                    break ;

                case S_SLEEP:
                case S_SLEEP_FORCE:
                    if ( params[1] == S_SLEEP_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_SLEEP ) )
                        LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_SLEEPING ;
                    break ;

                case S_FREEZE:
                case S_FREEZE_FORCE:
                    if ( params[1] == S_FREEZE_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_FREEZE ) )
                        LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_FROZEN ;
                    break ;

                case S_KILL_TREE:
                case S_KILL_TREE_FORCE:
                    if ( params[1] == S_KILL_TREE_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_KILL_TREE ) )
                        LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_KILLED ;
                    break ;

                case S_WAKEUP_TREE:
                case S_WAKEUP_TREE_FORCE:
                    if ( params[1] == S_WAKEUP_TREE_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_WAKEUP_TREE ) )
                        LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_RUNNING ;
                    break ;

                case S_SLEEP_TREE:
                case S_SLEEP_TREE_FORCE:
                    if ( params[1] == S_SLEEP_TREE_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_SLEEP_TREE ) )
                        LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_SLEEPING ;
                    break ;

                case S_FREEZE_TREE:
                case S_FREEZE_TREE_FORCE:
                    if ( params[1] == S_FREEZE_TREE_FORCE || !( LOCDWORD( mod_proc, i, SIGNAL_ACTION ) & SMASK_FREEZE_TREE ) )
                        LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_FROZEN ;
                    break ;

                default:
                    return 1 ;
            }
        }

        if ( params[1] >= S_TREE )
        {
            fake_params[1] = params[1] ;
            i = instance_getson( i ) ;
            while ( i )
            {
                fake_params[0] = LOCDWORD( mod_proc, i, PROCESS_ID ) ;
                modproc_signal( my, fake_params ) ;
                i = instance_getbigbro( i )  ;
            }
        }
    }
    return 1 ;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_signal_action( INSTANCE * my, int * params )
{
    int action = params[1];

    if ( my )
    {
        switch ( params[0] )
        {
            case S_KILL:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_KILL;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_KILL;
                        break;
                }
                break ;

            case S_WAKEUP:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_WAKEUP;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_WAKEUP;
                        break;
                }
                break ;

            case S_SLEEP:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_SLEEP;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_SLEEP;
                        break;
                }
                break ;

            case S_FREEZE:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_FREEZE;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_FREEZE;
                        break;
                }
                break ;

            case S_KILL_TREE:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_KILL_TREE;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_KILL_TREE;
                        break;
                }
                break ;

            case S_WAKEUP_TREE:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_WAKEUP_TREE;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_WAKEUP_TREE;
                        break;
                }
                break ;

            case S_SLEEP_TREE:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_SLEEP_TREE;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_SLEEP_TREE;
                        break;
                }
                break ;

            case S_FREEZE_TREE:
                switch ( action )
                {
                    case S_IGN:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) |=  SMASK_FREEZE_TREE;
                        break;

                    case S_DFL:
                        LOCDWORD( mod_proc, my, SIGNAL_ACTION ) &= ~SMASK_FREEZE_TREE;
                        break;
                }
                break ;
        }
    }
    return 1 ;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_signal_action3( INSTANCE * my, int * params )
{
    INSTANCE * i, * ctx ;

    if ( params[0] == ALL_PROCESS )
    {
        i = first_instance ;
        while ( i )
        {
            modproc_signal_action( i, &params[1] ) ;
            i = i->next ;
        }
        return 0 ;
    }
    else if ( params[0] < FIRST_INSTANCE_ID )
    {
        ctx = NULL;
        while ( ( i = instance_get_by_type( params[0], &ctx ) ) )
        {
            modproc_signal_action( i, &params[1] ) ;
        }
        return 0 ;
    }

    i = instance_get( params[0] ) ;
    if ( i ) modproc_signal_action( i, &params[1] ) ;

    return 1;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_let_me_alone( INSTANCE * my, int * params )
{
    INSTANCE * i = first_instance ;

    while ( i )
    {
        if ( i != my && ( LOCDWORD( mod_proc, i, STATUS ) & ~STATUS_WAITING_MASK ) != STATUS_DEAD )
            LOCDWORD( mod_proc, i, STATUS ) = ( LOCDWORD( mod_proc, i, STATUS ) & STATUS_WAITING_MASK ) | STATUS_KILLED ;
        i = i->next ;
    }
    if ( LOCDWORD( mod_proc, my, STATUS ) > STATUS_KILLED ) LOCDWORD( mod_proc, my, STATUS ) = STATUS_RUNNING;
    return 1 ;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_get_id( INSTANCE * my, int * params )
{
    INSTANCE * ptr = first_instance, ** ctx ;

    if ( !params[0] )
    {
        LOCDWORD( mod_proc, my, TYPE_SCAN ) = 0 ;
        if ( LOCDWORD( mod_proc, my, ID_SCAN ) )
        {
            ptr = instance_get( LOCDWORD( mod_proc, my, ID_SCAN ) ) ;
            if ( ptr ) ptr = ptr->next ;
        }

        while ( ptr )
        {
            if (( LOCDWORD( mod_proc, ptr, STATUS ) & ~STATUS_WAITING_MASK ) >= STATUS_RUNNING )
            {
                LOCDWORD( mod_proc, my, ID_SCAN ) = LOCDWORD( mod_proc, ptr, PROCESS_ID ) ;
                return LOCDWORD( mod_proc, ptr, PROCESS_ID ) ;
            }
            ptr = ptr->next ;
        }
        return 0 ;
    }

    LOCDWORD( mod_proc, my, ID_SCAN ) = 0 ;
    /* Check if already in scan by type and we reach limit */
    ctx = ( INSTANCE ** ) LOCADDR( mod_proc, my, CONTEXT );
/*
    if ( !*ctx && LOCDWORD( mod_proc, my, TYPE_SCAN ) )
    {
        LOCDWORD( mod_proc, my, TYPE_SCAN ) = 0;
        return 0;
    }
*/
    /* Check if type change from last call */
    if ( LOCDWORD( mod_proc, my, TYPE_SCAN ) != params[0] )
    {
        *ctx = NULL;
        LOCDWORD( mod_proc, my, TYPE_SCAN ) = params[0];
    }

    while ( ( ptr = instance_get_by_type( params[0], ctx ) ) )
    {
        if ( /*ptr != my &&*/ ( LOCDWORD( mod_proc, ptr, STATUS ) & ~STATUS_WAITING_MASK ) >= STATUS_RUNNING )
        {
            return LOCDWORD( mod_proc, ptr, PROCESS_ID ) ;
        }
    }

    return 0 ;
}

/* ----------------------------------------------------------------- */

CONDITIONALLY_STATIC int modproc_get_status( INSTANCE * my, int * params )
{
    INSTANCE * i ;
    if ( !params[0] || !( i = instance_get( params[0] ) ) ) return 0;
    return LOCDWORD( mod_proc, i, STATUS ) ;
}

/* ----------------------------------------------------------------- */
