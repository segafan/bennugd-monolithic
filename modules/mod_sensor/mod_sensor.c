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

/* ---------------------------------------------------------------------- */

static int modsensor_number( INSTANCE * my, int * params )
{
    int n=0;
#ifndef FAKE
    n = SDL_NumSensors();
#endif
    return n ;
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_sensor, functions_exports )[] =
{
    { "SENSOR_NUMBER", "S", TYPE_UNDEFINED, modsensor_number     },
    { 0         , 0  , 0             , 0              }
};

/* --------------------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_initialize )()
{
#ifndef FAKE
    int n, i;
    Uint8 type;
    SDL_Sensor * sensor;

    if ( !SDL_WasInit( SDL_INIT_SENSOR ) )
    {
        SDL_InitSubSystem( SDL_INIT_SENSOR );
    }

    n = SDL_NumSensors();
    SDL_Log("I found %d sensors in your system\nHere they are:", n);
    for(i=0; i<n; i++) {
        sensor = SDL_SensorOpen(i);
        type = SDL_SensorType(sensor);
        SDL_SensorClose(sensor);
        SDL_Log("Sensor %d: '%s' of type: %d", i, SDL_SensorNameForIndex(i), type);
    }
#endif
}

/* ----------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_finalize )()
{
#ifndef FAKE
    if ( SDL_WasInit( SDL_INIT_SENSOR ) ) SDL_QuitSubSystem( SDL_INIT_SENSOR );
#endif
}
