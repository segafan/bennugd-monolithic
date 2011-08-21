#include "Cuerpo.h"
#include "constantes.h"
#include "locales.h"
#include "estructuras.h"
#include "Miscelanea.h"

extern cpSpace * cpEspacio;
extern DataPointer  ListaCuerpos;

int modgetBody(INSTANCE * my, int * params)
{
    return ( int  ) cpEspacio->staticBody;
}

int modcpBodyLocal2World(INSTANCE * my, int * params)
{
    cpVect *ind=params[2];
    *ind = cpBodyLocal2World(( cpBody * ) params[0], *(cpVect *) params[1]);
    return 0;
}

int modDefcpBody(INSTANCE * my, int * params)
{
    cpVect  *flo2;
    int sel=params [1];
    float flo1;
    cpBody * espacio = ( cpBody * ) params [0];

    switch (sel)
    {
    case CP_C_M:
        flo1 = *((float *)&params[2]);
        //espacio->m=flo1;
        cpBodySetMass(espacio,flo1);
        break;
    case CP_C_I:
        flo1 = *((float *)&params[2]);
        //espacio->i=flo1;
        cpBodySetMoment(espacio,flo1);
        break;
    case CP_C_P:
        flo2=params[2];
        espacio->p=*flo2;
        break;
    case CP_C_V:
        flo2=params[2];
        espacio->v=*flo2;
        break;
    case CP_C_F:
        flo2=params[2];
        espacio->f=*flo2;
        break;
    case CP_C_A:
        flo1 = *((float *)&params[2]);
        //espacio->a=flo1;
        cpBodySetAngle(espacio, flo1 );

        break;
    case CP_C_W:
        flo1 = *((float *)&params[2]);
        espacio->w=flo1;
        break;
    case CP_C_T:
        flo1 = *((float *)&params[2]);
        espacio->t=flo1;
        break;
    case CP_C_ROT:
        flo2=params[2];
        espacio->rot=*flo2;
        break;
    case CP_C_V_LIMIT:
        flo1 = *((float *)&params[2]);
        espacio->v_limit=flo1;
        break;
    case CP_C_W_LIMIT:
        flo1 = *((float *)&params[2]);
        espacio->w_limit=flo1;
        break;
    }

    return 0;
}


int modGetEcpBody(INSTANCE * my, int * params)
{
    int sel=params [1];
    cpBody * espacioM = ( cpBody * ) params [0];
    cpVect cp;
    cpVect *vec;
    float a;
    switch (sel)
    {
    case CP_C_M:
        return *((int *)&espacioM->m);
        break;
    case CP_C_I:
        return *((int *)&espacioM->i);
        break;
    case CP_C_P:
        cp=espacioM->p;  //puntero
        vec=params [2];
        vec->x=cp.x;
        vec->y=cp.y;
        return 0;
        break;
    case CP_C_V:
        cp=espacioM->v;  //puntero
        vec=params [2];
        vec->x=cp.x;
        vec->y=cp.y;
        return 0;
        break;
    case CP_C_F:
        cp=espacioM->f;  //puntero
        vec=params [2];
        vec->x=cp.x;
        vec->y=cp.y;
        return 0;
        break;
    case CP_C_A:
        a=(float)espacioM->a;
        return *((int *)&a);
        break;
    case CP_C_W:
        a=(float)espacioM->w;
        return *((int *)&a);
        break;
    case CP_C_T:
        a=(float)espacioM->t;
        return *((int *)&a);
        break;
    case CP_C_ROT:
        cp=espacioM->rot;  //puntero
        vec=params [2];
        vec->x=cp.x;
        vec->y=cp.y;
        return 0;
        break;
    case CP_C_V_LIMIT:
        return *((int *)&espacioM->v_limit);
        break;
    case CP_C_W_LIMIT:
        return *((int *)&espacioM->w_limit);
        break;
    case CP_C_DATA:
        return espacioM->data;
        break;
    }

    return 0;
}



int modcpBodySetMass(INSTANCE * my, int * params)
{
    cpBodySetMass((cpBody * ) params[0],*(( float * ) &params[1]));
    return 0;
}

int modcpBodySetMoment(INSTANCE * my, int * params)
{
    cpBodySetMoment((cpBody * ) params[0],*(( float * ) &params[1]));
    return 0;
}

int modcpBodySetAngle(INSTANCE * my, int * params)
{
    cpBodySetAngle((cpBody * ) params[0],*(( float * ) &params[1]));
    return 0;
}

int modcpBodyUpdatePosition(INSTANCE * my, int * params)
{
    cpBodyUpdatePosition((cpBody * ) params[0],*(( float * ) &params[1]));
    return 0;
}

int modcpBodyResetForces(INSTANCE * my, int * params)
{
    cpBodyResetForces((cpBody * ) params[0]);
    return 0;
}

int modcpBodyIsSleeping(INSTANCE * my, int * params)
{
    return cpBodyIsSleeping((cpBody * ) params[0]);
}


int modcpBodySleep(INSTANCE * my, int * params)
{
    cpBodySleep((cpBody * ) params[0]);
    return 0;
}

int modcpBodyActivate(INSTANCE * my, int * params)
{
    cpBodyActivate((cpBody * ) params[0]);
    return 0;
}

int modcpBodyIsStatic(INSTANCE * my, int * params)
{
    int a = cpBodyIsStatic((cpBody * ) params[0]);
    return a;
}

int modcpBodyIsRogue(INSTANCE * my, int * params)
{
    int a = cpBodyIsRogue((cpBody * ) params[0]);
    return a;
}


int modcpBodySleepWithGroup(INSTANCE * my, int * params)
{
    cpBodySleepWithGroup( (cpBody * ) params[0], (cpBody * ) params[1]);
    return 0;
}

int modcpBodyApplyForce(INSTANCE * my, int * params)
{
    cpBodyApplyForce((cpBody * ) params[0], *(cpVect *)params[1], *(cpVect *)params[2]);
    return 0;

}

int modcpBodyApplyImpulse(INSTANCE * my, int * params)
{
    cpBodyApplyImpulse((cpBody * ) params[0], *(cpVect *)params[1], *(cpVect *)params[2]);
    return 0;

}

int modcpBodyWorld2Local(INSTANCE * my, int * params)
{
    cpVect  *vc=params[2];
    *vc=cpBodyWorld2Local((cpBody * ) params[0], *(cpVect *)params[1]);
    return 0;

}

int modcpBodySlew(INSTANCE * my, int * params)
{
    cpBodySlew((cpBody * ) params[0], *(cpVect *)params[1],*((float *)  &params[2]));
    return 0;

}

int modcpBodyUpdateVelocity(INSTANCE * my, int * params)
{
    cpBodyUpdateVelocity((cpBody * ) params[0], *(cpVect *)params[1],*(float *)  &params[2],*(float *)  &params[3]);
    return 0;

}

int modActivateProcessTouchingIt(INSTANCE * my, int * params)
{
    cpSpaceActivateShapesTouchingShape(cpEspacio,(cpShape *)LOCDWORD(mod_chipmunk, my,LOC_SHAPE));
    return 0;
}

//shapes con ids y funciones de control interno

void addListaProcesos(INSTANCE * ins)
{

    cpBody * a;
    if ( LOCDWORD( mod_chipmunk,ins, LOC_STATIC))
    {
        a=cpBodyNewStatic();
    }
    else
    {
        a=cpBodyNew(*(float*)LOCADDR( mod_chipmunk, ins, LOC_MASS ),*(float*)LOCADDR( mod_chipmunk, ins, LOC_INERTIA ));
        a = cpSpaceAddBody(cpEspacio, a);
    }

    LOCDWORD( mod_chipmunk, ins, LOC_BODY )=(uint32_t)a;
    DataPointer dataP=malloc(sizeof(Data_Pointer));
    a->data=dataP;
    dataP->father=LOCDWORD( mod_chipmunk, ins, LOC_ID );
    a->p.x=dataP->x=LOCDWORD( mod_chipmunk, ins, LOC_X );
    a->p.y=dataP->y=LOCDWORD( mod_chipmunk, ins, LOC_Y );
    dataP->angle=LOCDWORD( mod_chipmunk, ins, LOC_ANGLE );
    dataP->estado=STATUS_RUNNING;
    cpBodySetAngle(a,-modChipmunkdeg2rad(dataP->angle));
    dataP->sig=ListaCuerpos->sig;
    dataP->nShapes=0;
    dataP->body=a;
    dataP->Shapes=NULL;
    LLinicializa(&(dataP->Constraints));
    dataP->typeShape=LOCDWORD( mod_chipmunk, ins, LOC_SHAPETYPE );
    ListaCuerpos->sig=dataP;

}

int modaddCircleShape(INSTANCE * my, int * params)
{
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE )==TYPE_NONE)
    {
        LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE )=TYPE_CIRCLE;
    }
    else
    {
        if (LOCDWORD( mod_chipmunk, my, LOC_BODY)==0 )
        {
            creaBodyAndShapeAutomat(my);
        }
    }

    if (LOCDWORD( mod_chipmunk, my, LOC_BODY )==0)
    {
        addListaProcesos(my);
    }
    cpBody* bod=(cpBody*) LOCDWORD( mod_chipmunk, my, LOC_BODY );
    DataPointer dato=(DataPointer)bod->data;
    cpShape * sha= cpCircleShapeNew(bod, *(float *)&params[2], cpv(*(float *)&params[0],*(float *)&params[1]));
    if (dato->nShapes==0)
    {
        dato->nShapes++;
        dato->Shapes=malloc(sizeof(cpShape*));
    }
    else
    {
        dato->nShapes++;
        dato->Shapes=realloc(dato->Shapes,sizeof(cpShape*)*(dato->nShapes));
    }
    sha->e=*(float*)LOCADDR( mod_chipmunk,  my, LOC_ELASTICITY );
    sha->u=*(float*)LOCADDR( mod_chipmunk,  my, LOC_FRICTION );
    sha->group=LOCDWORD( mod_chipmunk,  my, LOC_GROUP );
    sha->layers=LOCDWORD( mod_chipmunk,  my, LOC_LAYERS );


    dato->Shapes[dato->nShapes-1]=sha;
    if ( cpBodyIsStatic(bod) )
        cpSpaceAddStaticShape(cpEspacio, sha);
    else
        cpSpaceAddShape(cpEspacio, sha);
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPE )==0)
        LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;

if ( LOCDWORD( mod_chipmunk,my, LOC_STATIC))
    {
         cpSpaceReindexShapesForBody(cpEspacio,(cpBody *)LOCDWORD( mod_chipmunk, my, LOC_BODY ));
    }
    return (int) sha;
}

int modaddSegmentShape(INSTANCE * my, int * params)
{
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE )==TYPE_NONE)
    {
        LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE )=TYPE_LINE;
    }
    else
    {
        if (LOCDWORD( mod_chipmunk, my, LOC_BODY)==0 )
        {
            creaBodyAndShapeAutomat(my);
        }
    }

    if (LOCDWORD( mod_chipmunk, my, LOC_BODY )==0)
    {
        addListaProcesos(my);
    }
    cpBody* bod=(cpBody*) LOCDWORD( mod_chipmunk, my, LOC_BODY );
    DataPointer dato=(DataPointer)bod->data;
    cpShape * sha= cpSegmentShapeNew(bod, cpv(*(float *)&params[0],*(float *)&params[1]), cpv(*(float *)&params[2],*(float *)&params[3]),*(float *)&params[4]);
    if (dato->nShapes==0)
    {
        dato->nShapes++;
        dato->Shapes=malloc(sizeof(cpShape*));
    }
    else
    {
        dato->nShapes++;
        dato->Shapes=realloc(dato->Shapes,sizeof(cpShape*)*(dato->nShapes));
    }
    sha->e=*(float*)LOCADDR( mod_chipmunk,  my, LOC_ELASTICITY );
    sha->u=*(float*)LOCADDR( mod_chipmunk,  my, LOC_FRICTION );
    sha->group=LOCDWORD( mod_chipmunk,  my, LOC_GROUP );
    sha->layers=LOCDWORD( mod_chipmunk,  my, LOC_LAYERS );
    dato->Shapes[dato->nShapes-1]=sha;
    if ( cpBodyIsStatic(bod))
        cpSpaceAddStaticShape(cpEspacio, sha);
    else
        cpSpaceAddShape(cpEspacio, sha);
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPE )==0)
        LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;
        if ( LOCDWORD( mod_chipmunk,my, LOC_STATIC))
    {
         cpSpaceReindexShapesForBody(cpEspacio,(cpBody *)LOCDWORD( mod_chipmunk, my, LOC_BODY ));
    }
    return (int) sha;
}

int modaddPolyShape(INSTANCE * my, int * params)
{
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE )==TYPE_NONE)
    {
        LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE )=TYPE_CONVEX_POLYGON;
    }
    else
    {
        if (LOCDWORD( mod_chipmunk, my, LOC_BODY)==0 )
        {
            creaBodyAndShapeAutomat(my);
        }
    }

    if (LOCDWORD( mod_chipmunk, my, LOC_BODY )==0)
    {
        addListaProcesos(my);
    }
    cpBody* bod=(cpBody*) LOCDWORD( mod_chipmunk, my, LOC_BODY );
    DataPointer dato=(DataPointer)bod->data;


    cpShape * sha= cpPolyShapeNew(bod,params[2], params[3], cpv(*(float *)&params[0],*(float *)&params[1]));
    if (dato->nShapes==0)
    {
        dato->nShapes++;
        dato->Shapes=malloc(sizeof(cpShape*));
    }
    else
    {
        dato->nShapes++;
        dato->Shapes=realloc(dato->Shapes,sizeof(cpShape*)*(dato->nShapes));
    }
    sha->e=*(float*)LOCADDR( mod_chipmunk,  my, LOC_ELASTICITY );
    sha->u=*(float*)LOCADDR( mod_chipmunk,  my, LOC_FRICTION );
    sha->group=LOCDWORD( mod_chipmunk,  my, LOC_GROUP );
    sha->layers=LOCDWORD( mod_chipmunk,  my, LOC_LAYERS );
    dato->Shapes[dato->nShapes-1]=sha;
    if ( cpBodyIsStatic(bod))
        cpSpaceAddStaticShape(cpEspacio, sha);
    else
        cpSpaceAddShape(cpEspacio, sha);
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPE )==0)
        LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;
if ( LOCDWORD( mod_chipmunk,my, LOC_STATIC))
    {
         cpSpaceReindexShapesForBody(cpEspacio,(cpBody *)LOCDWORD( mod_chipmunk, my, LOC_BODY ));
    }
    return (int) sha;
}

int creaPoly(int * params,cpBody* bod)
{
    cpVect  vec[params[2]];
    int val=2;
    int z;
    for (z=0; z<params[2]; z++)
    {
        //vc=params[2]+z*sizeof(cpvec);
        val++;
        vec[z].x=params[val];
        ++val;
        vec[z].y=params[val];
    }
    cpShape *sha= cpPolyShapeNew(bod,params[2], &vec, cpv(params[0],params[1]));
    return sha;
}
#define ajustaTam LOCDWORD( mod_chipmunk, my, LOC_SIZE )/100.0
int creaBodyAndShapeAutomat(INSTANCE *my)
{
    addListaProcesos(my);
    cpBody* bod=(cpBody*) LOCDWORD( mod_chipmunk, my, LOC_BODY );
    DataPointer dato=(DataPointer)bod->data;
    cpShape * sha;


    if (((int*)LOCDWORD( mod_chipmunk, my, LOC_PARAMS ))!=NULL)
    {
        int *params= ((int*)LOCDWORD( mod_chipmunk, my, LOC_PARAMS ));

        switch (LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE ))
        {
        case TYPE_CIRCLE:
            sha= cpCircleShapeNew(bod, params[2], cpv(params[0],params[1]));
            break;
        case TYPE_LINE:
            //printf("%d %d %d %d %d\n",params[0],params[1],params[2],params[3],params[4]); fflush(stdout);
            sha=cpSegmentShapeNew(bod, cpv(params[0],params[1]), cpv(params[2],params[3]),params[4]);
            break;
        case TYPE_EMPTY:
            return 0;
            break;
        case TYPE_CONVEX_POLYGON:
        case TYPE_BOX:
            sha=creaPoly(params,bod);
            break;

        }

    }
    else
    {

        GRAPH * map=bitmap_get( LOCDWORD( mod_chipmunk, my, LOC_FILE ), LOCDWORD( mod_chipmunk, my, LOC_GRAPH ) );
        if (map==NULL) return 0;
        int params[5];
        cpVect arr[4];
        switch (LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE ))
        {
        case TYPE_CIRCLE:
            if ( map->ncpoints > 0 )
            {
                if ( map->cpoints[0].x != CPOINT_UNDEFINED )
                    params[0]= map->cpoints[0].x ;
            }
            else
                params[0]= map->width / 2 ;

            if ( map->ncpoints > 0 )
            {
                if ( map->cpoints[0].y != CPOINT_UNDEFINED )
                    params[1]= map->cpoints[0].y ;
            }
            else
                params[1]= map->height / 2 ;

            params[0]-= map->width / 2;
            params[1]-= map->height / 2 ;
            params[2]=(map->height+ map->width )/4;
            sha= cpCircleShapeNew(bod, ajustaTam*params[2], cpv(ajustaTam*-1*params[0],ajustaTam*-1*params[1]));
            break;
        case TYPE_EMPTY:

            return 0;
            break;
        case TYPE_LINE:
            if (map->height>map->width)
            {
                params[2]=params[0]=0;
                params[1]=(map->height/2)*-1.0;
                params[3]=params[1]*-1.0;
                params[4]=map->width/2;
            }
            else
            {
                params[1]=params[3]=0;
                params[0]=(map->width/2)*-1.0;
                params[2]=params[0]*-1.0;
                params[4]=map->height/2;
            }

            sha=cpSegmentShapeNew(bod, cpv(ajustaTam*params[0],ajustaTam*params[1]), cpv(ajustaTam*params[2],ajustaTam*params[3]),ajustaTam*params[4]);
            break;
        case TYPE_CONVEX_POLYGON:
        case TYPE_BOX:

            if ( map->ncpoints > 0 )
            {
                if ( map->cpoints[0].x != CPOINT_UNDEFINED )
                    params[0]= map->cpoints[0].x ;
                if ( map->cpoints[0].y != CPOINT_UNDEFINED )
                    params[1]= map->cpoints[0].y ;
            }
            else
            {
                params[0]= map->width / 2 ;
                params[1]= map->height / 2 ;
            }

            params[0]-= map->width / 2;
            params[1]-= map->height / 2 ;
            params[2]=4;


            arr[0].x=ajustaTam*((map->width / 2)*-1.0 );
            arr[0].y=ajustaTam*((map->height / 2)*-1.0) ;

            arr[1].x=ajustaTam*((map->width / 2)*-1.0);
            arr[1].y=ajustaTam*((map->height / 2 ));

            arr[2].x=ajustaTam*((map->width / 2)) ;
            arr[2].y=ajustaTam*((map->height / 2)) ;

            arr[3].x=ajustaTam*((map->width / 2 ));
            arr[3].y=ajustaTam*((map->height / 2)*-1.0);

            sha= cpPolyShapeNew(bod,params[2], &arr, cpv(ajustaTam*(-1*params[0]),ajustaTam*(-1*params[1])));
            break;
        }
    }

    dato->nShapes++;
    dato->Shapes=malloc(sizeof(cpShape*));
    sha->e=*(float*)LOCADDR( mod_chipmunk,  my, LOC_ELASTICITY );
    sha->u=*(float*)LOCADDR( mod_chipmunk,  my, LOC_FRICTION );
    sha->group=LOCDWORD( mod_chipmunk,  my, LOC_GROUP );
    sha->layers=LOCDWORD( mod_chipmunk,  my, LOC_LAYERS );
    dato->Shapes[dato->nShapes-1]=sha;
    if ( cpBodyIsStatic(bod))
        cpSpaceAddStaticShape(cpEspacio, sha);
    else
        cpSpaceAddShape(cpEspacio, sha);
    LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;
    if ( LOCDWORD( mod_chipmunk,my, LOC_STATIC))
    {
         cpSpaceReindexShapesForBody(cpEspacio,(cpBody *)LOCDWORD( mod_chipmunk, my, LOC_BODY ));
    }
    return 0;
}

