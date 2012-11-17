#include "LL.h"
//#include <stdio.h>

void LLinicializa(nodo ** n){
    *n= malloc(sizeof(nodo));
    (*n)->elem=NULL;
    (*n)->sig=NULL;
}

void LLagrega(nodo * n, void * p){
    nodo * sig=n->sig;
    n->sig= malloc(sizeof(nodo));
    n->sig->elem=p;
    n->sig->sig=sig;
}

void LLelimina(nodo * n,void * am, funCom r, funcionElm funEl,int hFree){
    for(;n->sig!=NULL;n=n->sig){
        if (r(am,n->sig->elem)){
            nodo * sig = n->sig->sig;
            funEl(n->sig->elem);
            if (hFree)
                free(n->sig);
            n->sig=sig;
            if (n->sig==NULL)
                return;
        }
    }
}

void * LLbusca(nodo * n,void * bm, funCom r){
    for(;n->sig!=NULL;n=n->sig){
        if (r(bm,n->sig->elem)){
//            printf("busca  %d  %d\n",n->sig->elem, bm); fflush(stdout);
                return n->sig->elem;
        }
    }
    return NULL;
}

void LLeliminaTodo(nodo * n,funcionElm funEl,int hFree){
    while(n!=NULL && n->sig!=NULL){
            nodo * sig = n->sig->sig;
            funEl(n->sig->elem);
            if (hFree){
                free(n->sig);
                n->sig=sig;
            }
    }
    free(n);
}

void LLimprime(nodo * n){
    if (n==NULL){
        printf("Lista vacia \n");
        return;
        }
    printf("____________________________\n");fflush(stdout);
    for(;n->sig!=NULL;n=n->sig){
            printf("%d\n",n->sig->elem);fflush(stdout);
    }
    printf("____________________________\n");fflush(stdout);
}
