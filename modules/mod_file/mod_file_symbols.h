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

#ifndef __MODFILE_H
#define __MODFILE_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modfile_save( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_load( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fopen( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fclose( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fread( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fwrite( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_freadC( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fwriteC( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fseek( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_frewind( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_ftell( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_filelength( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fputs( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_fgets( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_file( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_feof( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_exists( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_remove( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modfile_move( INSTANCE * my, int * params );
#endif

/* ----------------------------------------------------------------- */

DLCONSTANT  __bgdexport( mod_file, constants_def)[] =
{
    { "O_READ"      , TYPE_INT, 0  },
    { "O_READWRITE" , TYPE_INT, 1  },
    { "O_RDWR"      , TYPE_INT, 1  },
    { "O_WRITE"     , TYPE_INT, 2  },
    { "O_ZREAD"     , TYPE_INT, 3  },
    { "O_ZWRITE"    , TYPE_INT, 4  },
	
    { "SEEK_SET"    , TYPE_INT, 0  },
    { "SEEK_CUR"    , TYPE_INT, 1  },
    { "SEEK_END"    , TYPE_INT, 2  },
	
    { NULL          , 0       , 0  }
} ;

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_file, functions_exports )[] =
{
    /* Ficheros */
    { "SAVE"        , "SV++" , TYPE_INT         , SYSMACRO(modfile_save)        },
    { "LOAD"        , "SV++" , TYPE_INT         , SYSMACRO(modfile_load)        },
    { "FOPEN"       , "SI"   , TYPE_INT         , SYSMACRO(modfile_fopen)       },
    { "FCLOSE"      , "I"    , TYPE_INT         , SYSMACRO(modfile_fclose)      },
    { "FREAD"       , "IV++" , TYPE_INT         , SYSMACRO(modfile_fread)       },
    { "FREAD"       , "PII"  , TYPE_INT         , SYSMACRO(modfile_freadC)      },
    { "FWRITE"      , "IV++" , TYPE_INT         , SYSMACRO(modfile_fwrite)      },
    { "FWRITE"      , "PII"  , TYPE_INT         , SYSMACRO(modfile_fwriteC)     },
    { "FSEEK"       , "III"  , TYPE_INT         , SYSMACRO(modfile_fseek)       },
    { "FREWIND"     , "I"    , TYPE_UNDEFINED   , SYSMACRO(modfile_frewind)     },
    { "FTELL"       , "I"    , TYPE_INT         , SYSMACRO(modfile_ftell)       },
    { "FLENGTH"     , "I"    , TYPE_INT         , SYSMACRO(modfile_filelength)  },
    { "FPUTS"       , "IS"   , TYPE_INT         , SYSMACRO(modfile_fputs)       },
    { "FGETS"       , "I"    , TYPE_STRING      , SYSMACRO(modfile_fgets)       },
    { "FEOF"        , "I"    , TYPE_INT         , SYSMACRO(modfile_feof)        },
    { "FILE"        , "S"    , TYPE_STRING      , SYSMACRO(modfile_file)        },
    { "FEXISTS"     , "S"    , TYPE_INT         , SYSMACRO(modfile_exists)      } ,
    { "FILE_EXISTS" , "S"    , TYPE_INT         , SYSMACRO(modfile_exists)      } ,
    { "FREMOVE"     , "S"    , TYPE_INT         , SYSMACRO(modfile_remove)      } ,
    { "FMOVE"       , "SS"   , TYPE_INT         , SYSMACRO(modfile_move)        } ,
    { 0             , 0      , 0                , 0                   }
};


#endif