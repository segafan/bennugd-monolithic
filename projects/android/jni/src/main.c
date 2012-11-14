/*
 *  Copyright © 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright © 2002-2006 Fenix Team (Fenix)
 *  Copyright © 1999-2002 José Luis Cebrián Pagüe (Fenix)
 *
 *  This file is part of Bennu - Game Development
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */

/*
 * INCLUDES
 */

#ifdef _WIN32
#define  _WIN32_WINNT 0x0500
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bgdi.h"
#include "bgdrtm.h"
#include "xstrings.h"
#include "dirs.h"

#if defined(TARGET_IOS) || defined(TARGET_ANDROID)
#include <SDL.h>
#elif defined(TARGET_WII)
#include <SDL.h>
#include <fat.h>
#endif

/* ---------------------------------------------------------------------- */

static char * dcb_exts[] = { ".dcb", ".dat", ".bin", NULL };

static int standalone  = 0;  /* 1 only if this is an standalone interpreter   */
static int embedded    = 0;  /* 1 only if this is a stub with an embedded DCB */

/* ---------------------------------------------------------------------- */

/*
 *  FUNCTION : main
 *
 *  Main function
 *
 *  PARAMS:
 *      INT n: ERROR LEVEL to return to OS
 *
 *  RETURN VALUE:
 *      No value
 *
 */

int main( int argc, char *argv[] )
{
    char * filename = NULL, dcbname[ __MAX_PATH ], *ptr, *arg0, *ext ;
    int i, j, ret = -1;
    file * fp = NULL;
    INSTANCE * mainproc_running;
    dcb_signature dcb_signature;

    SDL_Log("BennuGD Init");

    /* get my executable name */

    arg0 = strdup( argv[0] );

    ptr = arg0 + strlen( arg0 );
    while ( ptr > arg0 && ptr[-1] != '\\' && ptr[-1] != '/' ) ptr-- ;

    appexename = strdup( ptr );

    /* get executable full pathname  */
    fp = NULL;
    appexefullpath = getfullpath( arg0 );
    if ( ( !strchr( arg0, '\\' ) && !strchr( arg0, '/' ) ) )
    {
        struct stat st;
        if ( stat( appexefullpath, &st ) || !S_ISREG( st.st_mode ) )
        {
            char *p = whereis( appexename );
            if ( p )
            {
                char * tmp = calloc( 1, strlen( p ) + strlen( appexename ) + 2 );
                free( appexefullpath );
                sprintf( tmp, "%s/%s", p, appexename );
                appexefullpath = getfullpath( tmp );
                free( tmp );
            }
        }
    }

    /* get pathname of executable */
    ptr = strstr( appexefullpath, appexename );
    appexepath = calloc( 1, ptr - appexefullpath + 1 );
    strncpy( appexepath, appexefullpath, ptr - appexefullpath );

    standalone = ( strncmpi( appexename, "bgdi", 4 ) == 0 ) ;

    /* add binary path */
    file_addp( appexepath );


    if(file_exists("main.dcb")) {
        filename = "main.dcb";
        debug = 4;
        SDL_Log("%s: main.dcb exists in APK\n", appexename);
    }
    else
    {
        SDL_Log("main.dcb not found in APK, quitting\n");
        return -1 ;
    }

    /* Initialization (modules needed before dcb_load) */

    string_init() ;
    init_c_type() ;

    /* Init application title for windowed modes */

    strcpy( dcbname, filename ) ;

    ptr = filename + strlen( filename );
    while ( ptr > filename && ptr[-1] != '\\' && ptr[-1] != '/' ) ptr-- ;

    appname = strdup( ptr ) ;
    if ( strlen( appname ) > 3 )
    {
        char ** dcbext = dcb_exts, *ext = &appname[ strlen( appname ) - 4 ];
        while ( dcbext && *dcbext )
        {
            if ( !strncmpi( ext, *dcbext, 4 ) )
            {
                *ext = '\0';
                break;
            }
            dcbext++;
        }
    }

#ifdef __DEBUG__
printf( "appname        %s\n", appname);
printf( "appexename     %s\n", appexename);
printf( "appexepath     %s\n", appexepath);
printf( "appexefullpath %s\n", appexefullpath);
printf( "dcbname        %s\n", dcbname);
fflush(stdout);
#endif

    if ( !embedded )
    {
        /* First try to load directly (we expect myfile.dcb) */
        if ( !dcb_load( dcbname ) )
        {
            char ** dcbext = dcb_exts;
            int dcbloaded = 0;

            while ( dcbext && *dcbext )
            {
                strcpy( dcbname, appname ) ;
                strcat( dcbname, *dcbext ) ;
                if (( dcbloaded = dcb_load( dcbname ) ) ) break;
                dcbext++;
            }

            if ( !dcbloaded )
            {
                SDL_Log( "%s: doesn't exist or isn't version %d DCB compatible\n", filename, DCB_VERSION >> 8 ) ;
                return -1 ;
            }
        }
    }
    else
    {
        dcb_load_from( fp, dcbname, dcb_signature.dcb_offset );
    }

    /* If the dcb is not in debug mode */

    if ( dcb.data.NSourceFiles == 0 ) debug = 0;

    /* Initialization (modules needed after dcb_load) */

    sysproc_init() ;

    argv[0] = filename;
    bgdrtm_entry( argc, argv );

    if ( mainproc )
    {
        mainproc_running = instance_new( mainproc, NULL ) ;
        ret = instance_go_all() ;
    }

    SDL_Log("bgdrtm_exit");
    bgdrtm_exit( ret );

    free( appexename        );
    free( appexepath        );
    free( appexefullpath    );
    free( appname           );
    SDL_Log("Done");
    return ret;
}

