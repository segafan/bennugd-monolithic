/*
 *  Copyright � 2006-2010 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
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

/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TARGET_MAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "bgddl.h"
#include "bgdrtm.h"
#include "xstrings.h"
#include "dlvaracc.h"

/* --------------------------------------------------------------------------- */

static SDL_CD * sdl_cd = NULL;
static int      sdl_cdnum = -1;

/* ----------------------------------------------------------------- */

#define CD_TRACK        0
#define CD_FRAME        1
#define CD_TRACKS       2
#define CD_MINUTE       3
#define CD_SECOND       4
#define CD_SUBFRAME     5
#define CD_MINUTES      6
#define CD_SECONDS      7
#define CD_FRAMES       8
#define CD_TRACKINFO    9     /* 400 INTs */

/* ----------------------------------------------------------------- */
/* Son las variables que se desea acceder.                           */
/* El interprete completa esta estructura, si la variable existe.    */
/* (usada en tiempo de ejecucion)                                    */
DLVARFIXUP  __bgdexport( mod_cd, globals_fixup )[] =
{
    /* Nombre de variable global, puntero al dato, tama�o del elemento, cantidad de elementos */
    { "cdinfo.current_track", NULL, -1, -1 },
    { "cdinfo.current_frame", NULL, -1, -1 },
    { "cdinfo.tracks", NULL, -1, -1 },
    { "cdinfo.minute", NULL, -1, -1 },
    { "cdinfo.second", NULL, -1, -1 },
    { "cdinfo.subframe", NULL, -1, -1 },
    { "cdinfo.minutes", NULL, -1, -1 },
    { "cdinfo.seconds", NULL, -1, -1 },
    { "cdinfo.subframes", NULL, -1, -1 },
    { "cdinfo.track", NULL, -1, -1 },
    { NULL, NULL, -1, -1 }
};

/* ----------------------------------------------------------------- */
/**
   int CD_DRIVES()
   Returns the number of CD drives in the system
 **/

CONDITIONALLY_STATIC int modcd_drives( INSTANCE * my, int * params )
{
    return SDL_CDNumDrives();
}

/* --------------------------------------------------------------------------- */
/**
   int CD_STATUS (int CD)
   Returns the status of a CD (using SDL constants)
 **/

CONDITIONALLY_STATIC int modcd_status( INSTANCE * my, int * params )
{
    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    return SDL_CDStatus( sdl_cd );
}

/* --------------------------------------------------------------------------- */
/**
   string CD_NAME (int CD)
   Returns a human-readable string with the name of a CD drive
 **/

CONDITIONALLY_STATIC int modcd_name( INSTANCE * my, int * params )
{
    int result;

    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    result = string_new( SDL_CDName( params[0] ) );
    string_use( result );
    return result;
}

/* --------------------------------------------------------------------------- */
/**
   CD_GETINFO(int CD)
   Fills the global structure CD with information about the current CD
   Returns 1 if there is a valid CD in the drive or 0 otherwise
 **/

CONDITIONALLY_STATIC int modcd_getinfo( INSTANCE * my, int * params )
{
    int i, total = 0;
    char * trackinfo;

    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    GLODWORD( mod_cd, CD_TRACKS ) = sdl_cd->numtracks;
    GLODWORD( mod_cd, CD_TRACK )  = sdl_cd->cur_track;
    FRAMES_TO_MSF( sdl_cd->cur_frame, &GLODWORD( mod_cd, CD_MINUTE ), &GLODWORD( mod_cd, CD_SECOND ), &GLODWORD( mod_cd, CD_SUBFRAME ) );

    trackinfo = ( char * ) & GLODWORD( mod_cd, CD_TRACKINFO );

    for ( i = 0; i < sdl_cd->numtracks ; i++, trackinfo += 16 )
    {
        total += sdl_cd->track[i].length;
        *( Uint32 * ) trackinfo = ( sdl_cd->track[i].type == SDL_AUDIO_TRACK );
        FRAMES_TO_MSF( sdl_cd->track[i].length, trackinfo + 4, trackinfo + 8, trackinfo + 12 );
    }
    FRAMES_TO_MSF( total, &GLODWORD( mod_cd, CD_MINUTES ), &GLODWORD( mod_cd, CD_SECONDS ), &GLODWORD( mod_cd, CD_FRAMES ) );
    return 1;
}

/* --------------------------------------------------------------------------- */
/**
   CD_PLAY (int CD, int TRACK)
   Starts playing a track of the given CD
 **/

CONDITIONALLY_STATIC int modcd_play( INSTANCE * my, int * params )
{
    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    if ( CD_INDRIVE( SDL_CDStatus( sdl_cd ) ) )
        return !SDL_CDPlayTracks( sdl_cd, params[1], 0, 1, 0 );

    return 0;
}

/* --------------------------------------------------------------------------- */
/**
   CD_PLAY (int CD, int TRACK, int NUMTRACKS)
   Plays a series of tracks of the CD
 **/

CONDITIONALLY_STATIC int modcd_playtracks( INSTANCE * my, int * params )
{
    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    if ( CD_INDRIVE( SDL_CDStatus( sdl_cd ) ) )
        return !SDL_CDPlayTracks( sdl_cd, params[1], 0, params[2], 0 );

    return 0;
}

/* --------------------------------------------------------------------------- */
/**
   CD_EJECT (int CD)
   Ejects a CD
 **/

CONDITIONALLY_STATIC int modcd_eject( INSTANCE * my, int * params )
{
    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    return !SDL_CDEject( sdl_cd );
}

/* --------------------------------------------------------------------------- */
/**
   CD_PAUSE (int CD)
   Pauses the CD playing
 **/

CONDITIONALLY_STATIC int modcd_pause( INSTANCE * my, int * params )
{
    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    return !SDL_CDPause( sdl_cd );
}

/* --------------------------------------------------------------------------- */
/**
   CD_RESUME (int CD)
   Resumes a CD in pause
 **/

CONDITIONALLY_STATIC int modcd_resume( INSTANCE * my, int * params )
{
    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    return !SDL_CDResume( sdl_cd );
}

/* --------------------------------------------------------------------------- */
/**
   CD_STOP (int CD)
   Stops the CD
 **/

CONDITIONALLY_STATIC int modcd_stop( INSTANCE * my, int * params )
{
    if ( params[0] < 0 || params[0] >= SDL_CDNumDrives() ) return 0;

    if ( sdl_cd == NULL || sdl_cdnum != params[0] )
    {
        if ( sdl_cd ) SDL_CDClose( sdl_cd );
        sdl_cd = SDL_CDOpen( params[0] );
        if ( sdl_cd == NULL ) return 0;
        sdl_cdnum = params[0];
    }

    return !SDL_CDStop( sdl_cd );
}

/* --------------------------------------------------------------------------- */
/* Funciones de inicializacion del modulo/plugin                               */

void  __bgdexport( mod_cd, module_initialize )()
{
    if ( !SDL_WasInit( SDL_INIT_CDROM ) ) SDL_InitSubSystem( SDL_INIT_CDROM );
}

/* --------------------------------------------------------------------------- */

void  __bgdexport( mod_cd, module_finalize )()
{
    if ( SDL_WasInit( SDL_INIT_CDROM ) ) SDL_QuitSubSystem( SDL_INIT_CDROM );
}

/* --------------------------------------------------------------------------- */