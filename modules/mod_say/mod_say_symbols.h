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

#ifndef __MODSAY_SYMBOLS_H
#define __MODSAY_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern void __bgdexport( mod_say, module_initialize )();
extern CONDITIONALLY_STATIC int modsay_say( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modsay_say_fast( INSTANCE * my, int * params );
#endif

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_say, functions_exports )[] =
{
    { "SAY"     , "S", TYPE_UNDEFINED, SYSMACRO(modsay_say)     },
    { "SAY_FAST", "S", TYPE_UNDEFINED, SYSMACRO(modsay_say_fast)},
    { 0         , 0  , 0             , 0              }
};

#endif
