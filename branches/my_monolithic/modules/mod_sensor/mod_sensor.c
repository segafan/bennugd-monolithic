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
#include "xstrings.h"

#ifndef FAKE
static SDL_Sensor * sensor;
#endif

/* ---------------------------------------------------------------------- */

int modsensor_number( INSTANCE * my, int * params )
{
    int n=0;
#ifndef FAKE
    n = SDL_NumSensors();
#endif
    return n ;
}

void modsensor_log( INSTANCE * my, int * params )
{
#ifndef FAKE
    SDL_SensorUpdate();
#endif
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_sensor, functions_exports )[] =
{
    { "SENSOR_NUMBER", "", TYPE_INT, modsensor_number     },
    { "SENSOR_LOG", "", TYPE_UNDEFINED, modsensor_log     },
    { 0         , 0  , 0             , 0              }
};

/* --------------------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_initialize )()
{
#ifndef FAKE
    int n, i;

    if ( !SDL_WasInit( SDL_INIT_SENSOR ) )
    {
        SDL_InitSubSystem( SDL_INIT_SENSOR );
    }
#endif
}

/* ----------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_finalize )()
{
#ifndef FAKE
    SDL_SensorClose(sensor);
    if ( SDL_WasInit( SDL_INIT_SENSOR ) ) SDL_QuitSubSystem( SDL_INIT_SENSOR );
#endif
}
