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

#ifndef __MODMEM_SYMBOLS_H
#define __MODMEM_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
DLSYSFUNCS __bgdexport( mod_mem, functions_exports )[] =
{
    { "MEM_CALLOC"      , "II"    , TYPE_POINTER, 0 },
    { "MEM_ALLOC"       , "I"     , TYPE_POINTER, 0 },
    { "MEM_FREE"        , "P"     , TYPE_INT    , 0 },
    { "MEM_REALLOC"     , "PI"    , TYPE_POINTER, 0 },
    { "MEM_CMP"         , "PPI"   , TYPE_INT    , 0 },
    { "MEM_SET"         , "PBI"   , TYPE_INT    , 0 },
    { "MEM_SETW"        , "PWI"   , TYPE_INT    , 0 },
    { "MEM_SETI"        , "PII"   , TYPE_INT    , 0 },
    { "MEM_COPY"        , "PPI"   , TYPE_INT    , 0 },
    { "MEM_MOVE"        , "PPI"   , TYPE_INT    , 0 },
    { "MEM_AVAILABLE"   , ""      , TYPE_INT    , 0 },
    { "MEM_TOTAL"       , ""      , TYPE_INT    , 0 },
    { "CALLOC"          , "II"    , TYPE_POINTER, 0 },
    { "ALLOC"           , "I"     , TYPE_POINTER, 0 },
    { "FREE"            , "P"     , TYPE_INT    , 0 },
    { "REALLOC"         , "PI"    , TYPE_POINTER, 0 },
    { "MEMCMP"          , "PPI"   , TYPE_INT    , 0 },
    { "MEMSET"          , "PBI"   , TYPE_INT    , 0 },
    { "MEMSETW"         , "PWI"   , TYPE_INT    , 0 },
    { "MEMSETI"         , "PII"   , TYPE_INT    , 0 },
    { "MEMCOPY"         , "PPI"   , TYPE_INT    , 0 },
    { "MEMMOVE"         , "PPI"   , TYPE_INT    , 0 },
    { "MEMORY_FREE"     , ""      , TYPE_INT    , 0 },
    { "MEMORY_TOTAL"    , ""      , TYPE_INT    , 0 },
    { 0                 , 0       , 0           , 0 }
};
#else
extern DLSYSFUNCS __bgdexport( mod_mem, functions_exports )[];
#endif

#endif
