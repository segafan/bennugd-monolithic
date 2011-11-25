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
#include <bgddl.h>
#include <xstrings.h>
#include <curl/curl.h>
#include <SDL.h>

// Status vars
// This code really needs some cleanup to allow multiple transfers
// at a time
static int transfer_in_progress=0;
static int transfer_done=0;
static int transfer_failed=0;

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

typedef struct
{
    char *src;
    char *dst;
    int ( *fn )();
} bgdata ;

/* --------------------------------------------------------------------------- */

/**
 * PREP
 * Helper function preparing params
 **/

static bgdata *prep( int *params )
{
    bgdata *t = ( bgdata* )malloc( sizeof( bgdata ) );
    t->src = ( char * )string_get( params[0] );
    t->dst = ( char * )string_get( params[1] );
    string_discard( params[0] );
    string_discard( params[1] );
    return t;
}

/* --------------------------------------------------------------------------- */
/**
 * bgDoLoad
 * Helper function executed in the new thread
 **/

static int bgDoLoad( void *d )
{
    bgdata *t = ( bgdata* )d;
    ( *t->fn )( t->src, t->dst );
    free( t );
    return 0;
}

// Actual transfer function
void curl_get(char *src, char *dst) {
    CURL *curl;
    FILE *fd;
    
    // First, get the file descriptor for the output file
    fd = fopen(dst, "w");
    // Check file opening
    if (fd == NULL) {
        transfer_failed = 1;
        return;
    }
    
    transfer_in_progress = 1;
    
    // Set up some download variables
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
    curl_easy_setopt(curl, CURLOPT_URL, src);
    
    // Perform download, this function won't quit until it's done
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    fclose(fd);

    transfer_in_progress = 0;
    transfer_done = 1;

    return;
}

// Start a new download in a new thread
static int bgd_curl_get(INSTANCE * my, int * params) {
    if(transfer_in_progress == 1)
        return -1;
    
    bgdata *t = prep( params );
    t->fn = curl_get;
    
    // Reset values
    transfer_done   = 0;
    transfer_failed = 0;
    
#if SDL_VERSION_ATLEAST(1,3,0)
    SDL_CreateThread( bgDoLoad, "CURL download thread", (void *)t );
#else
    SDL_CreateThread( bgDoLoad, (void *)t );
#endif
    
    return 0;
}

// Get info about current download
// Accepts two parameters to future-proof the API, but only the second
// one is used
static int bgd_curl_info(INSTANCE * my, int * params) {
    switch (params[1]) {
        case 0:
            return transfer_in_progress;
            
        case 1:
            return transfer_done;
            
        case 2:
            return transfer_failed;
    }
    
    return -1;
}

DLSYSFUNCS __bgdexport( mod_curl, functions_exports )[] =
{
    { "CURL_GET"            , "SS"  , TYPE_INT,   bgd_curl_get       },
    { "CURL_INFO"           , "II"  , TYPE_INT,   bgd_curl_info      },
    { 0                     , 0     , 0          , 0}
};
