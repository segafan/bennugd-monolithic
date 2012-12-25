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
#include "SDL_config.h"

#if SDL_VIDEO_DRIVER_ANDROID

#include <android/log.h>

#include "SDL_events.h"
#include "../../events/SDL_mouse_c.h"

#include "SDL_androidmouse.h"

#define ACTION_DOWN 0
#define ACTION_UP   1
#define ACTION_MOVE 2
#define BUTTON_PRIMARY   1
#define BUTTON_SECONDARY 2
#define BUTTON_TERTIARY  3

static void Android_GetWindowCoordinates(float x, float y,
                                         int *window_x, int *window_y)
{
    int window_w, window_h;

    SDL_GetWindowSize(Android_Window, &window_w, &window_h);
    *window_x = (int)(x * window_w);
    *window_y = (int)(y * window_h);
}

void Android_OnMouse(int action, int buttonId, float x, float y)
{
    int window_x, window_y, button;

    if (!Android_Window) {
        return;
    }
	
	switch(buttonId) {
		case BUTTON_PRIMARY:
			button = SDL_BUTTON_LEFT;
			break;
		case BUTTON_SECONDARY:
			button = SDL_BUTTON_RIGHT;
			break;
		case BUTTON_TERTIARY:
			button = SDL_BUTTON_MIDDLE;
			break;
	}

    switch (action) {
        case ACTION_DOWN:
            Android_GetWindowCoordinates(x, y, &window_x, &window_y);
            SDL_SendMouseMotion(NULL, 0, window_x, window_y);
            SDL_SendMouseButton(NULL, SDL_PRESSED, button);
            break;
        case ACTION_MOVE:
            Android_GetWindowCoordinates(x, y, &window_x, &window_y);

            SDL_SendMouseMotion(NULL, 0, window_x, window_y);
            break;
        case ACTION_UP:
            SDL_SendMouseButton(NULL, SDL_RELEASED, button);
            break;
    }
}

#endif /* SDL_VIDEO_DRIVER_ANDROID */

/* vi: set ts=4 sw=4 expandtab: */
