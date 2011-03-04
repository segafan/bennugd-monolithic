/*
 *  Copyright � 2006-2011 SplinterGU (Fenix/Bennugd)
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

/* --------------------------------------------------------------------------- */

#ifndef __MOD_IMAGE_H
#define __MOD_IMAGE_H

#include <stdio.h>
#include <string.h>

#include "libgrbase.h"
#include "libvideo.h"
#include "libblit.h"
#include "libfont.h"

#include "arrange.h"
#include "files.h"

/* --------------------------------------------------------------------------- */

/* CABECERAS DE FICHEROS */
#define MAP_MAGIC "map\x1A\x0D\x0A\x00"
#define M32_MAGIC "m32\x1A\x0D\x0A\x00"
#define M16_MAGIC "m16\x1A\x0D\x0A\x00"
#define M01_MAGIC "m01\x1A\x0D\x0A\x00"

#define PAL_MAGIC "pal\x1A\x0D\x0A\x00"

#define FNT_MAGIC "fnt\x1A\x0D\x0A\x00"
#define FNX_MAGIC "fnx\x1A\x0D\x0A\x00"

#define FPG_MAGIC "fpg\x1A\x0D\x0A\x00"
#define F32_MAGIC "f32\x1A\x0D\x0A\x00"
#define F16_MAGIC "f16\x1A\x0D\x0A\x00"
#define F01_MAGIC "f01\x1A\x0D\x0A\x00"

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

typedef struct
{
    uint8_t magic[7] ;
    uint8_t version ;
    uint16_t width ;
    uint16_t height ;
    uint32_t code ;
    int8_t name[32] ;
}
#ifdef __GNUC__
__attribute__ ((packed))
#endif
MAP_HEADER ;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

/* ------------------------------------------ */

extern int gr_load_fpg( const char * filename ) ;
extern int gr_load_map( const char * filename ) ;
extern int gr_load_pal( const char * filename ) ;
extern int gr_load_png( const char * filename ) ;
extern int gr_load_pcx( const char * filename ) ;

extern int gr_save_system_pal( const char * filename ) ;

extern int gr_save_fpg( int libid, const char * filename ) ;
extern int gr_save_map( GRAPH * gr, char * filename ) ;
extern int gr_save_pal( const char * filename, PALETTE * pal ) ;
extern int gr_save_png( GRAPH * gr, const char * filename ) ;

extern GRAPH * gr_read_png( const char * filename );

extern PALETTE * gr_read_pal( file * fp ) ;
extern PALETTE * gr_read_pal_with_gamma( file * fp );

extern int gr_font_load( char * filename ) ;
extern int gr_load_bdf( const char * filename ) ;
extern int gr_load_ttf( const char * filename, int size, int bpp, int fg, int bg ) ;
extern int gr_font_save( int fontid, const char * filename ) ;

#endif
