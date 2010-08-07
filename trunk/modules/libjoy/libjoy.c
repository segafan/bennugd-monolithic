/*
 *  Copyright � 2006-2010 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
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

/* --------------------------------------------------------------------------- */
/* Thanks Sandman for suggest on openjoys at initialization time               */
/* --------------------------------------------------------------------------- */
/* Credits SplinterGU/Sandman 2007-2009                                        */
/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TARGET_MAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#ifndef __MONOLITHIC__
#include "libjoy_symbols.h"
#endif

/* --------------------------------------------------------------------------- */

#include "bgddl.h"

#include "bgdrtm.h"

#include "files.h"
#include "xstrings.h"

/* --------------------------------------------------------------------------- */

#ifdef TARGET_CAANOO
#include "caanoo/te9_tf9_hybrid_driver.c"
#endif

#ifdef TARGET_WII
#include "wiiuse/wpad.h"
#endif

/* --------------------------------------------------------------------------- */

#define MAX_JOYS    32

static int _max_joys = 0;
static SDL_Joystick * _joysticks[MAX_JOYS];
static int _selected_joystick = -1;

/* --------------------------------------------------------------------------- */
/**
 * libjoy_num ()
 * Returns the number of joysticks present in the system
 **/

int libjoy_num( void )
{
#ifdef TARGET_CAANOO
    return _max_joys - 1 ;
#else
    return _max_joys ;
#endif
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_name (int JOY)
 * Returns the name for a given joystick present in the system
 **/

int libjoy_name( int joy )
{
    int result;
#ifdef TARGET_CAANOO
    if ( joy > 0 ) joy++;
#endif
    result = string_new( SDL_JoystickName( joy ) );
    string_use( result );
    return result;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_select (int JOY)
 * Returns the selected joystick number
 **/

int libjoy_select( int joy )
{
#ifdef TARGET_CAANOO
    if ( joy > 0 ) joy++;
#endif
    return ( _selected_joystick = joy );
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_buttons ()
 * Returns the selected joystick total buttons
 **/

int libjoy_buttons( void )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
        return SDL_JoystickNumButtons( _joysticks[ _selected_joystick ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_axes ()
 * Returns the selected joystick total axes
 **/

int libjoy_axes( void )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( _selected_joystick == 0 ) return SDL_JoystickNumAxes( _joysticks[ 2 ] ) ;
#endif
        return SDL_JoystickNumAxes( _joysticks[ _selected_joystick ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_button ( int button )
 * Returns the selected joystick state for the given button
 **/

int libjoy_get_button( int button )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( _selected_joystick == 0 )
        {
            switch ( button )
            {
                case    1: /* UPLF */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) < -16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) < -16384 );

                case    3: /* DWLF */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) >  16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) < -16384 );

                case    5: /* DWRT */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) >  16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) >  16384 );

                case    7: /* UPRT */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) < -16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) >  16384 );

                case    0: /* UP */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) < -16384 );

                case    4: /* DW */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) > 16384 );

                case    2: /* LF */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) < -16384 );
                        break;

                case    6: /* RT */
                        return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) > 16384 );
            }
        }
#endif
        return SDL_JoystickGetButton( _joysticks[ _selected_joystick ], button ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_position ( int axis )
 * Returns the selected joystick state for the given axis
 **/

int libjoy_get_position( int axis )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( _selected_joystick == 0 ) return SDL_JoystickGetAxis( _joysticks[ 2 ], axis ) ;
#endif
        return SDL_JoystickGetAxis( _joysticks[ _selected_joystick ], axis ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_hats ()
 * Returns the total number of POV hats of the current selected joystick
 **/

int libjoy_hats( void )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
        return SDL_JoystickNumHats( _joysticks[ _selected_joystick ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_balls ()
 * Returns the total number of balls of the current selected joystick
 **/

int libjoy_balls( void )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
        return SDL_JoystickNumBalls( _joysticks[ _selected_joystick ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_hat (int HAT)
 * Returns the state of the specfied hat on the current selected joystick
 **/

int libjoy_get_hat( int hat )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
        if ( hat >= 0 && hat <= SDL_JoystickNumHats( _joysticks[ _selected_joystick ] ) )
        {
            return SDL_JoystickGetHat( _joysticks[ _selected_joystick ], hat ) ;
        }
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_ball (int BALL, int* dx, int* dy)
 * Returns the state of the specfied ball on the current selected joystick
 **/

int libjoy_get_ball( int ball, int * dx, int * dy )
{
    if ( _selected_joystick >= 0 && _selected_joystick < _max_joys )
    {
        if ( ball >= 0 && ball <= SDL_JoystickNumBalls( _joysticks[ball] ) )
        {
            return SDL_JoystickGetBall( _joysticks[ _selected_joystick ], ball, dx, dy ) ;
        }
    }
    return -1 ;
}

/* --------------------------------------------------------------------------- */

int libjoy_get_accel( int * x, int * y, int * z )
{
#ifdef TARGET_CAANOO
    if ( _selected_joystick < 2 )
    {
        KIONIX_ACCEL_read_LPF_g( x, y, z );
	    return 0;
    }
#elif defined(TARGET_WII)
	WPADData *wd;
	
    // First, ensure Wiimote is available
    if( WPAD_Probe(_selected_joystick, NULL) == 0 )
	{
		// Assign the values
		wd = WPAD_Data( _selected_joystick );
		*x = wd->accel.x;
		*y = wd->accel.y;
		*z = wd->accel.z;
	}
#endif
    return -1;
}

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/**
 * libjoy_buttons_specific (int JOY)
 * Returns the selected joystick total buttons
 **/

int libjoy_buttons_specific( int joy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy > 0 ) joy++;
#endif
        return SDL_JoystickNumButtons( _joysticks[ joy ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_axes_specific (int JOY)
 * Returns the selected joystick total axes
 **/

int libjoy_axes_specific( int joy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy == 0 ) joy = 2;
        else joy++;
#endif
        return SDL_JoystickNumAxes( _joysticks[ joy ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_button_specific (int JOY, int button)
 * Returns the selected joystick state for the given button
 **/

int libjoy_get_button_specific( int joy, int button )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy > 0 ) joy++;
#endif
        if ( button >= 0 && button <= SDL_JoystickNumButtons( _joysticks[ joy ] ) )
        {
#ifdef TARGET_CAANOO
            if ( joy == 0 )
            {
                switch ( button )
                {
                    case    1: /* UPLF */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) < -16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) < -16384 );

                    case    3: /* DWLF */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) >  16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) < -16384 );

                    case    5: /* DWRT */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) >  16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) >  16384 );

                    case    7: /* UPRT */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) < -16384 && SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) >  16384 );

                    case    0: /* UP */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) < -16384 );

                    case    4: /* DW */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 1 ) > 16384 );

                    case    2: /* LF */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) < -16384 );
                            break;

                    case    6: /* RT */
                            return ( SDL_JoystickGetAxis( _joysticks[ 2 ], 0 ) > 16384 );
                }
            }
#endif
            return SDL_JoystickGetButton( _joysticks[ joy ], button ) ;
        }
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_position_specific (int JOY, int axis)
 * Returns the selected joystick state for the given axis
 **/

int libjoy_get_position_specific( int joy, int axis )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy == 0 ) joy = 2;
        else joy++;
#endif
        if ( axis >= 0 && axis <= SDL_JoystickNumAxes( _joysticks[ joy ] ) )
        {
            return SDL_JoystickGetAxis( _joysticks[ joy ], axis ) ;
        }
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/* Added by Sandman */
/* --------------------------------------------------------------------------- */
/**
 * libjoy_hats_specific (int JOY)
 * Returns the total number of POV hats of the specified joystick
 **/

int libjoy_hats_specific( int joy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy > 0 ) joy++;
#endif
        return SDL_JoystickNumHats( _joysticks[ joy ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_balls_specific (int JOY)
 * Returns the total number of balls of the specified joystick
 **/

int libjoy_balls_specific( int joy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy > 0 ) joy++;
#endif
        return SDL_JoystickNumBalls( _joysticks[ joy ] ) ;
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_hat_specific (int JOY, int HAT)
 * Returns the state of the specfied hat on the specified joystick
 **/

int libjoy_get_hat_specific( int joy, int hat )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy > 0 ) joy++;
#endif
        if ( hat >= 0 && hat <= SDL_JoystickNumHats( _joysticks[ joy ] ) )
        {
            return SDL_JoystickGetHat( _joysticks[ joy ], hat ) ;
        }
    }
    return 0 ;
}

/* --------------------------------------------------------------------------- */
/**
 * libjoy_get_ball_specific (int JOY, int BALL, int* dx, int* dy)
 * Returns the state of the specfied ball on the specified joystick
 **/

int libjoy_get_ball_specific( int joy, int ball, int * dx, int * dy )
{
    if ( joy >= 0 && joy < _max_joys )
    {
#ifdef TARGET_CAANOO
        if ( joy > 0 ) joy++;
#endif
        if ( ball >= 0 && ball <= SDL_JoystickNumBalls( _joysticks[ joy ] ) )
        {
            return SDL_JoystickGetBall( _joysticks[ joy ], ball, dx, dy ) ;
        }
    }
    return -1 ;
}

/* --------------------------------------------------------------------------- */

int libjoy_get_accel_specific( int joy, int * x, int * y, int * z )
{
#ifdef TARGET_CAANOO
    if ( joy < 2 )
    {
        KIONIX_ACCEL_read_LPF_g( x, y, z );
	    return 0;
    }
#elif defined(TARGET_WII)
	WPADData *wd;
	
    // First, ensure Wiimote is available
    if( WPAD_Probe( joy, NULL ) == 0 )
	{
		// Assign the values
		wd = WPAD_Data( joy );
		*x = wd->accel.x;
		*y = wd->accel.y;
		*z = wd->accel.z;
	}
#endif
    return -1;
}

/* --------------------------------------------------------------------------- */

void  __bgdexport( libjoy, module_initialize )()
{
    int i;

    if ( !SDL_WasInit( SDL_INIT_JOYSTICK ) )
    {
        SDL_InitSubSystem( SDL_INIT_JOYSTICK );
        SDL_JoystickEventState( SDL_ENABLE ) ;
    }

    /* Open all joysticks */
    if (( _max_joys = SDL_NumJoysticks() ) > MAX_JOYS )
    {
        printf( "[JOY] Warning: maximum number of joysticks exceeded (%i>%i)", _max_joys, MAX_JOYS );
        _max_joys = MAX_JOYS;
    }

    for ( i = 0; i < _max_joys; i++ )
    {
        _joysticks[i] = SDL_JoystickOpen( i ) ;
        if ( !_joysticks[ i ] ) printf( "[JOY] Failed to open joystick '%i'", i );
    }

    SDL_JoystickUpdate() ;

#ifdef TARGET_CAANOO
    KIONIX_ACCEL_init();

    if ( KIONIX_ACCEL_get_device_type() != DEVICE_TYPE_KIONIX_KXTF9 ) KIONIX_ACCEL_deinit();

    KXTF9_set_G_range(2);
    KXTF9_set_resolution(12);
    KXTF9_set_lpf_odr(400);

    KIONIX_ACCEL_enable_outputs();
#endif
}

/* ----------------------------------------------------------------- */

void  __bgdexport( libjoy, module_finalize )()
{
    int i;

#ifdef TARGET_CAANOO
    KIONIX_ACCEL_deinit();
#endif

    for ( i = 0; i < _max_joys; i++ )
        if ( _joysticks[ i ] ) SDL_JoystickClose( _joysticks[ i ] ) ;

    if ( SDL_WasInit( SDL_INIT_JOYSTICK ) ) SDL_QuitSubSystem( SDL_INIT_JOYSTICK );

}

/* ----------------------------------------------------------------- */
