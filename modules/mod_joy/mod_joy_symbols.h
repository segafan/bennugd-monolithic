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

#ifndef __MODJOY_SYMBOLS_H
#define __MODJOY_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
DLSYSFUNCS  __bgdexport( mod_joy, functions_exports )[] =
{
    { "JOY_AXES"            , ""      , TYPE_INT    , 0 },
    { "JOY_AXES"            , "I"     , TYPE_INT    , 0 },
    { "JOY_NUMAXES"         , ""      , TYPE_INT    , 0 },
    { "JOY_NUMAXES"         , "I"     , TYPE_INT    , 0 },
    { "JOY_GETAXIS"         , "I"     , TYPE_INT    , 0 },
    { "JOY_GETAXIS"         , "II"    , TYPE_INT    , 0 },
    { "JOY_BUTTONS"         , ""      , TYPE_INT    , 0 },
    { "JOY_BUTTONS"         , "I"     , TYPE_INT    , 0 },
    { "JOY_NAME"            , "I"     , TYPE_STRING , 0 },
    { "JOY_NUMBUTTONS"      , ""      , TYPE_INT    , 0 },
    { "JOY_NUMBUTTONS"      , "I"     , TYPE_INT    , 0 },
    { "JOY_NUMBER"          , ""      , TYPE_INT    , 0 },
    { "JOY_NUMJOYSTICKS"    , ""      , TYPE_INT    , 0 },
    { "JOY_SELECT"          , "I"     , TYPE_INT    , 0 },
    { "JOY_GETBUTTON"       , "I"     , TYPE_INT    , 0 },
    { "JOY_GETBUTTON"       , "II"    , TYPE_INT    , 0 },
    { "JOY_GETPOSITION"     , "I"     , TYPE_INT    , 0 },
    { "JOY_GETPOSITION"     , "II"    , TYPE_INT    , 0 },
    { "JOY_NUMHATS"         , ""      , TYPE_INT    , 0 },
    { "JOY_NUMHATS"         , "I"     , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_NUMBALLS"        , ""      , TYPE_INT    , 0 },
    { "JOY_NUMBALLS"        , "I"     , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_GETHAT"          , "I"     , TYPE_INT    , 0 },
    { "JOY_GETHAT"          , "II"    , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_GETBALL"         , "IPP"   , TYPE_INT    , 0 },
    { "JOY_GETBALL"         , "IIPP"  , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_GETACCEL"        , "PPP"   , TYPE_INT    , 0 },
    { "JOY_GETACCEL"        , "IPPP"  , TYPE_INT    , 0 },
    /* Compatibility */
    { "NUMBER_JOY"          , ""      , TYPE_INT    , 0 },
    { "SELECT_JOY"          , "I"     , TYPE_INT    , 0 },
    { "GET_JOY_BUTTON"      , "I"     , TYPE_INT    , 0 },
    { "GET_JOY_BUTTON"      , "II"    , TYPE_INT    , 0 },
    { "GET_JOY_POSITION"    , "I"     , TYPE_INT    , 0 },
    { "GET_JOY_POSITION"    , "II"    , TYPE_INT    , 0 },
    { 0                     , 0       , 0           , 0 }
};

char * __bgdexport( mod_joy, modules_dependency )[] =
{
    "libjoy",
    NULL
};
#else
extern DLSYSFUNCS  __bgdexport( mod_joy, functions_exports )[];
extern char * __bgdexport( mod_joy, modules_dependency )[];
#endif

#endif
