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
        #include <monolithic_includes.h>
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

#ifndef TARGET_BEOS
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

#ifdef TARGET_PSP
#define __PSP_fprintf fprintf
#else
#define __PSP_fprintf
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

static dlibhandle * dlibopen( const char * fname )
{
  int i=0;

    // Fake-load the library
    // What we're really doing is checking if the library name given to us is in the list
    // of supported modules, and return its place in the symbols array.

    // PSP
    __PSP_fprintf(stderr, "dlibopenning: %s\n", fname );

    while (symbol_list[i].module_name != NULL) {
        if(strncmp(fname, symbol_list[i].module_name,
          strlen(symbol_list[i].module_name)) == 0) {
            dlibhandle * dlib = (dlibhandle*) malloc( sizeof( dlibhandle ) );
            if ( !dlib )
            {
                printf("Couldn't allocate resources for fake-loading the module %s :(\n",
                       __dliberr);
				        return NULL;
			      }
			
      			dlib->index = i;
      			
            // PSP
            __PSP_fprintf( stderr, "dlibopen exiting...\n" );
            return ( dlib );
        }
		
		    i++;
	  }

    return NULL;
}

static void * _dlibaddr( dlibhandle * handle, const char * symbol )
{
    // PSP
    __PSP_fprintf(stderr, "Asked for symbol \"%s\" for library %s.\n", symbol,
	        symbol_list[handle->index].module_name);
	
    // Return the symbol they asked us for, or NULL
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
	
    // Unknown symbol, much probably an error in this implementation or a
    // change in the BennuGD ABI
    __PSP_fprintf(stderr, "Symbol %s is unknown, this is most likely a bug\n contact the author.\n", symbol);
#endif

    return NULL;
}

#endif //__MONOLITHIC__
#endif
