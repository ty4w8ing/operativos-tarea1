#ifndef MONITOR_H
#define MONITOR_H

typedef struct Monitor{
    char* nombre;
    int   largo;
    int   ancho;
    int   prioridad;  
};

void agregarMonitor();

#endif /* MONITOR_H */

