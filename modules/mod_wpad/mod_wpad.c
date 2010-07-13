/*
 *  Copyright © 2010 Joseba García Etxebarria <joseba.gar@gmail.com>
 *
 *  mod_wpad is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  mod_wpad is distributed in the hope that it will be useful,
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
#include "libvideo.h"
#ifdef TARGET_WII
#include "wiiuse/wpad.h"
#endif

#include "mod_wpad.h"


#ifdef TARGET_WII
// Checks wether a given wpad number corresponds to a Wii Balance Board
int is_bb(int i) {
    u32 type;

    WPAD_Probe(i, &type);
    if (type==WPAD_EXP_WIIBOARD)
        return 1;
    else
        return 0;
}
#endif

/* Check the status of each Wiimote */
int modwpad_is_ready( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    int res=0;
    u32 type;

    res = WPAD_Probe(params[0], &type);
    if(res == 0)
        return 1;   // So it's true in BennuGD code
    else
        return res;
#else
    return -1;  // No wiimote
#endif
}

// Get info from generic controller
int modwpad_info( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    u32 type;
    WPADData *wd;

    // Ensure it's been correctly initialized
    if( WPAD_Probe(params[0], &type) != 0 )
        return 0;

    // Return the info the user asked for
    wd = WPAD_Data(params[0]);
    switch(params[1]) {
        case 0:     // Battery level (0<level<256)
            return (int)WPAD_BatteryLevel(params[0]);
        case 1:     // X position
            return wd->ir.x;
        case 2:     // Y position
            return wd->ir.y;
        case 3:     // Z position (distance from screen in m)
            return wd->ir.z;
        case 4:     // Angle, BennuGD likes 1/1000th of degrees
            return -(int)(wd->ir.angle*1000.);
        case 5:     // Pitch angle, BennuGD likes 1/1000th of degrees
            return (int)(wd->orient.pitch*1000.);
        case 6:     // Roll angle,  BennuGD likes 1/1000th of degrees
            return (int)(wd->orient.roll*1000.);    // Uses accelerometer
        case 7:     // Acceleration in x axis
            return wd->accel.x;
        case 8:     // Acceleration in y axis
            return wd->accel.y;
        case 9:     // Acceleration in z axis
            return wd->accel.z;
        case 10:    // Check wether controller is a balance board
            return is_bb(params[0]);
    }
#endif

    return 0;
}

// Get data from the Wii Balance Board
int modwpad_info_bb( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    struct expansion_t exp;
    u32 type;

    // First of all, check if the given wpad is a balanceboard
    if (! is_bb(params[0]))
        return 0;

    // Ensure it's been correctly initialized
    if( WPAD_Probe(params[0], &type) != 0 )
        return 0;

    // Return the info the user asked for
    WPAD_Expansion(params[0], &exp);
    switch(params[1]) {
        case 0:     // Battery level (0<level<256)
            return (int)WPAD_BatteryLevel(params[0]);
        case 1:     // X position
            return (int)exp.wb.x;
        case 2:     // Y position
            return (int)exp.wb.y;
        case WPAD_WTL:     // Weight measured on the TOP-LEFT base (Balance Board)
            return (int)exp.wb.tl;
        case WPAD_WTR:     // Weight in TOP-RIGHT
            return (int)exp.wb.tr;
        case WPAD_WBL:     // Weight in BOTTOM-LEFT
            return (int)exp.wb.bl;
        case WPAD_WBR:     // Weight in BOTTOM-RIGHT
            return (int)exp.wb.br;
    }
#endif

    return 0;
}

// Make a controller rumble (or stop rumbling)
void modwpad_rumble( INSTANCE * my, int * params)
{
#ifdef TARGET_WII
    WPAD_Rumble(params[0], params[1]);
#endif
}

/* ----------------------------------------------------------------- */
