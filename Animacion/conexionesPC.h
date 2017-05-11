#ifndef CONEXIONESPC_H
#define CONEXIONESPC_H

#include "objeto.h"
#include "monitor.h"
#include "matrizCanvas.h"
#include <pthread.h>

struct elementosHilo{
    struct Objeto* objeto;
    struct Monitor* monitores;
    struct Canvas* canvas;
};

int ejecutarHilos(struct Objeto* objetos, struct Monitor* monitores, struct Canvas* canvas, int numeroObjetos, pthread_t hilos[]);
void terminarConexiones(int idConexiones[]);
void iniciarSocket(char* archivo);

#endif /* CONEXIONESPC_H */

