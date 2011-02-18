/*
 *  Copyright © 2006-2011 SplinterGU (Fenix/Bennugd)
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

#ifdef __BGDC__
DLCONSTANT  __bgdexport( mod_sound, constants_def )[] =
{
    { "MODE_MONO"   , TYPE_INT, 0  },
    { "MODE_STEREO" , TYPE_INT, 1  },
    { "ALL_SOUND"   , TYPE_INT, -1 },
    { NULL          , 0       , 0  }
} ;

char __bgdexport( mod_sound, globals_def )[] =
    "   sound_freq = 22050 ;\n"
    "   sound_mode = MODE_STEREO ;\n"
    "   sound_channels = 8 ;\n";

DLSYSFUNCS  __bgdexport( mod_sound, functions_exports )[] =
{
    { "SOUND_INIT"          , ""     , TYPE_INT , 0 },
    { "SOUND_CLOSE"         , ""     , TYPE_INT , 0 },
    { "LOAD_SONG"           , "S"    , TYPE_INT , 0 },
    { "PLAY_SONG"           , "II"   , TYPE_INT , 0 },
    { "UNLOAD_SONG"         , "I"    , TYPE_INT , 0 },
    { "STOP_SONG"           , ""     , TYPE_INT , 0 },
    { "PAUSE_SONG"          , ""     , TYPE_INT , 0 },
    { "RESUME_SONG"         , ""     , TYPE_INT , 0 },
    { "SET_SONG_VOLUME"     , "I"    , TYPE_INT , 0 },
    { "IS_PLAYING_SONG"     , ""     , TYPE_INT , 0 },
    { "LOAD_WAV"            , "S"    , TYPE_INT , 0 },
    { "PLAY_WAV"            , "II"   , TYPE_INT , 0 },
    { "UNLOAD_WAV"          , "I"    , TYPE_INT , 0 },
    { "STOP_WAV"            , "I"    , TYPE_INT , 0 },
    { "PAUSE_WAV"           , "I"    , TYPE_INT , 0 },
    { "RESUME_WAV"          , "I"    , TYPE_INT , 0 },
    { "IS_PLAYING_WAV"      , "I"    , TYPE_INT , 0 },
    { "SET_WAV_VOLUME"      , "II"   , TYPE_INT , 0 },
    { "FADE_MUSIC_IN"       , "III"  , TYPE_INT , 0 },
    { "FADE_MUSIC_OFF"      , "I"    , TYPE_INT , 0 },
    { "SET_CHANNEL_VOLUME"  , "II"   , TYPE_INT , 0 },
    { "RESERVE_CHANNELS"    , "I"    , TYPE_INT , 0 },
    { "SET_PANNING"         , "III"  , TYPE_INT , 0 },
    { "SET_POSITION"        , "III"  , TYPE_INT , 0 },
    { "SET_DISTANCE"        , "II"   , TYPE_INT , 0 },
    { "REVERSE_STEREO"      , "II"   , TYPE_INT , 0 },
    { "PLAY_WAV"            , "III"  , TYPE_INT , 0 },
    { "SET_MUSIC_POSITION"  , "F"    , TYPE_INT , 0 },
    { "UNLOAD_SONG"         , "P"    , TYPE_INT , 0 },
    { "UNLOAD_WAV"          , "P"    , TYPE_INT , 0 },
    { 0                     , 0      , 0        , 0 }
};
#else
extern DLCONSTANT  __bgdexport( mod_sound, constants_def )[];
extern char __bgdexport( mod_sound, globals_def )[];
extern DLVARFIXUP  __bgdexport( mod_sound, globals_fixup )[];
extern DLSYSFUNCS  __bgdexport( mod_sound, functions_exports )[];
extern void  __bgdexport( mod_sound, module_initialize )();
extern void __bgdexport( mod_sound, module_finalize )();
#endif

#endif
