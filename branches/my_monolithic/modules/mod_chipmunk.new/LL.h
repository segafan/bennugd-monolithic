#ifndef LL_H
#define LL_H

#include <stdio.h>

typedef struct nodo{
    void * elem;
    struct nodo * sig;
} nodo;

typedef void (*funcionElm)(void* parametro) ;

typedef int (*funCom)(void *a, void* b) ;
void LLeliminaTodo(nodo * n,funcionElm funEl,int hFree);
void LLinicializa(nodo ** n);
void LLagrega(nodo * n, void * p);
void LLelimina(nodo * n,void * b, funCom r,funcionElm funEl,int hFree);
void * LLbusca(nodo * n,void * b, funCom r);
void LLimprime(nodo * n);

#endif //LL_H
