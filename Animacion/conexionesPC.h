#ifndef CONEXIONESPC_H
#define CONEXIONESPC_H

#include "monitor.h"

void imprimirEjemplos(struct Monitor* monitores);
void terminarConexiones(int idConexiones[]);
void iniciarSocket(char* archivo);

#endif /* CONEXIONESPC_H */

