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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FAKE
#include <SDL.h>
#endif

#include "bgddl.h"

/* ---------------------------------------------------------------------- */

static int modsensor_say( INSTANCE * my, int * params )
{
#ifndef FAKE
    /* Show debugging info also in stdout */
    SDL_Log( "%s\n", string_get( params[0] ) );
#endif
    fflush( stdout );
    string_discard( params[0] ) ;
    return 1 ;
}

/* ---------------------------------------------------------------------- */

static int modsensor_say_fast( INSTANCE * my, int * params )
{
#ifndef FAKE
    /* Show debugging info also in stdout */
    SDL_Log( "%s\n", string_get( params[0] ) );
#endif
    string_discard( params[0] ) ;
    return 1 ;
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_sensor, functions_exports )[] =
{
    { "SSAY"     , "S", TYPE_UNDEFINED, modsensor_say     },
    { "SSAY_FAST", "S", TYPE_UNDEFINED, modsensor_say_fast},
    { 0         , 0  , 0             , 0              }
};

/* --------------------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_initialize )()
{
#ifndef FAKE
    int n;

    if ( !SDL_WasInit( SDL_INIT_SENSOR ) )
    {
        SDL_InitSubSystem( SDL_INIT_SENSOR );
    }

    n = SDL_NumSensors();
    SDL_Log("I found %d sensors in your system", n);
    /* Open all joysticks
    if (( _max_joys = SDL_NumJoysticks() ) > MAX_JOYS )
    {
        printf( "[JOY] Warning: maximum number of joysticks exceeded (%i>%i)", _max_joys, MAX_JOYS );
        _max_joys = MAX_JOYS;
    }

    for ( i = 0; i < _max_joys; i++ )
    {
        _joysticks[i] = SDL_JoystickOpen( i ) ;
        if ( !_joysticks[ i ] ) printf( "[JOY] Failed to open joystick '%i'", i );
    }

    SDL_JoystickUpdate() ;*/
#endif
}

/* ----------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_finalize )()
{
#ifndef FAKE
    if ( SDL_WasInit( SDL_INIT_SENSOR ) ) SDL_QuitSubSystem( SDL_INIT_SENSOR );
#endif
}
