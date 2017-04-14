#ifndef MONITOR_H
#define MONITOR_H

struct Monitor{
    int     id;
    int     idConexion;
    int     largo;
    int     ancho;
    char*   nombre;
    struct  Monitor* siguienteMonitor;
};

struct Monitor* extraerMonitoresArchivo(char* archivo, int cantidadMonitores);
struct Monitor* ordenarMonitores(struct Monitor* monitores, int cantidadMonitores);
void inicializarMonitor(struct Monitor** monitores, char* descripcionMonitor);
int cantidadMonitores(char* archivo);
void insertarConexiones(struct Monitor** monitores, int idConexiones[], int numeroConexiones);
void imprimirMonitores(struct Monitor* monitores);

#endif /* MONITOR_H */

