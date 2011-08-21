#include "arreglos.h"
#include "LL.h"

typedef struct DatosConstraint{
int fatherA;
int fatherB;
PROCDEF * funcion;
PROCDEF * funcionPre;
}DatosConstraint;

typedef struct cpsegmentqueryinfoB
{
    int shape,id;
    float x,y,t;
    cpVect n;
} cpsegmentqueryinfoB;



typedef struct handlersC
{
    Arreglo* arr;
    Arreglo * colisiones;
    cpCollisionType a, b;

} colHand;
Arreglo * HandlerColisions;



typedef struct cpContactPointSetM
{
    int count;
    int id1, id2;
    int shape1,shape2;
    struct
    {
        cpVect point, normal;
        float dist;
    } points[CP_MAX_CONTACTS_PER_ARBITER];
} cpContactPointSetM;

struct Data_Pointer
{
    int father;
    int estado;
    struct Data_Pointer * sig;
    int x,y;
    cpBody * body;
    int angle;
    int nShapes;
    cpShape ** Shapes;
    int nConstraints;
    nodo * Constraints;
//    cpBody ** constraintsBody;
    int typeShape;
}Data_Pointer;

typedef struct Data_Pointer
 *DataPointer;
