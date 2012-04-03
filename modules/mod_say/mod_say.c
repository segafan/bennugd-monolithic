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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bgddl.h"
#include "xstrings.h"

#ifndef __MONOLITHIC__
#include "mod_say_symbols.h"
#endif

#ifdef TARGET_PSP
	#include <pspkernel.h>
	#include <pspdebug.h>
#endif


/* ---------------------------------------------------------------------- */

CONDITIONALLY_STATIC int modsay_say( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
	FILE *fd = fopen("stdout.txt", "a");

	fprintf(fd, "%s\n", string_get( params[0] ));
	fflush( fd );
	string_discard( params[0] ) ;
	fclose( fd );
#else 
	#ifdef TARGET_PSP
	fprintf(stderr, "running SAY...\n");
	pspDebugScreenPrintf( "%s\n", string_get( params[0] ) );
	fflush(stdout);
	string_discard( params[0] );
	#else
    /* Show debugging info also in stdout */
    printf( "%s\n", string_get( params[0] ) );
    fflush( stdout );
    string_discard( params[0] ) ;
	#endif
#endif
    return 1 ;
}

/* ---------------------------------------------------------------------- */

CONDITIONALLY_STATIC int modsay_say_fast( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
	FILE *fd = fopen("stdout.txt", "a");

	fprintf(fd, "%s\n", string_get( params[0] ));
	string_discard( params[0] ) ;
	fclose( fd );
#else
    /* Show debugging info also in stdout */
    printf( "%s\n", string_get( params[0] ) );
    string_discard( params[0] ) ;
#endif
    return 1 ;
}

/* ----------------------------------------------------------------- */
void  __bgdexport( mod_say, module_initialize )()
{
#ifdef TARGET_WII
    // Delete stdout.txt if it exists (we'll overwrite it)
    FILE *fd;

    if( (fd = fopen("stdout.txt", "a")) != NULL ) {
        fclose(fd);
        unlink("stdout.txt");
    }
#else ifdef TARGET_PSP
	fprintf( stderr, "Initializing mod_say...\n" 	);
	pspDebugScreenSetBackColor(0x00000000);
	pspDebugScreenSetTextColor(0xFFFFFFFF);
	pspDebugScreenInit();
#endif
}
