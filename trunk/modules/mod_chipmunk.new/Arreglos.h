#ifndef ARREGLOS_H
#define ARREGLOS_H

#define AVANCE 20

typedef struct{
    int cant;
    int max;
    void ** arreglo;
} Arreglo;



Arreglo * nuevoArreglo(int tam);
void destruyeArreglo(Arreglo ** a, int eliminaMiembros);
void ArregloPush(Arreglo * a, void * o);
void * ArregloPop(Arreglo * a);
typedef void (*itF )(void *ptr, void *data);
void arregloItera(Arreglo * a, itF iterador, void *datos);
int ArregloCantidad(Arreglo * a);
void  ArregloLimpia(Arreglo * a, int eliminaMiembros);
#endif // ARREGLOS_H
