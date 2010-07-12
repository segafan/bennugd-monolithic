#include "mod_wiiuse.h"
#include <SDL_stdinc.h>
#ifndef __MONOLITHIC__
#include "mod_wiiuse_symbols.h"
#endif

CONDITIONALLY_STATIC int wiiInit(INSTANCE *my, int *params){

    return( (int) wiiuse_init(params[0]) );

}

CONDITIONALLY_STATIC int wiiFind(INSTANCE *my, int *params){

    wiiMote **wl = (wiiMote **)(params[0]);
    return(wiiuse_find(wl, params[1], params[2]));

}

CONDITIONALLY_STATIC int wiiConnect(INSTANCE *my, int *params){

    wiiMote **wl = (wiiMote **)(params[0]);
   	return(wiiuse_connect(wl, params[1]));

}

CONDITIONALLY_STATIC void wiiDestroy(INSTANCE *my, int *params){

    wiiMote **wl = (wiiMote **)(params[0]);
    wiiuse_cleanup(wl, params[1]);

}

CONDITIONALLY_STATIC int wiiPoll(INSTANCE *my, int *params){

    wiiMote **wm = (wiiMote **)(params[0]);
    return(wiiuse_poll(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiGet(INSTANCE *my, int *params){

    wiiMote **wl = (wiiMote **)(params[0]);
    return((int)wl[params[1]]);

}

CONDITIONALLY_STATIC int wiiMoteGetEvent(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(wm->event);

}

CONDITIONALLY_STATIC void wiiMoteDisconnected(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    wiiuse_disconnected(wm);

}

CONDITIONALLY_STATIC void wiiMoteSetLeds(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    wiiuse_set_leds(wm, params[1]);

}

CONDITIONALLY_STATIC void wiiMoteSetRumble(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    wiiuse_rumble(wm, params[1]);

}

CONDITIONALLY_STATIC void wiiMoteSetMotion(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    wiiuse_set_ir(wm, params[1]);

}

CONDITIONALLY_STATIC void wiiMoteSetRotation(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    wiiuse_motion_sensing(wm, params[1]);

}

CONDITIONALLY_STATIC void wiiMoteToggleRumble(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    wiiuse_toggle_rumble(wm);

}

CONDITIONALLY_STATIC int wiiMoteIsMotionActivated(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(WIIUSE_USING_IR(wm));

}

CONDITIONALLY_STATIC int wiiMoteIsRotationActivated(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(WIIUSE_USING_ACC(wm));

}

CONDITIONALLY_STATIC int wiiMoteIsUsingExpansion(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(WIIUSE_USING_EXP(wm));

}

CONDITIONALLY_STATIC int wiiMoteGetExpansion(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(wm->exp.type);

}

CONDITIONALLY_STATIC int wiiMoteIsKeyPressed(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(IS_PRESSED(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiMoteIsKeyJustPressed(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(IS_JUST_PRESSED(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiMoteIsKeyReleased(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(IS_RELEASED(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiMoteIsKeyHeld(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(IS_HELD(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiNunchukIsKeyPressed(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    return(IS_PRESSED(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiNunchukIsKeyJustPressed(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    return(IS_JUST_PRESSED(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiNunchukIsKeyReleased(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    return(IS_RELEASED(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiNunchukIsKeyHeld(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    return(IS_HELD(wm, params[1]));

}

CONDITIONALLY_STATIC int wiiNunchukGetRoll(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->orient.roll;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiNunchukGetPitch(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->orient.pitch;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiNunchukGetYaw(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->orient.yaw;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiNunchukGetAccelX(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->accel.x;
    return(value);

}

CONDITIONALLY_STATIC int wiiNunchukGetAccelY(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    int value = wm->accel.y;
    return(value);

}

CONDITIONALLY_STATIC int wiiNunchukGetAccelZ(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    int value = wm->accel.x;
    return(value);

}

CONDITIONALLY_STATIC int wiiNunchukGetGravityX(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->gforce.x;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiNunchukGetGravityY(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->gforce.y;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiNunchukGetGravityZ(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->gforce.z;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiNunchukGetAngle(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->js.ang;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiNunchukGetMagnitude(INSTANCE *my, int *params){

    wiiMote *aux = (wiiMote *)(params[0]);
    wiiNunchuk *wm = (wiiNunchuk *)&aux->exp.nunchuk;
    float value = wm->js.mag;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiMoteGetRoll(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    float value = wm->orient.roll;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiMoteGetPitch(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    float value = wm->orient.pitch;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiMoteGetYaw(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    float value = wm->orient.yaw;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiMoteGetX(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(wm->ir.x);

}

CONDITIONALLY_STATIC int wiiMoteGetY(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    return(wm->ir.y);

}

CONDITIONALLY_STATIC int wiiMoteGetZ(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    float value = wm->ir.z;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiMoteGetAccelX(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    int value = wm->accel.x;
    return(value);

}

CONDITIONALLY_STATIC int wiiMoteGetAccelY(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    int value = wm->accel.y;
    return(value);

}

CONDITIONALLY_STATIC int wiiMoteGetAccelZ(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    int value = wm->accel.z;
    return(value);

}

CONDITIONALLY_STATIC int wiiMoteGetGravityX(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    float value = wm->gforce.x;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiMoteGetGravityY(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    float value = wm->gforce.y;
    return(*(Sint32 *)&value);

}

CONDITIONALLY_STATIC int wiiMoteGetGravityZ(INSTANCE *my, int *params){

    wiiMote *wm = (wiiMote *)(params[0]);
    float value = wm->gforce.z;
    return(*(Sint32 *)&value);

}

