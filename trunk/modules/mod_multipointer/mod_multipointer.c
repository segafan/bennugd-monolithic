/*
 *  Copyright (c) 2011 Joseba García Echebarria. All rights reserved.
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
#include <SDL.h>
#include <bgddl.h>

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2
#error This module needs SDL 1.3, refusing to compile
#endif

int numpointers=0;

/* Process SDL events looking for multitouch-related ones */
void parse_input_events() {
    SDL_Event e;
    SDL_Touch *state;
    
    // Reset the value
    numpointers = 0;
    
    while ( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_FINGERDOWN, SDL_MULTIGESTURE ) > 0 ) {
        switch ( e.type ) {
            case SDL_FINGERDOWN:
                state = SDL_GetTouch(e.tfinger.touchId);
                // Now I should fill a structure with all the touch data
                // But for now I'll just record the number of fingers in the
                // touch device
                numpointers = state->num_fingers;
                break;

            case SDL_FINGERUP:
                // What to do here?
                // Looks like I cannot access the fingers from here
                break;
        }
    }
}

static int modmulti_numpointers() {
    return numpointers;
}

DLSYSFUNCS  __bgdexport( mod_multipointer, functions_exports )[] =
{
    { "MULTI_NUMPOINTERS"     , ""      , TYPE_INT    , modmulti_numpointers    },
};

/* Bigest priority first execute
 Lowest priority last execute
 We need to run before libsdlhandler or otherwise touch events will be
 discarded. */

HOOK __bgdexport( mod_multipointer, handler_hooks )[] =
{
    { 5500, parse_input_events                },
    {    0, NULL                              }
} ;

/* ----------------------------------------------------------------- */

/*
 SDL_FINGERDOWN      = 0x700,
 SDL_FINGERUP,
 SDL_FINGERMOTION,
 SDL_TOUCHBUTTONDOWN,
 SDL_TOUCHBUTTONUP,    
 
 // Gesture events
SDL_DOLLARGESTURE   = 0x800,
SDL_DOLLARRECORD,
SDL_MULTIGESTURE,
*/