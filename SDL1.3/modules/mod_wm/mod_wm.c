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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgddl.h"
#include "bgdrtm.h"
#include "xstrings.h"

#include "libgrbase.h"
#include "libvideo.h"

#ifdef TARGET_MAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#if defined( WIN32 ) || ( __linux && ( defined( SDL_VIDEO_DRIVER_X11 ) ) )
#include <SDL_syswm.h>
#endif

/* --------------------------------------------------------------------------- */
/* Window Manager                                                              */
/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int bgd_set_title( INSTANCE * my, int * params )
{
    gr_set_caption( ( char * )string_get( params[0] ) ) ;
    return 1 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int bgd_set_icon( INSTANCE * my, int * params )
{
    gr_set_icon( bitmap_get( params[0], params[1] ) );
    return 1 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int bgd_minimize( INSTANCE * my, int * params )
{
    return SDL_WM_IconifyWindow();
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int bgd_move_window( INSTANCE * my, int * params )
{
    int res = 0;
    if ( full_screen ) return 0;

#if SDL_VERSION_ATLEAST(1,3,0)
    SDL_SetWindowPosition(SDL_GetWindowFromID(0), params[0], params[1]);
#else

#   if defined( WIN32 ) || ( __linux && ( defined( SDL_VIDEO_DRIVER_X11 ) ) )
    SDL_SysWMinfo wminfo ;

    SDL_VERSION( &wminfo.version );
    if ( SDL_GetWMInfo( &wminfo ) != 1 ) return 0 ;
#   endif


#   ifdef WIN32
    /* Set the new window position */
    res = SetWindowPos(
                wminfo.window,     // handle to window
                HWND_NOTOPMOST,    // Possibly will have no effect... it stays below top-most
                params[0],          // horizontal position
                params[1],          // vertical position
                0,                  // keep the old window width
                0,                  // keep the old window height
                SWP_SHOWWINDOW | SWP_NOSIZE // Make it visible and retain size
            ) ;
#   elif __linux
#       ifdef SDL_VIDEO_DRIVER_X11
    Window root, parent, *children = NULL;
    unsigned int children_count;

    if ( wminfo.subsystem == SDL_SYSWM_X11 )
    {
        if ( XQueryTree( wminfo.info.x11.display, wminfo.info.x11.window, &root, &parent, &children, &children_count ) != BadWindow )
        {
            wminfo.info.x11.lock_func();
            res = XMoveWindow( wminfo.info.x11.display, parent, params[0], params[1] );
            XMapRaised(wminfo.info.x11.display, parent); /* Show Window */
            wminfo.info.x11.unlock_func();
            if ( children ) XFree( children );
        }
    }
#       endif
#   endif
#endif

    // Missing BeOS & MAC support
    return res ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int bgd_get_window_pos( INSTANCE * my, int * params )
{
    if ( full_screen ) return -1;

#if SDL_VERSION_ATLEAST(1,3,0)
    int x,y;

    SDL_GetWindowPosition(SDL_GetWindowFromID(0), &x, &y );
    if ( params[0] ) *(( int * )( params[0] ) ) = x;
    if ( params[1] ) *(( int * )( params[1] ) ) = y;
#else

#   if defined( WIN32 ) || ( __linux && ( defined( SDL_VIDEO_DRIVER_X11 ) ) )
    SDL_SysWMinfo wminfo ;

    SDL_VERSION( &wminfo.version );
    if ( SDL_GetWMInfo( &wminfo ) != 1 ) return -1 ;
#   endif

#   ifdef WIN32
    RECT Rect;

    if ( GetWindowRect( wminfo.window, &Rect ) )
    {
        if ( params[0] ) *(( int * )( params[0] ) ) = Rect.left;
        if ( params[1] ) *(( int * )( params[1] ) ) = Rect.top;
    }
#   elif __linux
#       ifdef SDL_VIDEO_DRIVER_X11
    Window root, parent, *children = NULL;
    unsigned int children_count;
    XWindowAttributes wattr;
    int res ;

    wminfo.info.x11.lock_func();
    if ( XQueryTree( wminfo.info.x11.display, wminfo.info.x11.window, &root, &parent, &children, &children_count ) != BadWindow )
    {
        if ( children ) XFree( children );

        if ( XQueryTree( wminfo.info.x11.display, parent, &root, &parent, &children, &children_count ) != BadWindow )
        {
            if ( children ) XFree( children );

            res = XGetWindowAttributes( wminfo.info.x11.display, parent, &wattr );
            if ( res != BadDrawable && res != BadWindow )
            {
                if ( params[0] ) *(( int * )( params[0] ) ) = wattr.x;
                if ( params[1] ) *(( int * )( params[1] ) ) = wattr.y;
            }
        }
    }
    wminfo.info.x11.unlock_func();
#       endif
#   endif
#endif
    return 1 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int bgd_get_window_size( INSTANCE * my, int * params )
{
#if SDL_VERSION_ATLEAST(1,3,0)
    int w,h;

    SDL_GetWindowSize(SDL_GetWindowFromID(0), &w, &h );
    if ( params[0] ) *(( int * )( params[0] ) ) = w;
    if ( params[1] ) *(( int * )( params[1] ) ) = h;
    //FIXME: Get this working
    if ( params[2] ) *(( int * )( params[2] ) ) = w;
    if ( params[3] ) *(( int * )( params[3] ) ) = h;    
#else

#   if defined( WIN32 ) || ( __linux && ( defined( SDL_VIDEO_DRIVER_X11 ) ) )
    SDL_SysWMinfo wminfo ;

    SDL_VERSION( &wminfo.version );
    if ( SDL_GetWMInfo( &wminfo ) != 1 ) return -1 ;
#   endif

#   ifdef WIN32
    RECT Rect;

    if ( GetWindowRect( wminfo.window, &Rect ) )
    {
        if ( params[0] ) *(( int * )( params[0] ) ) = Rect.right - Rect.left;
        if ( params[1] ) *(( int * )( params[1] ) ) = Rect.bottom - Rect.top;

        if ( GetClientRect( wminfo.window, &Rect ) )
        {
            if ( params[2] ) *(( int * )( params[2] ) ) = Rect.right - Rect.left;
            if ( params[3] ) *(( int * )( params[3] ) ) = Rect.bottom - Rect.top;
        }
    }
#   elif __linux
#       ifdef SDL_VIDEO_DRIVER_X11
    int res ;
    XWindowAttributes wattr;

    Window root, parent, *children = NULL;
    unsigned int children_count;

    wminfo.info.x11.lock_func();
    if ( XQueryTree( wminfo.info.x11.display, wminfo.info.x11.window, &root, &parent, &children, &children_count ) != BadWindow )
    {
        if ( children ) XFree( children );

        res = XGetWindowAttributes( wminfo.info.x11.display, parent, &wattr );
        if ( res != BadDrawable && res != BadWindow )
        {
            if ( params[2] ) *(( int * )( params[2] ) ) = wattr.width;
            if ( params[3] ) *(( int * )( params[3] ) ) = wattr.height;

            if ( XQueryTree( wminfo.info.x11.display, parent, &root, &parent, &children, &children_count ) != BadWindow )
            {
                if ( children ) XFree( children );

                res = XGetWindowAttributes( wminfo.info.x11.display, parent, &wattr );
                if ( res != BadDrawable && res != BadWindow )
                {
                    if ( params[0] ) *(( int * )( params[0] ) ) = wattr.width;
                    if ( params[1] ) *(( int * )( params[1] ) ) = wattr.height;
                }
            }
        }
    }
    wminfo.info.x11.unlock_func();
#       endif
#   endif
#endif

    return 1 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int bgd_get_desktop_size( INSTANCE * my, int * params )
{
#if SDL_VERSION_ATLEAST(1,3,0)
    SDL_DisplayMode * mode;
    
    if(SDL_GetDesktopDisplayMode(mode) == -1 ) return -1;

    if ( params[0] ) *(( int * )( params[0] ) ) = mode->w;
    if ( params[1] ) *(( int * )( params[1] ) ) = mode->h;
#else
#   ifdef WIN32
    RECT Rect;

    if ( GetClientRect( GetDesktopWindow(), &Rect ) )
    {
        *(( int * )( params[0] ) ) = Rect.right - Rect.left;
        *(( int * )( params[1] ) ) = Rect.bottom - Rect.top;
    }
#   elif __linux
#       ifdef SDL_VIDEO_DRIVER_X11
    int res ;
    Window root, parent, *children = NULL;
    XWindowAttributes wattr;
    unsigned int children_count;

    SDL_SysWMinfo wminfo ;

    SDL_VERSION( &wminfo.version );
    if ( SDL_GetWMInfo( &wminfo ) != 1 ) return -1 ;

    wminfo.info.x11.lock_func();
    if ( XQueryTree(wminfo.info.x11.display, wminfo.info.x11.window, &root, &parent, &children, &children_count ) != BadWindow )
    {
        if ( children ) XFree( children );

        res = XGetWindowAttributes( wminfo.info.x11.display, root, &wattr );
        if ( res != BadDrawable && res != BadWindow )
        {
            if ( params[0] ) *(( int * )( params[0] ) ) = wattr.width;
            if ( params[1] ) *(( int * )( params[1] ) ) = wattr.height;
        }
    }
    wminfo.info.x11.unlock_func();
#       endif
#   elif defined(TARGET_WII)
    // Not really returning desktop size, but at least a mode the user
    // can set_mode
    SDL_Surface* screen = NULL;
    
    screen = SDL_GetVideoSurface();
    if ( params[0] ) *(( int * )( params[0] ) ) = screen->w;
    if ( params[1] ) *(( int * )( params[1] ) ) = screen->h;
#   endif

#endif
    return 1 ;
}

/* --------------------------------------------------------------------------- */
