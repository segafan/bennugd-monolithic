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

#ifndef __WM_SYMBOLS_H
#define __WM_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern DLVARFIXUP  __bgdexport( libwm, globals_fixup )[];
extern HOOK __bgdexport( libwm, handler_hooks )[];
#endif

/* --------------------------------------------------------------------------- */
/* Definicion de variables globales (usada en tiempo de compilacion) */

char __bgdexport( libwm, globals_def )[] =
"exit_status = 0;\n"                /* SDL_QUIT status */
"window_status = 1;\n"              /* MINIMIZED:0 VISIBLE:1 */
"focus_status = 1;\n"               /* FOCUS status */
"mouse_status = 1;\n";              /* MOUSE status (INSIDE WINDOW:1) */

/* --------------------------------------------------------------------------- */

char * __bgdexport( libwm, modules_dependency )[] =
{
    "libsdlhandler",
    NULL
};

#endif
