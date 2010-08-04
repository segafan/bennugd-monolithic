/*
 *  Copyright � 2006-2010 SplinterGU (Fenix/Bennugd)
 *
 *  This file is part of Bennu - Game Development
 *
 *  Bennu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Bennu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __MONOLITHIC_INCLUDES_H
#define __MONOLITHIC_INCLUDES_H

#include <libsdlhandler_symbols.h>
#include <libjoy_symbols.h>
#include <mod_say_symbols.h>
#include <mod_string_symbols.h>
#include <mod_math_symbols.h>
#include <mod_mathi_symbols.h>
#include <mod_time_symbols.h>
#include <mod_file_symbols.h>
#include <mod_sound_symbols.h>
#include <mod_joy_symbols.h>
#include <mod_proc_symbols.h>
#include <mod_sort_symbols.h>
#include <mod_timers_symbols.h>
#include <mod_regex_symbols.h>
#include <libgrbase_symbols.h>
#include <libblit_symbols.h>
#include <libvideo_symbols.h>
#include <librender_symbols.h>
#include <mod_video_symbols.h>
#include <libmouse_symbols.h>
#include <mod_mouse_symbols.h>
#include <mod_map_symbols.h>
#include <libfont_symbols.h>
#include <mod_dir_symbols.h>
#include <libtext_symbols.h>
#include <mod_text_symbols.h>
#include <mod_rand_symbols.h>
#include <mod_grproc_symbols.h>
#include <libscroll_symbols.h>
#include <mod_scroll_symbols.h>
#include <libkey_symbols.h>
#include <mod_key_symbols.h>
#include <mod_draw_symbols.h>
#include <mod_screen_symbols.h>
#include <mod_path_symbols.h>
#include <mod_effects_symbols.h>
#include <mod_blendop_symbols.h>
#include <mod_m7_symbols.h>
#include <libwm_symbols.h>
#include <mod_wm_symbols.h>
#include <mod_sys_symbols.h>
#include <mod_mem_symbols.h>
#include <mod_flic_symbols.h>
#include <mod_debug_symbols.h>
/* Unofficial modules */
#include <iconv_symbols.h>
#ifdef TARGET_WII
#include <mod_wpad_symbols.h>
#endif
//#include <image_symbols.h>
//#include <mod_sqlite3_symbols.h>

typedef struct
{
	char       * module_name;
	char       * modules_dependency;
	DLCONSTANT * constants_def;
	char       * types_def;
	char       * globals_def;
	char       * locals_def;
	DLSYSFUNCS * functions_exports;
} basic_symbols ;

#ifndef __BGDC__
typedef struct
{
	DLVARFIXUP    * globals_fixup;
	DLVARFIXUP    * locals_fixup;
	FN_HOOK         module_initialize;
	FN_HOOK         module_finalize;
	INSTANCE_HOOK   instance_create_hook;
	INSTANCE_HOOK   instance_destroy_hook;
	INSTANCE_HOOK   process_exec_hook;
	FN_HOOK       * handler_hooks;
} extra_symbols;
#endif

// Basic symbols used by the compiler and the runtime
basic_symbols symbol_list[] =
{
	// Libs go first, modules later
	{ "libsdlhandler.so", NULL, NULL, NULL, NULL, NULL, NULL },
	{ "libjoy.so"       , libjoy_modules_dependency, libjoy_constants_def, NULL, NULL, NULL, NULL },
	{ "libgrbase.so"    , NULL, NULL, NULL, libgrbase_globals_def, NULL, NULL },
	{ "libblit.so"      , NULL, libblit_constants_def, NULL, NULL, NULL, NULL },
	{ "libvideo.so"     , libvideo_modules_dependency, libvideo_constants_def, NULL, libvideo_globals_def, NULL, NULL },
	{ "librender.so"    , librender_modules_dependency, librender_constants_def, NULL, librender_globals_def, librender_locals_def, NULL },
	{ "libmouse.so"     , libmouse_modules_dependency, NULL, NULL, libmouse_globals_def, NULL, NULL },
	{ "libfont.so"      , libfont_modules_dependency, NULL, NULL, NULL, NULL, NULL },
	{ "libtext.so"      , libtext_modules_dependency, NULL, NULL, libtext_globals_def, NULL, NULL },
	{ "libscroll.so"    , libscroll_modules_dependency, libscroll_constants_def, NULL, libscroll_globals_def, libscroll_locals_def, NULL },
	{ "libkey.so"       , libkey_modules_dependency, libkey_constants_def, NULL, libkey_globals_def, NULL, NULL},
	{ "libdraw.so"      , NULL, NULL, NULL, NULL, NULL, NULL },
	{ "libwm.so"        , libwm_modules_dependency, NULL, NULL, libwm_globals_def, NULL, NULL },
	{ "mod_say.so"      , NULL, NULL, NULL, NULL, NULL, mod_say_functions_exports },
	{ "mod_string.so"   , NULL, NULL, NULL, NULL, NULL, mod_string_functions_exports },
	{ "mod_math.so"     , NULL, mod_math_constants_def, NULL, NULL, NULL, mod_math_functions_exports },
	{ "mod_mathi.so"    , NULL, mod_mathi_constants_def, NULL, NULL, NULL, mod_mathi_functions_exports },
	{ "mod_time.so"     , NULL, NULL, NULL, NULL, NULL, mod_time_functions_exports },
	{ "mod_file.so"     , NULL, mod_file_constants_def, NULL, NULL, NULL, mod_file_functions_exports },
	{ "mod_sound.so"    , NULL, mod_sound_constants_def, NULL, mod_sound_globals_def, NULL, mod_sound_functions_exports },
	{ "mod_joy.so"      , mod_joy_modules_dependency, NULL, NULL, NULL, NULL, mod_joy_functions_exports },
	{ "mod_proc.so"     , NULL, mod_proc_constants_def, NULL, NULL, mod_proc_locals_def, mod_proc_functions_exports },
	{ "mod_sort.so"     , NULL, NULL, NULL, NULL, NULL, mod_sort_functions_exports },
	{ "mod_timers.so"   , NULL, NULL, NULL, mod_timers_globals_def, NULL, NULL },
	{ "mod_regex.so"    , NULL, NULL, NULL, mod_regex_globals_def, NULL, mod_regex_functions_exports },
	{ "mod_video.so"    , mod_video_modules_dependency, NULL, NULL, NULL, NULL, mod_video_functions_exports },
	{ "mod_mouse.so"    , mod_mouse_modules_dependency, NULL, NULL, NULL, NULL, NULL },
	{ "mod_map.so"      , mod_map_modules_dependency, mod_map_constants_def, NULL, NULL, NULL, mod_map_functions_exports },
	{ "mod_dir.so"      , NULL, NULL, NULL, mod_dir_globals_def, NULL, mod_dir_functions_exports },
	{ "mod_text.so"     , mod_text_modules_dependency, mod_text_constants_def, NULL, NULL, NULL, mod_text_functions_exports },
	{ "mod_rand.so"     , NULL, NULL, NULL, NULL, NULL, mod_rand_functions_exports },
	{ "mod_grproc.so"   , mod_grproc_modules_dependency, NULL, NULL, NULL, mod_grproc_locals_def, mod_grproc_functions_exports },
	{ "mod_scroll.so"   , mod_scroll_modules_dependency, NULL, NULL, NULL, NULL, mod_scroll_functions_exports },
	{ "mod_key.so"      , mod_key_modules_dependency, NULL, NULL, NULL, NULL, mod_key_functions_exports },
	{ "mod_draw.so"     , mod_draw_modules_dependency, NULL, NULL, NULL, NULL, mod_draw_functions_exports },
	{ "mod_screen.so"   , mod_screen_modules_dependency, NULL, NULL, NULL, NULL, mod_screen_functions_exports },
	{ "mod_path.so"     , mod_path_modules_dependency, NULL, NULL, NULL, NULL, mod_path_functions_exports },
	{ "mod_effects.so"  , mod_effects_modules_dependency, mod_effects_constants_def, NULL, NULL, NULL, mod_effects_functions_exports },
	{ "mod_blendop.so"  , mod_blendop_modules_dependency, NULL, NULL, NULL, NULL, mod_blendop_functions_exports },
	{ "mod_m7.so"       , mod_m7_modules_dependency, mod_m7_constants_def, NULL, mod_m7_globals_def, mod_m7_locals_def, mod_m7_functions_exports },
	{ "mod_wm.so"       , NULL, NULL, NULL, NULL, NULL, NULL },
	{ "mod_sys.so"      , NULL, mod_sys_constants_def, NULL, NULL, NULL, mod_sys_functions_exports },
	{ "mod_mem.so"      , NULL, NULL, NULL, NULL, NULL, mod_mem_functions_exports },
	{ "mod_flic.so"     , NULL, NULL, NULL, NULL, NULL, mod_flic_functions_exports },
	{ "mod_debug.so"    , mod_debug_modules_dependency, NULL, NULL, NULL, NULL, NULL },
	/* Unofficial modules */
	{ "mod_iconv.so"    , NULL, NULL, NULL, NULL, NULL, mod_iconv_functions_exports },
#ifdef TARGET_WII
	{ "mod_wpad.so"     , mod_wpad_modules_dependency, mod_wpad_constants_def, NULL, NULL, NULL, mod_wpad_functions_exports },
#endif
	//{ "image.so"        , image_modules_dependency, NULL, NULL, NULL, NULL, image_functions_exports },
	//{ "mod_sqlite3.so"        , NULL, mod_sqlite3_constants_def, mod_sqlite3_types_def, NULL, NULL, mod_sqlite3_functions_exports },
	{ NULL              , NULL, NULL, NULL, NULL, NULL, NULL }
};

#ifndef __BGDC__
// Symbols only required by the runtime, ordered just as on symbol_list
// As a separate array to avoid compilation nightmares
extra_symbols symbol_list_runtime[] =
{
	{ NULL, NULL, libsdlhandler_module_initialize, libsdlhandler_module_finalize, NULL, NULL, NULL, libsdlhandler_handler_hooks },		//libsdlhandler
	{ NULL, NULL, libjoy_module_initialize, libjoy_module_finalize, NULL, NULL, NULL, NULL }, //libjoy
	{ libgrbase_globals_fixup, NULL, libgrbase_module_initialize, NULL, NULL, NULL, NULL, NULL }, //libgrbase
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //libblit
	{ libvideo_globals_fixup, NULL, libvideo_module_initialize, libvideo_module_finalize, NULL, NULL, NULL, NULL }, //libvideo
	{ librender_globals_fixup, librender_locals_fixup, librender_module_initialize, librender_module_finalize, librender_instance_create_hook, librender_instance_destroy_hook, NULL, librender_handler_hooks }, //librender
	{ libmouse_globals_fixup, NULL, libmouse_module_initialize, NULL, NULL, NULL, NULL, libmouse_handler_hooks}, //libmouse
	{ NULL, NULL, libfont_module_initialize, NULL, NULL, NULL, NULL, NULL }, //libfont
	{ libtext_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //libtext
	{ libscroll_globals_fixup, libscroll_locals_fixup, NULL, NULL, NULL, NULL, NULL, NULL }, //libscroll
	{ libkey_globals_fixup, NULL, libkey_module_initialize, libkey_module_finalize, NULL, NULL, NULL, libkey_handler_hooks }, //libkey
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //libdraw
	{ libwm_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, libwm_handler_hooks }, //libwm
	{ NULL, NULL, mod_say_module_initialize, NULL, NULL, NULL, NULL, NULL }, //mod_say
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_string
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_math
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_mathi
	{ NULL, NULL, mod_time_module_initialize, mod_time_module_finalize, NULL, NULL, NULL, NULL }, //mod_time
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_file
	{ mod_sound_globals_fixup, NULL, mod_sound_module_initialize, mod_sound_module_finalize, NULL, NULL, NULL, NULL}, //mod_sound
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_joy
	{ NULL, mod_proc_locals_fixup, NULL, NULL, NULL, NULL, mod_proc_process_exec_hook, NULL}, //mod_proc
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_sort
	{ mod_timers_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, mod_timers_handler_hooks }, //mod_timers
	{ mod_regex_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_regex
	{ mod_video_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_video
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_mouse
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_map
	{ mod_dir_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_dir
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_text
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_rand
	{ mod_grproc_globals_fixup, mod_grproc_locals_fixup, mod_grproc_module_initialize, NULL, NULL, NULL, mod_grproc_process_exec_hook, NULL }, //mod_grproc
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_scroll
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_key
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_draw
	{ mod_screen_globals_fixup, mod_screen_locals_fixup, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_screen
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_path
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_effects
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_blendop
	{ mod_m7_globals_fixup, mod_m7_locals_fixup, mod_m7_module_initialize, NULL, NULL, NULL, NULL, NULL }, //mod_m7
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_wm
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_sys
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_mem
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_flic
	{ mod_debug_globals_fixup, mod_debug_locals_fixup, mod_debug_module_initialize, mod_debug_module_finalize, NULL, NULL, mod_debug_process_exec_hook, NULL }, //mod_debug
	/* Unofficial modules */
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_iconv
#ifdef TARGET_WII
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_wpad
#endif
	//{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_image
	//{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_sqlite3
};
#endif

#endif
