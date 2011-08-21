#include "Espacio.h"

extern cpSpace * cpEspacio;

int modcpSpaceGetCurrentTimeStep(INSTANCE * my, int * params){
    float r=cpSpaceGetCurrentTimeStep(cpEspacio);
    return *(int*)&r;
}



int modGetStaticBody(INSTANCE * my, int * params)
{
    return cpEspacio->staticBody;
}

 int modcpSpaceActivateShapesTouchingShape(INSTANCE * my, int * params)
{
    cpSpaceActivateShapesTouchingShape(cpEspacio,( cpShape * ) params[0]);
    return 0;
}
 int modcpSpaceResizeStaticHash(INSTANCE * my, int * params)
{
    //cpHashResizeHash(cpEspacio,*(( float * ) &params[0]),params[1]);
    printf("Función en desuso\n");
    return 0;
}

 int modcpSpaceResizeActiveHash(INSTANCE * my, int * params)
{
   // cpSpaceResizeActiveHash(cpEspacio,*(( float * ) &params[0]),params[1]);
    printf("Función en desuso\n");
    return 0;
}

int modcpSpaceUseSpatialHash(INSTANCE * my, int * params)
{
    cpSpaceUseSpatialHash(cpEspacio, *(float*)&params[0], params[1]);
    return 1;
}

