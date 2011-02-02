/*
 *  Copyright © 2006-2011 SplinterGU (Fenix/Bennugd)
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

/* --------------------------------------------------------------------------- */

#define _GNU_SOURCE
#include <math.h>

#include <stdio.h>

#include "bgddl.h"

#ifndef __MONOLITHIC__
#include "mod_mathi_symbols.h"
#endif

/* --------------------------------------------------------------------------- */
/* Funciones matemáticas */
/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_abs( INSTANCE * my, int * params )
{
    float num = *( float * ) &params[0] ;
    float res = ( num < 0 ) ? -num : num ;
    return *(( int * )&res ) ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_pow( INSTANCE * my, int * params )
{
    float res = ( float )pow( *( float * ) & params[0], *( float * ) & params[1] ) ;
    return *(( int * )&res ) ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_sqrt( INSTANCE * my, int * params )
{
    float res = ( float )sqrt( *( float * ) & params[0] ) ;
    return *(( int * )&res ) ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_cos( INSTANCE * my, int * params )
{
    return cos(( double )( params[0] * M_PI / 180000.0 )) * 1000 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_sin( INSTANCE * my, int * params )
{
    return sin(( double )( params[0] * M_PI / 180000.0 )) * 1000 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_tan( INSTANCE * my, int * params )
{
    return tan(( double )( params[0] * M_PI / 180000.0 )) * 1000 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_acos( INSTANCE * my, int * params )
{
    return acos(( double )( params[0] * 180000.0 / M_PI )) * 1000 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_asin( INSTANCE * my, int * params )
{
    return asin(( double )( params[0] * 180000.0 / M_PI )) * 1000 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_atan( INSTANCE * my, int * params )
{
    return atan(( double )( params[0] * 180000.0 / M_PI )) * 1000 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_atan2( INSTANCE * my, int * params )
{
    return atan2(( double )( params[0] * 180000.0 / M_PI ), ( double )( params[1] * 180000.0 / M_PI )) * 1000 ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_isinf( INSTANCE * my, int * params )
{
    double param = ( double ) *( float * ) & params[0] ;
    return isinf( param );
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_isnan( INSTANCE * my, int * params )
{
    double param = ( double ) *( float * ) & params[0] ;
    return isnan( param );
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_finite( INSTANCE * my, int * params )
{
    double param = ( double ) *( float * ) & params[0] ;
#ifdef TARGET_IOS
	return ( !isnan(param) && !isinf(param) );
#else
    return finite ( param );
#endif
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_get_disty( INSTANCE * my, int * params )
{
    double angle = params[0] * M_PI / 180000.0 ;
    return ( int )( params[1] * -sin( angle ) ) ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_fget_angle( INSTANCE * my, int * params )
{
    double dx = params[2] - params[0] ;
    double dy = params[3] - params[1] ;
    int angle ;

    if ( dx == 0 ) return ( dy > 0 ) ? 270000L : 90000L ;

    angle = ( int )( atan( dy / dx ) * 180000.0 / M_PI ) ;

    return ( dx > 0 ) ? -angle : -angle + 180000L ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_fget_dist( INSTANCE * my, int * params )
{
    double dx = params[2] - params[0] ;
    double dy = params[3] - params[1] ;

    return ( int )sqrt( dx*dx + dy*dy ) ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_near_angle( INSTANCE * my, int * params )
{
    int angle = params[0] ;
    int dest  = params[1] ;
    int incr  = params[2] ;

    if ( angle < dest && dest - angle > 180000L )
        angle += 360000L ;

    if ( angle > dest && angle - dest > 180000L )
        angle -= 360000L ;

    if ( angle < dest )
    {
        angle += incr ;
        if ( angle > dest ) angle = dest ;
    }
    else
    {
        angle -= incr ;
        if ( angle < dest ) angle = dest ;
    }

    if ( angle < 0 ) return angle + 360000L ;
    if ( angle >= 360000L ) return angle - 360000L ;
    return angle ;
}

/* --------------------------------------------------------------------------- */

CONDITIONALLY_STATIC int mathi_get_distx( INSTANCE * my, int * params )
{
    double angle = params[0] * M_PI / 180000.0 ;
    return ( int )( params[1] * cos( angle ) ) ;
}

/* --------------------------------------------------------------------------- */
