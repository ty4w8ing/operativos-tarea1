#ifndef OBJETO_H
#define OBJETO_H

typedef struct ObjetoAlmacenado{
    char* nombre;
    char* figura;
} Figura;

void menuObjetos();
void movimiento0G(char* nombreObj);
void movimiento90G(char* nombreObj);
void movimiento180G(char* nombreObj);
void movimiento270G(char* nombreObj);
void agregarObjeto(char* nombre, char* figura);
void eliminarObjeto(char* nombre);
void mostrarObjeto(char* figura);
Figura extraerObjeto(char* nombre);
void imprimirListaObjetosAlmacenados();

#endif /* OBJETO_H */

