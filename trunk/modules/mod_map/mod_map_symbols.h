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

#ifndef __MODMAP_SYMBOLS_H
#define __MODMAP_SYMBOLS_H

#include <bgddl.h>
#include "mod_map.h"

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modmap_graphic_set( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_graphic_info( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_set_point( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_set_center( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_get_point( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_load_png( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_load_pcx( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_save_png( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_buffer( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_clear( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_new_map( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_new_map_extend( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_clone( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_put( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_xput( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_xputnp( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_name( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_set_name( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_exists( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_map_block_copy( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_load_map( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_unload_map( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_save_map( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_load_pal( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_save_pal( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_save_system_pal( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_convert_palette( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_set_colors( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_get_colors( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_roll_palette( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_find_color( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_get_rgb( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_get_rgba( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_rgb( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_rgba( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_get_rgb_depth( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_get_rgba_depth( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_rgb_depth( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_rgba_depth( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fade( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fade_on( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fade_off( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_create( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_clone( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_unload( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_refresh( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_refresh_2( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_map_assign( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_map_remove( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_map_getid( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_set_system_pal( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_set_system_pal_raw( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_set( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_pal_get( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_load_fpg( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_save_fpg( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_unload_fpg( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fpg_exists( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fpg_add( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fpg_new( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_bgload_fpg( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_load_fnt( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_load_bdf( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_unload_fnt( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fnt_new( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fnt_new_charset( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_fnt_new_from_bitmap( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_get_glyph( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_set_glyph( INSTANCE * my, int * params );
extern CONDITIONALLY_STATIC int modmap_save_fnt( INSTANCE * my, int * params );
#endif

/* --------------------------------------------------------------------------- */

DLCONSTANT __bgdexport( mod_map, constants_def )[] =
{
    { "G_WIDE",         TYPE_INT,   G_WIDE      },    /* Obsolete */
    { "G_WIDTH",        TYPE_INT,   G_WIDTH     },
    { "G_HEIGHT",       TYPE_INT,   G_HEIGHT    },
    { "G_CENTER_X",     TYPE_INT,   G_CENTER_X  },
    { "G_X_CENTER",     TYPE_INT,   G_X_CENTER  },
    { "G_CENTER_Y",     TYPE_INT,   G_CENTER_Y  },
    { "G_Y_CENTER",     TYPE_INT,   G_Y_CENTER  },
    { "G_PITCH",        TYPE_INT,   G_PITCH     },
    { "G_DEPTH",        TYPE_INT,   G_DEPTH     },

    { "B_CLEAR",        TYPE_INT,   B_CLEAR     },

    { NULL              , 0       , 0           }
} ;

/* --------------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_map, functions_exports )[] =
{
    /* Bitmaps */
    { "MAP_BLOCK_COPY"      , "IIIIIIIIII"  , TYPE_INT      , SYSMACRO(modmap_map_block_copy)     },
    { "MAP_PUT"             , "IIIII"       , TYPE_INT      , SYSMACRO(modmap_map_put)            },
    { "MAP_XPUT"            , "IIIIIIII"    , TYPE_INT      , SYSMACRO(modmap_map_xput)           },
    { "MAP_NEW"             , "III"         , TYPE_INT      , SYSMACRO(modmap_new_map)            },
    { "MAP_NEW"             , "IIII"        , TYPE_INT      , SYSMACRO(modmap_new_map_extend)     },
    { "MAP_CLEAR"           , "III"         , TYPE_INT      , SYSMACRO(modmap_map_clear)          },
    { "MAP_CLONE"           , "II"          , TYPE_INT      , SYSMACRO(modmap_map_clone)          },
    { "MAP_NAME"            , "II"          , TYPE_STRING   , SYSMACRO(modmap_map_name)           },
    { "MAP_SET_NAME"        , "IIS"         , TYPE_INT      , SYSMACRO(modmap_map_set_name)       },
    { "MAP_EXISTS"          , "II"          , TYPE_INT      , SYSMACRO(modmap_map_exists)         },
    { "MAP_XPUTNP"          , "IIIIIIIIII"  , TYPE_INT      , SYSMACRO(modmap_map_xputnp)         },
    { "MAP_DEL"             , "II"          , TYPE_INT      , SYSMACRO(modmap_unload_map)         },
    { "MAP_UNLOAD"          , "II"          , TYPE_INT      , SYSMACRO(modmap_unload_map)         },
    { "MAP_LOAD"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_map)           },
    { "MAP_SAVE"            , "IIS"         , TYPE_INT      , SYSMACRO(modmap_save_map)           },
    { "MAP_BUFFER"          , "II"          , TYPE_POINTER  , SYSMACRO(modmap_map_buffer)         },

    /* FPG */
    { "FPG_ADD"             , "IIII"        , TYPE_INT      , SYSMACRO(modmap_fpg_add)            },
    { "FPG_NEW"             , ""            , TYPE_INT      , SYSMACRO(modmap_fpg_new)            },
    { "FPG_EXISTS"          , "I"           , TYPE_INT      , SYSMACRO(modmap_fpg_exists)         },
    { "FPG_LOAD"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_fpg)           },
    { "FPG_LOAD"            , "SP"          , TYPE_INT      , SYSMACRO(modmap_bgload_fpg)         },
    { "FPG_SAVE"            , "IS"          , TYPE_INT      , SYSMACRO(modmap_save_fpg)           },
    { "FPG_DEL"             , "I"           , TYPE_INT      , SYSMACRO(modmap_unload_fpg)         },
    { "FPG_UNLOAD"          , "I"           , TYPE_INT      , SYSMACRO(modmap_unload_fpg)         },

    /* Palette */
    { "PAL_NEW"             , ""            , TYPE_INT      , SYSMACRO(modmap_pal_create)         },
    { "PAL_DEL"             , "I"           , TYPE_INT      , SYSMACRO(modmap_pal_unload)         },
    { "PAL_UNLOAD"          , "I"           , TYPE_INT      , SYSMACRO(modmap_pal_unload)         },
    { "PAL_CLONE"           , "I"           , TYPE_INT      , SYSMACRO(modmap_pal_clone)          },
    { "PAL_REFRESH"         , ""            , TYPE_INT      , SYSMACRO(modmap_pal_refresh)        },
    { "PAL_REFRESH"         , "I"           , TYPE_INT      , SYSMACRO(modmap_pal_refresh_2)      },
    { "PAL_MAP_GETID"       , "II"          , TYPE_INT      , SYSMACRO(modmap_pal_map_getid)      },
    { "PAL_MAP_ASSIGN"      , "III"         , TYPE_INT      , SYSMACRO(modmap_pal_map_assign)     },
    { "PAL_MAP_REMOVE"      , "II"          , TYPE_INT      , SYSMACRO(modmap_pal_map_remove)     },
    { "PAL_GET"             , "IIP"         , TYPE_INT      , SYSMACRO(modmap_get_colors)         },
    { "PAL_GET"             , "IIIP"        , TYPE_INT      , SYSMACRO(modmap_pal_get)            },
    { "PAL_SYS_SET"         , "I"           , TYPE_INT      , SYSMACRO(modmap_set_system_pal)     },
    { "PAL_SYS_SET"         , "P"           , TYPE_INT      , SYSMACRO(modmap_set_system_pal_raw) },
    { "PAL_SET"             , "IIP"         , TYPE_INT      , SYSMACRO(modmap_set_colors)         },
    { "PAL_SET"             , "IIIP"        , TYPE_INT      , SYSMACRO(modmap_pal_set)            },
    { "PAL_SAVE"            , "S"           , TYPE_INT      , SYSMACRO(modmap_save_system_pal)    },
    { "PAL_SAVE"            , "SI"          , TYPE_INT      , SYSMACRO(modmap_save_pal)           },
    { "PAL_LOAD"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_pal)           },

    { "COLORS_SET"          , "IIP"         , TYPE_INT      , SYSMACRO(modmap_set_colors)         },
    { "COLORS_SET"          , "IIIP"        , TYPE_INT      , SYSMACRO(modmap_pal_set)            },
    { "COLORS_GET"          , "IIP"         , TYPE_INT      , SYSMACRO(modmap_get_colors)         },
    { "COLORS_GET"          , "IIIP"        , TYPE_INT      , SYSMACRO(modmap_pal_get)            },

    { "PALETTE_ROLL"        , "III"         , TYPE_INT      , SYSMACRO(modmap_roll_palette)       },
    { "PALETTE_CONVERT"     , "IIP"         , TYPE_INT      , SYSMACRO(modmap_convert_palette)    },

    { "COLOR_FIND"          , "BBB"         , TYPE_INT      , SYSMACRO(modmap_find_color)         },

    { "RGB"                 , "BBBI"        , TYPE_INT      , SYSMACRO(modmap_rgb_depth)          },
    { "RGBA"                , "BBBBI"       , TYPE_INT      , SYSMACRO(modmap_rgba_depth)         },
    { "RGB_GET"             , "IPPPI"       , TYPE_INT      , SYSMACRO(modmap_get_rgb_depth)      },
    { "RGBA_GET"            , "IPPPPI"      , TYPE_INT      , SYSMACRO(modmap_get_rgba_depth)     },

    { "RGB"                 , "BBB"         , TYPE_INT      , SYSMACRO(modmap_rgb)                },
    { "RGBA"                , "BBBB"        , TYPE_INT      , SYSMACRO(modmap_rgba)               },
    { "RGB_GET"             , "IPPP"        , TYPE_INT      , SYSMACRO(modmap_get_rgb)            },
    { "RGBA_GET"            , "IPPPP"       , TYPE_INT      , SYSMACRO(modmap_get_rgba)           },

    { "FADE"                , "IIII"        , TYPE_INT      , SYSMACRO(modmap_fade)               },
    { "FADE_ON"             , ""            , TYPE_INT      , SYSMACRO(modmap_fade_on)            },
    { "FADE_OFF"            , ""            , TYPE_INT      , SYSMACRO(modmap_fade_off)           },

    /* Informacion de graficos */
    { "MAP_INFO_SET"        , "IIII"        , TYPE_INT      , SYSMACRO(modmap_graphic_set)        },
    { "MAP_INFO_GET"        , "III"         , TYPE_INT      , SYSMACRO(modmap_graphic_info)       },
    { "MAP_INFO"            , "III"         , TYPE_INT      , SYSMACRO(modmap_graphic_info)       },

    { "GRAPHIC_SET"         , "IIII"        , TYPE_INT      , SYSMACRO(modmap_graphic_set)        },
    { "GRAPHIC_INFO"        , "III"         , TYPE_INT      , SYSMACRO(modmap_graphic_info)       },

    /* Puntos de control */
    { "POINT_GET"           , "IIIPP"       , TYPE_INT      , SYSMACRO(modmap_get_point)          },
    { "POINT_SET"           , "IIIII"       , TYPE_INT      , SYSMACRO(modmap_set_point)          },

    { "CENTER_SET"          , "IIII"        , TYPE_INT      , SYSMACRO(modmap_set_center)         },

    /* Fonts */
    { "FNT_LOAD"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_fnt)           },
    { "FNT_UNLOAD"          , "I"           , TYPE_INT      , SYSMACRO(modmap_unload_fnt)         },
    { "FNT_SAVE"            , "IS"          , TYPE_INT      , SYSMACRO(modmap_save_fnt)           },
    { "FNT_NEW"             , "I"           , TYPE_INT      , SYSMACRO(modmap_fnt_new)            },
    { "FNT_NEW"             , "II"          , TYPE_INT      , SYSMACRO(modmap_fnt_new_charset)    },
    { "FNT_NEW"             , "IIIIIIII"    , TYPE_INT      , SYSMACRO(modmap_fnt_new_from_bitmap)},

    { "BDF_LOAD"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_bdf)           },

    { "GLYPH_GET"           , "II"          , TYPE_INT      , SYSMACRO(modmap_get_glyph)          },
    { "GLYPH_SET"           , "IIII"        , TYPE_INT      , SYSMACRO(modmap_set_glyph)          },

    /* Importacion de archivos graficos */
    { "PNG_LOAD"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_png)           },
    { "PCX_LOAD"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_pcx)           },

    /* Exportacion de mapas Graficos */
    { "PNG_SAVE"            , "IIS"         , TYPE_INT      , SYSMACRO(modmap_save_png)           },

    /* ------------ Compatibility ------------ */

    /* Mapas */
    { "NEW_MAP"             , "III"         , TYPE_INT      , SYSMACRO(modmap_new_map)            },
    { "LOAD_MAP"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_map)           },
    { "UNLOAD_MAP"          , "II"          , TYPE_INT      , SYSMACRO(modmap_unload_map)         },
    { "SAVE_MAP"            , "IIS"         , TYPE_INT      , SYSMACRO(modmap_save_map)           },

    /* Palette */
    { "NEW_PAL"             , ""            , TYPE_INT      , SYSMACRO(modmap_pal_create)         },
    { "LOAD_PAL"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_pal)           },
    { "UNLOAD_PAL"          , "I"           , TYPE_INT      , SYSMACRO(modmap_pal_unload)         },
    { "SAVE_PAL"            , "S"           , TYPE_INT      , SYSMACRO(modmap_save_system_pal)    },
    { "SAVE_PAL"            , "SI"          , TYPE_INT      , SYSMACRO(modmap_save_pal)           },
    { "SET_COLORS"          , "IIP"         , TYPE_INT      , SYSMACRO(modmap_set_colors)         },
    { "SET_COLORS"          , "IIIP"        , TYPE_INT      , SYSMACRO(modmap_pal_set)            },
    { "GET_COLORS"          , "IIP"         , TYPE_INT      , SYSMACRO(modmap_get_colors)         },
    { "GET_COLORS"          , "IIIP"        , TYPE_INT      , SYSMACRO(modmap_pal_get)            },
    { "ROLL_PALETTE"        , "III"         , TYPE_INT      , SYSMACRO(modmap_roll_palette)       },
    { "CONVERT_PALETTE"     , "IIP"         , TYPE_INT      , SYSMACRO(modmap_convert_palette)    },
    { "FIND_COLOR"          , "BBB"         , TYPE_INT      , SYSMACRO(modmap_find_color)         },
    { "GET_RGB"             , "IPPPI"       , TYPE_INT      , SYSMACRO(modmap_get_rgb_depth)      },
    { "GET_RGBA"            , "IPPPPI"      , TYPE_INT      , SYSMACRO(modmap_get_rgba_depth)     },
    { "GET_RGB"             , "IPPP"        , TYPE_INT      , SYSMACRO(modmap_get_rgb)            },
    { "GET_RGBA"            , "IPPPP"       , TYPE_INT      , SYSMACRO(modmap_get_rgba)           },

    /* FPG */
    { "NEW_FPG"             , ""            , TYPE_INT      , SYSMACRO(modmap_fpg_new)            },
    { "LOAD_FPG"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_fpg)           },
    { "LOAD_FPG"            , "SP"          , TYPE_INT      , SYSMACRO(modmap_bgload_fpg)         },
    { "SAVE_FPG"            , "IS"          , TYPE_INT      , SYSMACRO(modmap_save_fpg)           },
    { "UNLOAD_FPG"          , "I"           , TYPE_INT      , SYSMACRO(modmap_unload_fpg)         },

    /* Puntos de control */
    { "GET_POINT"           , "IIIPP"       , TYPE_INT      , SYSMACRO(modmap_get_point)          },
    { "SET_POINT"           , "IIIII"       , TYPE_INT      , SYSMACRO(modmap_set_point)          },
    { "SET_CENTER"          , "IIII"        , TYPE_INT      , SYSMACRO(modmap_set_center)         },

    /* Fonts */
    { "NEW_FNT"             , "I"           , TYPE_INT      , SYSMACRO(modmap_fnt_new)            },
    { "LOAD_FNT"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_fnt)           },
    { "UNLOAD_FNT"          , "I"           , TYPE_INT      , SYSMACRO(modmap_unload_fnt)         },
    { "SAVE_FNT"            , "IS"          , TYPE_INT      , SYSMACRO(modmap_save_fnt)           },
    { "LOAD_BDF"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_bdf)           },
    { "GET_GLYPH"           , "II"          , TYPE_INT      , SYSMACRO(modmap_get_glyph)          },
    { "SET_GLYPH"           , "IIII"        , TYPE_INT      , SYSMACRO(modmap_set_glyph)          },

    /* Importacion de archivos graficos */
    { "LOAD_PNG"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_png)           },
    { "LOAD_PCX"            , "S"           , TYPE_INT      , SYSMACRO(modmap_load_pcx)           },

    /* Exportacion de mapas Graficos */
    { "SAVE_PNG"            , "IIS"         , TYPE_INT      , SYSMACRO(modmap_save_png)           },

    { 0                     , 0             , 0             , 0                         }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_map, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "libblit",
    "libfont",
    NULL
};

/* --------------------------------------------------------------------------- */

#endif
