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
#include <bgdrtm.h>
#include <curl/curl.h>
#include <SDL.h>

#ifndef MAX_DOWNLOADS
#define MAX_DOWNLOADS 16
#endif

/* --------------------------------------------------------------------------- */

typedef struct
{
    CURL *curl;
    struct curl_httppost *formpost;
    struct curl_httppost *lastptr;
    FILE *outfd;        // Used when downloading to a file
    int used;
} curl_info ;

typedef struct
{
    int  *id;
    int  *status;
    int ( *fn )();
} bgdata ;

curl_info download_info[MAX_DOWNLOADS];

// Find the first free curl_info index, return numeric index
int findindex() {
    int i=0;
    
    for (i=0; i<MAX_DOWNLOADS; i++) {
        if (download_info[i].used == 0) {
            // Initialize values, just in case they haven't been already
            download_info[i].formpost = NULL;
            download_info[i].lastptr  = NULL;
            download_info[i].outfd    = NULL;
            download_info[i].used     = 1;
            return i;
        }
    }
    
    return -1;
}

/* --------------------------------------------------------------------------- */

/**
 * PREP
 * Helper function preparing params
 **/

static bgdata *prep( int *params )
{
    bgdata *t = ( bgdata* )malloc( sizeof( bgdata ) );

    t->id     = ( int* )params[0];
    t->status = ( int* )params[1];

    return t;
}

/* --------------------------------------------------------------------------- */
/**
 * bgDoLoad
 * Helper function executed in the new thread
 **/

static int bgDoLoad( void *d )
{
    bgdata *t  = ( bgdata* )d;
    *( t->status ) = -2 ;
    *( t->status ) = ( *t->fn )( t->id );
    free( t );
    return 0;
}

// Maps curl_global_init
static int bgd_curl_global_init(INSTANCE * my, int * params) {
    return curl_global_init(CURL_GLOBAL_ALL);
}

// Maps curl_global_cleanup
static int bgd_curl_global_cleanup(INSTANCE * my, int * params) {
    curl_global_cleanup();
    
    return 0;
}

// Maps curl_formadd
static int bgd_curl_formadd(INSTANCE * my, int * params) {
    int retval = 0;

    if(params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;
    
    // Actually perform curl_formadd
    retval = curl_formadd(&download_info[params[0]].formpost,
                 &download_info[params[0]].lastptr,
                 params[1], string_get(params[2]),
                 params[3], string_get(params[4]),
                 CURLFORM_END);
    
    string_discard(params[2]);
    string_discard(params[4]);
    
    return retval;
}

// Maps curl_formfree
static int bgd_curl_formfree(INSTANCE * my, int * params) {
    if(params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;
    
    // Actually perform curl_formfree
    curl_formfree(download_info[params[0]].formpost);
    
    return 0;
}

// Maps curl_easy_init
static int bgd_curl_easy_init(INSTANCE * my, int * params) {
    int i;
    
    // Get the index of the connection
    if( (i = findindex()) == -1)
        return -1;
    
    download_info[i].curl = curl_easy_init();
    
    if (download_info[i].curl == NULL)
        return -1;

    return i;
}

// Maps curl_easy_cleanup
static int bgd_curl_easy_cleanup(INSTANCE * my, int * params) {
    if(params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;
    
    download_info[params[0]].used = 0;
    
    curl_easy_cleanup(download_info[params[0]].curl);

    return 0;
}

// Maps curl_easy_setopt
static int bgd_curl_easy_setopt(INSTANCE * my, int * params) {
    if(params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;
    
    CURLcode retval;
    
    // Actually perform curl_easy_setopt
    switch (params[1]) {
        case CURLOPT_HTTPPOST:
            retval = curl_easy_setopt(download_info[params[0]].curl,
                                      CURLOPT_HTTPPOST,
                                      download_info[params[0]].formpost);
            break;

        default:
            retval = curl_easy_setopt(download_info[params[0]].curl,
                                      params[1],
                                      params[2]);
            break;
    }
    
    return (int)retval;
}

static int bgd_curl_easy_setopt2(INSTANCE * my, int * params) {
    if(params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;
    
    CURLcode retval;
    
    // Actually perform curl_easy_setopt
    switch (params[1]) {
            // Handle some special cases
        case CURLOPT_WRITEDATA:
            // Point the output file pointer to the given location
            download_info[params[0]].outfd = fopen(string_get(params[2]), "w");
            string_discard(params[2]);
            if(download_info[params[0]].outfd == NULL)
                return -1;
            
            retval = curl_easy_setopt(download_info[params[0]].curl,
                                      CURLOPT_WRITEDATA,
                                      download_info[params[0]].outfd);
            break;
            
        default:
            retval = curl_easy_setopt(download_info[params[0]].curl,
                                      params[1],
                                      string_get(params[2]));
            string_discard(params[2]);
            break;
    }
    
    return (int)retval;
}

// Actual perform function
int curl_perform(int id) {
    if(download_info[id].curl == NULL)
        return -1;
    
    // Perform download, this function won't quit until it's done
    curl_easy_perform(download_info[id].curl);
    
    // If downloading to a file, close its file descriptor
    if (download_info[id].outfd != NULL) {
        fclose(download_info[id].outfd);
    }
    
    return 0;
}

// Map curl_easy_perform
static int bgd_curl_easy_perform(INSTANCE * my, int * params) {
    bgdata *t = prep( params );
    t->fn = curl_perform;
    
#if SDL_VERSION_ATLEAST(1,3,0)
    SDL_CreateThread( bgDoLoad, "CURL perform thread", (void *)t );
#else
    SDL_CreateThread( bgDoLoad, (void *)t );
#endif
    
    return 0;
}

DLSYSFUNCS __bgdexport( mod_curl, functions_exports )[] =
{
    { "CURL_GLOBAL_INIT"    , ""      , TYPE_INT , bgd_curl_global_init    },
    { "CURL_GLOBAL_CLEANUP" , ""      , TYPE_INT , bgd_curl_global_cleanup },
    { "CURL_INIT"           , ""      , TYPE_INT , bgd_curl_easy_init      },
    { "CURL_CLEANUP"        , "I"     , TYPE_INT , bgd_curl_easy_cleanup   },
    { "CURL_FORMADD"        , "IISIS" , TYPE_INT , bgd_curl_formadd        },
    { "CURL_FORMFREE"       , "I"     , TYPE_INT , bgd_curl_formfree       },
    { "CURL_SETOPT"         , "III"   , TYPE_INT , bgd_curl_easy_setopt    },
    { "CURL_SETOPT"         , "IIS"   , TYPE_INT , bgd_curl_easy_setopt2   },
    { "CURL_PERFORM"        , "IP"    , TYPE_INT , bgd_curl_easy_perform   },
    { 0                     , 0       , 0        , 0                       }
};
