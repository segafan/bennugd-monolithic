#ifndef __MODWIIUSE_SYMBOLS_H
#define __MODWIIUSE_SYMBOLS_H

#include <bgddl.h>
#include "mod_wiiuse.h"

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int wiiInit(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiFind(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiConnect(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC void wiiDestroy(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiPoll(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiGet(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetEvent(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC void wiiMoteDisconnected(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC void wiiMoteSetLeds(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC void wiiMoteSetRumble(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC void wiiMoteSetMotion(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC void wiiMoteSetRotation(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC void wiiMoteToggleRumble(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteIsMotionActivated(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteIsRotationActivated(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteIsUsingExpansion(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetExpansion(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteIsKeyPressed(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteIsKeyJustPressed(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteIsKeyReleased(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteIsKeyHeld(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukIsKeyPressed(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukIsKeyJustPressed(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukIsKeyReleased(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukIsKeyHeld(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetRoll(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetPitch(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetYaw(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetAccelX(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetAccelY(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetAccelZ(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetGravityX(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetGravityY(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetGravityZ(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetAngle(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiNunchukGetMagnitude(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetRoll(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetPitch(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetYaw(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetX(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetY(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetZ(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetAccelX(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetAccelY(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetAccelZ(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetGravityX(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetGravityY(INSTANCE *my, int *params);
extern CONDITIONALLY_STATIC int wiiMoteGetGravityZ(INSTANCE *my, int *params);
#endif

DLLEXPORT DLSYSFUNCS __bgdexport(mod_wiiuse, functions_exports)[] = {
    {"WIIINIT"                   , "I"  , TYPE_INT      , SYSMACRO(wiiInit)                     },
    {"WIIFIND"                   , "III", TYPE_INT      , SYSMACRO(wiiFind)                     },
    {"WIICONNECT"                , "II" , TYPE_INT      , SYSMACRO(wiiConnect)                  },
    {"WIIDESTROY"                , "II" , TYPE_UNDEFINED, SYSMACRO(wiiDestroy)                  },
	
    {"WIIGET"                    , "II" , TYPE_DWORD    , SYSMACRO(wiiGet)                      },
    {"WIIPOLL"                   , "II" , TYPE_INT      , SYSMACRO(wiiPoll)                     },
	
    {"WIIMOTEGETEVENT"           , "I"  , TYPE_INT      , SYSMACRO(wiiMoteGetEvent)             },
    {"WIIMOTEDISCONNECTED"       , "I"  , TYPE_UNDEFINED, SYSMACRO(wiiMoteDisconnected)         },
	
    {"WIIMOTESETLEDS"            , "II" , TYPE_UNDEFINED, SYSMACRO(wiiMoteSetLeds)              },
    {"WIIMOTESETRUMBLE"          , "II" , TYPE_UNDEFINED, SYSMACRO(wiiMoteSetRumble)            },
    {"WIIMOTESETROTATION"        , "II" , TYPE_UNDEFINED, SYSMACRO(wiiMoteSetRotation)          },
    {"WIIMOTESETMOTION"          , "II" , TYPE_UNDEFINED, SYSMACRO(wiiMoteSetMotion)            },
    {"WIIMOTETOGGLERUMBLE"       , "I"  , TYPE_UNDEFINED, SYSMACRO(wiiMoteToggleRumble)         },
    {"WIIMOTEISROTATIONACTIVATED", "I"  , TYPE_INT      , SYSMACRO(wiiMoteIsRotationActivated)  },
    {"WIIMOTEISMOTIONACTIVATED"  , "I"  , TYPE_INT      , SYSMACRO(wiiMoteIsMotionActivated)    },
    {"WIIMOTEGETEXPANSION"       , "I"  , TYPE_INT      , SYSMACRO(wiiMoteGetExpansion)         },
    {"WIIMOTEISUSINGEXPANSION"   , "I"  , TYPE_INT      , SYSMACRO(wiiMoteIsUsingExpansion)     },
	
    {"WIIMOTEISKEYPRESSED"       , "II" , TYPE_INT      , SYSMACRO(wiiMoteIsKeyPressed)         },
    {"WIIMOTEISKEYJUSTPRESSED"   , "II" , TYPE_INT      , SYSMACRO(wiiMoteIsKeyJustPressed)     },
    {"WIIMOTEISKEYRELEASED"      , "II" , TYPE_INT      , SYSMACRO(wiiMoteIsKeyReleased)        },
    {"WIIMOTEISKEYHELD"          , "II" , TYPE_INT      , SYSMACRO(wiiMoteIsKeyHeld)            },
	
    {"WIIMOTEGETROLL"            , "I"  , TYPE_FLOAT    , SYSMACRO(wiiMoteGetRoll)              },
    {"WIIMOTEGETPITCH"           , "I"  , TYPE_FLOAT    , SYSMACRO(wiiMoteGetPitch)             },
    {"WIIMOTEGETYAW"             , "I"  , TYPE_FLOAT    , SYSMACRO(wiiMoteGetYaw)               },
    {"WIIMOTEGETX"               , "I"  , TYPE_INT      , SYSMACRO(wiiMoteGetX)                 },
    {"WIIMOTEGETY"               , "I"  , TYPE_INT      , SYSMACRO(wiiMoteGetY)                 },
    {"WIIMOTEGETZ"               , "I"  , TYPE_FLOAT    , SYSMACRO(wiiMoteGetZ)                 },
    {"WIIMOTEGETACCELX"          , "I"  , TYPE_INT      , SYSMACRO(wiiMoteGetAccelX)            },
    {"WIIMOTEGETACCELY"          , "I"  , TYPE_INT      , SYSMACRO(wiiMoteGetAccelY)            },
    {"WIIMOTEGETACCELZ"          , "I"  , TYPE_INT      , SYSMACRO(wiiMoteGetAccelZ)            },
    {"WIIMOTEGETGRAVITYX"        , "I"  , TYPE_FLOAT    , SYSMACRO(wiiMoteGetGravityX)          },
    {"WIIMOTEGETGRAVITYY"        , "I"  , TYPE_FLOAT    , SYSMACRO(wiiMoteGetGravityY)          },
    {"WIIMOTEGETGRAVITYZ"        , "I"  , TYPE_FLOAT    , SYSMACRO(wiiMoteGetGravityZ)          },
	
    {"WIINUNCHUKISKEYPRESSED"    , "II" , TYPE_INT      , SYSMACRO(wiiNunchukIsKeyPressed)      },
    {"WIINUNCHUKISKEYJUSTPRESSED", "II" , TYPE_INT      , SYSMACRO(wiiNunchukIsKeyJustPressed)  },
    {"WIINUNCHUKISKEYRELEASED"   , "II" , TYPE_INT      , SYSMACRO(wiiNunchukIsKeyReleased)     },
    {"WIINUNCHUKISKEYHELD"       , "II" , TYPE_INT      , SYSMACRO(wiiNunchukIsKeyHeld)         },
	
    {"WIINUNCHUKGETANGLE"        , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetAngle)          },
    {"WIINUNCHUKGETMAGNITUDE"    , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetMagnitude)      },
    {"WIINUNCHUKGETROLL"         , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetRoll)           },
    {"WIINUNCHUKGETPITCH"        , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetPitch)          },
    {"WIINUNCHUKGETYAW"          , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetYaw)            },
    {"WIINUNCHUKGETACCELX"       , "I"  , TYPE_INT      , SYSMACRO(wiiNunchukGetAccelX)         },
    {"WIINUNCHUKGETACCELY"       , "I"  , TYPE_INT      , SYSMACRO(wiiNunchukGetAccelY)         },
    {"WIINUNCHUKGETACCELZ"       , "I"  , TYPE_INT      , SYSMACRO(wiiNunchukGetAccelZ)         },
    {"WIINUNCHUKGETGRAVITYX"     , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetGravityX)       },
    {"WIINUNCHUKGETGRAVITYY"     , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetGravityY)       },
    {"WIINUNCHUKGETGRAVITYZ"     , "I"  , TYPE_FLOAT    , SYSMACRO(wiiNunchukGetGravityZ)       },
	
    {0, 0, 0, 0}
	
};

DLLEXPORT DLCONSTANT __bgdexport(mod_wiiuse, constants_def)[] = {
	
    {"WIIMOTE_LED_NONE"                  , TYPE_DWORD, WIIMOTE_LED_NONE                   },
    {"WIIMOTE_LED_1"                     , TYPE_DWORD, WIIMOTE_LED_1                      },
    {"WIIMOTE_LED_2"                     , TYPE_DWORD, WIIMOTE_LED_2                      },
    {"WIIMOTE_LED_3"                     , TYPE_DWORD, WIIMOTE_LED_3                      },
    {"WIIMOTE_LED_4"                     , TYPE_DWORD, WIIMOTE_LED_4                      },
	
    {"WIIMOTE_BUTTON_A"                  , TYPE_DWORD, WIIMOTE_BUTTON_A                   },
    {"WIIMOTE_BUTTON_B"                  , TYPE_DWORD, WIIMOTE_BUTTON_B                   },
    {"WIIMOTE_BUTTON_UP"                 , TYPE_DWORD, WIIMOTE_BUTTON_UP                  },
    {"WIIMOTE_BUTTON_DOWN"               , TYPE_DWORD, WIIMOTE_BUTTON_DOWN                },
    {"WIIMOTE_BUTTON_LEFT"               , TYPE_DWORD, WIIMOTE_BUTTON_LEFT                },
    {"WIIMOTE_BUTTON_RIGHT"              , TYPE_DWORD, WIIMOTE_BUTTON_RIGHT               },
    {"WIIMOTE_BUTTON_MINUS"              , TYPE_DWORD, WIIMOTE_BUTTON_MINUS               },
    {"WIIMOTE_BUTTON_PLUS"               , TYPE_DWORD, WIIMOTE_BUTTON_PLUS                },
    {"WIIMOTE_BUTTON_ONE"                , TYPE_DWORD, WIIMOTE_BUTTON_ONE                 },
    {"WIIMOTE_BUTTON_TWO"                , TYPE_DWORD, WIIMOTE_BUTTON_TWO                 },
    {"WIIMOTE_BUTTON_HOME"               , TYPE_DWORD, WIIMOTE_BUTTON_HOME                },
	
    {"WIIMOTE_BUTTON_C"                  , TYPE_DWORD, NUNCHUK_BUTTON_C                   },
    {"WIIMOTE_BUTTON_Z"                  , TYPE_DWORD, NUNCHUK_BUTTON_Z                   },
	
    {"WIIUSE_NONE"                       , TYPE_DWORD, WIIUSE_NONE                        },
    {"WIIUSE_EVENT"                      , TYPE_DWORD, WIIUSE_EVENT                       },
    {"WIIUSE_STATUS"                     , TYPE_DWORD, WIIUSE_STATUS                      },
    {"WIIUSE_DISCONNECT"                 , TYPE_DWORD, WIIUSE_DISCONNECT                  },
    {"WIIUSE_UNEXPECTED_DISCONNECT"      , TYPE_DWORD, WIIUSE_UNEXPECTED_DISCONNECT       },
    {"WIIUSE_READ_DATA"                  , TYPE_DWORD, WIIUSE_READ_DATA                   },
    {"WIIUSE_NUNCHUK_INSERTED"           , TYPE_DWORD, WIIUSE_NUNCHUK_INSERTED            },
    {"WIIUSE_CLASSIC_CTRL_INSERTED"      , TYPE_DWORD, WIIUSE_CLASSIC_CTRL_INSERTED       },
    {"WIIUSE_GUITAR_HERO_3_CTRL_INSERTED", TYPE_DWORD, WIIUSE_GUITAR_HERO_3_CTRL_INSERTED },
    {"WIIUSE_NUNCHUK_REMOVED"            , TYPE_DWORD, WIIUSE_NUNCHUK_REMOVED             },
    {"WIIUSE_CLASSIC_CTRL_REMOVED"       , TYPE_DWORD, WIIUSE_CLASSIC_CTRL_REMOVED        },
    {"WIIUSE_GUITAR_HERO_3_CTRL_REMOVED" , TYPE_DWORD, WIIUSE_GUITAR_HERO_3_CTRL_REMOVED  },
	
    {"WII_EXP_NONE"                      , TYPE_DWORD, EXP_NONE                           },
    {"WII_EXP_NUNCHUK"                   , TYPE_DWORD, EXP_NUNCHUK                        },
    {"WII_EXP_CLASSIC"                   , TYPE_DWORD, EXP_CLASSIC                        },
    {"WII_EXP_GUITARHERO3"               , TYPE_DWORD, EXP_GUITAR_HERO_3                  },
	
    {NULL                                , 0         , 0                                  }
	
} ;

#endif
