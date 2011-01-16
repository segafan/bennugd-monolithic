/*
 *  Copyright © 2006-2010 SplinterGU (Fenix/Bennugd)
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

#define _LIBKEY_C

#include <stdio.h>
#include <stdlib.h>

#ifdef TARGET_MAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "xctype.h"
#include "bgddl.h"
#include "dlvaracc.h"
#include "libkey.h"
#include "libkey_stats.h"

#ifndef __MONOLITHIC__
#include "libkey_symbols.h"
#endif

/* ----------------------------------------------------------------- */

#define SHIFTSTATUS             0
#define ASCII                   1
#define SCANCODE                2

/* ---------------------------------------------------------------------- */

typedef struct
{
    SDLKey sym;   /* SDL virtual keysym */
    SDLMod mod;   /* current key modifiers */
    HOTKEY_CALLBACK callback;
} hotkey ;

static hotkey * hotkey_list = NULL ;
static int hotkey_allocated = 0 ;
static int hotkey_count = 0 ;

/* ----------------------------------------------------------------- */

/* Publicas */
key_equiv key_table[127] ;              /* Now we have a search table with equivs */
unsigned char * keystate = NULL;        /* Pointer to key states */

/* ----------------------------------------------------------------- */

#if SDL_VERSION_ATLEAST(1,3,0)
static int sdl_equiv[SDL_NUM_SCANCODES+1] ;
#else
static int sdl_equiv[SDLK_LAST+1] ;
#endif

static int equivs[] =
{
#if SDL_VERSION_ATLEAST(1,3,0)
    SDL_SCANCODE_ESCAPE,        1,
    SDL_SCANCODE_1,             2,
    SDL_SCANCODE_KP_1,          2,
    SDL_SCANCODE_2,             3,
    SDL_SCANCODE_KP_2,          3,
    SDL_SCANCODE_3,             4,
    SDL_SCANCODE_KP_3,          4,
    SDL_SCANCODE_4,             5,
    SDL_SCANCODE_KP_4,          5,
    SDL_SCANCODE_5,             6,
    SDL_SCANCODE_KP_5,          6,
    SDL_SCANCODE_6,             7,
    SDL_SCANCODE_KP_6,          7,
    SDL_SCANCODE_7,             8,
    SDL_SCANCODE_KP_7,          8,
    SDL_SCANCODE_8,             9,
    SDL_SCANCODE_KP_8,          9,
    SDL_SCANCODE_9,             10,
    SDL_SCANCODE_KP_9,          10,
    SDL_SCANCODE_0,             11,
    SDL_SCANCODE_KP_0,          11,
    SDL_SCANCODE_MINUS,         12,
    SDL_SCANCODE_EQUALS,        13,
    SDL_SCANCODE_BACKSPACE,     14,
    SDL_SCANCODE_TAB,           15,
    SDL_SCANCODE_Q,             16,
    SDL_SCANCODE_W,             17,
    SDL_SCANCODE_E,             18,
    SDL_SCANCODE_R,             19,
    SDL_SCANCODE_T,             20,
    SDL_SCANCODE_Y,             21,
    SDL_SCANCODE_U,             22,
    SDL_SCANCODE_I,             23,
    SDL_SCANCODE_O,             24,
    SDL_SCANCODE_P,             25,
    SDL_SCANCODE_LEFTBRACKET,   26,
    SDL_SCANCODE_RIGHTBRACKET,  27,
    SDL_SCANCODE_RETURN,        28,
    SDL_SCANCODE_KP_ENTER,      28,
    SDL_SCANCODE_LCTRL,         29,
    SDL_SCANCODE_RCTRL,         29,
    SDL_SCANCODE_LCTRL,         96,
    SDL_SCANCODE_RCTRL,         94,
    SDL_SCANCODE_A,             30,
    SDL_SCANCODE_S,             31,
    SDL_SCANCODE_D,             32,
    SDL_SCANCODE_F,             33,
    SDL_SCANCODE_G,             34,
    SDL_SCANCODE_H,             35,
    SDL_SCANCODE_J,             36,
    SDL_SCANCODE_K,             37,
    SDL_SCANCODE_L,             38,
    SDL_SCANCODE_SEMICOLON,     39,
    SDL_SCANCODE_APOSTROPHE,    40,
    SDL_SCANCODE_GRAVE,         41,
    SDL_SCANCODE_LSHIFT,        42,
    SDL_SCANCODE_BACKSLASH,     43,
    SDL_SCANCODE_Z,             44,
    SDL_SCANCODE_X,             45,
    SDL_SCANCODE_C,             46,
    SDL_SCANCODE_V,             47,
    SDL_SCANCODE_B,             48,
    SDL_SCANCODE_N,             49,
    SDL_SCANCODE_M,             50,
    SDL_SCANCODE_COMMA,         51,
    SDL_SCANCODE_PERIOD,        52,
    SDL_SCANCODE_KP_PERIOD,     52,
    SDL_SCANCODE_SLASH,         53,
    SDL_SCANCODE_KP_DIVIDE,     53,
    SDL_SCANCODE_RSHIFT,        54,
    /*  SDL_SCANCODE_PRINT,         55,*/
    SDL_SCANCODE_KP_MULTIPLY,   55,
    SDL_SCANCODE_LALT,          56,
    SDL_SCANCODE_RALT,          56,
    SDL_SCANCODE_LALT,          95,
    SDL_SCANCODE_RALT,          93,
    SDL_SCANCODE_MODE,          93,
    SDL_SCANCODE_MODE,          56,
    SDL_SCANCODE_RGUI,          56,
    SDL_SCANCODE_LGUI,          56,
    SDL_SCANCODE_SPACE,         57,
    SDL_SCANCODE_CAPSLOCK,      58,
    SDL_SCANCODE_F1,            59,
    SDL_SCANCODE_F2,            60,
    SDL_SCANCODE_F3,            61,
    SDL_SCANCODE_F4,            62,
    SDL_SCANCODE_F5,            63,
    SDL_SCANCODE_F6,            64,
    SDL_SCANCODE_F7,            65,
    SDL_SCANCODE_F8,            66,
    SDL_SCANCODE_F9,            67,
    SDL_SCANCODE_F10,           68,
    SDL_SCANCODE_NUMLOCKCLEAR,  69,
    SDL_SCANCODE_SCROLLLOCK,    70,
    SDL_SCANCODE_HOME,          71,
    SDL_SCANCODE_UP,            72,
    SDL_SCANCODE_PAGEUP,        73,
    SDL_SCANCODE_KP_MINUS,      74,
    SDL_SCANCODE_LEFT,          75,
    SDL_SCANCODE_RIGHT,         77,
    SDL_SCANCODE_KP_PLUS,       78,
    SDL_SCANCODE_END,           79,
    SDL_SCANCODE_DOWN,          80,
    SDL_SCANCODE_PAGEDOWN,      81,
    SDL_SCANCODE_INSERT,        82,
    SDL_SCANCODE_DELETE,        83,
    SDL_SCANCODE_F11,           87,
    SDL_SCANCODE_F12,           88,
    SDL_SCANCODE_KP_LESS,       89,
    SDL_SCANCODE_KP_PLUS,       90,
    SDL_SCANCODE_KP_GREATER,    91,
    //SDL_SCANCODE_QUESTION,      92,
    SDL_SCANCODE_GRAVE,         93,
    SDL_SCANCODE_SYSREQ,        55,
    SDL_SCANCODE_PAUSE,         95,
    SDL_SCANCODE_MENU,          97,
    SDL_SCANCODE_LGUI,          98,
    SDL_SCANCODE_RGUI,          99,
    //SDL_SCANCODE_COMPOSE,       99,
#else
    SDLK_ESCAPE,        1,
    SDLK_1,             2,
    SDLK_KP1,           2,
    SDLK_2,             3,
    SDLK_KP2,           3,
    SDLK_3,             4,
    SDLK_KP3,           4,
    SDLK_4,             5,
    SDLK_KP4,           5,
    SDLK_5,             6,
    SDLK_KP5,           6,
    SDLK_6,             7,
    SDLK_KP6,           7,
    SDLK_7,             8,
    SDLK_KP7,           8,
    SDLK_8,             9,
    SDLK_KP8,           9,
    SDLK_9,             10,
    SDLK_KP9,           10,
    SDLK_0,             11,
    SDLK_KP0,           11,
    SDLK_MINUS,         12,
    SDLK_EQUALS,        13,
    SDLK_BACKSPACE,     14,
    SDLK_TAB,           15,
    SDLK_q,             16,
    SDLK_w,             17,
    SDLK_e,             18,
    SDLK_r,             19,
    SDLK_t,             20,
    SDLK_y,             21,
    SDLK_u,             22,
    SDLK_i,             23,
    SDLK_o,             24,
    SDLK_p,             25,
    SDLK_LEFTBRACKET,   26,
    SDLK_RIGHTBRACKET,  27,
    SDLK_RETURN,        28,
    SDLK_KP_ENTER,      28,
    SDLK_LCTRL,         29,
    SDLK_RCTRL,         29,
    SDLK_LCTRL,         96,
    SDLK_RCTRL,         94,
    SDLK_a,             30,
    SDLK_s,             31,
    SDLK_d,             32,
    SDLK_f,             33,
    SDLK_g,             34,
    SDLK_h,             35,
    SDLK_j,             36,
    SDLK_k,             37,
    SDLK_l,             38,
    SDLK_SEMICOLON,     39,
    SDLK_QUOTE,         40,
    SDLK_BACKQUOTE,     41,
    SDLK_LSHIFT,        42,
    SDLK_BACKSLASH,     43,
    SDLK_z,             44,
    SDLK_x,             45,
    SDLK_c,             46,
    SDLK_v,             47,
    SDLK_b,             48,
    SDLK_n,             49,
    SDLK_m,             50,
    SDLK_COMMA,         51,
    SDLK_PERIOD,        52,
    SDLK_KP_PERIOD,     52,
    SDLK_SLASH,         53,
    SDLK_KP_DIVIDE,     53,
    SDLK_RSHIFT,        54,
    /*  SDLK_PRINT,         55,*/
    SDLK_KP_MULTIPLY,   55,
    SDLK_LALT,          56,
    SDLK_RALT,          56,
    SDLK_LALT,          95,
    SDLK_RALT,          93,
    SDLK_MODE,          93,
    SDLK_MODE,          56,
    SDLK_RMETA,         56,
    SDLK_LMETA,         56,
    SDLK_SPACE,         57,
    SDLK_CAPSLOCK,      58,
    SDLK_F1,            59,
    SDLK_F2,            60,
    SDLK_F3,            61,
    SDLK_F4,            62,
    SDLK_F5,            63,
    SDLK_F6,            64,
    SDLK_F7,            65,
    SDLK_F8,            66,
    SDLK_F9,            67,
    SDLK_F10,           68,
    SDLK_NUMLOCK,       69,
    SDLK_SCROLLOCK,     70,
    SDLK_HOME,          71,
    SDLK_UP,            72,
    SDLK_PAGEUP,        73,
    SDLK_KP_MINUS,      74,
    SDLK_LEFT,          75,
    SDLK_RIGHT,         77,
    SDLK_KP_PLUS,       78,
    SDLK_END,           79,
    SDLK_DOWN,          80,
    SDLK_PAGEDOWN,      81,
    SDLK_INSERT,        82,
    SDLK_DELETE,        83,
    SDLK_F11,           87,
    SDLK_F12,           88,
    SDLK_LESS,          89,
    SDLK_PLUS,          90,
    SDLK_GREATER,       91,
    SDLK_QUESTION,      92,
    SDLK_CARET,         93,
    SDLK_SYSREQ,        55,
    SDLK_PAUSE,         95,
    SDLK_MENU,          97,
    SDLK_LSUPER,        98,
    SDLK_RSUPER,        99,
    SDLK_COMPOSE,       99,
#endif
    -1, -1
} ;

/* ----------------------------------------------------------------- */
/* Son las variables que se desea acceder.                           */
/* El interprete completa esta estructura, si la variable existe.    */
/* (usada en tiempo de ejecucion)                                    */

DLVARFIXUP  __bgdexport( libkey, globals_fixup )[] =
{
    /* Nombre de variable global, puntero al dato, tamaño del elemento, cantidad de elementos */
    { "shift_status" , NULL, -1, -1 },
    { "ascii"        , NULL, -1, -1 },
    { "scan_code"    , NULL, -1, -1 },
    { NULL           , NULL, -1, -1 }
};

/* ----------------------------------------------------------------- */

static void add_key_equiv( int equiv, int keyconst )
{
    key_equiv * curr = &key_table[keyconst] ;

    if ( curr->next != NULL ) while ( curr->next != NULL ) curr = curr->next ;

    if ( curr->sdlk_equiv != 0 )
    {
        curr->next = malloc( sizeof( key_equiv ) ) ;
        curr = curr->next ;
        curr->next = NULL ;
    }

    curr->sdlk_equiv = equiv ;
}

/* ----------------------------------------------------------------- */

void hotkey_add( int mod, int sym, HOTKEY_CALLBACK callback )
{
    if ( hotkey_count >= hotkey_allocated )
    {
        hotkey_allocated = hotkey_count + 5;
        hotkey_list = realloc( hotkey_list, hotkey_allocated * sizeof( hotkey_list[0] ) );
    }

    if ( !hotkey_list )
    {
        fprintf( stderr, "No memory for alloc hotkey\n" );
        exit( -1 );
    }

    hotkey_list [hotkey_count].mod = mod;
    hotkey_list [hotkey_count].sym = sym;
    hotkey_list [hotkey_count].callback = callback;
    hotkey_count++;
}

/* ----------------------------------------------------------------- */

/*
 *  FUNCTION : process_key_events
 *
 *  Process all pending SDL events, updating all global variables
 *  and handling debug key presses and cannot be changed
 *
 *  PARAMS :
 *      None
 *
 *  RETURN VALUE :
 *      None
 */

static void process_key_events()
{
    SDL_Event e ;
    SDLMod m ;
    int k, asc ;
    int pressed ;
    key_equiv * curr ;
    int keypress ;
    static struct
    {
        int ascii ;
        int scancode ;
    }
    keyring [64] ;
    static int keyring_start = 0, keyring_tail = 0 ;
    int ignore_key, n;

    /* Actualizar eventos */

    keypress = 0 ;
    m = SDL_GetModState() ;

    /* Procesa los eventos pendientes */
    /* Reset ascii and scancode if last key was released... */
    /* must check all the linked equivs */

    pressed = 0 ;
    if ( GLODWORD( libkey,  SCANCODE ) )
    {
        curr = &key_table[GLODWORD( libkey,  SCANCODE )] ;
        while ( curr != NULL && pressed == 0 )
        {
            if ( keystate[curr->sdlk_equiv] ) pressed = 1 ;
            curr = curr->next ;
        }
    }

    if ( !pressed )
    {
        GLODWORD( libkey,  ASCII )     = 0 ;
        GLODWORD( libkey,  SCANCODE )  = 0 ;
    }

#if SDL_VERSION_ATLEAST(1,3,0)
    while ( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYUP ) > 0 )
#else
    while ( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_EVENTMASK(SDL_KEYDOWN)|SDL_EVENTMASK(SDL_KEYUP) ) > 0 )
#endif
    {
        switch ( e.type )
        {
            case SDL_KEYDOWN:
                ignore_key = 0;
                /* KeyDown HotKey */
                if ( hotkey_count )
                    for ( n = 0; n < hotkey_count; n++ )
                    {
                        if ((( hotkey_list[n].mod & e.key.keysym.mod ) == hotkey_list[n].mod ) &&
                                ( !hotkey_list[n].sym || ( hotkey_list[n].sym == e.key.keysym.sym ) ) )
                        {
                            ignore_key = hotkey_list[n].callback( e.key.keysym );
                        }
                    }
                /* KeyDown HotKey */

                if ( ignore_key ) break ;

                /* Almacena la pulsación de la tecla */

                k = sdl_equiv[e.key.keysym.sym];

                m = e.key.keysym.mod ;

                if ( !keypress )
                {
                    GLODWORD( libkey,  SCANCODE )  = k ;
                    if ( e.key.keysym.unicode )
                    {
                        asc = win_to_dos[e.key.keysym.unicode & 0xFF] ;

                        /* ascii mayusculas */
                        if ( asc >= 'a' && asc <= 'z' && ( m & KMOD_LSHIFT || m & KMOD_RSHIFT || keystate[SDLK_CAPSLOCK] ) )
                            asc -= 0x20 ;
                    }
                    else
                    {
                        asc = 0 ; /* NON PRINTABLE */
                    }

                    GLODWORD( libkey,  ASCII ) = asc ;
                    keypress = 1 ;
                }
                else
                {
                    keyring[keyring_tail].scancode = k ;
                    if ( e.key.keysym.unicode )
                    {
                        asc = win_to_dos[e.key.keysym.unicode & 0x7F] ;

                        /*ascii mayusculas */
                        if ( asc >= 'a' && asc <= 'z' && ( m & KMOD_LSHIFT || m & KMOD_RSHIFT || keystate[SDLK_CAPSLOCK] ) )
                            asc -= 0x20 ;
                    }
                    else
                    {
                        asc = 0 ; /* NON PRINTABLE */
                    }
                    keyring[keyring_tail].ascii = asc ;
                    if ( ++keyring_tail == 64 ) keyring_tail = 0 ;
                }

                break ;

            case SDL_KEYUP:
                /* Do nothing, Bennu is key_up unsensitive */
                break ;
        }
    }

    if ( !keypress && keyring_start != keyring_tail )
    {
        GLODWORD( libkey,  ASCII )     = keyring[keyring_start].ascii ;
        GLODWORD( libkey,  SCANCODE )  = keyring[keyring_start].scancode ;
        if ( ++keyring_start == 64 ) keyring_start = 0 ;
    }

    /* Now actualized every frame... */
    GLODWORD( libkey,  SHIFTSTATUS ) =
        ( ( m & KMOD_RSHIFT ) ? STAT_RSHIFT : 0 ) |
        ( ( m & KMOD_LSHIFT ) ? STAT_LSHIFT : 0 ) |

        ( ( m & KMOD_CTRL   ) ? STAT_CTRL   : 0 ) |
        ( ( m & KMOD_ALT    ) ? STAT_ALT    : 0 ) |

        ( ( m & KMOD_RCTRL  ) ? STAT_RCTRL  : 0 ) |
        ( ( m & KMOD_LCTRL  ) ? STAT_LCTRL  : 0 ) |

        ( ( m & KMOD_RALT   ) ? STAT_RALT   : 0 ) |
        ( ( m & KMOD_LALT   ) ? STAT_LALT   : 0 ) |

        ( ( m & KMOD_NUM    ) ? STAT_NUM    : 0 ) |
        ( ( m & KMOD_CAPS   ) ? STAT_CAPS   : 0 ) |
        ( ( m & KMOD_SHIFT  ) ? STAT_SHIFT  : 0 ) ;
}

/* ----------------------------------------------------------------- */

/* Bigest priority first execute
   Lowest priority last execute */

HOOK __bgdexport( libkey, handler_hooks )[] =
{
    { 4900, process_key_events },
    {    0, NULL               }
} ;

/* ----------------------------------------------------------------- */
/* Funciones de inicializacion del modulo/plugin                     */

void __bgdexport( libkey, module_initialize )()
{
    int * ptr = equivs ;

    if ( !SDL_WasInit( SDL_INIT_VIDEO ) ) SDL_InitSubSystem( SDL_INIT_VIDEO );

    memset( sdl_equiv, 0, sizeof( sdl_equiv ) );
    memset( key_table, 0, sizeof( key_table ) ) ;

    while ( *ptr != -1 )
    {
        sdl_equiv[*ptr] = ptr[1] ;
        add_key_equiv( ptr[0], ptr[1] ) ;
        ptr += 2 ;
    }

#if SDL_VERSION_ATLEAST(1,3,0)
    if ( !keystate ) keystate = SDL_GetKeyboardState( NULL );
#else
    if ( !keystate ) keystate = SDL_GetKeyState( NULL );
#endif

    SDL_EnableUNICODE( 1 );
}

/* ----------------------------------------------------------------- */

void __bgdexport( libkey, module_finalize )()
{
    /* FREE used key_equivs... note base 127 equivs are static not allocated... */
    int i ;
    key_equiv * aux ;
    key_equiv * curr = key_table ;

    for ( i = 0;i < 127;i++ )
    {
        if ( curr->next != NULL )
        {
            curr = curr->next ;
            while ( curr->next != NULL )
            {
                aux = curr ;
                curr = curr->next;
                free( aux ) ;
            }
            free( curr ) ;
        }
    }

    if ( SDL_WasInit( SDL_INIT_VIDEO ) ) SDL_QuitSubSystem( SDL_INIT_VIDEO );
}

/* ----------------------------------------------------------------- */
