#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrizCanvas.h"

struct Canvas* crearMatriz(int filas, int columnas){
    struct Canvas* matriz = (struct Canvas*)malloc(sizeof(struct Canvas));
    struct elementoCv* canvas = (struct elementoCv*)malloc(sizeof(struct elementoCv));
    struct elementoCv* temp; 
    
    matriz->largo = filas*columnas;
    matriz->canvas = canvas;

    int i;
    for(i = 0; i < filas; i+=1){
        int j;
        for(j = 0; j < columnas; j+=1){
            temp = (struct elementoCv*)malloc(sizeof(struct elementoCv));
            temp->estaOcupado = 0;
            temp->y = i;
            temp->x = j;
            temp->siguiente = NULL;
            
            if(canvas != NULL){
                canvas->siguiente = temp;
            }
            canvas = temp;
        }
    }
    
    return matriz;
}

void desbloquearPosiciones(struct Canvas* matriz, int x, int y){
    struct elementoCv* canvas;
    int xIni = x - 2;
    int yIni = y - 2;
    int topeX = xIni + 5;
    int topeY = yIni + 5;
    
    canvas = matriz->canvas;
    
    while(canvas != NULL){
       for(xIni; xIni < topeX; xIni += 1){
            for(yIni; yIni < topeY; yIni +=1){
                if(canvas->x == xIni && canvas->y == yIni){
                    canvas->estaOcupado = 0;
                    break;
                }
            }
        } 
        canvas = canvas->siguiente;
    }
    
}

void bloquearPosiciones(struct Canvas* matriz, int x, int y){
    struct elementoCv* canvas;
    int xIni = x - 2;
    int yIni = y - 2;
    int topeX = xIni + 5;
    int topeY = yIni + 5;
    
    for(xIni; xIni < topeX; xIni += 1){
        for(yIni; yIni < topeY; yIni +=1){
            canvas = matriz->canvas;
            
            
            while(canvas != NULL){
                if(canvas->x == xIni && canvas->y == yIni){
                    canvas->estaOcupado = 1;
                    break;
                }
                
                canvas = canvas->siguiente;
            }
            matriz->canvas = canvas;
        }
    }
}

int posicionesOcupadas(struct Canvas* matriz, int x, int y, int posXObjeto, int posYObj){
    struct elementoCv* canvas;
    int estaOcupado = 0;
    
    int xIni = x - 2;
    int yIni = y - 2;
    int topeX = xIni + 5;
    int topeY = yIni + 5;
    
    for(xIni; xIni < topeX; xIni += 1){
        for(yIni; yIni < topeY; yIni +=1){
            
            canvas = (struct elementoCv*)malloc(matriz->largoLista*sizeof(struct elementoCv));
            canvas = matriz->canvas;
            int estadoActual = 0;
            
            while(canvas != NULL){
                if(canvas->x == xIni && canvas->y == yIni){
                    estadoActual = canvas->estaOcupado;
                    break;
                }
                
                canvas = canvas->siguiente;
            }
            if(estadoActual == 1){
                estaOcupado = 1;
                break;
            }
        }
    }
    
    
    return estaOcupado;
}

void imprimirCanvasPos(struct Canvas* matriz, int x, int y){
    struct elementoCv* canvas = matriz->canvas;
    
    while(canvas != NULL){
        if(x == canvas->x && y == canvas->y){
            printf("%d/%d ->%d\n",canvas->x,canvas->y,canvas->estaOcupado);
            break;
        }
        canvas = canvas->siguiente;
    }
}

void imprimirCanvas(struct Canvas* matriz){
    struct elementoCv* canvas = matriz->canvas;
    
    while(canvas != NULL){
        printf("%d/%d ->%d\n",canvas->x,canvas->y,canvas->estaOcupado);
        canvas = canvas->siguiente;
    }
}