#ifndef OBJETO_H
#define OBJETO_H

#include "monitor.h"
#include "conexionesPC.h"

struct Objeto{
    char*   tipo;
    char*   figura;
    int     scheduler; //1 si es sorteo o 0 si es rounf robbin
    int     tiempoEntrada;
    int     tiquetes; //En caso de que el scheduler sea por sorteo
    int     posXIni;
    int     posYIni;
    int     posXFin;
    int     posYFin;
    int     posXAct;
    int     posYAct;
    int     rotacion;
    int*    posiblesMovimientos;
    int     numeroMovs; 
    struct Objeto*         siguienteObjeto;
};

void* iniciarObjeto(void* argumentos);
int realizarMovimiento(struct Objeto* objeto, struct Monitor* monitores, struct Canvas* canvas);
void ejecutarAnimacionObjeto(struct Objeto* objeto, struct Monitor* monitores, struct Canvas* canvas);

int cantidadObjetos(struct Objeto* objetos);
int** matrizPosiciones(struct Objeto* objetos);
void buscarPosiciones(struct Objeto* objetos);
int cantidadPosiciones(int xAct,int yAct,int xFin,int yFin);
void moverObjetos(struct Objeto* objetos);
int posicionLibre(int x, int y, int posicionesObjeto[], int cantidadIter);
void iniciarAnimacion(struct Objeto* objetos, struct Monitor* monitores);
int* siguientesPosiciones(int xAct,int yAct,int xFin,int yFin, int cantidadMovimientos);
void ejecutarAnimacion(struct Objeto* objetos, struct Monitor* monitores);
int ejecutarMovimiento(struct Objeto* objetos, struct Monitor* monitores);

char* movimiento180Grados(char* figura);
char* movimiento270Grados(char* figura);
char* moverFigura(char* figura, int rotacion);
char* objetoParseado(char* filaObjeto);
struct Objeto* extraerObjetosArchivo(char* archivo);
void inicializarObjeto(struct Objeto** objetos, char* descripcionObjeto);
void imprimirObjetos(struct Objeto* objetos);
char* extraerFigura(char* nombreObjeto);
void mostrarFigura(struct Monitor* monitores, char figura[], int posX, int posY);
void mostrarFiguraMonitor(struct Monitor* monitores, char filaFigura[], int posX, int posY);

#endif /* OBJETO_H */

