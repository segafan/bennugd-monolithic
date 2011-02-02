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

#ifndef __TEXT_SYMBOLS_H
#define __TEXT_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
/* --------------------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion) */

char __bgdexport( libtext, globals_def )[] =
    "text_z = -256;\n"
    "text_flags;\n"
    ;

/* --------------------------------------------------------------------------- */

char * __bgdexport( libtext, modules_dependency )[] =
{
    "libgrbase",
    "libblit",
    "librender",
    "libfont",
    NULL
};
#else
extern char __bgdexport( libtext, globals_def )[];
extern char __bgdexport( libtext, modules_dependency )[];
extern DLVARFIXUP __bgdexport( libtext, globals_fixup )[];
#endif

#endif
