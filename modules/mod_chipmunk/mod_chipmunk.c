/*
 *  Copyright © 2011 Prg <orlando8nov@yahoo.com.mx>
 *
 *  BennuGD bindings for Chipmunk physics library
 *
 *  mod_chipmunk is free software; you can redistribute it and/or modify
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

/*
 *  Thanks to SplinterGU & Josebita
 */



#ifndef __libChipmunk
#define __libChipmunk
#include <stdlib.h>
#include <math.h>


#include <chipmunk.h>
#include "bgddl.h"
#include "bgdrtm.h"
#include "xstrings.h"
#include <math.h>
#include "dlvaracc.h"
#include "libdraw.h"
#include "librender.h"
#include "mod_map.h"


//Globales c/bennu
#define GLO_SPACE                   0
#define GLO_GRAVITY_X               1
#define GLO_GRAVITY_Y               2
#define GLO_BIAS_COEF               3
#define GLO_COLLISION_SLOP          4
#define GLO_CONTACT_PERSISTENCE     5
#define GLO_ITERATIONS              6
#define GLO_DAMPING                 7
#define GLO_IDLESPEEDTHRESHOLD      8
#define GLO_SLEEPTIMETHRESHOLD      9
#define GLO_INTERVAL                10
#define GLO_PHRESOLUTION            11


char * __bgdexport( mod_chipmunk, globals_def ) =
    "STRUCT gphysics\n"
    "int space;\n"
    "float gravity_X;\n"                                                  /* Access and set with *(FLOAT *)GLOADDR(mod_chipmunk,GLO_GRAVITY_X)) */
    "float gravity_Y;\n"                                                  /* Access and set with *(FLOAT *)GLOADDR(mod_chipmunk,GLO_GRAVITY_Y)) */
    "float bias_coef=0.5;\n"                                                  /* Access and set with *(FLOAT *)GLOADDR(mod_chipmunk,GLO_BIAS_COEF)) */
    "float collision_slop=0.1;\n"                                             /* Access and set with *(FLOAT *)GLOADDR(mod_chipmunk,GLO_COLLISION_SLOP)) */
    "int contact_persistence=3;\n"
    "int iterations=10;\n"                                        /* Access and set with GLOADDR(mod_chipmunk,GLO_CONTACT_PERSISTENCE)) */
    "float damping=1.0;\n"
    "float idleSpeedThreshold =0;\n"
    "float sleepTimeThreshold =infinity;\n"
    "float interval =1.0/25.0;\n"
    "int phresolution =3;\n"
    "END\n"
    "cpVect cpvzero=0,0;\n"
    ;

DLVARFIXUP __bgdexport( mod_chipmunk, globals_fixup )[] =
{
    { "gphysics.space", NULL, -1, -1 },
    { "gphysics.gravity_X", NULL, -1, -1 },
    { "gphysics.gravity_Y", NULL, -1, -1 },
    { "gphysics.bias_coef", NULL, -1, -1 },
    { "gphysics.collision_slop", NULL, -1, -1 },
    { "gphysics.contact_persistence", NULL, -1, -1 },
    { "gphysics.iterations", NULL, -1, -1 },
    { "gphysics.damping", NULL, -1, -1 },
    { "gphysics.idleSpeedThreshold", NULL, -1, -1 },
    { "gphysics.sleepTimeThreshold", NULL, -1, -1 },
    { "gphysics.interval", NULL, -1, -1 },
    { "gphysics.phresolution", NULL, -1, -1 },

    { NULL, NULL, -1, -1 }
};


//Locales c/bennu
#define LOC_BODY                     0
#define LOC_SHAPE                    1
#define LOC_X                        2
#define LOC_Y                        3
#define LOC_ANGLE                    4
#define LOC_ID                       5
#define LOC_INCR_X                   6
#define LOC_INCR_Y                   7
#define LOC_INERTIA                  8
#define LOC_MASS                     9
#define LOC_STATIC                  10
#define LOC_ELASTICITY              11
#define LOC_FRICTION                12
#define LOC_GROUP                   13
#define LOC_LAYERS                  14
#define LOC_RSTATUS                 15
#define LOC_SHAPETYPE               16
#define LOC_PARAMS                  17
#define LOC_FILE                    18
#define LOC_GRAPH                   19
#define LOC_COLLISIONTYPE           20
#define LOC_RESOLUTION              21





char * __bgdexport( mod_chipmunk, locals_def ) =
    "STRUCT lphysics\n"
    "int body=0;\n"
    "int shape=0;\n"
    "int incr_x=0;\n"
    "int incr_y=0;\n"
    "float inertia=1;\n"
    "float mass=1;\n"
    "int static=0;\n"
    "float elasticity=1;\n"
    "float friction=1;\n"
    "int group=CP_NO_GROUP;\n"
    "int layers=CP_ALL_LAYERS;\n"
    "int ShapeType=TYPE_NONE;\n"
    "int * params=null;\n"
    "int collisionType=0;\n"
    "end\n"
;

DLVARFIXUP __bgdexport( mod_chipmunk, locals_fixup )[] =
{
    { "lphysics.body", NULL, -1, -1 },
    { "lphysics.shape", NULL, -1, -1 },
    { "x", NULL, -1, -1 },
    { "y", NULL, -1, -1 },
    { "angle", NULL, -1, -1 },
    { "id", NULL, -1, -1 },
    { "lphysics.incr_x", NULL, -1, -1 },
    { "lphysics.incr_y", NULL, -1, -1 },
    { "lphysics.inertia", NULL, -1, -1 },
    { "lphysics.mass", NULL, -1, -1 },
    { "lphysics.static", NULL, -1, -1 },
    { "lphysics.elasticity", NULL, -1, -1 },
    { "lphysics.friction", NULL, -1, -1 },
    { "lphysics.group", NULL, -1, -1 },
    { "lphysics.layers", NULL, -1, -1 },
    { "reserved.status", NULL, -1, -1 },
    { "lphysics.ShapeType", NULL, -1, -1 },
    { "lphysics.params", NULL, -1, -1 },
    { "file", NULL, -1, -1 },
    { "graph", NULL, -1, -1 },
    { "lphysics.collisionType", NULL, -1, -1 },
    { "resolution"              , NULL, -1, -1 },

    { NULL, NULL, -1, -1 }
};

//CONSTANTES
#define CP_C_ITERATIONS 0
#define CP_C_GRAVITY 1
#define CP_C_DAMPING 2
#define CP_C_IDLESPEEDTHRESHOLD 3
#define CP_C_SLEEPTIMETHRESHOLD 4
#define CP_C_staticBody 5

#define CP_C_M  0
#define CP_C_I  1
#define CP_C_P  2
#define CP_C_V  3
#define CP_C_F  4
#define CP_C_A  5
#define CP_C_W  6
#define CP_C_T  7
#define CP_C_ROT  8
#define CP_C_V_LIMIT  9
#define CP_C_W_LIMIT  10

#define CP_C_BODY   0
#define CP_C_BB   1
#define CP_C_E   2
#define CP_C_U   3
#define CP_C_SENSOR   4
#define CP_C_SURFACE_V   5
#define CP_C_COLLISION_TYPE   6
#define CP_C_GROUP   7
#define CP_C_LAYERS   8
#define CP_C_DATA   20

#define GRABABLE_MASK_BIT (1<<31)
#define NOT_GRABABLE_MASK (~GRABABLE_MASK_BIT)


#define CP_C_MAXFORCE 0
#define CP_C_BIASCOEF 1
#define CP_C_MAXBIAS  2
#define CP_C_CA  3
#define CP_C_CB  4


#define CM_PI 3.14159265

#define TYPE_NONE           0
#define TYPE_BOX            1
#define TYPE_CIRCLE         2
#define TYPE_CONVEX_POLYGON 3
#define TYPE_LINE           4
#define TYPE_EMPTY          5

#define     CP_C_ANCHR1     1
#define     CP_C_ANCHR2     10
#define     CP_C_DIST       3
#define     CP_C_MIN        4
#define     CP_C_MAX        5
#define     CP_C_GROOVEB    6
#define     CP_C_GROOVEA    7
#define     CP_C_RESTLENGTH 8
#define     CP_C_STIFFNESS  9
//#define     CP_C_DAMPING    2
#define     CP_C_RESTANGLE  11
#define     CP_C_ANGLE      12
#define     CP_C_PHASE      13
#define     CP_C_RATCHET    14
#define     CP_C_RATIO      15
#define     CP_C_RATE       16



//constantes bennu




char * __bgdexport( mod_chipmunk, types_def ) =
    "TYPE cpVect\n"" float x;\n"" float y;\n""END\n"
    "TYPE cpBB\n"" float l, b, r ,t;\n""END\n"
    "TYPE cpsegmentqueryinfo\n""int shape, id;\n""float x,y,t; cpVect n; \n""END\n"
    "TYPE tPoints\n"" cpVect point, normal;\n"" float dist; end \n"
    "TYPE cpContactPointSet\n""int count;\n""int id1, id2;\n""int shape1,shape2;\n"" tPoints points[6];  end\n"
;

DLCONSTANT __bgdexport( mod_chipmunk, constants_def )[] =
{
    { "CP_C_ITERATIONS", TYPE_INT, CP_C_ITERATIONS },
    { "CP_C_GRAVITY", TYPE_INT, CP_C_GRAVITY },
    { "CP_C_DAMPING", TYPE_INT, CP_C_DAMPING },
    { "CP_C_IDLESPEEDTHRESHOLD", TYPE_INT, CP_C_IDLESPEEDTHRESHOLD },
    { "CP_C_SLEEPTIMETHRESHOLD", TYPE_INT, CP_C_SLEEPTIMETHRESHOLD },
    { "CP_C_staticBody", TYPE_INT, CP_C_staticBody },

    { "CP_C_M", TYPE_INT, CP_C_M },
    { "CP_C_I", TYPE_INT, CP_C_I },
    { "CP_C_P", TYPE_INT, CP_C_P },
    { "CP_C_V", TYPE_INT, CP_C_V },
    { "CP_C_F", TYPE_INT, CP_C_F },
    { "CP_C_A", TYPE_INT, CP_C_A },
    { "CP_C_W", TYPE_INT, CP_C_W },
    { "CP_C_T", TYPE_INT, CP_C_T },
    { "CP_C_ROT", TYPE_INT, CP_C_ROT },
    { "CP_C_V_LIMIT", TYPE_INT, CP_C_V_LIMIT },
    { "CP_C_W_LIMIT", TYPE_INT, CP_C_W_LIMIT },

    { "CP_C_BODY", TYPE_INT, CP_C_BODY },
    { "CP_C_BB", TYPE_INT, CP_C_BB },
    { "CP_C_E", TYPE_INT, CP_C_E },
    { "CP_C_U", TYPE_INT, CP_C_U },
    { "CP_C_SENSOR", TYPE_INT, CP_C_SENSOR },
    { "CP_C_SURFACE_V", TYPE_INT, CP_C_SURFACE_V },
    { "CP_C_COLLISION_TYPE", TYPE_INT, CP_C_COLLISION_TYPE },
    { "CP_C_GROUP", TYPE_INT, CP_C_GROUP },
    { "CP_C_LAYERS", TYPE_INT, CP_C_LAYERS },
    { "CP_C_DATA", TYPE_INT, CP_C_DATA },
    { "INFINITY", TYPE_FLOAT, INFINITY },
    { "NOT_GRABABLE_MASK", TYPE_INT, NOT_GRABABLE_MASK },
    { "GRABABLE_MASK_BIT", TYPE_INT, GRABABLE_MASK_BIT },

    { "CP_NO_GROUP", TYPE_INT, CP_NO_GROUP },

    { "CP_C_MAXFORCE", TYPE_INT, CP_C_MAXFORCE },
    { "CP_C_BIASCOEF", TYPE_INT, CP_C_BIASCOEF },
    { "CP_C_MAXBIAS", TYPE_INT, CP_C_MAXBIAS },
    { "CP_C_CA", TYPE_INT, CP_C_CA },
    { "CP_C_CB", TYPE_INT, CP_C_CB },

    { "CP_ALL_LAYERS", TYPE_INT, CP_ALL_LAYERS },

    { "TYPE_NONE", TYPE_INT, TYPE_NONE },
    { "TYPE_BOX", TYPE_INT, TYPE_BOX },
    { "TYPE_CIRCLE", TYPE_INT, TYPE_CIRCLE },
    { "TYPE_CONVEX_POLYGON", TYPE_INT, TYPE_CONVEX_POLYGON },
    { "TYPE_LINE", TYPE_INT, TYPE_LINE },
    { "TYPE_EMPTY", TYPE_INT, TYPE_EMPTY },

    { "CP_C_ANCHR1", TYPE_INT, CP_C_ANCHR1 },
    { "CP_C_ANCHR2", TYPE_INT, CP_C_ANCHR2 },
    { "CP_C_DIST", TYPE_INT, CP_C_DIST },
    { "CP_C_MIN", TYPE_INT, CP_C_MIN },
    { "CP_C_MAX", TYPE_INT, CP_C_MAX },
    { "CP_C_GROOVEB", TYPE_INT, CP_C_GROOVEB },
    { "CP_C_GROOVEA", TYPE_INT, CP_C_GROOVEA },
    { "CP_C_RESTLENGTH", TYPE_INT, CP_C_RESTLENGTH },
    { "CP_C_STIFFNESS", TYPE_INT, CP_C_STIFFNESS },
    { "CP_C_DAMPING", TYPE_INT, CP_C_DAMPING },
    { "CP_C_RESTANGLE", TYPE_INT, CP_C_RESTANGLE },
    { "CP_C_ANGLE", TYPE_INT, CP_C_ANGLE },
    { "CP_C_PHASE", TYPE_INT, CP_C_PHASE },
    { "CP_C_RATCHET", TYPE_INT, CP_C_RATCHET },
    { "CP_C_RATIO", TYPE_INT, CP_C_RATIO },
    { "CP_C_RATE", TYPE_INT, CP_C_RATE },

    { "CM_PI", TYPE_INT, CM_PI },

    { NULL , 0 , 0 }
} ;

//globales c

typedef struct Data_Pointer Data_Pointer;

typedef
struct Data_Pointer
{
    int father;
    int estado;
    Data_Pointer * sig;
    int x,y;
    cpBody * body;
    int angle;
    int nShapes;
    cpShape ** Shapes;
    int nConstraints;
    cpConstraint ** Constraints;
    cpBody ** constraintsBody;
    int typeShape;
} *DataPointer;



//Globales
DataPointer  ListaCuerpos=NULL;
int Crear=1;
DataPointer  DataP_Espacio;
DataPointer *lista;
int numLista=0;
cpBool elim=0;

//ESTRUCTURAS
typedef
struct mis
{
    float x, y;
} cpvec;

typedef struct cpbb
{
    float l, b, r ,t;
} cpbb;

typedef struct cpsegmentqueryinfoB
{
    int shape,id;
    float x,y,t;
    cpvec n;
} cpsegmentqueryinfoB;



typedef struct handlersC
{
    cpArray* arr;
    cpArray* colisiones;
    cpCollisionType a, b;

} colHand;
cpArray * HandlerColisions;




typedef struct cpContactPointSetM
{
    int count;
    int id1, id2;
    int shape1,shape2;
    struct
    {
        cpvec point, normal;
        float dist;
    } points[CP_MAX_CONTACTS_PER_ARBITER];
} cpContactPointSetM;


//MACROS
#define igual(a,b,c)    b=c; a.x=b->x; a.y=b->y;
#define igualBB(a,d,c)    d=c; a.l=d->l; a.b=d->b; a.r=d->r; a.t=d->t;

static modAddLista(DataPointer a);
static int creaBodyAndShapeAutomat(INSTANCE *my);


static float deg2rad(float ang)
{
    return (ang/180000)*CM_PI;
}

static float rad2deg(float ang)
{
    return (ang*180000)/CM_PI;
}


//funciones matemáticas

static int modcpflerp(INSTANCE * my, int * params)
{
    float  f = *( float * ) &params[0];
    float  min = *( float * ) &params[1];
    float  max = *( float * ) &params[2];
    float res=cpflerp( f,  min,  max);
    return *(( int * )&(res));
}

static int modcpfclamp(INSTANCE * my, int * params)
{
    float  f = *( float * ) &params[0];
    float  min = *( float * ) &params[1];
    float  max = *( float * ) &params[2];
    float res=cpfclamp( f,  min,  max);
    return *(( int * )&(res));
}

static int modcpflerpconst(INSTANCE * my, int * params)
{
    float  f = *( float * ) &params[0];
    float  min = *( float * ) &params[1];
    float  max = *( float * ) &params[2];
    float res=cpflerpconst( f,  min,  max);
    return *(( int * )&(res));
}


//FUNCIONES DE LOS VECTORES

static int modcpveql(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    int res = (int) cpveql(v1, v2);
    return res;
}

static int modcpvadd(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    cpVect res = cpvadd(v1, v2);
    ve=params[2];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvsub(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    cpVect res = cpvsub(v1, v2);
    ve=params[2];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}


static int modcpvneg(INSTANCE * my, int * params)
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    cpVect res = cpvneg(v1);
    ve=params[1];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvmult(INSTANCE * my, int * params)
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    float flo=*( float * ) &params[1];
    cpVect res = cpvmult(v1, flo);
    ve=params[2];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvdot(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float res = cpvdot(v1, v2);
    return *(( int * )&(res));
}

static int modcpvcross(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float res = cpvcross(v1, v2);
    return *(( int * )&(res));
}



static int modcpvperp(INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    cpVect res = cpvperp(v1);
    ve=params[1];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}


static int modcpvrperp (INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    cpVect res = cpvrperp(v1);
    ve=params[1];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvnormalize (INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    cpVect res = cpvnormalize(v1);
    ve=params[1];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}


static int modcpvnormalize_safe (INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    cpVect res = cpvnormalize_safe(v1);
    ve=params[1];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}


static int modcpvproject(INSTANCE * my, int * params) //dos vectores
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    cpVect res = cpvproject(v1, v2);
    ve=params[2];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvrotate(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    cpVect res = cpvrotate(v1, v2);
    ve=params[2];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}


static int modcpvunrotate(INSTANCE * my, int * params)

{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    cpVect res = cpvunrotate(v1, v2);
    ve=params[2];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvlength (INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    float res = cpvlength(v1);
    return *(( int * )&(res));
}

static int modcpvlengthsq (INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    float res = cpvlengthsq(v1);
    return *(( int * )&(res));
}


static int modcpvtoangle (INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    float res = cpvtoangle(v1);
    return *(( int * )&(res));
}

static int modcpvstr (INSTANCE * my, int * params)  //un vector
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    char * res = cpvstr(v1);
    char * result=string_new(res);
    return result;
}

static int modcpvforangle(INSTANCE * my, int * params)
{
    float  v1=*( float * ) &params[0];
    cpvec *ve;
    cpVect res = cpvforangle(v1);
    ve=params[1];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}



static int modcpvclamp(INSTANCE * my, int * params)
{
    cpVect  v1;
    cpvec *ve;
    igual(v1,ve,params[0]);
    float v2=*( float * ) &params[1];
    cpVect res = cpvclamp(v1, v2);
    ve=params[2];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvdist(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float res = cpvdist(v1, v2);
    return *(( int * )&(res));
}

static int modcpvdistsq(INSTANCE * my, int * params)
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float res = cpvdistsq(v1, v2);
    return *(( int * )&(res));
}

static int modcpvlerp(INSTANCE * my, int * params) //vec,vec,flot, ret int
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float flo=*( float * ) &params[2];
    cpVect res = cpvlerp(v1, v2,flo);
    ve=params[3];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvlerpconst(INSTANCE * my, int * params) //vec,vec,flot, ret int
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float flo=*( float * ) &params[2];
    cpVect res = cpvlerpconst(v1, v2,flo);
    ve=params[3];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvslerp(INSTANCE * my, int * params) //vec,vec,flot, ret int
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float flo=*( float * ) &params[2];
    cpVect res = cpvslerp(v1, v2,flo);
    ve=params[3];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}

static int modcpvslerpconst(INSTANCE * my, int * params) //vec,vec,flot, ret int
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float flo=*( float * ) &params[2];
    cpVect res = cpvslerpconst(v1, v2,flo);
    ve=params[3];
    ve->x=res.x;
    ve->y=res.y;
    return 0;
}


static int modcpvnear(INSTANCE * my, int * params) //vec,vec,flot, ret int
{
    cpVect  v1,v2;
    cpvec *ve;
    igual(v1,ve,params[0]);
    igual(v2,ve,params[1]);
    float flo=*( float * ) &params[2];
    int res = cpvnear(v1, v2,flo);
    return res;
}


static int modcpv(INSTANCE * my, int * params) //vec,vec,flot, ret int
{
    cpvec  *v1=(cpvec *)params[2];
    float  ver = *( float * ) &params [0];
    float flo=*( float * ) &params[1];
    v1->x=ver;
    v1->y=flo;
    return params[2];
}


//cpBB

static int modcpBBNew(INSTANCE * my, int * params)
{
    cpbb *ve;
    float l=*( float * ) &params[0];
    float b=*( float * ) &params[1];
    float r=*( float * ) &params[2];
    float t=*( float * ) &params[3];
    cpBB res = cpBBNew(l,b,r,t);
    ve=params[4];
    ve->l=res.l;
    ve->b=res.b;
    ve->r=res.r;
    ve->t=res.t;
    return 0;
}



static int modcpBBintersects(INSTANCE * my, int * params)
{
    cpbb *ve;
    cpBB a,b;
    igualBB(a,ve,params[0])
    igualBB(b,ve,params[1])
    int res = cpBBintersects(a,b);
    return res;
}



static int modcpBBcontainsBB(INSTANCE * my, int * params)
{
    cpbb *ve;
    cpBB a,b;
    igualBB(a,ve,params[0])
    igualBB(b,ve,params[1])
    int res = cpBBcontainsBB(a,b);
    return res;
}



static int modcpBBmerge(INSTANCE * my, int * params)
{
    cpbb *ve;
    cpBB a,b;
    igualBB(a,ve,params[0])
    igualBB(b,ve,params[1])
    cpBB res=cpBBmerge(a,b);
    ve=params[2];
    ve->l=res.l;
    ve->b=res.b;
    ve->r=res.r;
    ve->t=res.t;
    return 0;
}


static int modcpBBcontainsVect(INSTANCE * my, int * params)
{
    cpbb *ve;
    cpBB a;
    cpvec *aux;
    cpVect b;
    igualBB(a,ve,params[0])
    igual(b,aux,params[1])
    int res = cpBBcontainsVect(a,b);
    return res;
}



static int modcpBBexpand(INSTANCE * my, int * params)
{
    cpbb *ve;
    cpBB a;
    cpvec *aux;
    cpVect b;
    igualBB(a,ve,params[0])
    igual(b,aux,params[1])
    cpBB res =cpBBexpand(a,b);
    ve=params[2];
    ve->l=res.l;
    ve->b=res.b;
    ve->r=res.r;
    ve->t=res.t;
    return 0;
}



static int modcpBBClampVect(INSTANCE * my, int * params)
{
    cpbb *ve;
    cpBB a;
    cpvec *aux;
    cpVect b;
    igualBB(a,ve,params[0])
    igual(b,aux,params[1])
    cpVect res=cpBBClampVect(a,b);
    aux=params[2];
    aux->x=res.x;
    aux->y=res.y;
    return 0;
}



static int modcpBBWrapVect(INSTANCE * my, int * params)
{
    cpbb *ve;
    cpBB a;
    cpvec *aux;
    cpVect b;
    igualBB(a,ve,params[0])
    igual(b,aux,params[1])
    cpVect res=cpBBWrapVect(a,b);
    aux=params[2];
    aux->x=res.x;
    aux->y=res.y;
    return 0;
}

//cpBody

static int modgetBody(INSTANCE * my, int * params)
{
    cpSpace * espacio = ( cpSpace * ) params[0];
    return ( int  ) &(espacio->staticBody);
}

cpFloat infinito(cpFloat a)
{
    return (isnan( a)? INFINITY : a);
}


static int modcpBodyLocal2World(INSTANCE * my, int * params)
{
    cpBody * s2 = ( cpBody * ) params[0];
    cpVect ind;
    cpvec *a;
    igual(ind,a,params[1])
    cpVect res = cpBodyLocal2World(s2, ind);
    a=params[2];
    a->x=(float)res.x;
    a->y=(float)res.y;
    return 0;
}

static int modDefcpBody(INSTANCE * my, int * params)
{
    cpVect  flo2;
    int sel=params [1];
    cpvec *ve;
    float flo1;
    cpBody * espacio = ( cpBody * ) params [0];

    switch (sel)
    {
    case CP_C_M:
        flo1 = *((float *)&params[2]);
        //espacio->m=flo1;
        cpBodySetMass(espacio,infinito(flo1));
        break;
    case CP_C_I:
        flo1 = *((float *)&params[2]);
        //espacio->i=flo1;
        cpBodySetMoment(espacio,infinito(flo1));
        break;
    case CP_C_P:
        igual(flo2,ve,params[2]);
        espacio->p=flo2;
        break;
    case CP_C_V:
        igual(flo2,ve,params[2]);
        espacio->v=flo2;
        break;
    case CP_C_F:
        igual(flo2,ve,params[2]);
        espacio->f=flo2;
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
        igual(flo2,ve,params[2]);
        espacio->rot=flo2;
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


static int modGetEcpBody(INSTANCE * my, int * params)
{
    int sel=params [1];
    cpBody * espacioM = ( cpBody * ) params [0];
    cpVect cp;
    cpvec *vec;
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


static int modcpMomentForCircle(INSTANCE * my, int * params)
{
    float m = *( float * ) &params[0];
    float  r1 = *( float * ) &params [1];
    float  r2 = *( float * ) &params [2];
    cpVect  off;
    cpvec *vc;
    igual(off,vc,params[3]);//se obtiene el parámetro 3
    float  res = cpMomentForCircle(m,r1,r2,off);
    return *(( int * )&res);

}



static int modcpMomentForSegment(INSTANCE * my, int * params)
{
    float m = *( float * ) &params[0];
    cpVect  a,b;
    cpvec *vc;
    igual(a,vc,params[1]);
    igual(b,vc,params[2]);
    float  res = cpMomentForSegment(m,a,b);
    return *(( int * )&res);

}



static int modcpMomentForPoly(INSTANCE * my, int * params)
{


    float m = *( float * ) &params[0];
    int numVertsb = params[1];
    cpVect  a;
    cpvec *vc;
    igual(a,vc,params[3]);
    cpVect  vec[numVertsb];
    int z;

    for (z=0; z<numVertsb; z++)
    {
        vc=params[2]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }
    vc=params[2];

    float  res = cpMomentForPoly(m,numVertsb,&vec,a);

    return *(( int * )&res);

}

static int modcpMomentForCircle1(INSTANCE * my, int * params)
{
    float m = *( float * ) &params[0];
    float  r1 = *( float * ) &params [1];
    float  r2 = *( float * ) &params [2];
    cpVect  off=cpv(*( float * ) &params [3],*( float * ) &params [4]);
    float  res = cpMomentForCircle(m,r1,r2,off);
    return *(( int * )&res);

}



static int modcpMomentForSegment1(INSTANCE * my, int * params)
{
    float m = *( float * ) &params[0];
    cpVect  a,b;
    a=cpv(*( float * ) &params[1],*( float * ) &params[2]);
    b=cpv(*( float * ) &params[3],*( float * ) &params[4]);
    float  res = cpMomentForSegment(m,a,b);
    return *(( int * )&res);

}



static int modcpMomentForPoly1(INSTANCE * my, int * params)
{
    float m = *( float * ) &params[0];
    int numVertsb = params[1];
    cpVect  a=cpv(*( float * ) &params[3],*( float * ) &params[4]);
    cpvec *vc;
    cpVect  vec[numVertsb];
    int z;

    for (z=0; z<numVertsb; z++)
    {
        vc=params[2]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }
   // vc=params[2];

    float  res = cpMomentForPoly(m,numVertsb,&vec,a);

    return *(( int * )&res);

}

static int modcpMomentForBox(INSTANCE * my, int * params)
{
    float m = *( float * ) &params[0];
    float  w = *( float * ) &params [1];
    float  h = *( float * ) &params [2];
    float  res = cpMomentForBox(m, w, h);
    return *(( int * )&res);
}

static int modcpAreaForCircle(INSTANCE * my, int * params)
{
    float m = *( float * ) &params[0];
    float  w = *( float * ) &params [1];
    float res = cpAreaForCircle(m,w) ;
    return *(( int * )&res);
}

static int modcpAreaForSegment(INSTANCE * my, int * params)
{
    cpVect  a,b;
    cpvec *vc;
    igual(a,vc,params[0]);
    igual(b,vc,params[1]);
    float r = *( float * ) &params[2];
    float  res = cpAreaForSegment(a,b,r);
    return *(( int * )&res);

}

static int modcpAreaForPoly(INSTANCE * my, int * params)
{
    int numVertsb = params[0];
    cpvec *vc;
    cpVect  vec[numVertsb];
    int z;
    for (z=0; z<numVertsb; z++)
    {
        vc=params[1]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }
    float  res = cpAreaForPoly(numVertsb,&vec);
    return *(( int * )&res);

}

static int modcpBodySetMass(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    float  flo = *(( float * ) &params[1]);
    cpBodySetMass(bou,infinito(flo));
    return 0;
}



static int modcpBodySetMoment(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    float  flo = *(( float * ) &params[1]);
    cpBodySetMoment(bou,infinito(flo));
    return 0;
}

static int modcpBodySetAngle(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    float  flo = *(( float * ) &params[1]);
    cpBodySetAngle(bou,flo);
    return 0;
}

static int modcpBodyUpdatePosition(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    float  flo = *(( float * ) &params[1]);
    cpBodyUpdatePosition(bou,flo);
    return 0;
}

static int modcpBodyResetForces(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    cpBodyResetForces(bou);
    return 0;
}

static int modcpBodyIsSleeping(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    int a = cpBodyIsSleeping(bou);
    return a;
}


static int modcpBodySleep(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    cpBodySleep(bou);
    return 0;
}

static int modcpBodyActivate(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    cpBodyActivate(bou);
    return 0;
}

static int modcpBodyIsStatic(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    int a = cpBodyIsStatic(bou);
    return a;
}

static int modcpBodyIsRogue(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    int a = cpBodyIsRogue(bou);
    return a;
}


static int modcpBodySleepWithGroup(INSTANCE * my, int * params)
{
    cpBody  * bou = (cpBody * ) params[0];
    cpBody  * bod1 = (cpBody * ) params[1];
    cpBodySleepWithGroup(bou, bod1);
    return 0;
}

static int modcpBodyApplyForce(INSTANCE * my, int * params)
{
    cpBody  * bod = (cpBody * ) params[0];
    cpVect  a,b;
    cpvec *vc;
    igual(a,vc,params[1]);
    igual(b,vc,params[2]);
    cpBodyApplyForce(bod, a, b);
    return 0;

}

static int modcpBodyApplyImpulse(INSTANCE * my, int * params)
{
    cpBody  * bod = (cpBody * ) params[0];
    cpVect  a,b;
    cpvec *vc;
    igual(a,vc,params[1]);
    igual(b,vc,params[2]);

    cpBodyApplyImpulse(bod, a, b);
    return 0;

}

static int modcpBodyWorld2Local(INSTANCE * my, int * params)
{
    cpBody  * bod = (cpBody * ) params[0];
    cpVect  a;
    cpvec *vc;
    igual(a,vc,params[1]);
    a=cpBodyWorld2Local(bod, a);
    vc=params[2];
    vc->x=a.x;
    vc->y=a.y;
    return 0;

}

static int modcpBodySlew(INSTANCE * my, int * params)
{
    cpBody  * bod = (cpBody * ) params[0];
    cpVect  a;
    cpvec *vc;
    igual(a,vc,params[1]);
    float flo = *((float *)  &params[2]);
    cpBodySlew(bod, a,flo);
    return 0;

}

static int modcpBodyUpdateVelocity(INSTANCE * my, int * params)
{
    cpBody  * bod = (cpBody * ) params[0];
    cpVect  a;
    cpvec *vc;
    igual(a,vc,params[1]);

    float flo = *((float *)  &params[2]);
    float flo2 = *((float *)  &params[3]);
    cpBodyUpdateVelocity(bod, a,flo,flo2);
    return 0;

}


//-----------------------------------------------------------------------------------------------------------------------------------



static int modDefcpShape(INSTANCE * my, int * params)
{
    float  flo2;// = *( float * ) &params[0];
    cpCollisionType  ct ;//= *( cpCollisionType * ) &params[2];
    cpDataPointer *dP;
    cpvec * vAux, * vAux2;
    cpVect  vec;
    cpbb *bounding;
    cpBB bound;
    cpShape * espacio = ( cpShape * ) params[0];
    int res=params[1];
    switch (res)
    {
    case CP_C_BODY:
        espacio->body=(cpBody *) params[2];
        break;
    case CP_C_BB:
        igualBB(bound,bounding,params[2]);
        espacio->bb=bound;
        break;
    case CP_C_E:
        flo2= *( float * ) &params[2];
        espacio->e=flo2;
        break;
    case CP_C_U:
        flo2= *( float * ) &params[2];
        espacio->u=flo2;
        break;
    case CP_C_SENSOR:
        res= (int) params[2];
        espacio->sensor=res;
        break;
    case CP_C_SURFACE_V:
        igual(vec,vAux,params[2])
        espacio->surface_v=vec;
        break;
    case CP_C_COLLISION_TYPE:
        res = params[2];
        espacio->collision_type=res;
        break;
    case CP_C_GROUP:
        res= (int) params[2];
        espacio->group=res;
        break;
    case CP_C_LAYERS:
        res= (int) params[2];
        espacio->layers=res;
        break;
    case CP_C_DATA:
        dP= (cpDataPointer *) params[2];
        espacio->data=dP;
        break;



    }
    return 0;
}

static int modGetcpShape(INSTANCE * my, int * params)
{
    cpShape * espacio = ( cpShape * ) params[0];
    int res=params[1];
    cpvec * vc;
    cpbb *bb;
    float a;
    switch (res)
    {
    case CP_C_BODY:
        return (int) espacio->body;
        break;
    case CP_C_BB:
        bb=params[2];
        bb->b=espacio->bb.b;
        bb->l=espacio->bb.l;
        bb->r=espacio->bb.r;
        bb->t=espacio->bb.t;
        return 0;
        break;
    case CP_C_E:
        a=espacio->e;
        return *(int*)&a;
        break;
    case CP_C_U:
    a=espacio->u;
        return *(int*)&a;
        break;
    case CP_C_SENSOR:
        return (int)espacio->sensor;
        break;
    case CP_C_SURFACE_V:
        vc=params[2];
        vc->x=espacio->surface_v.x;
        vc->y=espacio->surface_v.y;
        break;
    case CP_C_COLLISION_TYPE:
        return(espacio->collision_type);

        break;
    case CP_C_GROUP:
        return (espacio->group);
        break;
    case CP_C_LAYERS:
        return (espacio->layers);
        break;
    case CP_C_DATA:
        return (int) espacio->data;
        break;



    }
    return 0;
}


static int modcpPolyShapeGetVert(INSTANCE * my, int * params)
{
    cpShape * s2 = ( cpShape * ) params[0];
    int  ind = *( int * ) &params[1];
    cpVect res = cpPolyShapeGetVert(s2, ind);
    cpvec *a=params[2];
    a->x=(float)res.x;
    a->y=(float)res.y;
    return (0);
}

static int modcpResetShapeIdCounter(INSTANCE * my, int * params)
{
    cpResetShapeIdCounter();
    return (0);
}


static int modcpShapeCacheBB(INSTANCE * my, int * params)
{
    cpShape * s2 = ( cpShape * ) params[0];
    cpBB res= cpShapeCacheBB(s2);

    cpbb *ve=params[1];
    ve->l=res.l;
    ve->b=res.b;
    ve->r=res.r;
    ve->t=res.t;
    return (0);
}


static int modcpPolyShapeGetNumVerts(INSTANCE * my, int * params)
{
    cpShape * s2 = ( cpShape * ) params[0];
    int a =cpPolyShapeGetNumVerts(s2);
    return (a);
}


static int modcpSegmentShapeGetA(INSTANCE * my, int * params)
{
    cpShape * a= params[0];
    cpVect res=cpSegmentShapeGetA(a);
    cpvec *aux=params[1];
    aux->x=res.x;
    aux->y=res.y;
    return 0;
}

static int modcpSegmentShapeGetB(INSTANCE * my, int * params)
{
    cpShape * a= params[0];
    cpVect res=cpSegmentShapeGetB(a);
    cpvec *aux=params[1];
    aux->x=res.x;
    aux->y=res.y;
    return 0;
}


static int modcpCircleShapeGetOffset(INSTANCE * my, int * params)
{
    cpShape * a= params[0];
    cpVect res=cpCircleShapeGetOffset(a);
    cpvec *aux=params[1];
    aux->x=res.x;
    aux->y=res.y;
    return 0;
}


static int modcpSegmentShapeGetNormal(INSTANCE * my, int * params)
{
    cpShape * a= params[0];
    cpVect res=cpSegmentShapeGetNormal(a);
    cpvec *aux=params[1];
    aux->x=res.x;
    aux->y=res.y;
    return 0;
}



static int modcpCircleShapeGetRadius(INSTANCE * my, int * params)
{
    cpShape * a= params[0];
    float res=cpCircleShapeGetRadius(a);
    return *((int *)&res);
}


static int modcpSegmentShapeGetRadius(INSTANCE * my, int * params)
{
    cpShape * a= params[0];
    float res=cpSegmentShapeGetRadius(a);
    return *((int *)&res);
}


static int modcpCentroidForPoly(INSTANCE * my, int * params)
{
    int numV= params[0];
    cpvec *vc;
    cpVect  vec[numV];
    int z;
    for (z=0; z<numV; z++)
    {
        vc=params[1]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }

    cpVect res=cpCentroidForPoly(numV,&vec);
    cpvec *aux=params[2];
    aux->x=res.x;
    aux->y=res.y;
    return 0;
}


static int modcpRecenterPoly(INSTANCE * my, int * params)
{
    int numV= params[0];
    cpvec *vc;
    cpVect  vec[numV];
    int z;
    for (z=0; z<numV; z++)
    {
        vc=params[1]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }

    cpRecenterPoly(numV,&vec);
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------
//cpSpace

static int modDefSpace(INSTANCE * my, int * params)
{
    cpSpace * espacio = ( cpSpace * ) params[0];
    int sel=params[1];
    int  flo0;
    cpVect  vec;
    cpvec * vecD;
    float  flo1;
    cpBody *bp;

    switch (sel)
    {
    case CP_C_ITERATIONS:
        flo0 = params[2];
        espacio->iterations=flo0;
        break;

    case CP_C_GRAVITY:
        igual(vec,vecD,params[2]);
        espacio->gravity=vec;
        break;
    case CP_C_DAMPING:
        flo1 = *( float * ) &params[2];
        espacio->damping=flo1;
        break;
    case CP_C_IDLESPEEDTHRESHOLD :
        flo1 = *( float * ) &params[2];
        espacio->idleSpeedThreshold =flo1;
        break;
    case CP_C_SLEEPTIMETHRESHOLD :
        flo1 = *( float * ) &params[2];
        espacio->sleepTimeThreshold =infinito(flo1);
        break;
    case CP_C_staticBody :
        bp = ( cpBody * ) params[2];
        espacio->staticBody=*bp;
        break;
    }
    return 0;
}

static int modcpSpaceRehashStatic(INSTANCE * my, int * params)
{
    cpSpaceRehashStatic((cpSpace*)GLODWORD(mod_chipmunk, GLO_SPACE ));
    return 0;
}

//static int modcpSpaceRehashShape(INSTANCE * my, int * params)
//{
//     cpShape *shape =( cpShape * ) params[1];
//    cpSpaceRehashShape(bod,shape);
//    return 0;
//}

static int modcpSpaceActivateShapesTouchingShape(INSTANCE * my, int * params)
{
    cpShape *shape =( cpShape * ) params[0];
    cpSpaceActivateShapesTouchingShape((cpSpace*)GLODWORD(mod_chipmunk, GLO_SPACE ),shape);
    return 0;
}
static int modcpSpaceResizeStaticHash(INSTANCE * my, int * params)
{
    float dim =*(( float * ) &params[0]);
    int count = params[1];
    cpSpaceResizeStaticHash((cpSpace*)GLODWORD(mod_chipmunk, GLO_SPACE ),dim,count);
    return 0;
}

static int modcpSpaceResizeActiveHash(INSTANCE * my, int * params)
{
    float dim =*(( float * ) &params[0]);
    int count = params[1];
    cpSpaceResizeActiveHash((cpSpace*)GLODWORD(mod_chipmunk, GLO_SPACE ),dim,count);
    return 0;
}

static int modcpConstraintGetImpulse(INSTANCE * my, int * params)
{
    cpConstraint * bod = ( cpConstraint * ) params[0];
    float a = cpConstraintGetImpulse(bod);
    return *((int * )&a);
}


static int modDefcpConstraint(INSTANCE * my, int * params)
{
    cpConstraint * espacio = ( cpConstraint * ) params[0];
    int res=params[1];

    switch (res)
    {
    case CP_C_MAXFORCE:
        espacio->maxForce=infinito(*( float*) &params[2]);
        break;
    case CP_C_BIASCOEF:
        espacio->biasCoef=*( float*) &params[2];
        break;
    case CP_C_MAXBIAS:
        espacio->maxBias=infinito(*( float*) &params[2]);
        break;
    case CP_C_CA:
        espacio->a=( cpBody*) params[2];
        break;
    case CP_C_CB:
        espacio->b=( cpBody*) params[2];
        break;
    }
    return 0;
}

static int modGetcpConstraint(INSTANCE * my, int * params)
{
    cpConstraint * espacio = ( cpConstraint * ) params[0];
    int res=params[1];

    switch (res)
    {
    case CP_C_MAXFORCE:
        return(*(int *)&espacio->maxForce);
        break;
    case CP_C_BIASCOEF:
        return(*(int *)&espacio->biasCoef);
        break;
    case CP_C_MAXBIAS:
        return(*(int *)&espacio->maxBias);
        break;
    case CP_C_CA:
        return((int)espacio->a);
        break;
    case CP_C_CB:
        return((int)espacio->b);
        break;
    }
    return 0;
}

//Collision points y raycast
static int modcpSpacePointQueryFirst(INSTANCE * my, int * params)
{
    cpSpace *space= (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    cpvec *vc;
    cpVect anchr1,anchr2;
    igual(anchr1,vc,params[0])
    cpLayers layers= params[1];
    cpGroup group= params[2];
    cpShape *res =cpSpacePointQueryFirst(space, anchr1, layers, group);
    return (int) res;
}

static int modcpShapePointQuery(INSTANCE * my, int * params)
{
    cpShape *shape= (cpShape *)params[0];
    cpvec *vc;
    cpVect p;
    igual(p,vc,params[1])
    int res = (int) cpShapePointQuery(shape, p);
    return  res;
}

static int modcpShapeSegmentQuery(INSTANCE * my, int * params)
{
    cpShape *shape= (cpShape *)params[0];
    cpvec *vc;
    cpVect a,b;
    igual(a,vc,params[1])
    igual(b,vc,params[2])
    cpSegmentQueryInfo info;
    cpsegmentqueryinfoB *inf;
    int res = (int) cpShapeSegmentQuery(shape, a, b, &info);
    inf=params[3];
    inf->x=info.n.x;
    inf->y=info.n.y;
    inf->shape=(int)info.shape;
    inf->t=info.t;
    inf->n.x=info.n.x;
    inf->n.y=info.n.y;
    if (info.shape->body->data!=NULL)
    {
        DataPointer din=(DataPointer)info.shape->body->data;
        inf->id= din->father ;
    }
    else
    {
        inf->id=0;
    }

    return  res;
}
static int modcpSegmentQueryHitPoint(INSTANCE * my, int * params)
{

    cpvec *vc;
    cpVect a,b;
    igual(a,vc,params[0])
    igual(b,vc,params[1])
    cpSegmentQueryInfo info;
    cpsegmentqueryinfoB *inf=params[2];
    info.t=inf->t;
    info.n=cpv(inf->x,inf->y);
    info.shape=(cpShape *)inf->shape;
    cpVect resAux = cpSegmentQueryHitPoint(a, b, info);
    vc=params[3];
    vc->x=resAux.x;
    vc->y=resAux.y;
    return  0;
}

static int modcpSegmentQueryHitDist(INSTANCE * my, int * params)
{

    cpvec *vc;
    cpVect a,b;
    igual(a,vc,params[0])
    igual(b,vc,params[1])
    cpSegmentQueryInfo info;
    cpsegmentqueryinfoB *inf=params[2];
    info.t=inf->t;
    info.n=cpv(inf->x,inf->y);
    info.shape=(cpShape *)inf->shape;
    float res = cpSegmentQueryHitDist(a, b, info);

    return  *(int *) &res;
}

static int modcpSpaceSegmentQueryFirst(INSTANCE * my, int * params)
{

    cpSpace *space = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    cpvec *vc;
    cpVect a,b;
    igual(a,vc,params[0])
    igual(b,vc,params[1])
    cpLayers lay=params[2];
    cpGroup group = params[3];
    cpSegmentQueryInfo info;
    cpShape *res = cpSpaceSegmentQueryFirst(space,a,b,lay,group,&info);
    cpsegmentqueryinfoB *inf=params[4];
    inf->x=info.n.x;
    inf->y=info.n.y;
    inf->shape=(int)info.shape;
    inf->t=info.t;
    inf->n.x=info.n.x;
    inf->n.y=info.n.y;
    if (info.shape->body->data!=NULL)
    {
        DataPointer din=(DataPointer)info.shape->body->data;
        inf->id= din->father ;
    }
    else
    {
        inf->id=0;
    }

    return  (int ) res;
}

static int addConstr(cpBody *bod1, cpBody *bod2,cpConstraint * cons)
{
    int z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    if (bod1==&espacio->staticBody)
        bod1=0;
    if (bod2==&espacio->staticBody)
        bod2=0;
    if (bod1!=0)
    {
        DataPointer elem= (DataPointer)bod1->data;
        if (elem->nConstraints==0)
        {
            elem->nConstraints++;
            elem->Constraints=malloc(sizeof(cpConstraint *));
            elem->constraintsBody=malloc(sizeof(cpConstraint *));
            elem->Constraints[elem->nConstraints-1]=cons;
            elem->constraintsBody[elem->nConstraints-1]=bod2;
        }
        else
        {
            for (z=0; z<elem->nConstraints; z++)
            {
                if (elem->Constraints[z]==0)
                {
                    elem->Constraints[z]=cons;
                    elem->constraintsBody[z]=bod2;
                    break;
                }

            }

            if (z==elem->nConstraints)
            {
                elem->nConstraints++;
                elem->Constraints=realloc(elem->Constraints,sizeof(cpConstraint *)*(elem->nConstraints));
                elem->constraintsBody=realloc(elem->constraintsBody,sizeof(cpConstraint *)*(elem->nConstraints));
                elem->Constraints[elem->nConstraints-1]=cons;
                elem->constraintsBody[elem->nConstraints-1]=bod2;
            }
        }

    }

    if (bod2!=0)
    {
        DataPointer elem= (DataPointer)bod2->data;
        if (elem->nConstraints==0)
        {
            elem->nConstraints++;
            elem->Constraints=malloc(sizeof(cpConstraint *));
            elem->constraintsBody=malloc(sizeof(cpConstraint *));
            elem->Constraints[elem->nConstraints-1]=cons;
            elem->constraintsBody[elem->nConstraints-1]=bod2;
        }
        else
        {
            for (z=0; z<elem->nConstraints; z++)
            {
                if (elem->Constraints[z]==0)
                {
                    elem->Constraints[z]=cons;
                    elem->constraintsBody[z]=bod1;
                    break;
                }

            }
            if (z==elem->nConstraints)
            {
                elem->nConstraints++;
                elem->Constraints=realloc(elem->Constraints,sizeof(cpConstraint *)*(elem->nConstraints));
                elem->constraintsBody=realloc(elem->constraintsBody,sizeof(cpConstraint *)*(elem->nConstraints));
                elem->Constraints[elem->nConstraints-1]=cons;
                elem->constraintsBody[elem->nConstraints-1]=bod1;
            }
        }

    }
    return 0;
}


static int modaddDampedSpring(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpDampedSpringNew(b1,b2,cpv(*(float *)&params[2],*(float *)&params[3]),cpv(*(float *)&params[4],*(float *)&params[5]),*(float *)&params[6],*(float *)&params[7],*(float *)&params[8]);
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddPinJoint(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=(cpBody *)LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=(cpBody *)LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpPinJointNew(b1,b2,cpv(*(float *)&params[2],*(float *)&params[3]),cpv(*(float *)&params[4],*(float *)&params[5]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddPivotJoint2(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpPivotJointNew2(b1,b2,cpv(*(float *)&params[2],*(float *)&params[3]),cpv(*(float *)&params[4],*(float *)&params[5]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddSlideJoint(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpSlideJointNew(b1,b2,cpv(*(float *)&params[2],*(float *)&params[3]),cpv(*(float *)&params[4],*(float *)&params[5]),*(float *)&params[6],*(float *)&params[7]);
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddGrooveJoint(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpGrooveJointNew(b1,b2,cpv(*(float *)&params[2],*(float *)&params[3]),cpv(*(float *)&params[4],*(float *)&params[5]),cpv(*(float *)&params[6],*(float *)&params[7]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddSimpleMotor(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpSimpleMotorNew(b1,b2,deg2rad(*(float *)&params[2]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddRatchetJoint(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpRatchetJointNew(b1,b2,deg2rad(*(float *)&params[2]),deg2rad(*(float *)&params[3]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}
static int modaddRotaryLimitJoint(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpRotaryLimitJointNew(b1,b2,deg2rad(*(float *)&params[2]),deg2rad(*(float *)&params[3]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddGearJoint(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpGearJointNew(b1,b2,deg2rad(*(float *)&params[2]),deg2rad(*(float *)&params[3]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddDampedRotarySpring(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpDampedRotarySpringNew(b1,b2,deg2rad(*(float *)&params[2]),*(float *)&params[3],*(float *)&params[4]);
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

static int modaddPivotJoint(INSTANCE * my, int * params)
{
    cpBody *	b1, *b2;
    cpConstraint * z;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    INSTANCE * b;
    if (params[0]!=0)
    {
        b = instance_get( params[0] ) ;
        b1=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b1 = &espacio->staticBody;
    }

    if (params[1]!=0)
    {
        b = instance_get( params[1] ) ;
        b2=LOCDWORD(mod_chipmunk,b,LOC_BODY);
    }
    else
    {
        b2 = &espacio->staticBody;
    }
    z=cpPivotJointNew(b1,b2,cpv(*(float *)&params[2],*(float *)&params[3]));
    cpSpaceAddConstraint(espacio, z);
    addConstr(b1,b2,z);
    return (int)z;
}

//funciones ide body

static int modSlew(INSTANCE * my, int * params)
{
    cpBodySlew(LOCDWORD(mod_chipmunk,my,LOC_BODY), cpv(*(float *)&params[0],*(float *)&params[1]), *(float *)&params[2]);
    return 0;
}

static int modUpdateVelocity(INSTANCE * my, int * params)
{
    cpBodyUpdateVelocity(LOCDWORD(mod_chipmunk,my,LOC_BODY), cpv(*(float *)GLOADDR(mod_chipmunk,GLO_GRAVITY_X),*(float *)GLOADDR(mod_chipmunk,GLO_GRAVITY_Y)), *(float *)GLOADDR(mod_chipmunk,GLO_DAMPING),*(float *)GLOADDR(mod_chipmunk,GLO_INTERVAL)/(float)GLODWORD(mod_chipmunk,GLO_PHRESOLUTION));
    return 0;
}

static int modUpdateVelocity2(INSTANCE * my, int * params)
{
    cpBodyUpdateVelocity(LOCDWORD(mod_chipmunk,my,LOC_BODY), cpv(*(float *)GLOADDR(mod_chipmunk,GLO_GRAVITY_X),*(float *)GLOADDR(mod_chipmunk,GLO_GRAVITY_Y)), *(float *)&params[0],*(float *)GLOADDR(mod_chipmunk,GLO_INTERVAL)/(float)GLODWORD(mod_chipmunk,GLO_PHRESOLUTION));
    return 0;
}

static int modLocal2World(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpVect vc=cpBodyLocal2World(LOCDWORD(mod_chipmunk, b,LOC_BODY), cpv(*(float *)&params[1],*(float *)&params[2]));
    int *x, *y;
    x=params[3];
    *x=vc.x;
    y=params[4];
    *y=vc.y;
    return 0;
}
static int modWorld2Local(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpVect vc=cpBodyWorld2Local(LOCDWORD(mod_chipmunk, b,LOC_BODY), cpv(*(float *)&params[1],*(float *)&params[2]));
    int *x, *y;
    x=params[3];
    *x=vc.x;
    y=params[4];
    *y=vc.y;

    return 0;
}

static int modApplyImpulse(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpBodyApplyImpulse(LOCDWORD(mod_chipmunk, b,LOC_BODY), cpv(*(float *)&params[1],*(float *)&params[2]),cpv(*(float *)&params[3],*(float *)&params[4]));
    return 0;
}

static int modResetForces(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpBodyResetForces(LOCDWORD(mod_chipmunk, b,LOC_BODY));
    return 0;
}

static int modApplyForce(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpBodyApplyForce(LOCDWORD(mod_chipmunk, b,LOC_BODY), cpv(*(float *)&params[1],*(float *)&params[2]),cpv(*(float *)&params[3],*(float *)&params[4]));
    return 0;
}

static int modSleep(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpBodySleep(LOCDWORD(mod_chipmunk, b,LOC_BODY));
    return 0;
}

static int modActivate(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpBodyActivate(LOCDWORD(mod_chipmunk, b,LOC_BODY));
    return 0;
}


static int modIsStatic(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    int a=cpBodyIsStatic(LOCDWORD(mod_chipmunk, b,LOC_BODY));
    return a;
}


static int modIsRogue(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    int a=cpBodyIsRogue(LOCDWORD(mod_chipmunk, b,LOC_BODY));
    return a;
}

static int modIsSleeping(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    int a= cpBodyIsSleeping(LOCDWORD(mod_chipmunk, b,LOC_BODY));
    return a;
}

static int modShapeCacheBB(INSTANCE * my, int * params)
{
    INSTANCE * b = instance_get( params[0] ) ;
    cpShape * s2 = LOCDWORD(mod_chipmunk, b,LOC_SHAPE);
    cpBB res= cpShapeCacheBB(s2);

    cpbb *ve=params[1];
    ve->l=res.l;
    ve->b=res.b;
    ve->r=res.r;
    ve->t=res.t;
    return (0);
}

//boundingbox ids
static int modIntersects(INSTANCE * my, int * params)
{
    INSTANCE * a = instance_get( params[0] ) ;
    INSTANCE * b = instance_get( params[1] ) ;
    int res= (int)cpBBintersects(cpShapeCacheBB(LOCDWORD(mod_chipmunk, a,LOC_SHAPE)),cpShapeCacheBB(LOCDWORD(mod_chipmunk, b,LOC_SHAPE)));
    return res;
}

static int modContains(INSTANCE * my, int * params)
{
    INSTANCE * a = instance_get( params[0] ) ;
    INSTANCE * b = instance_get( params[1] ) ;
    int res= (int)cpBBcontainsBB(cpShapeCacheBB(LOCDWORD(mod_chipmunk, a,LOC_SHAPE)),cpShapeCacheBB(LOCDWORD(mod_chipmunk, b,LOC_SHAPE)));
    return res;
}

static int modContainsVec(INSTANCE * my, int * params)
{
    INSTANCE * a = instance_get( params[0] ) ;
    int res= (int)cpBBcontainsVect(cpShapeCacheBB(LOCDWORD(mod_chipmunk, a,LOC_SHAPE)),cpv(*(float *)&params[1],*(float *)&params[2]));
    return res;
}

//locales de espacio

static int modActivateProcessTouchingIt(INSTANCE * my, int * params)
{
    cpSpaceActivateShapesTouchingShape((cpSpace*)GLODWORD(mod_chipmunk, GLO_SPACE ),(cpShape *)LOCDWORD(mod_chipmunk, my,LOC_SHAPE));
    return 0;
}

//shapes con ids y funciones de control interno

static void addListaProcesos(INSTANCE * ins)
{

    cpBody * a;
    if ( LOCDWORD( mod_chipmunk,ins, LOC_STATIC))
    {
        a=cpBodyNewStatic();
    }
    else
    {
        a=cpBodyNew(*(float*)LOCADDR( mod_chipmunk, ins, LOC_MASS ),*(float*)LOCADDR( mod_chipmunk, ins, LOC_INERTIA ));
        a = cpSpaceAddBody((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), a);
    }

    LOCDWORD( mod_chipmunk, ins, LOC_BODY )=(uint32_t)a;
    DataPointer dataP=malloc(sizeof(Data_Pointer));
    a->data=dataP;
    dataP->father=LOCDWORD( mod_chipmunk, ins, LOC_ID );
    a->p.x=dataP->x=LOCDWORD( mod_chipmunk, ins, LOC_X );
    a->p.y=dataP->y=LOCDWORD( mod_chipmunk, ins, LOC_Y );
    dataP->angle=LOCDWORD( mod_chipmunk, ins, LOC_ANGLE );
    dataP->estado=STATUS_RUNNING;
    cpBodySetAngle(a,-deg2rad(dataP->angle));
    dataP->sig=ListaCuerpos->sig;
    dataP->nShapes=0;
    dataP->body=a;
    dataP->Shapes=NULL;
    dataP->nConstraints=0;
    dataP->Constraints=NULL;
    dataP->typeShape=LOCDWORD( mod_chipmunk, ins, LOC_SHAPETYPE );
    ListaCuerpos->sig=dataP;

    if ( LOCDWORD( mod_chipmunk,ins, LOC_STATIC))
    {
        cpSpaceRehashStatic((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ));
    }
}



static int modaddCircleShape(INSTANCE * my, int * params)
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
    if ( LOCDWORD( mod_chipmunk, my, LOC_STATIC))
        cpSpaceAddStaticShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    else
        cpSpaceAddShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPE )==0)
        LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;


    return (int) sha;
}

static int modaddSegmentShape(INSTANCE * my, int * params)
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
    if ( LOCDWORD( mod_chipmunk, my, LOC_STATIC))
        cpSpaceAddStaticShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    else
        cpSpaceAddShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPE )==0)
        LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;
    return (int) sha;
}

static int modaddPolyShape(INSTANCE * my, int * params)
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
    int ver=params[2];
    cpVect  vec[ver];
    cpvec *vc;
    int z;
    for (z=0; z<ver; z++)
    {
        vc=params[3]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }

    cpShape * sha= cpPolyShapeNew(bod,ver, &vec, cpv(*(float *)&params[0],*(float *)&params[1]));
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
    if ( LOCDWORD( mod_chipmunk, my, LOC_STATIC))
        cpSpaceAddStaticShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    else
        cpSpaceAddShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPE )==0)
        LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;
    return (int) sha;
}

static int creaPoly(int * params,cpBody* bod)
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

static int creaBodyAndShapeAutomat(INSTANCE *my)
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
            sha= cpCircleShapeNew(bod, params[2], cpv(-1*params[0],-1*params[1]));



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
            sha=cpSegmentShapeNew(bod, cpv(params[0],params[1]), cpv(params[2],params[3]),params[4]);
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


            arr[0].x=(map->width / 2)*-1.0 ;
            arr[0].y=(map->height / 2)*-1.0 ;

            arr[1].x=(map->width / 2)*-1.0;
            arr[1].y=map->height / 2 ;

            arr[2].x=map->width / 2 ;
            arr[2].y=map->height / 2 ;

            arr[3].x=map->width / 2 ;
            arr[3].y=(map->height / 2)*-1.0;

            sha= cpPolyShapeNew(bod,params[2], &arr, cpv(-1*params[0],-1*params[1]));

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
    if ( LOCDWORD( mod_chipmunk, my, LOC_STATIC))
        cpSpaceAddStaticShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    else
        cpSpaceAddShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), sha);
    LOCDWORD( mod_chipmunk, my, LOC_SHAPE)=(int) sha;
    return 0;
}

static int modremoveConstraint(INSTANCE * my, int * params)
{
    INSTANCE * a = instance_get( params[0] ) ;
    cpBody *bod =(cpBody *)LOCDWORD( mod_chipmunk, a, LOC_BODY );
    int z,i;
    if (bod)
    {
        DataPointer elem= (DataPointer)bod->data;

        for (z=0; z<elem->nConstraints; z++)
        {
            if (elem->Constraints[z]==params[1])
            {

                //cpSpaceRemoveConstraint((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), elem->Constraints[z]);
                DataPointer dataP=malloc(sizeof(Data_Pointer));
                dataP->nShapes=0;
                dataP->body=0;
                dataP->Shapes=NULL;
                dataP->nConstraints=1;
                dataP->Constraints=malloc(sizeof(cpConstraint *));
                dataP->Constraints[0]=elem->Constraints[z];
                dataP->constraintsBody=malloc(sizeof(cpBody *));;
                dataP->constraintsBody[0]=0;
                modAddLista(dataP);
                cpBody *cuerpo=elem->constraintsBody[z];
                if (cuerpo!=0)
                {
                    DataPointer dato= (DataPointer)cuerpo->data;
                    for (i=0; i<dato->nConstraints; i++)
                    {
                        if (dato->Constraints[i]==elem->Constraints[z])
                        {
                            dato->Constraints[i]=0;
                        }
                    }
                    for (i=0; i<dato->nConstraints; i++)
                    {
                        if (dato->constraintsBody[i]==elem->body)
                            dato->constraintsBody[i]=0;
                    }
                }
                elem->Constraints[z]=0;
            }

        }

    }
    return 0;
}

int indiceConstraints;
DataPointer dataConstraints;

static int modgetConstraints(INSTANCE * my, int * params)
{
    INSTANCE * a = instance_get( params[0] ) ;
    cpBody *bod =(cpBody *)LOCDWORD( mod_chipmunk, a, LOC_BODY );
    int z,i;
    if (bod)
    {
        DataPointer elem= (DataPointer)bod->data;

        if (elem!=dataConstraints)
            indiceConstraints=0;
        dataConstraints=elem;
        if (elem->nConstraints==0)
            return 0;

        if (indiceConstraints>=elem->nConstraints)
        {
            indiceConstraints=0;
            return 0;
        }

        cpConstraint * res = elem->Constraints[indiceConstraints];
        indiceConstraints++;
        return (int) res;

    }
    return 0;
}


int indiceShapes;
DataPointer dataShapes;
static int modgetShapes(INSTANCE * my, int * params)
{
    INSTANCE * a = instance_get( params[0] ) ;
    cpBody *bod =(cpBody *)LOCDWORD( mod_chipmunk, a, LOC_BODY );
    int z,i;
    if (bod)
    {
        DataPointer elem= (DataPointer)bod->data;

        if (elem!=dataShapes)
            indiceShapes=0;
        dataShapes=elem;
        if (elem->nShapes==0)
            return 0;

        if (indiceShapes>=elem->nShapes)
        {
            indiceShapes=0;
            return 0;
        }

        cpConstraint * res = elem->Shapes[indiceShapes];
        indiceShapes++;
        return (int) res;

    }
    return 0;
}

static int modSpacePointQueryFirst(INSTANCE * my, int * params)
{

    cpShape * a=cpSpacePointQueryFirst((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), cpv(*(float*)&params[0],*(float*)&params[1]), params[2], params[3]);
    int id=0;
    if (a!=NULL)
    {
        if (a->body->data!=NULL)
        {
            DataPointer dat= (DataPointer) (a->body->data);
            id=dat->father;
        }
    }
    return id;
}

static int modSpaceSegmentQueryFirst(INSTANCE * my, int * params)
{
    cpLayers lay=params[4];
    cpGroup group = params[5];
    cpSegmentQueryInfo info;
    int id=-1;
    cpShape *a = cpSpaceSegmentQueryFirst((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ),cpv(*(float*)&params[0],*(float*)&params[1]),cpv(*(float*)&params[2],*(float*)&params[3]),lay,group,&info);
    if (a!=NULL)
    {
        cpsegmentqueryinfoB *inf=params[6];
        inf->x=info.n.x;
        inf->y=info.n.y;
        inf->shape=(int)info.shape;
        inf->t=info.t;
        if (a->body->data)
        {
            DataPointer dat= (DataPointer) (a->body->data);
            id=dat->father;

        }
        else
            return 0;
    }
    return id;
}



void buscaABCol(void *ptr, void *data)
{
    colHand* cla=(colHand*) ptr;
    int * arr=(int *)data;
    if (cla->a==arr[0] && cla->b==arr[1])
    {
        Crear=0;
    }

}

void eliminaContactPointSetM(void *ptr, void *data)
{
    cpContactPointSetM * setM =(cpContactPointSetM *)ptr;
    free(setM);
}


static void
recogeColisionHandler(cpArbiter *arb, cpSpace *space, void *dat)
{
    colHand* col= (colHand*)dat;
    cpArray* arr=  col->arr;
    CP_ARBITER_GET_SHAPES(arb, a, b);
    cpContactPointSet set = cpArbiterGetContactPointSet(arb);
    cpContactPointSetM * setM =(cpContactPointSetM*) malloc(sizeof(cpContactPointSetM));

    int i;
    for (i=0; i<set.count; i++)
    {
        setM->points[i].point.x=set.points[i].point.x;
        setM->points[i].point.y=set.points[i].point.y;
        setM->points[i].normal.x=set.points[i].normal.x;
        setM->points[i].normal.y=set.points[i].normal.y;
        setM->points[i].dist=set.points[i].dist;
    }
    setM->count=set.count;
    DataPointer dato=(DataPointer)a->body->data;
    if (dato)
        setM->id1=dato->father;
    else
        setM->id1=0;
    setM->shape1=a;
    dato=(DataPointer)b->body->data;
    if (dato)
        setM->id2=dato->father;
    else
        setM->id2;
    setM->shape2=b;
    cpArrayPush(arr, setM);
}


static int modcrearHandler(INSTANCE * my, int * params)
{
    Crear=1;
    int par[2];
    par[0]=params[0];
    par[1]=params[1];
    cpArrayEach(HandlerColisions, buscaABCol, &par);

    if (!Crear)
        return 0;
    cpArray* arr=cpArrayNew(1);
    cpArray* arr2=cpArrayNew(1);
//cpArrayPush(arr, 0);
    colHand* col= malloc(sizeof(colHand));

    col->arr=arr;
    col->colisiones=arr2;

    col->a=params[0];
    col->b=params[1];

    cpArrayPush(HandlerColisions, col);
    cpSpaceAddCollisionHandler((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), params[0], params[1], NULL, NULL, recogeColisionHandler, NULL, col);
    return (int) col;
}

static int modremoveHandler(INSTANCE * my, int * params)
{
    colHand* col=(colHand*)params[0];
    cpSpaceRemoveCollisionHandler((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), col->a, col->b);
    cpArrayDeleteObj(HandlerColisions, col);
    cpArrayEach(col->arr, (cpArrayIter)eliminaContactPointSetM, NULL);
    cpArrayDestroy(col->arr);
    cpArrayFree(col->arr);
    cpArrayEach(col->colisiones, (cpArrayIter)eliminaContactPointSetM, NULL);
    cpArrayDestroy(col->colisiones);
    cpArrayFree(col->colisiones);
    free(col);
    return 0;
}


static int modgetColInfo(INSTANCE * my, int * params)
{
    colHand* col=(colHand*)params[0];
    //col->colisiones=col->colisiones;
    if (col->colisiones->num>0)
    {
        cpContactPointSetM * set =(cpContactPointSetM *)cpArrayPop(col->colisiones);
        cpContactPointSetM * setM =(cpContactPointSetM *)params[1];
        setM->id1=set->id1;
        setM->id2=set->id2;
        setM->shape1=set->shape1;
        setM->shape2=set->shape2;
        setM->count=set->count;

        fflush(stdout);
        int i;
        for (i=0; i<set->count; i++)
        {
            setM->points[i].point.x=set->points[i].point.x;
            setM->points[i].point.y=set->points[i].point.y;
            setM->points[i].normal.x=set->points[i].normal.x;
            setM->points[i].normal.y=set->points[i].normal.y;
            setM->points[i].dist=set->points[i].dist;
        }
        free(set);
    }
    else
        return 0;

    return 1;
}

static int modsetPinJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_ANCHR1:
        cpPinJointSetAnchr1(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_ANCHR2:
        cpPinJointSetAnchr2(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_DIST:
        cpPinJointSetDist(constr,*(float *)&params[2]);
        break;
    }

    return 1;
}



static int modsetSlideJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_ANCHR1:
        cpSlideJointSetAnchr1(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_ANCHR2:
        cpSlideJointSetAnchr2(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_MIN:
        cpSlideJointSetMin(constr,*(float *)&params[2]);
        break;
    case CP_C_MAX:
        cpSlideJointSetMax(constr,*(float *)&params[2]);
        break;
    }

    return 1;
}



static int modsetPivotJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_ANCHR1:
        cpPivotJointSetAnchr1(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_ANCHR2:
        cpPivotJointSetAnchr2(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    }

    return 1;
}


static int modsetGrooveJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_GROOVEA:
        cpGrooveJointSetGrooveA(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_GROOVEB:
        cpGrooveJointSetGrooveB(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_ANCHR2:
        cpGrooveJointSetAnchr2(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    }

    return 1;
}



static int modsetDampedSpringProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_ANCHR1:
        cpDampedSpringSetAnchr1(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_ANCHR2:
        cpDampedSpringSetAnchr2(constr,cpv(*(float *)&params[2],*(float *)&params[3]));
        break;
    case CP_C_RESTLENGTH:
        cpDampedSpringSetRestLength(constr,*(float *)&params[2]);
        break;
    case CP_C_STIFFNESS:
        cpDampedSpringSetStiffness(constr,*(float *)&params[2]);
        break;
    case CP_C_DAMPING:
        cpDampedSpringSetDamping(constr,*(float *)&params[2]);
        break;
    }

    return 1;
}


static int modsetDampedRotarySpringProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_RESTANGLE:
        cpDampedRotarySpringSetRestAngle(constr,deg2rad(*(float *)&params[2]));
        break;
    case CP_C_STIFFNESS:
        cpDampedRotarySpringSetStiffness(constr,*(float *)&params[2]);
        break;
    case CP_C_DAMPING:
        cpDampedRotarySpringSetDamping(constr,*(float *)&params[2]);
        break;
    }

    return 1;
}



static int modsetRotaryLimitJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_MIN:
        cpRotaryLimitJointSetMin(constr, deg2rad(*(float *)&params[2]) );
        break;
    case CP_C_MAX:
        cpRotaryLimitJointSetMax(constr,deg2rad(*(float *)&params[2]) );
        break;
    }

    return 1;
}




static int modsetRatchetJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_ANGLE:
        cpRatchetJointSetAngle(constr,deg2rad(*(float *)&params[2]) );
        break;
    case CP_C_PHASE:
        cpRatchetJointSetPhase(constr,deg2rad(*(float *)&params[2]));
        break;
    case CP_C_RATCHET:
        cpRatchetJointSetRatchet(constr,deg2rad(*(float *)&params[2]));
        break;
    }

    return 1;
}



static int modsetGearJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_RATIO:
        cpGearJointSetRatio(constr,deg2rad(*(float *)&params[2]));
        break;
    case CP_C_PHASE:
        cpGearJointSetPhase(constr,deg2rad(*(float *)&params[2]));
        break;
    }

    return 1;
}



static int modsetSimpleMotorProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    switch (params[1])
    {
    case CP_C_RATIO:

        cpSimpleMotorSetRate(constr,deg2rad(*(float *)&params[2]) );
        break;
    }

    return 1;
}

static int modgetPinJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    cpVect ar;
    float *a,*b,res;
    switch (params[1])
    {
    case CP_C_ANCHR1:
        ar=cpPinJointGetAnchr1(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;

        break;
    case CP_C_ANCHR2:
        ar=cpPinJointGetAnchr2(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_DIST:
        res=cpPinJointGetDist(constr);
        return *(int *)&res;
        break;
    }

    return 1;
}



static int modgetSlideJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    cpVect ar;
    float *a,*b,res;
    switch (params[1])
    {
    case CP_C_ANCHR1:
        ar=cpSlideJointGetAnchr1(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_ANCHR2:
        ar=cpSlideJointGetAnchr2(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_MIN:
        res=cpSlideJointGetMin(constr);
        return *(int *)&res;
        break;
    case CP_C_MAX:
        res=cpSlideJointGetMax(constr);
        return *(int *)&res;
        break;
    }

    return 1;
}



static int modgetPivotJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    cpVect ar;
    float *a,*b,res;
    switch (params[1])
    {
    case CP_C_ANCHR1:
        ar=cpPivotJointGetAnchr1(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_ANCHR2:
        ar=cpPivotJointGetAnchr2(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    }

    return 1;
}


static int modgetGrooveJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    cpVect ar;
    float *a,*b,res;
    switch (params[1])
    {
    case CP_C_GROOVEA:
        ar=cpGrooveJointGetGrooveA(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_GROOVEB:
        ar=cpGrooveJointGetGrooveB(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_ANCHR2:
        cpGrooveJointGetAnchr2(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    }

    return 1;
}



static int modgetDampedSpringProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    cpVect ar;
    float *a,*b,res;
    switch (params[1])
    {
    case CP_C_ANCHR1:
        ar=cpDampedSpringGetAnchr1(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_ANCHR2:
        ar=cpDampedSpringGetAnchr2(constr);
        a=params[2];
        b=params[3];
        *a=ar.x;
        *b=ar.y;
        break;
    case CP_C_RESTLENGTH:
        res=cpDampedSpringGetRestLength(constr);
        return *(int *)&res;
        break;
    case CP_C_STIFFNESS:
        res=cpDampedSpringGetStiffness(constr);
        return *(int *)&res;
        break;
    case CP_C_DAMPING:
        res=cpDampedSpringGetDamping(constr);
        return *(int *)&res;
        break;
    }

    return 1;
}


static int modgetDampedRotarySpringProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    float res;
    switch (params[1])
    {
    case CP_C_RESTANGLE:
        res=cpDampedRotarySpringGetRestAngle(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    case CP_C_STIFFNESS:
        res=cpDampedRotarySpringGetStiffness(constr);
        return *(int *)&res;
        break;
    case CP_C_DAMPING:
        res=cpDampedRotarySpringGetDamping(constr);
        return *(int *)&res;
        break;
    }

    return 1;
}



static int modgetRotaryLimitJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    float res;
    switch (params[1])
    {
    case CP_C_MIN:
        res=cpRotaryLimitJointGetMin(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    case CP_C_MAX:
        res=cpRotaryLimitJointGetMax(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    }

    return 1;
}




static int modgetRatchetJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    float res;
    switch (params[1])
    {
    case CP_C_ANGLE:
        res=cpRatchetJointGetAngle(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    case CP_C_PHASE:
        res=cpRatchetJointGetPhase(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    case CP_C_RATCHET:
        res=cpRatchetJointGetRatchet(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    }

    return 1;
}



static int modgetGearJointProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    float res;
    switch (params[1])
    {
    case CP_C_RATIO:
        res=cpGearJointGetRatio(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    case CP_C_PHASE:
        res=cpGearJointGetPhase(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    }

    return 1;
}



static int modgetSimpleMotorProperties(INSTANCE * my, int * params)
{
    cpConstraint * constr=(cpConstraint *)params[0];
    float res;
    switch (params[1])
    {
    case CP_C_RATIO:
        res=cpSimpleMotorGetRate(constr);
        res=rad2deg(res);
        return *(int *)&res;
        break;
    }

    return 1;
}

static int modSegmentQueryHitPoint(INSTANCE * my, int * params)
{
    cpvec *vc;
    cpSegmentQueryInfo info;
    cpsegmentqueryinfoB *inf=params[4];
    info.t=inf->t;
    info.n=cpv(inf->x,inf->y);
    info.shape=(cpShape *)inf->shape;
    cpVect resAux = cpSegmentQueryHitPoint(cpv(params[0],params[1]),cpv(params[2],params[3]),info);
    int * x=params[5];
    int * y=params[6];
    *x=resAux.x;
    *y=resAux.y;
    return 1;
}

static int modSegmentQueryHitDist(INSTANCE * my, int * params)
{
    cpvec *vc;
    cpSegmentQueryInfo info;
    cpsegmentqueryinfoB *inf=params[4];
    info.t=inf->t;
    info.n=cpv(inf->x,inf->y);
    info.shape=(cpShape *)inf->shape;
    float res = cpSegmentQueryHitDist(cpv(params[0],params[1]),cpv(params[2],params[3]),info);
    return *(float *)&res;
}

static int moddeg2rad(INSTANCE * my, int * params)
{
    return ((*(float*)&params[0])/180000)*CM_PI;
}

//agregan cuerpos est[aticos al fondo

static int modaddInanimateShape(INSTANCE * my, int * params)
{
    if (params[0]<=TYPE_NONE || params[0]>=TYPE_EMPTY)
        return 0;
    cpSpace * espacio=(cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ) ;
    cpBody * bod=&espacio->staticBody;

    DataPointer dato= DataP_Espacio;
    cpShape* sha;
    if (params[0]== TYPE_BOX || params[0]== TYPE_CONVEX_POLYGON)
    {
        int ver=params[3];
        cpVect  vec[ver];
        cpvec *vc;
        int z;
        for (z=0; z<ver; z++)
        {
            vc=params[4]+z*sizeof(cpvec);
            vec[z].x=vc->x;
            vec[z].y=vc->y;
        }
        sha= cpPolyShapeNew(bod,ver, &vec, cpv(*(float *)&params[1],*(float *)&params[2]));
    }
    else
    {
        switch (params[0])
        {
        case TYPE_CIRCLE:
            sha= cpCircleShapeNew(bod, *(float *)&params[3], cpv(*(float *)&params[1],*(float *)&params[2]));
            break;
        case TYPE_LINE:
            sha= cpSegmentShapeNew(bod, cpv(*(float *)&params[1],*(float *)&params[2]), cpv(*(float *)&params[3],*(float *)&params[4]),*(float *)&params[5]);
            break;
        }
    }
    sha->e=1;
    sha->u=1;
    dato->nShapes++;
    dato->Shapes=realloc(dato->Shapes,sizeof(cpShape*)*(dato->nShapes));
    dato->Shapes[dato->nShapes-1]=sha;
    cpSpaceAddStaticShape(espacio, sha);

    return (int) sha;
}



static int modsetEndPointsLine(INSTANCE * my, int * params)
{
    cpSegmentShapeSetEndpoints((cpShape*)LOCDWORD( mod_chipmunk,  my, LOC_SHAPE), cpv(*(float*)&params[0],*(float*)&params[1]),cpv(*(float*)&params[2],*(float*)&params[3]));
    return 0;
}


static int modsetRadiusLine(INSTANCE * my, int * params)
{
    cpSegmentShapeSetRadius((cpShape*)LOCDWORD( mod_chipmunk,  my, LOC_SHAPE), *(float*)&params[0]);
    return 0;
}

static int modsetOffsetCircle(INSTANCE * my, int * params)
{
    cpCircleShapeSetOffset((cpShape*)LOCDWORD( mod_chipmunk,  my, LOC_SHAPE), cpv(*(float*)&params[0],*(float*)&params[1]));
    return 0;
}

static int modsetRadiusCircle(INSTANCE * my, int * params)
{
    cpCircleShapeSetRadius((cpShape*)LOCDWORD( mod_chipmunk,  my, LOC_SHAPE), *(float*)&params[0]);
    return 0;
}

static int modsetVertConvexPoligon(INSTANCE * my, int * params)
{

    int ver=params[2];
    cpVect  vec[ver];
    cpvec *vc;
    int z;
    for (z=0; z<ver; z++)
    {
        vc=params[3]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }
    cpPolyShapeSetVerts((cpShape*)LOCDWORD( mod_chipmunk,  my, LOC_SHAPE), ver, &vec,cpv(*(float*)&params[0],*(float*)&params[1]));
    return 0;
}

static int modsetEndPointsLineI(INSTANCE * my, int * params)
{
    cpSegmentShapeSetEndpoints((cpShape*)params[0], cpv(*(float*)&params[1],*(float*)&params[2]),cpv(*(float*)&params[3],*(float*)&params[4]));
    return 0;
}


static int modsetRadiusLineI(INSTANCE * my, int * params)
{
    cpSegmentShapeSetRadius((cpShape*)params[0], *(float*)&params[1]);
    return 0;
}

static int modsetOffsetCircleI(INSTANCE * my, int * params)
{
    cpCircleShapeSetOffset((cpShape*)params[0], cpv(*(float*)&params[1],*(float*)&params[2]));
    return 0;
}

static int modsetRadiusCircleI(INSTANCE * my, int * params)
{
    cpCircleShapeSetRadius((cpShape*)params[0], *(float*)&params[1]);
    return 0;
}

static int modsetVertConvexPoligonI(INSTANCE * my, int * params)
{

    int ver=params[3];
    cpVect  vec[ver];
    cpvec *vc;
    int z;
    for (z=0; z<ver; z++)
    {
        vc=params[4]+z*sizeof(cpvec);
        vec[z].x=vc->x;
        vec[z].y=vc->y;
    }
    cpPolyShapeSetVerts((cpShape*)params[0], ver, &vec,cpv(*(float*)&params[1],*(float*)&params[2]));
    return 0;
}

int gEstatico=0;

static void postStepRemove(void *a, void *b, void *unused)
{

    int z,i;
    if (lista!=NULL)
    {
        cpBool estatico;
        for (; numLista>0; numLista--)
        {
            DataPointer elem= lista[numLista];

            for (z=0; z<elem->nConstraints; z++)    //elimina todo registro de estas constraints de los demás procesos
            {

                if (elem->Constraints[z]!=0)
                {
                    cpSpaceRemoveConstraint((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), elem->Constraints[z]);
                    cpBody *cuerpo=elem->constraintsBody[z];

                    if (cuerpo!=0)
                    {
                        DataPointer dato= (DataPointer)cuerpo->data;
                        for (i=0; i<dato->nConstraints; i++)
                        {
                            if (dato->Constraints[i]==elem->Constraints[z])
                            {
                                dato->Constraints[i]=0;
                            }
                        }
                        for (i=0; i<dato->nConstraints; i++)
                        {
                            if (dato->constraintsBody[i]==elem->body)
                                dato->constraintsBody[i]=0;
                        }
                    }
                }
            }
            if (elem->body)
            {
                estatico=cpBodyIsStatic(elem->body);
                if (!estatico)
                    cpSpaceRemoveBody(GLODWORD(mod_chipmunk, GLO_SPACE ), elem->body);
            }
            else
                estatico=1;
            for (z=0; z<elem->nShapes; z++)

            {
                if (estatico)
                {
                    cpSpaceRemoveStaticShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), (cpShape *)elem->Shapes[z]);
                }
                else
                    cpSpaceRemoveShape((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), (cpShape *)elem->Shapes[z]);
            }
            for (z=0; z<elem->nConstraints; z++)
                cpConstraintFree(elem->Constraints[z]);

            if (elem->body)
                cpBodyFree((cpBody *)elem->body);

            for (z=0; z<elem->nShapes; z++)
                cpShapeFree(elem->Shapes[z]);
            fflush(stdout);
            if (lista[numLista]->Shapes!=   NULL)
                free(lista[numLista]->Shapes);
            if (lista[numLista]->Constraints!=   NULL)
                free(lista[numLista]->Constraints);
            free(lista[numLista]);
        }


    }
    if (elim)
    {
        free(lista);
        lista=NULL;
    }

}
static modInitLista()
{
    lista=malloc(sizeof(DataPointer));
    elim=0;
}

static modAddLista(DataPointer a)
{
    if (lista!=NULL)
    {
        numLista++;
        lista=realloc(lista,sizeof(DataPointer)*(numLista+1));
        lista[numLista]=a;
        cpSpaceAddPostStepCallback((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), (cpPostStepFunc)postStepRemove, NULL, NULL);
    }
}

static int modFreeLista()
{
    // cpSpaceAddPostStepCallback((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), (cpPostStepFunc)postStepRemove, NULL, NULL);
    //cpSpaceStep((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), *(float *)GLOADDR(mod_chipmunk,GLO_INTERVAL));
    postStepRemove(NULL,NULL,NULL);
    elim=1;
    return  0;
}



static void remueveProcesoListaProcesos(DataPointer a)
{
    DataPointer aux= a->sig->sig;
    modAddLista(a->sig);
    a->sig=aux;
}

static void inicializaListaProcesos( )
{
    ListaCuerpos=malloc(sizeof(Data_Pointer));
    ListaCuerpos->sig=NULL;
}
int existe(int id)
{
    INSTANCE * i, * ctx;

    if ( id == 0 ) return 0;

    if ( id >= FIRST_INSTANCE_ID )
    {
        i = instance_get( id ) ;
        if ( i && ( LOCDWORD( mod_chipmunk, i, LOC_RSTATUS ) & ~STATUS_WAITING_MASK ) >= STATUS_RUNNING ) return 1;
        return 0;
    }

    ctx = NULL;
    while ( ( i = instance_get_by_type( id, &ctx ) ) )
    {
        if ( ( LOCDWORD( mod_chipmunk, i, LOC_RSTATUS ) & ~STATUS_WAITING_MASK ) >= STATUS_RUNNING ) return 1;
    }

    return 0;


}
static void eliminaListaProcesos()
{
    DataPointer aux;
    for (aux= ListaCuerpos; aux->sig!=NULL; aux=aux->sig)
    {
        if (existe(aux->sig->father))
        {
            INSTANCE * i = instance_get( aux->sig->father) ;
            LOCDWORD( mod_chipmunk, i, LOC_BODY )=0;
            LOCDWORD( mod_chipmunk, i, LOC_SHAPE )=0;
            LOCDWORD( mod_chipmunk, i, LOC_SHAPETYPE )=TYPE_NONE;
        }
        modAddLista(aux->sig);
    }
    free(ListaCuerpos);
    ListaCuerpos=NULL;
}



void actualizaProcess(DataPointer dat)
{
    cpBody * cuerpo = dat->body;
    INSTANCE * ins= instance_get( dat->father ) ;
    if (!LOCDWORD( mod_chipmunk, ins, LOC_STATIC ))
    {
        if (LOCDWORD( mod_chipmunk, ins, LOC_RSTATUS )== STATUS_RUNNING && cpBodyIsSleeping(cuerpo))
        {
            cpBodyActivate(cuerpo);
        }
        else
        {
            if ((LOCDWORD( mod_chipmunk, ins, LOC_RSTATUS )== STATUS_SLEEPING || LOCDWORD( mod_chipmunk, ins, LOC_RSTATUS )== STATUS_FROZEN) && !cpBodyIsSleeping(cuerpo))
            {
                cpBodySleep(cuerpo);
            }

        }
    }
    float resolucion=LOCDWORD( mod_chipmunk, ins, LOC_RESOLUTION )>0? LOCDWORD( mod_chipmunk, ins, LOC_RESOLUTION ) : 1.0f;

    if (LOCDWORD( mod_chipmunk, ins, LOC_X )!= dat->x || LOCDWORD( mod_chipmunk, ins, LOC_Y )!= dat->y)
    {
        cuerpo->p.x=LOCDWORD( mod_chipmunk, ins, LOC_X )/resolucion;
        dat->x=LOCDWORD( mod_chipmunk, ins, LOC_X );
        dat->y=LOCDWORD( mod_chipmunk, ins, LOC_Y );
        cuerpo->p.y=LOCDWORD( mod_chipmunk, ins, LOC_Y )/resolucion;
        if (LOCDWORD( mod_chipmunk, ins, LOC_STATIC ))
        gEstatico=1;
           // cpSpaceRehashStatic((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ));
    }
    else
    {
        dat->x=LOCDWORD( mod_chipmunk, ins, LOC_X )=cuerpo->p.x*resolucion;
        dat->y=LOCDWORD( mod_chipmunk, ins, LOC_Y )=cuerpo->p.y*resolucion;
    }

    if (LOCDWORD( mod_chipmunk, ins, LOC_ANGLE )!=dat->angle)
    {
        dat->angle=LOCDWORD( mod_chipmunk, ins, LOC_ANGLE );
        cpBodySetAngle(cuerpo,-deg2rad(dat->angle));
        if (LOCDWORD( mod_chipmunk, ins, LOC_STATIC ))
            gEstatico=1;
           // cpSpaceRehashStatic((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ));
    }
    else
    {
        LOCDWORD( mod_chipmunk, ins, LOC_ANGLE )=-rad2deg(cuerpo->a);
        dat->angle=LOCDWORD( mod_chipmunk, ins, LOC_ANGLE );
    }
    if (cuerpo->m!=infinito(*(float*)LOCADDR( mod_chipmunk, ins, LOC_MASS )))
        cpBodySetMass(cuerpo,infinito(LOCDWORD( mod_chipmunk, ins, LOC_MASS )));

    if (cuerpo->i!=infinito(*(float*)LOCADDR( mod_chipmunk, ins, LOC_INERTIA )))
        cpBodySetMoment(cuerpo,infinito(*(float*)LOCADDR( mod_chipmunk, ins, LOC_INERTIA )));

    cpShape* shape=(cpShape*)LOCDWORD( mod_chipmunk, ins, LOC_SHAPE);
    if (shape!=NULL)
    {
        shape->e=*(float*)LOCADDR( mod_chipmunk, ins, LOC_ELASTICITY );
        shape->u=*(float*)LOCADDR( mod_chipmunk, ins, LOC_FRICTION );
        shape->group=LOCDWORD( mod_chipmunk, ins, LOC_GROUP );
        shape->layers=LOCDWORD( mod_chipmunk, ins, LOC_LAYERS );
        shape->collision_type=LOCDWORD( mod_chipmunk, ins, LOC_COLLISIONTYPE );
    }
    if (LOCDWORD( mod_chipmunk, ins, LOC_INCR_X )!=0 || LOCDWORD( mod_chipmunk, ins, LOC_INCR_Y )!=0)
    {
        cuerpo->p.x=(LOCDWORD( mod_chipmunk, ins, LOC_INCR_X )+LOCDWORD( mod_chipmunk, ins, LOC_X ))/resolucion;
        cuerpo->p.y=(LOCDWORD( mod_chipmunk, ins, LOC_INCR_Y )+LOCDWORD( mod_chipmunk, ins, LOC_Y ))/resolucion;
        if (LOCDWORD( mod_chipmunk, ins, LOC_STATIC ))
                        gEstatico=1;
            //cpSpaceRehashStatic((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ));
        LOCDWORD( mod_chipmunk, ins, LOC_INCR_X )=0;
        LOCDWORD( mod_chipmunk, ins, LOC_INCR_Y )=0;
    }

}

void ActualizaLista(void *ptr, void *data)
{
    colHand * col=(colHand*) ptr;
    cpArrayEach(col->colisiones, eliminaContactPointSetM, NULL);
    cpArrayDestroy(col->colisiones);
    cpArrayFree(col->colisiones);
    col->colisiones=col->arr;
    col->arr=cpArrayNew(1);
}



int contItUp;
DataPointer auxIterator;
static int updatePhisc()
{
    gEstatico=0;
    cpSpace * espacio = (cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE );
    espacio->gravity.x= *(float *)GLOADDR(mod_chipmunk,GLO_GRAVITY_X);
    espacio->gravity.y= *(float *)GLOADDR(mod_chipmunk,GLO_GRAVITY_Y);
    cp_bias_coef=*(float *)GLOADDR(mod_chipmunk,GLO_BIAS_COEF);
    cp_collision_slop=*(float *)GLOADDR(mod_chipmunk,GLO_COLLISION_SLOP);
    cp_contact_persistence=GLODWORD(mod_chipmunk,GLO_CONTACT_PERSISTENCE);
    espacio->iterations= GLODWORD(mod_chipmunk,GLO_ITERATIONS);
    espacio->damping= *(float *)GLOADDR(mod_chipmunk,GLO_DAMPING);
    espacio->idleSpeedThreshold= *(float *)GLOADDR(mod_chipmunk,GLO_IDLESPEEDTHRESHOLD);
    espacio->sleepTimeThreshold= infinito(*(float *)GLOADDR(mod_chipmunk,GLO_SLEEPTIMETHRESHOLD));
    for (contItUp=0; contItUp<GLODWORD(mod_chipmunk,GLO_PHRESOLUTION); contItUp++)
        cpSpaceStep(espacio,*(float *)GLOADDR(mod_chipmunk,GLO_INTERVAL)/(float)GLODWORD(mod_chipmunk,GLO_PHRESOLUTION) );

    cpArrayEach(HandlerColisions,ActualizaLista,NULL);
    INSTANCE *i = first_instance ;
    while ( i )
    {
        if (LOCDWORD( mod_chipmunk, i, LOC_BODY )==0 &&  LOCDWORD( mod_chipmunk, i, LOC_SHAPETYPE )!=0)
        {
            creaBodyAndShapeAutomat(i);
        }
        i = i->next ;
    }
    for (auxIterator=ListaCuerpos; auxIterator->sig!=NULL; )
    {
        if (existe(auxIterator->sig->father))
        {
            if (LOCDWORD( mod_chipmunk, instance_get(auxIterator->sig->father), LOC_SHAPETYPE )!=auxIterator->sig->typeShape || auxIterator->sig->estado==STATUS_DEAD)
            {
                if (LOCDWORD( mod_chipmunk, instance_get(auxIterator->sig->father), LOC_SHAPETYPE )!=auxIterator->sig->typeShape && LOCDWORD( mod_chipmunk, instance_get(auxIterator->sig->father), LOC_BODY )==auxIterator->sig->body)
                {
                    LOCDWORD( mod_chipmunk, instance_get(auxIterator->sig->father), LOC_BODY )=0;
                    LOCDWORD( mod_chipmunk, instance_get(auxIterator->sig->father), LOC_SHAPE )=0;
                }
                remueveProcesoListaProcesos(auxIterator);
            }
            else
            {
                actualizaProcess(auxIterator->sig);
                auxIterator=auxIterator->sig;
            }
        }
        else
        {
            remueveProcesoListaProcesos(auxIterator);
        }
    }

    if (gEstatico);
            cpSpaceRehashStatic((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ));

    return 0;
}

HOOK __bgdexport (mod_chipmunk , handler_hooks ) [] =
{
    { 4700 , updatePhisc},
    { 0 , NULL }
};


void __bgdexport( mod_chipmunk, module_initialize )()
{
    cpInitChipmunk();
    GLODWORD(mod_chipmunk, GLO_SPACE ) = (int)cpSpaceNew();
    cpSpaceInit(GLODWORD(mod_chipmunk, GLO_SPACE ));
    lista=malloc(sizeof(DataPointer));
    inicializaListaProcesos();
    HandlerColisions=cpArrayNew(0);

    DataP_Espacio=malloc(sizeof(Data_Pointer));
    DataP_Espacio->father=0;
    DataP_Espacio->sig=NULL;
    DataP_Espacio->nShapes=0;
    DataP_Espacio->body=0;
    DataP_Espacio->Shapes=malloc(0);
    DataP_Espacio->nConstraints=0;
    DataP_Espacio->Constraints=NULL;
    DataP_Espacio->typeShape=TYPE_EMPTY;
}


void eliminaHandlerLista(void *ptr, void *data)
{


    colHand* col=(colHand*) ptr;
    //cpSpaceRemoveCollisionHandler((cpSpace *)GLODWORD(mod_chipmunk, GLO_SPACE ), col->a, col->b);
    //cpArrayDeleteObj(HandlerColisions, col);
    cpArrayEach(col->arr, (cpArrayIter)eliminaContactPointSetM, NULL);
    cpArrayDestroy(col->arr);
    cpArrayFree(col->arr);
    cpArrayEach(col->colisiones, (cpArrayIter)eliminaContactPointSetM, NULL);
    cpArrayDestroy(col->colisiones);
    cpArrayFree(col->colisiones);
    free(col);
}

void __bgdexport( mod_chipmunk, module_finalize )()
{

    eliminaListaProcesos();
    modAddLista(DataP_Espacio);
    modFreeLista(lista);
    cpSpaceFreeChildren(GLODWORD(mod_chipmunk, GLO_SPACE ));
    cpSpaceFree(GLODWORD(mod_chipmunk, GLO_SPACE ));
    cpArrayEach(HandlerColisions,eliminaHandlerLista,NULL);
    cpArrayDestroy(HandlerColisions);
    cpArrayFree(HandlerColisions);

}

static int modcleanSpace(INSTANCE * my, int * params)
{
    //elimina todo el mundo físico
    eliminaListaProcesos();
    modAddLista(DataP_Espacio);
    modFreeLista(lista);
    cpSpaceFreeChildren(GLODWORD(mod_chipmunk, GLO_SPACE ));
    cpSpaceFree(GLODWORD(mod_chipmunk, GLO_SPACE ));
    cpArrayEach(HandlerColisions,eliminaHandlerLista,NULL);
    cpArrayDestroy(HandlerColisions);
    cpArrayFree(HandlerColisions);

    //crea el nuevo espacio
    GLODWORD(mod_chipmunk, GLO_SPACE ) = (int)cpSpaceNew();
    cpSpaceInit(GLODWORD(mod_chipmunk, GLO_SPACE ));
    lista=malloc(sizeof(DataPointer));
    inicializaListaProcesos();
    HandlerColisions=cpArrayNew(0);

    DataP_Espacio=malloc(sizeof(Data_Pointer));
    DataP_Espacio->father=0;
    DataP_Espacio->sig=NULL;
    DataP_Espacio->nShapes=0;
    DataP_Espacio->body=0;
    DataP_Espacio->Shapes=malloc(0);
    DataP_Espacio->nConstraints=0;
    DataP_Espacio->Constraints=NULL;
    DataP_Espacio->typeShape=TYPE_EMPTY;

    numLista=0;
}

static int modForceCreateBody(INSTANCE * my, int * params)
{
    if (LOCDWORD( mod_chipmunk, my, LOC_BODY )!=0)
    {
        cpBody * bod=(cpBody *) LOCDWORD( mod_chipmunk, my, LOC_BODY );
        DataPointer est= (DataPointer) bod->data;
        est->estado=STATUS_DEAD;
    }
    if (LOCDWORD( mod_chipmunk, my, LOC_SHAPETYPE )!=TYPE_NONE)
        creaBodyAndShapeAutomat(my);

    return 1;
}

char * __bgdexport( mod_chipmunk, modules_dependency )[] =
{
    "librender",
    "libgrbase",
    "libdraw",
    "libblit",
    NULL
};



DLSYSFUNCS __bgdexport( mod_chipmunk, functions_exports) [] =
{

    {"DEG2RAD" , "F",   TYPE_FLOAT, moddeg2rad},
    {"SEGMENTQUERYHITDIST" , "IIIIP",   TYPE_FLOAT, modSegmentQueryHitDist},
    {"SEGMENTQUERYHITPOINT" , "IIIIPPP",   TYPE_INT, modSegmentQueryHitPoint},
    {"FORCECREATEBODY" , "",   TYPE_INT, modForceCreateBody},

    //destrucción general
    {"CLEANSPACE" , "",   TYPE_INT, modcleanSpace},

    //Funciones matemáticas
    {"CPFLERP" , "FFF",   TYPE_FLOAT, modcpflerp},
    {"CPFCLAMP" , "FFF",   TYPE_FLOAT, modcpfclamp},
    {"CPFLERPCONST" , "FFF",   TYPE_FLOAT, modcpflerpconst},

    //OPERACIONES CON VECTORES
    {"CPVEQL" , "PP",   TYPE_INT, modcpveql},
    {"CPVADD" , "PPP",   TYPE_INT, modcpvadd},
    {"CPVSUB" , "PPP",   TYPE_INT, modcpvsub},
    {"CPVNEG" , "PP",   TYPE_INT, modcpvneg},
    {"CPVMULT" , "PFP",   TYPE_INT, modcpvmult},
    {"CPVPERP" , "PP",   TYPE_INT, modcpvperp},
    {"CPVRPERP" , "PP",   TYPE_INT, modcpvrperp},
    {"CPVNORMALIZE" , "PP",   TYPE_INT, modcpvnormalize},
    {"CPVNORMALIZE_SAFE" , "PP",   TYPE_INT, modcpvnormalize_safe},
    {"CPVPROJECT" , "PPP",   TYPE_INT, modcpvproject},
    {"CPVROTATE" , "PPP",   TYPE_INT, modcpvrotate},
    {"CPVUNROTATE" , "PPP",   TYPE_INT, modcpvunrotate},
    {"CPVFORANGLE" , "FP",   TYPE_INT, modcpvforangle},
    {"CPVCLAMP" , "PFP",   TYPE_INT, modcpvclamp},
    {"CPVLERP" , "PPFP",   TYPE_INT, modcpvlerp},
    {"CPVLERPCONST" , "PPFP",   TYPE_INT, modcpvlerpconst},
    {"CPVSLERP" , "PPFP",   TYPE_INT, modcpvslerp},
    {"CPVSLERPCONST" , "PPFP",   TYPE_INT, modcpvslerpconst},
    {"CPVNEAR" , "PPF",   TYPE_INT, modcpvnear},

    {"CPVDOT" , "PP",   TYPE_FLOAT, modcpvdot},
    {"CPVCROSS" , "PP",   TYPE_FLOAT, modcpvcross},
    {"CPVLENGTH" , "P",   TYPE_FLOAT, modcpvlength},
    {"CPVLENGTHSQ" , "P",   TYPE_FLOAT, modcpvlengthsq},
    {"CPVTOANGLE" , "P",   TYPE_FLOAT, modcpvtoangle},
    {"CPVDISTSQ" , "PP",   TYPE_FLOAT, modcpvdistsq},
    {"CPVDIST" , "PP",   TYPE_FLOAT, modcpvdist},

    {"CPVSTR" , "P",   TYPE_STRING, modcpvstr},
    {"CPV" , "FFP",    TYPE_POINTER, modcpv},


    //cpBB
    {"CPBBWRAPVECT" , "PPP",   TYPE_INT, modcpBBWrapVect},
    {"CPBBCLAMPVECT" , "PPP",   TYPE_INT, modcpBBClampVect},
    {"CPBBEXPAND" , "PPP",   TYPE_INT, modcpBBexpand},
    {"CPBBCONTAINSVECT" , "PP",   TYPE_INT, modcpBBcontainsVect},
    {"CPBBMERGE" , "PPP",   TYPE_INT, modcpBBmerge},
    {"CPBBCONTAINSBB" , "PP",   TYPE_INT, modcpBBcontainsBB},
    {"CPBBINTERSECTS" , "PP",   TYPE_INT, modcpBBintersects},
    {"CPBBNEW" , "FFFFP",   TYPE_INT, modcpBBNew},



    //cpBody
    {"DEFBODYP" , "IIP",   TYPE_INT, modDefcpBody},
    {"DEFBODYF" , "IIF",   TYPE_INT, modDefcpBody},
    {"DEFBODYI" , "III",   TYPE_INT, modDefcpBody},

    {"GETBODY" , "I",   TYPE_INT, modgetBody},
    {"CPBODYLOCAL2WORLD" , "IPP",   TYPE_INT, modcpBodyLocal2World},
    {"GETBODY" , "II",   TYPE_FLOAT, modGetEcpBody},
    {"GETBODY" , "IIP",   TYPE_INT, modGetEcpBody},

    {"CPMOMENTFORCIRCLE" , "FFFP",   TYPE_FLOAT, modcpMomentForCircle},
    {"CPMOMENTFORSEGMENT" , "FPP",   TYPE_FLOAT, modcpMomentForSegment},
    {"CPMOMENTFORPOLY" , "FIPP",   TYPE_FLOAT, modcpMomentForPoly},
    {"CPMOMENTFORBOX" , "FFF",   TYPE_FLOAT, modcpMomentForBox},
    {"CPMOMENTFORCIRCLE" , "FFFFF",   TYPE_FLOAT, modcpMomentForCircle1},
    {"CPMOMENTFORSEGMENT" , "FFFFF",   TYPE_FLOAT, modcpMomentForSegment1},
    {"CPMOMENTFORPOLY" , "FIPFF",   TYPE_FLOAT, modcpMomentForPoly1},
    {"CPAREAFORCIRCLE" , "FF",   TYPE_FLOAT, modcpAreaForCircle},
    {"CPAREAFORSEGMENT" , "PPF",   TYPE_FLOAT, modcpAreaForSegment},
    {"CPAREAFORPOLY" , "IP",   TYPE_FLOAT, modcpAreaForPoly},
    {"CPBODYSETMASS" , "IF",   TYPE_INT, modcpBodySetMass},
    {"CPBODYSETMOMENT" , "IF",   TYPE_INT, modcpBodySetMoment},
    {"CPBODYSETANGLE" , "IF",   TYPE_INT, modcpBodySetAngle},
    {"CPBODYUPDATEPOSITION" , "IF",   TYPE_INT, modcpBodyUpdatePosition},
    {"CPBODYRESETFORCES" , "I",   TYPE_INT, modcpBodyResetForces},
    {"CPBODYISSLEEPING" , "I",   TYPE_INT, modcpBodyIsSleeping},
    {"CPBODYSLEEP" , "I",   TYPE_INT, modcpBodySleep},
    {"CPBODYACTIVATE" , "I",   TYPE_INT, modcpBodyActivate},
    {"CPBODYISSTATIC" , "I",   TYPE_INT, modcpBodyIsStatic},
    {"CPBODYISROGUE" , "I",   TYPE_INT, modcpBodyIsRogue},
    {"CPBODYSLEEPWITHGROUP" , "II",   TYPE_INT, modcpBodySleepWithGroup},
    {"CPBODYAPPLYFORCE" , "IPP",   TYPE_INT, modcpBodyApplyForce},
    {"CPBODYAPPLYIMPULSE" , "IPP",   TYPE_INT, modcpBodyApplyImpulse},
    {"CPBODYWORLD2LOCAL" , "IPP",   TYPE_INT, modcpBodyWorld2Local},
    {"CPBODYSLEW" , "IPF",   TYPE_INT, modcpBodySlew},
    {"CPBODYUPDATEVELOCITY" , "IPFF",   TYPE_INT, modcpBodyUpdateVelocity},


    //cpShape
    {"DEFSHAPEI" , "III",   TYPE_INT, modDefcpShape},
    {"DEFSHAPEF" , "IIF",   TYPE_INT, modDefcpShape},
    {"DEFSHAPEP" , "IIP",   TYPE_INT, modDefcpShape},
    {"CPPOLYSHAPEGETVERT" , "IIP",   TYPE_INT, modcpPolyShapeGetVert},

    {"CPRECENTERPOLY" , "IP",   TYPE_INT, modcpRecenterPoly},
    {"CPCENTROIDFORPOLY" , "IPP",   TYPE_INT, modcpCentroidForPoly},
    {"CPSEGMENTSHAPEGETRADIUS" , "I",   TYPE_FLOAT, modcpSegmentShapeGetRadius},
    {"CPCIRCLESHAPEGETRADIUS" , "I",   TYPE_FLOAT, modcpCircleShapeGetRadius},
    {"CPSEGMENTSHAPEGETNORMAL" , "IP",   TYPE_INT, modcpSegmentShapeGetNormal},
    {"CPCIRCLESHAPEGETOFFSET" , "IP",   TYPE_INT, modcpCircleShapeGetOffset},
    {"CPSEGMENTSHAPEGETA" , "IP",   TYPE_INT, modcpSegmentShapeGetA},
    {"CPSEGMENTSHAPEGETB" , "IP",   TYPE_INT, modcpSegmentShapeGetB},

    {"CPPOLYSHAPEGETNUMVERTS" , "I",   TYPE_INT, modcpPolyShapeGetNumVerts},
    {"CPSHAPECACHEBB" , "IP",   TYPE_INT, modcpShapeCacheBB},
    {"CPRESETSHAPEIDCOUNTER" , "",   TYPE_INT, modcpResetShapeIdCounter},

    {"GETCPSHAPEI" , "II",   TYPE_INT, modGetcpShape},
    {"GETCPSHAPEF" , "II",   TYPE_FLOAT, modGetcpShape},
    {"GETCPSHAPEP" , "IIP",   TYPE_INT, modGetcpShape},

    //cpSpace

    {"DEFSPACEF" , "IIF",   TYPE_INT, modDefSpace},
    {"DEFSPACEI" , "III",   TYPE_INT, modDefSpace},
    {"DEFSPACEP" , "IIP",   TYPE_INT, modDefSpace},

    {"CPSPACEREHASHSTATIC" , "",   TYPE_INT, modcpSpaceRehashStatic},
    //{"CPSPACEREHASHSHAPE" , "II",   TYPE_INT, modcpSpaceRehashShape},

    {"CPSPACEACTIVATESHAPESTOUCHINGSHAPE" , "I",   TYPE_INT, modcpSpaceActivateShapesTouchingShape},
    {"SPACERESIZESTATICHASH" , "FI",   TYPE_INT, modcpSpaceResizeStaticHash},
    {"SPACERESIZEACTIVEHASH" , "FI",   TYPE_INT, modcpSpaceResizeActiveHash},


    //CONSTRAITNTS


    {"CPCONSTRAINTGETIMPULSE" , "I", TYPE_FLOAT, modcpConstraintGetImpulse},

    {"DEFCONSTRAINTF" , "IIF",   TYPE_INT, modDefcpConstraint},
    {"DEFCONSTRAINTI" , "III",   TYPE_INT, modDefcpConstraint},
    {"GETCONSTRAINTF" , "II",   TYPE_FLOAT, modGetcpConstraint},
    {"GETCONSTRAINTI" , "II",   TYPE_INT, modGetcpConstraint},

    //colisiones
    {"CPSPACEPOINTQUERYFIRST" , "PII",   TYPE_INT, modcpSpacePointQueryFirst},

    {"CPSHAPEPOINTQUERY" , "IP",   TYPE_INT, modcpShapePointQuery},
    {"CPSHAPESEGMENTQUERY" , "IPPP",   TYPE_INT, modcpShapeSegmentQuery},
    {"CPSEGMENTQUERYHITPOINT" , "PPPP",   TYPE_INT, modcpSegmentQueryHitPoint},
    {"CPSEGMENTQUERYHITDIST" , "PPP",   TYPE_FLOAT, modcpSegmentQueryHitDist},
    {"CPSPACESEGMENTQUERYFIRST" , "PPIIP",   TYPE_INT, modcpSpaceSegmentQueryFirst},

    //funciones Constraints con ids
    {"ADDDAMPEDSPRING" , "IIFFFFFFF",   TYPE_INT, modaddDampedSpring},
    {"ADDPIVOTJOINT" , "IIFF",   TYPE_INT, modaddPivotJoint},
    {"ADDDAMPEDROTARYSPRING" , "IIFFF",   TYPE_INT, modaddDampedRotarySpring},
    {"ADDROTARYLIMITJOINT" , "IIFF",   TYPE_INT, modaddRotaryLimitJoint},
    {"ADDRATCHETJOINT" , "IIFF",   TYPE_INT, modaddRatchetJoint},
    {"ADDSIMPLEMOTOR" , "IIF",   TYPE_INT, modaddSimpleMotor},
    {"ADDGROOVEJOINT" , "IIFFFFFF",   TYPE_INT, modaddGrooveJoint},
    {"ADDSLIDEJOINT" , "IIFFFFFF",   TYPE_INT, modaddSlideJoint},
    {"ADDPIVOTJOINT2" , "IIFFFF",   TYPE_INT, modaddPivotJoint2},
    {"ADDPINJOINT" , "IIFFFF",   TYPE_INT, modaddPinJoint},
    {"ADDGEARJOINT" , "IIFF",   TYPE_INT, modaddGearJoint},

    {"REMOVECONSTRAINT" , "II",   TYPE_INT, modremoveConstraint},

    //funciones de bodies con ids
    {"SLEW" , "FFF",   TYPE_INT, modSlew},
    {"UPDATEVELOCITY" , "",   TYPE_INT, modUpdateVelocity},
    {"UPDATEVELOCITY" , "F",   TYPE_INT, modUpdateVelocity2},
    {"LOCAL2WORLD" , "IFFPP",   TYPE_INT, modLocal2World},
    {"WORLD2LOCAL" , "IFFPP",   TYPE_INT, modWorld2Local},
    {"APPLYIMPULSE" , "IFFFF",   TYPE_INT, modApplyImpulse},
    {"RESETFORCES" , "I",   TYPE_INT, modResetForces},
    {"APPLYFORCE" , "IFFFF",   TYPE_INT, modApplyForce},
    {"SLEEP" , "I",   TYPE_INT, modSleep},
    {"ACTIVATE" , "I",   TYPE_INT, modActivate},
    {"ISSTATIC" , "I",   TYPE_INT, modIsStatic},
    {"ISROGUE" , "I",   TYPE_INT, modIsRogue},
    {"ISSLEEPING" , "I",   TYPE_INT, modIsSleeping},

    //funciones de bb con ids
    {"INTERSECTS" , "II",   TYPE_INT, modIntersects},
    {"CONTAINS" , "II",   TYPE_INT, modContains},
    {"CONTAINSVEC" , "IFF",   TYPE_INT, modContainsVec},

    //funciones de space con ids
    {"ACTIVATEPROCESSTOUCHINGME" , "",   TYPE_INT, modActivateProcessTouchingIt},

    //FUNCIONS DE SHAPE CON IDS
    {"ADDCIRCLESHAPE" , "FFF",   TYPE_INT, modaddCircleShape},
    {"ADDSEGMENTSHAPE" , "FFFFF",   TYPE_INT, modaddSegmentShape},
    {"ADDPOLYSHAPE" , "FFIP",   TYPE_INT, modaddPolyShape},

    {"SPACEPOINTQUERYFIRST" , "FFII",   TYPE_INT, modSpacePointQueryFirst},
    {"SPACESEGMENTQUERYFIRST" , "FFFFIIP",   TYPE_INT, modSpaceSegmentQueryFirst},

    {"COLLISIONHANDLERNEW" , "II",   TYPE_INT, modcrearHandler},
    {"REMOVECOLLISIONHANDLER" , "I",   TYPE_INT, modremoveHandler},
    {"GETCOLLISIONINFO" , "IP",   TYPE_INT, modgetColInfo},

    {"SETPINJOINTPROPERTIES" , "IIFF",   TYPE_INT, modsetPinJointProperties},
    {"SETPINJOINTPROPERTIES" , "IIF",   TYPE_INT, modsetPinJointProperties},
    {"SETSLIDEJOINTPROPERTIES" , "IIFF",   TYPE_INT, modsetSlideJointProperties},
    {"SETSLIDEJOINTPROPERTIES" , "IIF",   TYPE_INT, modsetSlideJointProperties},
    {"SETPIVOTJOINTPROPERTIES" , "IIFF",   TYPE_INT, modsetPivotJointProperties},
    {"SETGROOVEJOINTPROPERTIES" , "IIFF",   TYPE_INT, modsetGrooveJointProperties},
    {"SETDAMPEDSPRINGPROPERTIES" , "IIFF",   TYPE_INT, modsetDampedSpringProperties},
    {"SETDAMPEDSPRINGPROPERTIES" , "IIF",   TYPE_INT, modsetDampedSpringProperties},
    {"SETDAMPEDROTARYSPRINGPROPERTIES" , "IIF",   TYPE_INT, modsetDampedRotarySpringProperties},
    {"SETROTARYLIMITJOINTPROPERTIES" , "IIF",   TYPE_INT, modsetRotaryLimitJointProperties},
    {"SETRATCHETJOINTPROPERTIES" , "IIF",   TYPE_INT, modsetRatchetJointProperties},
    {"SETGEARJOINTPROPERTIES" , "IIF",   TYPE_INT, modsetGearJointProperties},
    {"SETSIMPLEMOTORPROPERTIES" , "IIF",   TYPE_INT, modsetSimpleMotorProperties},

    {"GETPINJOINTPROPERTIES" , "IIPP",   TYPE_INT, modgetPinJointProperties},
    {"GETPINJOINTPROPERTIES" , "II",   TYPE_FLOAT, modgetPinJointProperties},
    {"GETSLIDEJOINTPROPERTIES" , "IIPP",   TYPE_INT, modgetSlideJointProperties},
    {"GETSLIDEJOINTPROPERTIES" , "II",   TYPE_FLOAT, modgetSlideJointProperties},
    {"GETGROOVEJOINTPROPERTIES" , "IIPP",   TYPE_INT, modgetGrooveJointProperties},
    {"GETDAMPEDSPRINGPROPERTIES" , "IIPP",   TYPE_INT, modgetDampedSpringProperties},
    {"GETDAMPEDSPRINGPROPERTIES" , "II",   TYPE_FLOAT, modgetDampedSpringProperties},
    {"GETDAMPEDROTARYSPRINGPROPERTIES" , "II",   TYPE_FLOAT, modgetDampedRotarySpringProperties},
    {"GETROTARYLIMITJOINTPROPERTIES" , "II",   TYPE_FLOAT, modgetRotaryLimitJointProperties},
    {"GETRATCHETJOINTPROPERTIES" , "II",   TYPE_FLOAT, modgetRatchetJointProperties},
    {"GETGEARJOINTPROPERTIES" , "II",   TYPE_FLOAT, modgetGearJointProperties},
    {"GETSIMPLEMOTORPROPERTIES" , "II",   TYPE_FLOAT, modgetSimpleMotorProperties},
    {"GETPIVOTJOINTPROPERTIES" , "IIPP",   TYPE_INT, modgetPivotJointProperties},

    {"GETCONSTRAINTS" , "I",   TYPE_INT, modgetConstraints},
    {"GETSHAPES" , "I",   TYPE_INT, modgetShapes},

    {"ADDINANIMATESHAPE" , "IFFF",   TYPE_INT, modaddInanimateShape},
    {"ADDINANIMATESHAPE" , "IFFFFF",   TYPE_INT, modaddInanimateShape},
    {"ADDINANIMATESHAPE" , "IFFIP",   TYPE_INT, modaddInanimateShape},

    {"SETENDPOINTSLINE" , "FFFF",   TYPE_INT, modsetEndPointsLine},
    {"SETRADIUSLINE" , "F",   TYPE_INT, modsetRadiusLine},
    {"SETOFFSETCIRCLE" , "FF",   TYPE_INT, modsetOffsetCircle},
    {"SETRADIUSCIRCLE" , "F",   TYPE_INT, modsetRadiusCircle},
    {"SETVERTCONVEXPOLIGON" , "FFIP",   TYPE_INT, modsetVertConvexPoligon},

    {"SETENDPOINTSLINE" , "IFFFF",   TYPE_INT, modsetEndPointsLineI},
    {"SETRADIUSLINE" , "IF",   TYPE_INT, modsetRadiusLineI},
    {"SETOFFSETCIRCLE" , "IFF",   TYPE_INT, modsetOffsetCircleI},
    {"SETRADIUSCIRCLE" , "IF",   TYPE_INT, modsetRadiusCircleI},
    {"SETVERTCONVEXPOLIGON" , "IFFIP",   TYPE_INT, modsetVertConvexPoligonI},

    {"SHAPECACHEBB" , "IP",   TYPE_INT, modShapeCacheBB},
    {0, 0, 0, 0}//TYPE_POINTER
};

#endif

