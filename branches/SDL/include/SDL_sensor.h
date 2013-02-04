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
 *  \file SDL_sensor.h
 *
 *  Include file for SDL sensor event handling
 *
 * The term "device_index" identifies currently plugged in joystick devices between 0 and SDL_NumJoysticks, with the exact joystick
 *   behind a device_index changing as joysticks are plugged and unplugged.
 *
 * The term "instance_id" is the current instantiation of a joystick device in the system, if the joystick is removed and then re-inserted
 *   then it will get a new instance_id, instance_id's are monotonically increasing identifiers of a joystick plugged in.
 *
 * The term JoystickGUID is a stable 128-bit identifier for a joystick device that does not change over time, it identifies class of
 *   the device (a X360 wired controller for example). This identifier is platform dependent.
 *
 *
 */

#ifndef _SDL_sensor_h
#define _SDL_sensor_h

#include "SDL_stdinc.h"
#include "SDL_error.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
/* *INDENT-ON* */
#endif

/**
 *  \file SDL_sensor.h
 *
 *  In order to use these functions, SDL_Init() must have been called
 *  with the ::SDL_INIT_JOYSTICK flag.  This causes SDL to scan the system
 *  for joysticks, and load appropriate drivers.
 */

/* The joystick structure used to identify an SDL joystick */
struct _SDL_Sensor;
typedef struct _SDL_Sensor SDL_Sensor;

/* A structure that encodes the stable unique id for a joystick device */
typedef struct {
    Uint8 data[16];
} SDL_SensorGUID;

typedef int SDL_SensorID;

/* The different sensor types */
typedef enum
{
    SDL_SENSOR_UNKNOWN = 0x00000000,            /**< unknown sensor type */
    SDL_SENSOR_ACCEL = 0x00000001,              /**< accelerometer */
    SDL_SENSOR_MAGNET = 0x00000002,             /**< magnetometer */
    SDL_SENSOR_ORIENTATION = 0x00000003,        /**< orientation sensor */
    SDL_SENSOR_GYRO = 0x00000004,               /**< gyroscope */
    SDL_SENSOR_LIGHT = 0x00000005,              /**< light sensor */
    SDL_SENSOR_PRESSURE = 0x00000006,           /**< pressure sensor */
    SDL_SENSOR_TEMPERATURE = 0x00000007,        /**< temperature sensor */
    SDL_SENSOR_PROXIMITY = 0x00000008,          /**< proximity sensor */
    SDL_SENSOR_GRAVITY = 0x00000009,            /**< gravity sensor */
    SDL_SENSOR_LACCEL = 0x0000000a,             /**< linear acceleration sensor */
    SDL_SENSOR_ROTVECTOR = 0x0000000b,          /**< rotation vector sensor */
    SDL_SENSOR_RHUMIDITY = 0x0000000c           /**< relative humidity sensor */
} SDL_SensorFlags;

/* Function prototypes */
/**
 *  Count the number of sensors attached to the system right now
 */
extern DECLSPEC int SDLCALL SDL_NumSensors(void);

/**
 *  Get the implementation dependent name of a sensor.
 *  This can be called before any sensors are opened.
 *  If no name can be found, this function returns NULL.
 */
extern DECLSPEC const char *SDLCALL SDL_SensorNameForIndex(int device_index);

/**
 *  Open a sensor for use.
 *  The index passed as an argument refers tothe N'th sensor on the system.
 *  This index is the value which will identify this sensor in future sensor
 *  events.
 *
 *  \return A sensor identifier, or NULL if an error occurred.
 */
extern DECLSPEC SDL_Sensor *SDLCALL SDL_SensorOpen(int device_index);

/**
 *  Return the name for this currently opened sensor.
 *  If no name can be found, this function returns NULL.
 */
extern DECLSPEC const char *SDLCALL SDL_SensorName(SDL_Sensor * sensor);

/**
 *  Returns SDL_TRUE if the sensor has been opened and currently connected, or SDL_FALSE if it has not.
 */
extern DECLSPEC SDL_bool SDLCALL SDL_SensorGetAttached(SDL_Sensor * sensor);

/**
 *  Get the instance ID of an opened sensor.
 */
extern DECLSPEC SDL_SensorID SDLCALL SDL_SensorInstanceID(SDL_Sensor * sensor);

/**
 *  Get the number of general axis controls on a sensor.
 */
extern DECLSPEC int SDLCALL SDL_SensorNumAxes(SDL_Sensor * sensor);

/**
 *  Get the sensor type for an opened sensor.
 */
extern DECLSPEC Uint8 SDL_SensorType(SDL_Sensor * sensor);

/**
 *  Update the current state of the open sensors.
 *
 *  This is called automatically by the event loop if any sensor
 *  events are enabled.
 */
extern DECLSPEC void SDLCALL SDL_SensorUpdate(void);

/**
 *  Enable/disable sensor event polling.
 *
 *  If sensor events are disabled, you must call SDL_SensorUpdate()
 *  yourself and check the state of the sensor when you want sensor
 *  information.
 *
 *  The state can be one of ::SDL_QUERY, ::SDL_ENABLE or ::SDL_IGNORE.
 */
extern DECLSPEC int SDLCALL SDL_SensorEventState(int state);

/**
 *  Get the current state of an axis on a sensor.
 *
 *  The state is a value ranging from -32768 to 32767.
 *
 *  The axis indices start at index 0.
 */
extern DECLSPEC Sint16 SDLCALL SDL_SensorGetAxis(SDL_Sensor * sensor,
                                                   int axis);

/**
 *  Get the current resolution of an axis on a sensor.
 *
 *  The state is a value ranging from -32768 to 32767.
 *
 *  The axis indices start at index 0.
 */
extern DECLSPEC Sint16 SDLCALL SDL_SensorGetResolution(SDL_Sensor * sensor,
                                                   int axis);

/**
 *  Close a sensor previously opened with SDL_SensorOpen().
 */
extern DECLSPEC void SDLCALL SDL_SensorClose(SDL_Sensor * sensor);


/* Ends C function definitions when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#include "close_code.h"

#endif /* _SDL_sensor_h */

/* vi: set ts=4 sw=4 expandtab: */
