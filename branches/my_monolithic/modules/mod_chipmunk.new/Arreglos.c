 /*
 *  Copyright (c) 2010-2011 Prg orlando8nov@yahoo.com.mx
 *
 *  This file is part of mod_chipmunk, a Chipmunk physics binding for BennuGD.
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */

#include "Arreglos.h"
#include <stdlib.h>
#include <stdio.h>

Arreglo * nuevoArreglo(int tam)
{
    Arreglo * a= (Arreglo *) malloc(sizeof(Arreglo *));
    a->max=tam;
    a->arreglo=(void **)malloc(a->max*sizeof(void **));
    a->cant=0;
	return a;
}

void destruyeArreglo(Arreglo ** a, int eliminaMiembros){
//    printf("Destruido %p",a); fflush(stdout);
    if (eliminaMiembros){
        int i=0;
        for (i=0;i<(*a)->cant;i++){
            free((*a)->arreglo[i]);
        }
    }

    free ((*a)->arreglo);
    free(*a);
    *a=0;
}

void ArregloPush(Arreglo * a, void * o){
    if (a->cant==a->max){
        a->max+=AVANCE;
        a->arreglo=(void**)realloc(a->arreglo,a->max*sizeof(void**));
    }
        a->arreglo[a->cant]=o;
        a->cant++;
}

void * ArregloPop(Arreglo * a){
    a->cant--;
    void * puntero=a->arreglo[a->cant];
    a->arreglo[a->cant]=NULL;
    if (a->cant<(a->max-AVANCE)){
        a->max-=AVANCE;
        a->arreglo=(void**)realloc(a->arreglo,a->max*sizeof(void**));
    }
    return puntero;
}

void arregloItera(Arreglo * a, itF iterador, void *datos){
    int i;
    for (i=0;i<a->cant;i++)
        iterador(a->arreglo[i],datos);
}

int ArregloCantidad(Arreglo * a){
    return a->cant;
}

void  ArregloLimpia(Arreglo * a, int eliminaMiembros){

    if (eliminaMiembros){
        int i=0;
        for (i=0;i<a->cant;i++){
            free(a->arreglo[i]);
        }
    }

    a->max=AVANCE/2;
    a->arreglo=(void**)realloc(a->arreglo,a->max*sizeof(void**));
}


/*
cpBool
cpArrayContains(cpArray *arr, void *ptr)
{
	for(int i=0; i<arr->num; i++)
		if(arr->arr[i] == ptr) return cpTrue;

	return cpFalse;
}
*/
