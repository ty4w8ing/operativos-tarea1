#ifndef MONITOR_H
#define MONITOR_H

struct Monitor{
    char*   nombre;
    int     id;
    int     idConexion;
    int     largo;
    int     ancho;
    int     posXIni;
    int     posYIni;
    struct  Monitor* siguienteMonitor;
};

void posicionarCursor(struct Monitor* monitores);
struct Monitor* extraerMonitoresArchivo(char* archivo);
void inicializarMonitor(struct Monitor** monitores, char* descripcionMonitor);
void insertarConexiones(struct Monitor** monitores, int idConexiones[]);
void imprimirMonitores(struct Monitor* monitores);

#endif /* MONITOR_H */

