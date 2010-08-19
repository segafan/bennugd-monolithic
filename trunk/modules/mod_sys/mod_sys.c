/*
 *  Copyright � 2006-2010 SplinterGU (Fenix/Bennugd)
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bgddl.h"
#include "files.h"
#include "xstrings.h"
#include "mod_sys_defines.h"

#include <unistd.h>

#ifndef WIN32
#include <sys/wait.h>
#else
#include <process.h>
#endif

#ifndef __MONOLITHIC__
#include "mod_sys_symbols.h"
#endif

/* ---------------------------------------------------------------------- */

CONDITIONALLY_STATIC int modsys_exec( INSTANCE * my, int * params )
{
#if defined TARGET_WII || defined TARGET_PSP
	#warning NOT IMPLEMENTED FOR PSP or WII!
	return 0;
#else
    int mode = params[0];
    char * filename = ( char * ) string_get( params[1] );
    int argc = params[2];
    char ** argv;
    int n = 0;
#ifndef WIN32
    pid_t child;
#endif
    int status = -1;

    // fill argv
    argv = ( char ** ) calloc( argc + 2, sizeof( char * ) );
    argv[0] = filename;
    for ( n = 0; n < argc; n++ )
        argv[n + 1] = ( char * ) string_get((( int * )( params[3] ) )[n] );

    // Execute program
#ifdef WIN32
    status = spawnvp( mode, filename, ( const char ** )argv );
#else
    if (( child = fork() ) == -1 )
    {
        //Error
        status = -1 ;
    }
    else if ( child == 0 )
    {
        execvp( filename, ( const char ** )argv );
        exit(-1);
    }
    else
    {
        /* father */
        switch ( mode )
        {
            case _P_WAIT:
                if ( waitpid( child, &status, WUNTRACED ) != child )
                    status = -1;
                else
                    status = (int)(char)WEXITSTATUS(status);
                break;

            case _P_NOWAIT:
                status = child;
                break;
        }
    }
#endif

    // Free resources
    string_discard( params[1] );
    if ( argv ) free( argv );

    return ( status ) ;
#endif //TARGET_WII
}

/* ---------------------------------------------------------------------- */

CONDITIONALLY_STATIC int modsys_getenv( INSTANCE * my, int * params )
{
    char *e ;
    int str ;

    if (( e = getenv( string_get( params[0] ) ) ) )
    {
        str = string_new( e ) ;
    }
    else
    {
        str = string_new( "" ) ;
    }

    string_discard( params[0] ) ;
    string_use( str ) ;
    return str ;
}

/* ----------------------------------------------------------------- */
