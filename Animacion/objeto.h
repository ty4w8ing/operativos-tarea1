#ifndef OBJETO_H
#define OBJETO_H

typedef struct Objeto{
    char* nombre;
    char* figura;
} Figura;

char* splitCadena(char cadena[], char separador[], int posicion);
void agregarObjeto(char* nombre, char* figura);
void eliminarObjeto(char* nombre);
void mostrarObjeto(char* nombre);
Figura extraerObjeto(char* nombre);
void imprimirListaObjetosAlmacenados();

#endif /* OBJETO_H */

