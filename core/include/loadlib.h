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

#ifndef _LOADLIB_H
#define _LOADLIB_H

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#else
#define _GNU_SOURCE
#ifndef __MONOLITHIC__
#include <dlfcn.h>
#else
#include <libsdlhandler_symbols.h>
#include <libjoy_symbols.h>
#include <mod_say_symbols.h>
#include <mod_string_symbols.h>
#include <mod_math_symbols.h>
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
#endif
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define __stdcall
#define __dllexport
#define __dllimport
#endif

#ifdef _WIN32
#define dlclose(a)
#endif

// This first part handles systems where dynamic library opening is posible
#ifndef __MONOLITHIC__
typedef struct
{
    char * fname;
    void * hnd;
} dlibhandle ;

static char * __dliberr = NULL;

static char * dliberror( void )
{
    return __dliberr;
}

static int dlibclose( dlibhandle * handle )
{
    dlclose( handle->hnd );
    free( handle->fname );
    free( handle );

    return 0;
}

static dlibhandle * dlibopen( const char * fname )
{
#ifdef _WIN32
    void * hnd = LoadLibrary( fname );
#else
    void * hnd = dlopen( fname, RTLD_NOW | RTLD_GLOBAL );
#endif
    if ( !hnd )
    {
#ifdef _WIN32
        __dliberr = "Could not load library." ;
#else
        __dliberr = dlerror() ;
#endif
        printf("%s\n", __dliberr);
        return NULL;
    }

    {
        dlibhandle * dlib = (dlibhandle*) malloc( sizeof( dlibhandle ) );
        if ( !dlib )
        {
            __dliberr = "Could not load library." ;
            dlclose( hnd );
            return NULL;
        }

        dlib->fname = strdup( fname );
        if ( !dlib->fname )
        {
            __dliberr = "Could not load library." ;
            free( dlib );
            dlclose( hnd );
            return NULL;
        }

        dlib->hnd = hnd;

        return ( dlib );
    }
}

static void * dlibaddr( dlibhandle * handle, const char * symbol )
{
    char * ptr, * f;

#ifdef _WIN32
    void * addr = GetProcAddress( (HMODULE)handle->hnd, symbol );
    if ( !addr )
    {
        __dliberr = "Symbol not found." ;
        return NULL;
    }
#else
    void * addr = dlsym( handle->hnd, symbol ) ;

    if ( !addr )
    {
        __dliberr = dlerror() ;
        return NULL;
    }
    {
        Dl_info dli;
        dladdr( addr, &dli );

        ptr = ( char * ) dli.dli_fname; f = NULL;
        /*
            printf( "dli_fname=%s\n", dli.dli_fname );
            printf( "dli_fbase=%p\n", dli.dli_fbase );
            printf( "dli_sname=%s\n", dli.dli_sname );
            printf( "dli_saddr=%p\n", dli.dli_saddr );
        */
    }
    while ( *ptr )
    {
        if ( *ptr == '/' || *ptr == '\\' ) f = ptr ;
        ptr++;
    }
    if ( f ) ptr = f + 1;

    if ( strcmp( ptr, handle->fname ) )
    {
        __dliberr = "Symbol not found." ;
        return NULL;
    }
#endif
/*
    printf( "[%s:%s]->%p\n", handle->fname, symbol, addr );fflush( stdout );
*/

    return addr;
}

static void * _dlibaddr( dlibhandle * handle, const char * symbol )
{
    char * ptr, * f;
    char * sym = (char*)malloc( strlen( handle->fname ) + strlen( symbol ) + 2 );
    if ( !sym )
    {
        __dliberr = "Can't load symbol." ;
        return NULL;
    }

    strcpy( sym, handle->fname );
    ptr = ( char * ) sym; f = NULL;
    while ( *ptr )
    {
        if ( *ptr == '.' ) f = ptr ;
        ptr++;
    }

    if ( f ) *f = '\0';
    strcat( sym, "_" ); strcat( sym, symbol );

    {
        void * addr = dlibaddr( handle, sym );
        free( sym );
        return addr;
    }
}

// This second part handles systems with monolithic builds (ie: no dlopen)
#else

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

typedef struct
{
    int index;
} dlibhandle ;

static char * __dliberr = NULL;

static char * dliberror( void )
{
    return __dliberr;
}

static int dlibclose( dlibhandle * handle )
{
    handle->index=0;
    return 0;
}

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
	{ "mod_say.so"      , NULL, NULL, NULL, NULL, NULL, mod_say_functions_exports },
	{ "mod_string.so"   , NULL, NULL, NULL, NULL, NULL, mod_string_functions_exports },
	{ "mod_math.so"     , NULL, mod_math_constants_def, NULL, NULL, NULL, mod_math_functions_exports },
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
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_say
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_string
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_math
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
};
#endif

static dlibhandle * dlibopen( const char * fname )
{
	int i=0;

    // Fake-load the library
    // What we're really doing is checking if the library name given to us is in the list
	// of supported modules, and return its place in the symbols array.
	while (symbol_list[i].module_name != NULL) {
		if(strncmp(fname, symbol_list[i].module_name, strlen(symbol_list[i].module_name)) == 0) {
			dlibhandle * dlib = (dlibhandle*) malloc( sizeof( dlibhandle ) );
			if ( !dlib )
			{
				printf("Couldn't allocate resources for fake-loading the module %s :(\n", __dliberr);
				return NULL;
			}
			
			dlib->index = i;
			
			return ( dlib );
		}
		
		i++;
	}

    return NULL;
}

static void * _dlibaddr( dlibhandle * handle, const char * symbol )
{
	// Only for debugging purposes
	//printf("Asked for symbol \"%s\" for library %s.\n", symbol, symbol_list[handle->index].module_name);
	
	// Return the symbol they asked us, or NULL
	if(strncmp(symbol, "modules_dependency", strlen("modules_dependency")) == 0)
		return symbol_list[handle->index].modules_dependency;
	
	if(strncmp(symbol, "constants_def", strlen("constants_def")) == 0)
		return symbol_list[handle->index].constants_def;
	
	if(strncmp(symbol, "types_def", strlen("types_def")) == 0)
		return &symbol_list[handle->index].types_def;
	
	if(strncmp(symbol, "globals_def", strlen("globals_def")) == 0)
		return &symbol_list[handle->index].globals_def;
	
	if(strncmp(symbol, "locals_def", strlen("locals_def")) == 0)
		return &symbol_list[handle->index].locals_def;
	
	if(strncmp(symbol, "functions_exports", strlen("functions_exports")) == 0)
		return symbol_list[handle->index].functions_exports;

#ifndef __BGDC__
	if(strncmp(symbol, "globals_fixup", strlen("globals_fixup")) == 0)
		return symbol_list_runtime[handle->index].globals_fixup;
	
	if(strncmp(symbol, "locals_fixup", strlen("locals_fixup")) == 0)
		return symbol_list_runtime[handle->index].locals_fixup;
	
	if(strncmp(symbol, "module_initialize", strlen("module_initialize")) == 0)
		return symbol_list_runtime[handle->index].module_initialize;
	
	if(strncmp(symbol, "module_finalize", strlen("module_finalize")) == 0)
		return symbol_list_runtime[handle->index].module_finalize;
	
	if(strncmp(symbol, "instance_create_hook", strlen("instance_create_hook")) == 0)
		return symbol_list_runtime[handle->index].instance_create_hook;
	
	if(strncmp(symbol, "instance_destroy_hook", strlen("instance_destroy_hook")) == 0)
		return symbol_list_runtime[handle->index].instance_destroy_hook;
	
	if(strncmp(symbol, "process_exec_hook", strlen("process_exec_hook")) == 0)
		return symbol_list_runtime[handle->index].process_exec_hook;
	
	if(strncmp(symbol, "handler_hooks", strlen("handler_hooks")) == 0)
		return symbol_list_runtime[handle->index].handler_hooks;
	
	// Unknown symbol, much probably an error in this implementation or a change in the BennuGD ABI
	// fprintf(stderr, "Symbol %s is unknown to me, this is most likely a bug\n contact the author.\n", symbol);
#endif

    return NULL;
}

#endif //__MONOLITHIC__
#endif
