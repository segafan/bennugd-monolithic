/*
 *  Copyright © 2006-2010 SplinterGU (Fenix/Bennugd)
 *  Copyright © 2002-2006 Fenix Team (Fenix)
 *  Copyright © 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

#ifndef __MODSOUND_H
#define __MODSOUND_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modsound_load_song( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_play_song( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_unload_song( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_stop_song( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_pause_song( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_resume_song( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_is_playing_song( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_set_song_volume( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_fade_music_in( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_fade_music_off( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_load_wav( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_play_wav( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_play_wav_channel( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_unload_wav( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_stop_wav( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_pause_wav( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_resume_wav( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_is_playing_wav( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_set_channel_volume( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_reserve_channels( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_set_wav_volume( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_set_panning( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_set_position( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_set_distance( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_reverse_stereo( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_set_music_position( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_init( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsound_close( INSTANCE * my, int * params );
extern void __bgdexport( mod_sound, module_initialize )();
extern void __bgdexport( mod_sound, module_finalize )();
#endif

/* --------------------------------------------------------------------------- */
/* Definicion de constantes (usada en tiempo de compilacion)                   */

DLCONSTANT  __bgdexport( mod_sound, constants_def )[] =
{
    { "MODE_MONO"   , TYPE_INT, 0  },
    { "MODE_STEREO" , TYPE_INT, 1  },
    { "ALL_SOUND"   , TYPE_INT, -1 },
    { NULL          , 0       , 0  }
} ;

/* --------------------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion)           */

char __bgdexport( mod_sound, globals_def )[] =
#ifdef TARGET_WII
    "   sound_freq = 32000 ;\n"
#else
    "   sound_freq = 22050 ;\n"
#endif
    "   sound_mode = MODE_STEREO ;\n"
    "   sound_channels = 8 ;\n";

extern DLVARFIXUP  __bgdexport( mod_sound, globals_fixup )[];

/* --------------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_sound, functions_exports )[] =
{
    { "SOUND_INIT"          , ""     , TYPE_INT , SYSMACRO(modsound_init)               },
    { "SOUND_CLOSE"         , ""     , TYPE_INT , SYSMACRO(modsound_close)              },
    { "LOAD_SONG"           , "S"    , TYPE_INT , SYSMACRO(modsound_load_song)          },
    { "PLAY_SONG"           , "II"   , TYPE_INT , SYSMACRO(modsound_play_song)          },
    { "UNLOAD_SONG"         , "I"    , TYPE_INT , SYSMACRO(modsound_unload_song)        },
    { "STOP_SONG"           , ""     , TYPE_INT , SYSMACRO(modsound_stop_song)          },
    { "PAUSE_SONG"          , ""     , TYPE_INT , SYSMACRO(modsound_pause_song)         },
    { "RESUME_SONG"         , ""     , TYPE_INT , SYSMACRO(modsound_resume_song)        },
    { "SET_SONG_VOLUME"     , "I"    , TYPE_INT , SYSMACRO(modsound_set_song_volume)    },
    { "IS_PLAYING_SONG"     , ""     , TYPE_INT , SYSMACRO(modsound_is_playing_song)    },
    { "LOAD_WAV"            , "S"    , TYPE_INT , SYSMACRO(modsound_load_wav)           },
    { "PLAY_WAV"            , "II"   , TYPE_INT , SYSMACRO(modsound_play_wav)           },
    { "UNLOAD_WAV"          , "I"    , TYPE_INT , SYSMACRO(modsound_unload_wav)         },
    { "STOP_WAV"            , "I"    , TYPE_INT , SYSMACRO(modsound_stop_wav)           },
    { "PAUSE_WAV"           , "I"    , TYPE_INT , SYSMACRO(modsound_pause_wav)          },
    { "RESUME_WAV"          , "I"    , TYPE_INT , SYSMACRO(modsound_resume_wav)         },
    { "IS_PLAYING_WAV"      , "I"    , TYPE_INT , SYSMACRO(modsound_is_playing_wav)     },
    { "SET_WAV_VOLUME"      , "II"   , TYPE_INT , SYSMACRO(modsound_set_wav_volume)     },
    { "FADE_MUSIC_IN"       , "III"  , TYPE_INT , SYSMACRO(modsound_fade_music_in)      },
    { "FADE_MUSIC_OFF"      , "I"    , TYPE_INT , SYSMACRO(modsound_fade_music_off)     },
    { "SET_CHANNEL_VOLUME"  , "II"   , TYPE_INT , SYSMACRO(modsound_set_channel_volume) },
    { "RESERVE_CHANNELS"    , "I"    , TYPE_INT , SYSMACRO(modsound_reserve_channels)   },
    { "SET_PANNING"         , "III"  , TYPE_INT , SYSMACRO(modsound_set_panning)        },
    { "SET_POSITION"        , "III"  , TYPE_INT , SYSMACRO(modsound_set_position)       },
    { "SET_DISTANCE"        , "II"   , TYPE_INT , SYSMACRO(modsound_set_distance)       },
    { "REVERSE_STEREO"      , "II"   , TYPE_INT , SYSMACRO(modsound_reverse_stereo)     },
    { "PLAY_WAV"            , "III"  , TYPE_INT , SYSMACRO(modsound_play_wav_channel)   },
	{ "SET_MUSIC_POSITION"  , "F"    , TYPE_INT , SYSMACRO(modsound_set_music_position) },
    { 0                     , 0      , 0        , 0                           }
};

#endif
