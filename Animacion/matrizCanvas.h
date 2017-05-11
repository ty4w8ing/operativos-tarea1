#ifndef MATRIZCANVAS_H
#define MATRIZCANVAS_H

struct Canvas{
    int largoLista;
    int largo;
    int ancho;
    struct elementoCv* canvas;
};

struct elementoCv{
    int x;
    int y;
    int estaOcupado;
    struct elementoCv* siguiente;
};

void imprimirCanvasPos(struct Canvas* matriz, int x, int y);
struct Canvas* crearMatriz(int filas, int columnas);
void desbloquearPosiciones(struct Canvas* matriz, int x, int y);
void bloquearPosiciones(struct Canvas* matriz, int x, int y);
int posicionesOcupadas(struct Canvas* matriz, int x, int y, int posXObjeto, int posYObj);
void imprimirCanvas(struct Canvas* matriz);

#endif /* MATRIZCANVAS_H */

