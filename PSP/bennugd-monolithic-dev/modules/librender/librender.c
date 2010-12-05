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

/* --------------------------------------------------------------------------- */

#include <stdlib.h>

/* --------------------------------------------------------------------------- */

#include "bgddl.h"
#include "dlvaracc.h"

#ifndef __MONOLITHIC__
#include "librender_symbols.h"
#endif

#define __LIB_RENDER
#include "librender.h"

/* --------------------------------------------------------------------------- */
/* Son las variables que se desea acceder.                           */
/* El interprete completa esta estructura, si la variable existe.    */
/* (usada en tiempo de ejecucion)                                    */

DLVARFIXUP __bgdexport( librender, globals_fixup )[] =
{
    /* Nombre de variable global, puntero al dato, tamaño del elemento, cantidad de elementos */
    { "fps" , NULL, -1, -1 },
    { "speed_gauge" , NULL, -1, -1 },
    { "frame_time" , NULL, -1, -1 },

    { "scale_mode" , NULL, -1, -1 },
    { "restore_type" , NULL, -1, -1 },
    { "dump_type" , NULL, -1, -1 },

    { "fading" , NULL, -1, -1 },
    { "alpha_steps" , NULL, -1, -1 },

    { NULL , NULL, -1, -1 }
};

DLVARFIXUP __bgdexport( librender, locals_fixup )[] =
{
    { "ctype" , NULL, -1, -1 },                                             // 0            CTYPE               0
    { "cnumber" , NULL, -1, -1 },                                           // 1            CNUMBER             1

    { "x" , NULL, -1, -1 },                                                 // 2            COORDX              2
    { "y" , NULL, -1, -1 },                                                 // 3            COORDY              3
    { "z" , NULL, -1, -1 },                                                 // 4            COORDZ              4
    { "file" , NULL, -1, -1 },                                              // 5            FILEID              5
    { "graph" , NULL, -1, -1 },                                             // 6            GRAPHID             6
    { "size" , NULL, -1, -1 },                                              // 7            GRAPHSIZE           7
    { "angle" , NULL, -1, -1 },                                             // 8            ANGLE               8
    { "flags" , NULL, -1, -1 },                                             // 9            FLAGS               9
    { "alpha" , NULL, -1, -1 },                                             // 10           ALPHA               10
    { "palette" , NULL, -1, -1 },                                           // 11           PALETTEID           11
    { "region" , NULL, -1, -1 },                                            // 12           REGIONID            12
    { "resolution" , NULL, -1, -1 },                                        // 13           RESOLUTION          13
    { "size_x" , NULL, -1, -1 },                                            // 14           GRAPHSIZEX          14
    { "size_y" , NULL, -1, -1 },                                            // 15           GRAPHSIZEY          15
    { "blendop" , NULL, -1, -1 },                                           // 16           BLENDOP             16
    { "xgraph" , NULL, -1, -1 },                                            // 17           XGRAPH              17

    { "_render_reserved_.object_id" , NULL, -1, -1 },                       // 18           OBJECTID            18
    { "_render_reserved_.graph_ptr" , NULL, -1, -1 },                       // 19           GRAPHPTR            19
    { "_render_reserved_.xgraph_flags" , NULL, -1, -1 },                    // 20           XGRAPH_FLAGS        20

    { "_render_reserved_._saved_.x" , NULL, -1, -1 },                       // 21           SAVED_COORDX        21
    { "_render_reserved_._saved_.y" , NULL, -1, -1 },                       // 22           SAVED_COORDY        22
    { "_render_reserved_._saved_.z" , NULL, -1, -1 },                       // 23           SAVED_COORDZ        23
    { "_render_reserved_._saved_.file" , NULL, -1, -1 },                    // 24           SAVED_FILEID        24
    { "_render_reserved_._saved_.graph" , NULL, -1, -1 },                   // 25           SAVED_GRAPHID       25
    { "_render_reserved_._saved_.size" , NULL, -1, -1 },                    // 26           SAVED_GRAPHSIZE     26
    { "_render_reserved_._saved_.angle" , NULL, -1, -1 },                   // 27           SAVED_ANGLE         27
    { "_render_reserved_._saved_.flags" , NULL, -1, -1 },                   // 28           SAVED_FLAGS         28
    { "_render_reserved_._saved_.alpha" , NULL, -1, -1 },                   // 29           SAVED_ALPHA         29
    { "_render_reserved_._saved_.palette" , NULL, -1, -1 },                 // 30           SAVED_PALETTE       30
    { "_render_reserved_._saved_.size_x" , NULL, -1, -1 },                  // 31           SAVED_GRAPHSIZEX    31
    { "_render_reserved_._saved_.size_y" , NULL, -1, -1 },                  // 32           SAVED_GRAPHSIZEY    32
    { "_render_reserved_._saved_.blendop" , NULL, -1, -1 },                 // 33           SAVED_BLENDOP       33
    { "_render_reserved_._saved_.xgraph" , NULL, -1, -1 },                  // 34           SAVED_XGRAPH        34
    { "_render_reserved_._saved_.centerx" , NULL, -1, -1 },                 // 35           SAVED_COORDX        35
    { "_render_reserved_._saved_.centery" , NULL, -1, -1 },                 // 36           SAVED_COORDY        36

    { "reserved.status" , NULL, -1, -1 },                                   // 37           STATUS              37

    { NULL , NULL, -1, -1 }
};

/* --------------------------------------------------------------------------- */

/* Bigest priority first execute
   Lowest priority last execute */

HOOK __bgdexport( librender, handler_hooks )[] =
{
    { 9500, gr_wait_frame },
    { 9000, gr_draw_frame },
    {    0, NULL          }
} ;

/* --------------------------------------------------------------------------- */
