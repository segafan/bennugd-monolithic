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
#include <strings.h>
#include <bgddl.h>
#include <SDL.h>

#ifndef MAX_POINTERS
#   define MAX_POINTERS 10
#endif

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2
#    error This module needs SDL 1.3, refusing to compile
#endif

typedef struct {
    SDL_bool active;
    float x;
    float y;
    float pressure;
    SDL_FingerID fingerid;
} multi_pointer;

multi_pointer pointers[MAX_POINTERS];

int numpointers=0;

/* Return the position of finger in the pointers array, if it's not there,
return the first unused entry.
If there are none available, return -1 */
int get_sdlfinger_index(SDL_FingerID finger) {
    int n=0;

    // First, try to see if the given ID matches any active one
    for(n=0; n<MAX_POINTERS; n++) {
        if(finger == pointers[n].fingerid) {
            return n;
        }
    }
    
    // ID not found, try to find a free spot
    for(n=0; n<MAX_POINTERS; n++) {
        if(pointers[n].active == SDL_FALSE) {
            return n;
        }
    }
    
    // Fail
    return -1;
}

/* Process SDL events looking for multitouch-related ones */
void parse_input_events() {
    int n=0;
    SDL_Event e;
    SDL_Touch *state;

    while ( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_FINGERDOWN, SDL_FINGERMOTION ) > 0 ) {        
        switch ( e.type ) {
            case SDL_FINGERDOWN:
                // Retrive the touch state, the finger id and the position in the array
                state  = SDL_GetTouch(e.tfinger.touchId);
                n      = get_sdlfinger_index(e.tfinger.fingerId);

                // Quit if fingerid not found
                if (n == -1)
                    break;

                // Store the amount of fingers onscreen
                numpointers = state->num_fingers;
                // Store the data about this finger's position
                pointers[n].fingerid = e.tfinger.fingerId;
                pointers[n].active = SDL_TRUE;
                pointers[n].x = (float)e.tfinger.x / state->xres;
                pointers[n].y = (float)e.tfinger.y / state->yres;
                pointers[n].pressure = (float)e.tfinger.pressure / state->pressure_max ;
                break;
            
            case SDL_FINGERMOTION:
                // Retrive the touch state, the finger id and the position in the array
                state  = SDL_GetTouch(e.tfinger.touchId);
                n      = get_sdlfinger_index(e.tfinger.fingerId);
                
                // Quit if fingerid not found
                if (n == -1)
                    break;

                // Update the data about this finger's position
                pointers[n].x = (float)e.tfinger.x / state->xres;
                pointers[n].y = (float)e.tfinger.y / state->yres;
                pointers[n].pressure = (float)e.tfinger.pressure / state->pressure_max ;
                break;

            case SDL_FINGERUP:
                // Retrive the touch state, the finger id and the position in the array
                state  = SDL_GetTouch(e.tfinger.touchId);
                n      = get_sdlfinger_index(e.tfinger.fingerId);

                // Refresh the total number of fingers onscreen
                numpointers = state->num_fingers;
                
                // Quit if fingerid not found
                if (n == -1)
                    break;
                
                // Remove the data about this finger's position
                pointers[n].active = SDL_FALSE;
                pointers[n].x = -1.0;
                pointers[n].y = -1.0;
                pointers[n].pressure = -1.0;
                break;
        }
    }
}

// Return the total number of active pointers
static int modmulti_numpointers(INSTANCE * my, int * params) {
    return numpointers;
}

// Get some info about the given pointer
static float modmulti_info(INSTANCE * my, int * params) {
    const unsigned char *info = (unsigned char *) string_get(params[1]);
    int n=params[0];
    
    // Check for failure
    if (n >= MAX_POINTERS || n < 0)
        return -1.0;

    // Return the info we were asked for
    if(strncasecmp(info, "x", 1)) {
        return pointers[n].x;
    } else if(strncasecmp(info, "y", 1)) {
        return pointers[n].y;
    } else if(strncasecmp(info, "pressure", 8)) {
        return pointers[n].pressure;
    } else if(strncasecmp(info, "active", 6)) {
        if(pointers[n].active == SDL_TRUE)
            return 1.0;
        else
            return 0.0;
    }
    
    string_discard(params[1]);

    return -1.0;
}

/* ----------------------------------------------------------------- */

DLSYSFUNCS __bgdexport( mod_multi, functions_exports )[] =
{
    { "MULTI_NUMPOINTERS" , ""      , TYPE_INT    , modmulti_numpointers },
    { "MULTI_INFO"        , "IS"    , TYPE_FLOAT  , modmulti_info        },
    {0, 0, 0, 0}
};

HOOK __bgdexport( mod_multi, handler_hooks )[] =
{
    { 5500, parse_input_events                },
    {    0, NULL                              }
} ;

char * __bgdexport( mod_multi, modules_dependency )[] =
{
    "libsdlhandler",
    NULL
};

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