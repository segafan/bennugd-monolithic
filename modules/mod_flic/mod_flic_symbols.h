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

#ifndef __MODFLIC_SYMBOLS_H
#define __MODFLIC_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
DLSYSFUNCS  __bgdexport( mod_flic, functions_exports )[] =
{
    /* Animaciones FLI */
    { "START_FLI"       , "SII"         , TYPE_INT , 0 },
    { "END_FLI"         , ""            , TYPE_INT , 0 },
    { "FRAME_FLI"       , ""            , TYPE_INT , 0 },
    { "RESET_FLI"       , ""            , TYPE_INT , 0 },

    { "FLI_START"       , "SII"         , TYPE_INT , 0 },
    { "FLI_START"       , "SIIIIII"     , TYPE_INT , 0 },
    { "FLI_END"         , "I"           , TYPE_INT , 0 },
    { "FLI_FRAME"       , "I"           , TYPE_INT , 0 },
    { "FLI_RESET"       , "I"           , TYPE_INT , 0 },

    { "FLI_PARAMS"      , "IIIIIII"     , TYPE_INT , 0 },
    { "FLI_MOVE"        , "III"         , TYPE_INT , 0 },
    { "FLI_ANGLE"       , "II"          , TYPE_INT , 0 },
    { "FLI_SIZE"        , "II"          , TYPE_INT , 0 },
    { "FLI_FLAGS"       , "II"          , TYPE_INT , 0 },
    { "FLI_Z"           , "II"          , TYPE_INT , 0 },
    { "FLI_GETINFO"     , "IPPPPPPPPP"  , TYPE_INT , 0 },

    { NULL              , NULL          , 0        , NULL }
};
#else
extern DLSYSFUNCS  __bgdexport( mod_flic, functions_exports )[];
#endif

#endif
