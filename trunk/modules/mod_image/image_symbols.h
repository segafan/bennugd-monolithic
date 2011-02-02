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

#ifndef __IMAGE_SYMBOLS_H
#define __IMAGE_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern int bgd_load_image (INSTANCE * i, int * params);
extern int bgd_is_PCX (INSTANCE * i, int * params);
extern int bgd_is_GIF (INSTANCE * i, int * params);
extern int bgd_is_JPG (INSTANCE * i, int * params);
extern int bgd_is_PNG (INSTANCE * i, int * params);
extern int bgd_is_XPM (INSTANCE * i, int * params);
extern int bgd_is_BMP (INSTANCE * i, int * params);
extern int bgd_is_PNM (INSTANCE * i, int * params);
extern int bgd_is_TIF (INSTANCE * i, int * params);
extern int bgd_is_LBM (INSTANCE * i, int * params);
extern int bgd_is_XCF (INSTANCE * i, int * params);
#endif

DLSYSFUNCS __bgdexport( image, functions_exports )[] =
{
	{"LOAD_IMAGE", "S", TYPE_DWORD, SYSMACRO(bgd_load_image) },
	{"IS_BMP", "S", TYPE_DWORD, SYSMACRO(bgd_is_BMP)},
	{"IS_GIF", "S", TYPE_DWORD, SYSMACRO(bgd_is_GIF)},
	{"IS_JPG", "S", TYPE_DWORD, SYSMACRO(bgd_is_JPG)},
	{"IS_LBM", "S", TYPE_DWORD, SYSMACRO(bgd_is_LBM)},
	{"IS_PCX", "S", TYPE_DWORD, SYSMACRO(bgd_is_PCX)},
	{"IS_PNG", "S", TYPE_DWORD, SYSMACRO(bgd_is_PNG)},
	{"IS_PNM", "S", TYPE_DWORD, SYSMACRO(bgd_is_PNM)},
	{"IS_TIF", "S", TYPE_DWORD, SYSMACRO(bgd_is_TIF)},
	{"IS_XCF", "S", TYPE_DWORD, SYSMACRO(bgd_is_XCF)},
	{"IS_XPM", "S", TYPE_DWORD, SYSMACRO(bgd_is_XPM)},
	{0, 0, 0, 0}
};

char * __bgdexport( image, modules_dependency )[] =
{
	"libgrbase",
	"libvideo",
	NULL
};

#endif
