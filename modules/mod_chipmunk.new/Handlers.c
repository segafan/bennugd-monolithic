#include "Handlers.h"
#include "globales.h"
extern cpSpace * cpEspacio;

extern nodo * ListaHandlers;

typedef struct {int a,b;} param2d;

param2d modChipmunkParam(int a,int b){
    param2d v;
    v.a=a;
    v.b=b;
return v;
}
int compara(void *a, void* bp){
    param2d* am=a;
    Hands* bm=bp;
    if ((am->a == bm->a && am->b == bm->b) || (am->b == bm->a && am->a == bm->b))
        return 1;
    return 0;
}

 int modChipmunkBeginCall(cpArbiter *arb, struct cpSpace *space, void *data){
    int ret=1;
   INSTANCE * r ;
   Hands * d=data;
   r = instance_new ((d->funciones)[0], 0) ; // Create Function
   PRIDWORD(r, 0) = (int)arb ;    // Argument 1
   PRIDWORD(r, 4) = (d->parametros)[0] ;    // Argument 2
   ret = instance_go(r) ; // Call Function
   return ret;
}

int modChipmunkPreSolveCall(cpArbiter *arb, struct cpSpace *space, void *data){
    int ret=1;
   INSTANCE * r ;
   Hands * d=data;
   r = instance_new ((d->funciones)[1], 0) ; // Create Function
   PRIDWORD(r, 0) = (int)arb ;    // Argument 1
   PRIDWORD(r, 4) = (d->parametros)[1] ;    // Argument 2
   ret = instance_go(r) ; // Call Function
   return ret;
}

void modChipmunkPostSolveCall(cpArbiter *arb, struct cpSpace *space, void *data){
   INSTANCE * r ;
   Hands * d=data;
   r = instance_new ((d->funciones)[2], 0) ; // Create Function
   PRIDWORD(r, 0) = (int)arb ;    // Argument 1
   PRIDWORD(r, 4) = (d->parametros)[2] ;    // Argument 2
   instance_go(r) ; // Call Function
}

void modChipmunkSeparateCall(cpArbiter *arb, struct cpSpace *space, void *data){
   INSTANCE * r ;
   Hands * d=data;
   r = instance_new ((d->funciones)[3], 0) ; // Create Function
   PRIDWORD(r, 0) = (int)arb ;    // Argument 1
   PRIDWORD(r, 4) = (d->parametros)[3] ;    // Argument 2
   instance_go(r) ; // Call Function
}

Hands * modChipmunkNuevoHandler(){
    Hands * h=malloc(sizeof(Hands));
    memset(h->funciones,0,sizeof(PROCDEF *)*4);  //setear enteros
    memset(h->parametros,0,sizeof(void *)*4);
    return h;
}

void modChipmunkFalloHandler(int * params,Hands * h){
string_discard(params[2]);
    string_discard(params[3]);
    string_discard(params[4]);
    string_discard(params[5]);
free (h);
}

 int modcpSpaceAddCollisionHandler(INSTANCE * my, int * params){
    param2d par=modChipmunkParam(params[0], params[1]);
    if (LLbusca(ListaHandlers, &par, compara)){
        printf("Se intentó crear un handler a (%d, %d), pero ya existe uno \n",params[0],params[1]);
        return -1;
    }

    Hands * handler = modChipmunkNuevoHandler();
    char * begins = string_get(params[2]);
    char * preSolves = string_get(params[3]);
    char * postSolves = string_get(params[4]);
    char * separates = string_get(params[5]);
    mayusStr(begins);
    mayusStr(preSolves);
    mayusStr(postSolves);
    mayusStr(separates);
    handler->a=params[0];
    handler->b=params[1];

    PROCDEF * proc;
    if (strlen(begins)!=0){
        proc = procdef_get_by_name (begins); // Get definition function (name must be in uppercase)
        if (!proc)
        {
            printf ("Función %s no encontrada\n", begins) ;
            modChipmunkFalloHandler(params,handler);
            return -1 ;
        }
        handler->funciones[0]=proc;
        handler->parametros[0]=(void *)params[6];
    }else{
        handler->funciones[0]=NULL;
        handler->parametros[0]=NULL;
    }

    if (strlen(preSolves)!=0){
        proc = procdef_get_by_name (preSolves); // Get definition function (name must be in uppercase)
        if (!proc)
        {
            printf ("Función %s no encontrada\n", preSolves) ;
            modChipmunkFalloHandler(params,handler);
            return -1 ;
        }
        handler->funciones[1]=proc;
        handler->parametros[1]=(void *)params[7];
    }else{
        handler->funciones[1]=NULL;
        handler->parametros[1]=NULL;
    }

    if (strlen(postSolves)!=0){
        proc = procdef_get_by_name (postSolves); // Get definition function (name must be in uppercase)
        if (!proc)
        {
            printf ("Función %s no encontrada\n", postSolves) ;
            modChipmunkFalloHandler(params,handler);
            return -1 ;
        }
        handler->funciones[2]=proc;
        handler->parametros[2]=(void *)params[8];
    }else{
        handler->funciones[2]=NULL;
        handler->parametros[2]=NULL;
    }

    if (strlen(separates)!=0){
        proc = procdef_get_by_name (separates); // Get definition function (name must be in uppercase)
        if (!proc)
        {
            printf ("Función %s no encontrada\n", separates) ;
            modChipmunkFalloHandler(params,handler);
            return -1 ;
        }
        handler->funciones[3]=proc;
        handler->parametros[3]=(void *)params[9];
    }else{
        handler->funciones[3]=NULL;
        handler->parametros[3]=NULL;
    }

    cpSpaceAddCollisionHandler(
        cpEspacio,
        handler->a,handler->b,
        handler->funciones[0]? modChipmunkBeginCall : NULL, //si la string es null, poner null, de lo contrario poner beginCall
        handler->funciones[1]? modChipmunkPreSolveCall : NULL,
        handler->funciones[2]? modChipmunkPostSolveCall : NULL,
        handler->funciones[3]? modChipmunkSeparateCall : NULL,
        (void *)handler
    );
    string_discard(params[2]);
    string_discard(params[3]);
    string_discard(params[4]);
    string_discard(params[5]);
    LLagrega(ListaHandlers,handler);
    return 1;
}

int modcpSpaceRemoveCollisionHandler(INSTANCE * my, int * params){
    //cpSpaceRemoveCollisionHandler(cpEspacio, params[0], params[1],funcionElmHand);
    param2d par=modChipmunkParam(params[0], params[1]);
    LLelimina(ListaHandlers, &par, compara,funcionElmHand,1);
    return 1;
}

void funcionElmHand(void * v){
    Hands * h=v;
    cpSpaceRemoveCollisionHandler(cpEspacio, h->a, h->b);
    free (h);
}


