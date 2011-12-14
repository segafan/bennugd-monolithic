/*
 *  Copyright © 2006-2011 SplinterGU (Fenix/Bennugd)
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

#include "bgddl.h"

#include <SDL.h>

/* ----------------------------------------------------------------- */
/* Public functions                                                  */

static void dump_new_events()
{
    SDL_Event event;
    /* Remove all pendings events */

    /* We can't return -1, just return 0 (no event) on error */
#if SDL_VERSION_ATLEAST(1,3,0)
    // We'll only discard events that no module knows how to handle here...
    // Otherwise some events seem to get discarded
    SDL_FlushEvents(SDL_SYSWMEVENT, SDL_SYSWMEVENT);
    SDL_FlushEvents(SDL_TEXTEDITING, SDL_TEXTINPUT);
    SDL_FlushEvents(SDL_INPUTMOTION, SDL_LASTEVENT);
#else
    while ( SDL_PeepEvents( &event, 1, SDL_GETEVENT, SDL_ALLEVENTS ) > 0 );
#endif  

    /* Get new events */
    SDL_PumpEvents();
}

/* ----------------------------------------------------------------- */
/* Funciones de inicializacion del modulo/plugin                     */

void __bgdexport( libsdlhandler, module_initialize )()
{
#if SDL_VERSION_ATLEAST(1,3,0)
    // This is different in SDL 1.3
#else
    if ( !SDL_WasInit( SDL_INIT_EVENTTHREAD ) ) SDL_InitSubSystem( SDL_INIT_EVENTTHREAD );
#endif
}

/* ----------------------------------------------------------------- */

void __bgdexport( libsdlhandler, module_finalize )()
{
#if SDL_VERSION_ATLEAST(1,3,0)
    // This is different in SDL 1.3
#else
    if ( SDL_WasInit( SDL_INIT_EVENTTHREAD ) ) SDL_QuitSubSystem( SDL_INIT_EVENTTHREAD );
#endif
}

/* ----------------------------------------------------------------- */

/* Bigest priority first execute
   Lowest priority last execute */

HOOK __bgdexport( libsdlhandler, handler_hooks )[] =
{
    { 5000, dump_new_events                   },
    {    0, NULL                              }
} ;

/* ----------------------------------------------------------------- */
