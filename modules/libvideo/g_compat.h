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
 *  g_compat.h
 *
 *  This file contains functions for backwards compatibility with SDL 1.2
 *  for a very limited set of tasks. It's based on SDL1.3's SDL_compat
 */

#ifndef __G_COMPAT_H
#define __G_COMPAT_H

#include <SDL.h>

#if !SDL_VERSION_ATLEAST(2,0,0)
#error You shouldn't be building this in a SDL1.2 build
#endif

/**
 *  Surface flags
 **/
#define SDL_SRCALPHA        0x00010000
#define SDL_SRCCOLORKEY     0x00020000
#define SDL_ANYFORMAT       0x00100000
#define SDL_HWPALETTE       0x00200000
#define SDL_DOUBLEBUF       0x00400000
#define SDL_FULLSCREEN      0x00800000
#define SDL_RESIZABLE       0x01000000
#define SDL_NOFRAME         0x02000000
#define SDL_OPENGL          0x04000000
#define SDL_HWSURFACE       0x08000001  /**< \note Not used */
#define SDL_ASYNCBLIT       0x08000000  /**< \note Not used */
#define SDL_RLEACCELOK      0x08000000  /**< \note Not used */
#define SDL_HWACCEL         0x08000000  /**< \note Not used */

extern SDL_Window *window;

extern DECLSPEC SDL_Surface *SDLCALL SDL_SetVideoMode(int width, int height,
                                                      int bpp, Uint32 flags);
extern DECLSPEC SDL_Surface *SDLCALL SDL_GetVideoSurface(void);
extern DECLSPEC void SDLCALL SDL_UpdateRects(SDL_Surface * screen,
                                             int numrects, SDL_Rect * rects);
extern DECLSPEC void SDLCALL SDL_UpdateRect(SDL_Surface * screen,
                                            Sint32 x,
                                            Sint32 y, Uint32 w, Uint32 h);
extern DECLSPEC int SDLCALL SDL_Flip(SDL_Surface * screen);

#endif /* __G_COMPAT_H */
