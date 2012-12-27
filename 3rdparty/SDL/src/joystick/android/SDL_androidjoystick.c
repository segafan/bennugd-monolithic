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

#ifdef SDL_JOYSTICK_ANDROID

/* This is the system specific header for the SDL joystick API */
#include <stdio.h>              /* For the definition of NULL */

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_joystick.h"
#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"
#include "../../core/android/SDL_android.h"

#define MAX_JOYSTICKS	8

static char *SYS_JoystickNames[MAX_JOYSTICKS];

SDL_Joystick *
SDL_SYS_JoystickfromIndex(int index)
{
	int i = 0;
	SDL_Joystick * joy;
	
	for(i=0; i<SDL_numjoysticks; i++ )
	{
		if(SDL_JoystickOpened(i))
		{
			joy = SDL_JoystickOpen(i);
			if (joy->index == index)
			{
				SDL_JoystickClose(joy);
				return joy;
			}
			SDL_JoystickClose(joy);
		}
	}
}

/* Function to scan the system for joysticks.
 * This function should set SDL_numjoysticks to the number of available
 * joysticks.  Joystick 0 should be the system default joystick.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
int
SDL_SYS_JoystickInit(void)
{
	int i = 0;
	// The latest entry is for the accelerometer
	// TODO: handle the case where SDL_numjoysticks > MAX_JOYSTICKS
    SDL_numjoysticks = Android_JNI_GetNumJoysticks()+1;
	SDL_memset(SYS_JoystickNames, 0, (sizeof SYS_JoystickNames));
	
	for (i = 0; i < (SDL_numjoysticks-1); i++)
	{
		SYS_JoystickNames[i] = Android_JNI_GetJoystickName(i);
	}
	SYS_JoystickNames[i] = Android_GetAccelName();
    
    return (SDL_numjoysticks);
}

/* Function to get the device-dependent name of a joystick */
const char *
SDL_SYS_JoystickName(int index)
{
	return SYS_JoystickNames[index];
}

/* Function to open a joystick for use.
   The joystick to open is specified by the index field of the joystick.
   This should fill the nbuttons and naxes fields of the joystick structure.
   It returns 0, or -1 if there is an error.
 */
int
SDL_SYS_JoystickOpen(SDL_Joystick * joystick)
{
	// Handle the accelerometer separately
	if( joystick->index < (SDL_numjoysticks-1) )
	{
		// TODO: How to get the rest of the info??
		// TODO: Don't lie to the user
		joystick->nbuttons = 16;
		joystick->nhats = 0;
		joystick->nballs = 0;
		joystick->naxes = Android_JNI_GetJoystickAxes(joystick->index);
	}
	else if( joystick->index == (SDL_numjoysticks-1) )
	{
		joystick->nbuttons = 0;
		joystick->nhats = 0;
		joystick->nballs = 0;
		joystick->naxes = 3;
	}
	else
	{
		return -1;
	}
	
    return 0;
}


/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */
void
SDL_SYS_JoystickUpdate(SDL_Joystick * joystick)
{
    int i;
    Sint16 value;
    float values[3];

	if( joystick->index == (SDL_numjoysticks-1) )
	{
		if (Android_JNI_GetAccelerometerValues(values))
		{
			for ( i = 0; i < 3; i++ )
			{
				value = (Sint16)(values[i] * 32767.0f);
				SDL_PrivateJoystickAxis(joystick, i, value);
			}
		}
	}
}

/* Function to close a joystick after use */
void
SDL_SYS_JoystickClose(SDL_Joystick * joystick)
{
}

/* Function to perform any system-specific joystick related cleanup */
void
SDL_SYS_JoystickQuit(void)
{
	int i;
	
	for (i = 0; SYS_JoystickNames[i]; ++i)
	{
		SDL_free(SYS_JoystickNames[i]);
	}
	SYS_JoystickNames[0] = NULL;
}

int
Android_OnPadDown(int padId, int keycode)
{
	SDL_Log("Down on joy %d for key %d\n", padId, keycode);
	SDL_PrivateJoystickButton(SDL_SYS_JoystickfromIndex(padId), keycode, SDL_PRESSED);
	
	return 0;
}

int
Android_OnPadUp(int padId, int keycode)
{
	SDL_Log("Up on joy %d for key %d\n", padId, keycode);
	SDL_PrivateJoystickButton(SDL_SYS_JoystickfromIndex(padId), keycode, SDL_RELEASED);
	
	return 0;
}

#endif /* SDL_JOYSTICK_NDS */

/* vi: set ts=4 sw=4 expandtab: */
