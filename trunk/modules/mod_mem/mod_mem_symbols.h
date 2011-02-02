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

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modmem_memory_free( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_memory_total( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_memcmp( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_memmove( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_memcopy( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_memset( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_memsetw( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_memseti( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_calloc( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_alloc( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_realloc( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmem_free( INSTANCE * my, int * params );
#endif

/* ---------------------------------------------------------------------- */

DLSYSFUNCS __bgdexport( mod_mem, functions_exports )[] =
{
    /* Memory Handling */
    { "MEM_CALLOC"      , "II"    , TYPE_POINTER, SYSMACRO(modmem_calloc)         },
    { "MEM_ALLOC"       , "I"     , TYPE_POINTER, SYSMACRO(modmem_alloc)          },
    { "MEM_FREE"        , "P"     , TYPE_INT    , SYSMACRO(modmem_free)           },
    { "MEM_REALLOC"     , "PI"    , TYPE_POINTER, SYSMACRO(modmem_realloc)        },
    { "MEM_CMP"         , "PPI"   , TYPE_INT    , SYSMACRO(modmem_memcmp)         },
    { "MEM_SET"         , "PBI"   , TYPE_INT    , SYSMACRO(modmem_memset)         },
    { "MEM_SETW"        , "PWI"   , TYPE_INT    , SYSMACRO(modmem_memsetw)        },
    { "MEM_SETI"        , "PII"   , TYPE_INT    , SYSMACRO(modmem_memseti)        },
    { "MEM_COPY"        , "PPI"   , TYPE_INT    , SYSMACRO(modmem_memcopy)        },
    { "MEM_MOVE"        , "PPI"   , TYPE_INT    , SYSMACRO(modmem_memmove)        },
    { "MEM_AVAILABLE"   , ""      , TYPE_INT    , SYSMACRO(modmem_memory_free)    },
    { "MEM_TOTAL"       , ""      , TYPE_INT    , SYSMACRO(modmem_memory_total)   },
	
    { "CALLOC"          , "II"    , TYPE_POINTER, SYSMACRO(modmem_calloc)         },
    { "ALLOC"           , "I"     , TYPE_POINTER, SYSMACRO(modmem_alloc)          },
    { "FREE"            , "P"     , TYPE_INT    , SYSMACRO(modmem_free)           },
    { "REALLOC"         , "PI"    , TYPE_POINTER, SYSMACRO(modmem_realloc)        },
    { "MEMCMP"          , "PPI"   , TYPE_INT    , SYSMACRO(modmem_memcmp)         },
    { "MEMSET"          , "PBI"   , TYPE_INT    , SYSMACRO(modmem_memset)         },
    { "MEMSETW"         , "PWI"   , TYPE_INT    , SYSMACRO(modmem_memsetw)        },
    { "MEMSETI"         , "PII"   , TYPE_INT    , SYSMACRO(modmem_memseti)        },
    { "MEMCOPY"         , "PPI"   , TYPE_INT    , SYSMACRO(modmem_memcopy)        },
    { "MEMMOVE"         , "PPI"   , TYPE_INT    , SYSMACRO(modmem_memmove)        },
    { "MEMORY_FREE"     , ""      , TYPE_INT    , SYSMACRO(modmem_memory_free)    },
    { "MEMORY_TOTAL"    , ""      , TYPE_INT    , SYSMACRO(modmem_memory_total)   },
    { 0                 , 0       , 0           , 0                     }
};

#endif
