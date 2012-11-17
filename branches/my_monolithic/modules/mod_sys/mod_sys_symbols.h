/*
 *  Copyright © 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright © 2002-2006 Fenix Team (Fenix)
 *  Copyright © 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

#ifndef __MODSYS_SYMBOLS_H
#define __MODSYS_SYMBOLS_H

#ifdef __BGDC__
#define _P_WAIT     0
#define _P_NOWAIT   1

DLCONSTANT __bgdexport( mod_sys, constants_def )[] =
{
    { "_P_WAIT"     , TYPE_DWORD,  _P_WAIT   },
    { "_P_NOWAIT"   , TYPE_DWORD,  _P_NOWAIT },
    { NULL          , 0         ,  0         }
} ;

DLSYSFUNCS __bgdexport( mod_sys, functions_exports )[] =
{
    { "GETENV"  , "S"    , TYPE_STRING, 0 },
    { "EXEC"    , "ISIP" , TYPE_INT   , 0 },
    { 0         , 0      , 0          , 0 }
};
#else
extern DLCONSTANT __bgdexport( mod_sys, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_sys, functions_exports )[];
#endif

#endif
