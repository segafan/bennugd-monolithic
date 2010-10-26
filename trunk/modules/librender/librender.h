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

#ifndef __RENDER_H
#define __RENDER_H

/* --------------------------------------------------------------------------- */

#ifdef __LIB_RENDER
#include "bgdrtm.h"

#include "dlvaracc.h"
#include "bgddl.h"

#include "libgrbase.h"
#include "libvideo.h"
#include "libblit.h"
#endif

#include "g_fade.h"
#include "g_frame.h"
#include "g_instance.h"
#include "g_object.h"
#include "g_rects.h"
#include "g_screen.h"
#include "scaler.h"
#include "scaler_hq2x.h"
#include "scaler_normal.h"
#include "scaler_scale2x.h"
#include "scaler_scanline.h"

/* --------------------------------------------------------------------------- */

#define C_SCREEN            0

/* --------------------------------------------------------------------------- */

#ifdef __LIB_RENDER

/* Globals */

#define FPS                 0
#define SPEED_GAUGE         1
#define FRAME_TIME          2

#define SCALE_MODE          3
#define RESTORETYPE         4
#define DUMPTYPE            5

#define FADING              6
#define ALPHA_STEPS         7

/* Locals */

#define CTYPE               0
#define CNUMBER             1

#define COORDX              2
#define COORDY              3
#define COORDZ              4
#define FILEID              5
#define GRAPHID             6
#define GRAPHSIZE           7
#define ANGLE               8
#define FLAGS               9
#define ALPHA               10
#define PALETTEID           11
#define REGIONID            12
#define RESOLUTION          13
#define GRAPHSIZEX          14
#define GRAPHSIZEY          15
#define BLENDOP             16
#define XGRAPH              17

#define OBJECTID            18
#define GRAPHPTR            19
#define XGRAPH_FLAGS        20

#define SAVED_COORDX        21
#define SAVED_COORDY        22
#define SAVED_COORDZ        23
#define SAVED_FILEID        24
#define SAVED_GRAPHID       25
#define SAVED_GRAPHSIZE     26
#define SAVED_ANGLE         27
#define SAVED_FLAGS         28
#define SAVED_ALPHA         29
#define SAVED_PALETTE       30
#define SAVED_GRAPHSIZEX    31
#define SAVED_GRAPHSIZEY    32
#define SAVED_BLENDOP       33
#define SAVED_XGRAPH        34
#define SAVED_CENTERX       35
#define SAVED_CENTERY       36

#define STATUS              37

/* --------------------------------------------------------------------------- */

extern DLVARFIXUP __bgdexport( librender, globals_fixup )[];
extern DLVARFIXUP __bgdexport( librender, locals_fixup )[];

/* --------------------------------------------------------------------------- */
#endif

#endif
