/*
 Simple DirectMedia Layer
 Copyright (C) 1997-2012 Sam Lantinga <slouken@libsdl.org>
 
 This software is provided 'as-is', without any express or implied
 warranty.  In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 */


/**
 *  g_compat.c
 *
 *  This file contains functions for backwards compatibility with SDL 1.2
 *  for a very limited set of tasks. It's based on SDL1.3's SDL_compat
 */

#include <SDL.h>
#include "g_compat.h"

SDL_Window *window = NULL;
static SDL_Surface *g_windowsurface = NULL;
static SDL_Surface *g_videosurface = NULL;
static SDL_Surface *g_shadowsurface = NULL;
static SDL_Surface *g_publicsurface = NULL;
static Uint32 SDL_VideoFlags = 0;
static SDL_Rect SDL_VideoViewport;

static void
ClearVideoSurface()
{
    if (g_shadowsurface) {
        SDL_FillRect(g_shadowsurface, NULL,
                     SDL_MapRGB(g_shadowsurface->format, 0, 0, 0));
    }
    SDL_FillRect(g_windowsurface, NULL, 0);
    SDL_UpdateWindowSurface(window);
}

static int
g_eventfilter(void *userdata, SDL_Event * event)
{
    int window_w, window_h;

    switch (event->type) {
        case SDL_WINDOWEVENT:
            switch (event->window.event) {
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    // Recreate the window surface, this is needed in iOS
                    // and probably others
                    if(g_windowsurface)
                        SDL_FreeSurface(g_windowsurface);

                    g_windowsurface = SDL_GetWindowSurface(window);

                    /* Center the public surface in the window surface */
                    SDL_GetWindowSize(window, &window_w, &window_h);
                    SDL_VideoViewport.x = (window_w - g_windowsurface->w)/2;
                    SDL_VideoViewport.y = (window_h - g_windowsurface->h)/2;
                    SDL_VideoViewport.w = g_windowsurface->w;
                    SDL_VideoViewport.h = g_windowsurface->h;
                    
                    ClearVideoSurface();
                    break;
            }
    }
    return 1;
}

SDL_Surface *
SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags)
{
    SDL_DisplayMode desktop_mode;
    int display = SDL_GetWindowDisplay(window);
    int window_x = SDL_WINDOWPOS_UNDEFINED_DISPLAY(display);
    int window_y = SDL_WINDOWPOS_UNDEFINED_DISPLAY(display);
    int window_w;
    int window_h;
    Uint32 window_flags;
    Uint32 surface_flags;

    if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE)) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) < 0) {
            return NULL;
        }
    }

    SDL_GetDesktopDisplayMode(display, &desktop_mode);

    if (width == 0) {
        width = desktop_mode.w;
    }
    if (height == 0) {
        height = desktop_mode.h;
    }
    if (bpp == 0) {
        bpp = SDL_BITSPERPIXEL(desktop_mode.format);
    }

    /* Destroy existing window */
    g_publicsurface = NULL;
    if (g_shadowsurface) {
        g_shadowsurface->flags &= ~SDL_DONTFREE;
        SDL_FreeSurface(g_shadowsurface);
        g_shadowsurface = NULL;
    }
    if (g_videosurface) {
        g_videosurface->flags &= ~SDL_DONTFREE;
        SDL_FreeSurface(g_videosurface);
        g_videosurface = NULL;
    }
    if (window) {
        SDL_GetWindowPosition(window, &window_x, &window_y);
        SDL_DestroyWindow(window);
    }

    /* Set up the event filter */
    if (!SDL_GetEventFilter(NULL, NULL)) {
        SDL_SetEventFilter(g_eventfilter, NULL);
    }

    /* Create a new window */
    window_flags = SDL_WINDOW_SHOWN;
    if (flags & SDL_FULLSCREEN) {
        window_flags |= SDL_WINDOW_FULLSCREEN;
    }
    if (flags & SDL_OPENGL) {
        window_flags |= SDL_WINDOW_OPENGL;
    }
    if (flags & SDL_RESIZABLE) {
        window_flags |= SDL_WINDOW_RESIZABLE;
    }
    if (flags & SDL_NOFRAME) {
        window_flags |= SDL_WINDOW_BORDERLESS;
    }
    window =
        SDL_CreateWindow("", window_x, window_y, width, height,
                         window_flags);
    if (!window) {
        return NULL;
    }

    window_flags = SDL_GetWindowFlags(window);
    surface_flags = 0;
    if (window_flags & SDL_WINDOW_FULLSCREEN) {
        surface_flags |= SDL_FULLSCREEN;
    }
    if ((window_flags & SDL_WINDOW_OPENGL) && (flags & SDL_OPENGL)) {
        surface_flags |= SDL_OPENGL;
    }
    if (window_flags & SDL_WINDOW_RESIZABLE) {
        surface_flags |= SDL_RESIZABLE;
    }
    if (window_flags & SDL_WINDOW_BORDERLESS) {
        surface_flags |= SDL_NOFRAME;
    }

    SDL_VideoFlags = flags;

    /* Create the screen surface */
    g_windowsurface = SDL_GetWindowSurface(window);
    if (!g_windowsurface) {
        return NULL;
    }

    /* Center the public surface in the window surface */
    SDL_GetWindowSize(window, &window_w, &window_h);
    SDL_VideoViewport.x = (window_w - width)/2;
    SDL_VideoViewport.y = (window_h - height)/2;
    SDL_VideoViewport.w = width;
    SDL_VideoViewport.h = height;

    g_videosurface = SDL_CreateRGBSurfaceFrom(NULL, 0, 0, 32, 0, 0, 0, 0, 0);
    g_videosurface->flags |= surface_flags;
    g_videosurface->flags |= SDL_DONTFREE;
    SDL_FreeFormat(g_videosurface->format);
    g_videosurface->format = g_windowsurface->format;
    g_videosurface->format->refcount++;
    g_videosurface->w = width;
    g_videosurface->h = height;
    g_videosurface->pitch = g_windowsurface->pitch;
    g_videosurface->pixels = (void *)((Uint8 *)g_windowsurface->pixels +
        SDL_VideoViewport.y * g_videosurface->pitch +
        SDL_VideoViewport.x  * g_videosurface->format->BytesPerPixel);
    SDL_SetClipRect(g_videosurface, NULL);

    /* Create a shadow surface if necessary */
    if ((bpp != g_videosurface->format->BitsPerPixel)
        && !(flags & SDL_ANYFORMAT)) {
        g_shadowsurface =
            SDL_CreateRGBSurface(0, width, height, bpp, 0, 0, 0, 0);
        if (!g_shadowsurface) {
            return NULL;
        }
        g_shadowsurface->flags |= surface_flags;
        g_shadowsurface->flags |= SDL_DONTFREE;

        /* 8-bit g_shadowsurface surfaces report that they have exclusive palette */
        if (g_shadowsurface->format->palette) {
            g_shadowsurface->flags |= SDL_HWPALETTE;
            SDL_DitherColors(g_shadowsurface->format->palette->colors,
                             g_shadowsurface->format->BitsPerPixel);
        }
        SDL_FillRect(g_shadowsurface, NULL,
            SDL_MapRGB(g_shadowsurface->format, 0, 0, 0));
    }
    g_publicsurface =
        (g_shadowsurface ? g_shadowsurface : g_videosurface);

    ClearVideoSurface();

    /* We're finally done! */
    return g_publicsurface;
}

int
SDL_Flip(SDL_Surface * screen)
{
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    return 0;
}

void
SDL_UpdateRect(SDL_Surface * screen, Sint32 x, Sint32 y, Uint32 w, Uint32 h)
{
    if (screen) {
        SDL_Rect rect;

        /* Fill the rectangle */
        rect.x = (int) x;
        rect.y = (int) y;
        rect.w = (int) (w ? w : screen->w);
        rect.h = (int) (h ? h : screen->h);
        SDL_UpdateRects(screen, 1, &rect);
    }
}

void
SDL_UpdateRects(SDL_Surface * screen, int numrects, SDL_Rect * rects)
{
    int i;

    if (screen == g_shadowsurface) {
        for (i = 0; i < numrects; ++i) {
            SDL_BlitSurface(g_shadowsurface, &rects[i], g_videosurface,
                            &rects[i]);
        }

        /* Fall through to video surface update */
        screen = g_videosurface;
    }
    if (screen == g_videosurface) {
        if (SDL_VideoViewport.x || SDL_VideoViewport.y) {
            SDL_Rect *stackrects = SDL_stack_alloc(SDL_Rect, numrects);
            SDL_Rect *stackrect;
            const SDL_Rect *rect;
            
            /* Offset all the rectangles before updating */
            for (i = 0; i < numrects; ++i) {
                rect = &rects[i];
                stackrect = &stackrects[i];
                stackrect->x = SDL_VideoViewport.x + rect->x;
                stackrect->y = SDL_VideoViewport.y + rect->y;
                stackrect->w = rect->w;
                stackrect->h = rect->h;
            }
            SDL_UpdateWindowSurfaceRects(window, stackrects, numrects);
            SDL_stack_free(stackrects);
        } else {
            SDL_UpdateWindowSurfaceRects(window, rects, numrects);
        }
    }
}