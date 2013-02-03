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

#ifdef SDL_SENSOR_ANDROID

/* This is the system specific header for the SDL sensor API */
#include <stdio.h>              /* For the definition of NULL */
#include <android/sensor.h>

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_sensor.h"
#include "SDL_androidsensor.h"
#include "../SDL_syssensor.h"
#include "../SDL_sensor_c.h"
#include "../../core/android/SDL_android.h"

static ASensorManager* mSensorManager;

/* Function to scan the system for sensors.
 * Sensor 0 should be the system default sensor.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
int
SDL_SYS_SensorInit(void)
{
    mSensorManager = ASensorManager_getInstance();
    return 0;
}

int SDL_SYS_NumSensors()
{
    return ASensorManager_getSensorList(mSensorManager, NULL);
}

void SDL_SYS_SensorDetect()
{
}

SDL_bool SDL_SYS_SensorNeedsPolling()
{
    return SDL_FALSE;
}

/* Function to get the device-dependent name of a sensor
 * Should be callable even before opening the sensor */
const char *
SDL_SYS_SensorNameForDeviceIndex(int device_index)
{
    int n=0;
    ASensorList list;

    n = ASensorManager_getSensorList(mSensorManager, &list);
    if (device_index > n || ! list) {
        return "";
    }

    return ASensor_getName(list[device_index]);
}

/* Function to open a sensor for use.
   The sensor to open is specified by the index field of the sensor.
   This should fill the naxes fields of the sensor structure.
   It returns 0, or -1 if there is an error.
 */
int
SDL_SYS_SensorOpen(SDL_Sensor *sensor, int device_index)
{
    int n=0, type=0;
    ASensorList list;

    n = ASensorManager_getSensorList(mSensorManager, &list);
    if (device_index > n || ! list) {
        return -1;
    }

    sensor->hwdata = (struct sensor_hwdata *)
        SDL_malloc(sizeof(*sensor->hwdata));
    if (sensor->hwdata == NULL) {
        SDL_OutOfMemory();
        return -1;
    }

    //sensor->hwdata->asensor = list[device_index];
    sensor->naxes = 3;  /* 3 is the maximum we'll find */

    type = ASensor_getType(list[device_index]);
    switch(type) {
        case 1:
            sensor->type = SDL_SENSOR_ACCEL;
            break;
        case 2:
            sensor->type = SDL_SENSOR_MAGNET;
            break;
        case 4:
            sensor->type = SDL_SENSOR_GYRO;
            break;
        case 5:
            sensor->type = SDL_SENSOR_LIGHT;
            break;
        case 8:
            sensor->type = SDL_SENSOR_PROXIMITY;
            break;
        default:
            sensor->type = SDL_SENSOR_UNKNOWN;
    }

    return 0;
}

/* Function to update the state of a sensor - called as a device poll.
 * This function shouldn't update the sensor structure directly,
 * but instead should call SDL_PrivateSensor*() to deliver events
 * and update sensor device state.
 */
void
SDL_SYS_SensorUpdate(SDL_Sensor* sensor)
{
    int i;
    Sint16 value;
    /*float values[3];

    if (Android_JNI_GetAccelerometerValues(values))
    {
        for ( i = 0; i < 3; i++ )
        {
            value = (Sint16)(values[i] * 32767.0f);
            SDL_PrivateSensorAxis(sensor, i, value);
        }
    }*/
}

/* Function to determine is this sensor is attached to the system right now */
SDL_bool SDL_SYS_SensorAttached(SDL_Sensor *sensor)
{
    return SDL_TRUE;
}

/* Function to close a sensor after use */
void
SDL_SYS_SensorClose(SDL_Sensor * sensor)
{
    SDL_free(sensor->hwdata);
}

/* Function to perform any system-specific sensor related cleanup */
void
SDL_SYS_SensorQuit(void)
{
}

#endif /* SDL_SENSOR_ANDROID */

/* vi: set ts=4 sw=4 expandtab: */
