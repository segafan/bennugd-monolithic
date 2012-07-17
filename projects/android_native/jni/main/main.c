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

#include <android/log.h>
#include <android_native_app_glue.h>
#include <stdlib.h>


/**
 * Process the next input event.
 */
static void handle_input(struct android_app* app, AInputEvent* event) {
}

/**
 * Process the next main command.
 */
static void handle_cmd(struct android_app* app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            break;
    }
}

/* This'll be the main entry point for our app */
void android_main(struct android_app *state)
{
	app_dummy(); // Make sure glue isn't stripped
    state->onAppCmd = handle_cmd;
    state->onInputEvent = handle_input;
    
    while (!state->destroyRequested)
    {
        int events;
        struct android_poll_source *source;

        // Main Loop
        while ((ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
        {
            if (source)
            {
                source->process(state, source);
            }
        }
        
        // Do other needed stuff here
    }
}
