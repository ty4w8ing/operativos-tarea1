#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "funcionesExtra.h"
#include "objeto.h"
#include "matrizCanvas.h"
#include "conexionesPC.h"

void mostrarFiguraMonitor(struct Monitor* monitores, char filaFigura[], int posY, int posX){
    int i = 0;
    static char cadena[1];
    struct Monitor* monitorAct;
    int y = posY;
    int x = posX;
    
    for(i = 0; i < strlen(filaFigura); i +=1){
        char caracterAct = filaFigura[i];
        
        monitorAct = monitores;
        while(monitorAct != NULL){
            if(monitorAct->posXIni <= x && (monitorAct->posXIni + monitorAct->largo) >= x 
                    && monitorAct->posYIni <= y && (monitorAct->posYIni + monitorAct->ancho) >= y){
                sprintf(cadena,"\033[%d;%dH%c\n",monitorAct->ancho - (y - monitorAct->posYIni),x - monitorAct->posXIni,caracterAct);
                write(monitorAct->idConexion,cadena,strlen(cadena));
                break;
            }
            monitorAct = monitorAct->siguienteMonitor;
        }
        x +=1;
    }
    posicionarCursor(monitores);
}

void mostrarFigura(struct Monitor* monitores, char figura[], int posX, int posY){
    char* dividirCadena = strtok(figura, "|");
    int i;
    int fila = posY - 2;
    int col = posX - 2;
        
    for(i = 0; i < 5; i +=1){   
        char* filaFigura = objetoParseado(dividirCadena);
        mostrarFiguraMonitor(monitores, filaFigura, fila, col);
        dividirCadena = strtok(NULL, "|");
        fila +=1;
    }
}

void* iniciarObjeto(void* argumentos){
    struct elementosHilo* arg = (struct elementosHilo*) argumentos; 
    struct Objeto* objeto = arg->objeto;
    struct Monitor* monitores = arg->monitores;
    struct Canvas* canvas = arg->canvas;
    
    ejecutarAnimacionObjeto(objeto, monitores, canvas);
}

int* extraerNumeroMovs(struct Objeto* objetos, int cantidadObjs){
    int* numMovs = malloc(cantidadObjs*sizeof(int));
    int i;
    
    for(i = 0; i < cantidadObjs; i +=1){
        numMovs[i] = objetos->numeroMovs;
        objetos = objetos->siguienteObjeto;
    }
    
    return numMovs;
}

int realizarMovimiento(struct Objeto* objeto, struct Monitor* monitores, struct Canvas* canvas){
    char* movimiento;
    int recorridoObjetosTerminado = 1;
        
    if(objeto->posXAct != objeto->posXFin || objeto->posYAct != objeto->posYFin){
        recorridoObjetosTerminado = 0;
            
        int numeroMovimientos = objeto->numeroMovs;
        int objetoMovido = 0;
        int idPos;
            
        for(idPos = 0; idPos < numeroMovimientos; idPos +=2){
            int x = objeto->posiblesMovimientos[idPos];
            int y = objeto->posiblesMovimientos[idPos+1];
            
            int posicionOcupada = posicionesOcupadas(canvas, x, y, objeto->posXAct, objeto->posYAct);
                        
            if(posicionOcupada == 0){
                objetoMovido = 1;
                desbloquearPosiciones(canvas, objeto->posXAct, objeto->posYAct);
                bloquearPosiciones(canvas, x, y);
                    
                objeto->posXAct = x;
                objeto->posYAct = y;
            
                movimiento = moverFigura(objeto->figura, objeto->rotacion);
                strcpy(objeto->figura, movimiento);
                mostrarFigura(monitores, movimiento, x, y);
                    
                break;
            }
        }
    }
    
    return recorridoObjetosTerminado;
}

void ejecutarAnimacionObjeto(struct Objeto* objeto, struct Monitor* monitores, struct Canvas* canvas){
    int finalizar = 0;
    char figuraVacia[35];
    
    sleep(1);
    strcpy(figuraVacia, "     |     |     |     |     |");
    mostrarFigura(monitores, figuraVacia, objeto->posXAct,objeto->posYAct);
    bloquearPosiciones(canvas, objeto->posXAct,objeto->posYAct);
    imprimirCanvasPos(canvas, objeto->posXAct,objeto->posYAct);
    
    buscarPosiciones(objeto);
    finalizar = realizarMovimiento(objeto, monitores, canvas);
}

void buscarPosiciones(struct Objeto* objeto){
    int numeroMovimientos = cantidadPosiciones(objeto->posXAct, objeto->posYAct, objeto->posXFin, objeto->posYFin);
    objeto->numeroMovs = numeroMovimientos;
    int* nuevasPosiciones = siguientesPosiciones(objeto->posXAct, objeto->posYAct,objeto->posXFin, objeto->posYFin, numeroMovimientos);    
    objeto->posiblesMovimientos = nuevasPosiciones;
}

int cantidadPosiciones(int xAct,int yAct,int xFin,int yFin){
    int i = 0;
    
    if(xAct > xFin && yAct < yFin){
        i += 2;
    }
    if(xAct < xFin && yAct < yFin){
        i +=2;
    } 
    if(xAct > xFin && yAct > yFin){
        i += 2;
    }
    if(xAct < xFin && yAct > yFin){
        i += 2;
    }
    if(yAct < yFin){
        i += 2;
    }
    if(xAct > xFin){
        i += 2;
    }
    if(xAct < xFin){
        i += 2;
    }
    if(yAct > yFin){
        i += 2;
    }
    
    return i;
}

int* siguientesPosiciones(int xAct,int yAct,int xFin,int yFin, int cantidadMovimientos){
    int* posiciones = malloc(cantidadMovimientos*sizeof(int));
    int i = 0;
    
    if(xAct > xFin && yAct < yFin){
        posiciones[i] = xAct - 1;
        posiciones[i+1] = yAct + 1;
        i += 2;
    }
    if(xAct < xFin && yAct < yFin){
        posiciones[i] = xAct + 1;
        posiciones[i+1] = yAct + 1;
        i +=2;
    } 
    if(xAct > xFin && yAct > yFin){
        posiciones[i] = xAct - 1;
        posiciones[i+1] = yAct - 1;
        i += 2;
    }
    if(xAct < xFin && yAct > yFin){
        posiciones[i] = xAct + 1;
        posiciones[i+1] = yAct - 1;
        i += 2;
    }
    if(yAct < yFin){
        posiciones[i] = xAct;
        posiciones[i+1] = yAct + 1;
        i += 2;
    }
    if(xAct > xFin){
        posiciones[i] = xAct - 1;
        posiciones[i+1] = yAct;
        i += 2;
    }
    if(xAct < xFin){
        posiciones[i] = xAct + 1;
        posiciones[i+1] = yAct;
        i += 2;
    }
    if(yAct > yFin){
        posiciones[i] = xAct;
        posiciones[i+1] = yAct - 1;
        i += 2;
    }
    
    return posiciones;
}

int posicionLibre(int x, int y,int posicionesObjeto[], int cantidadIter){
    int libre = 1;
    int i;
    
    for(i = 0; i < cantidadIter; i+= 2){
        if((posicionesObjeto[i] - 4 < x || x > posicionesObjeto[i] + 4) && (posicionesObjeto[i+1] - 4 < y || y > posicionesObjeto[i+1] + 4)){
            libre = 0;
            break;
        }
    }
    
    return libre;
}

int cantidadObjetos(struct Objeto* objetos){
    int cantidad = 0;
    
    while(objetos != NULL){
        cantidad += 1;
        objetos = objetos->siguienteObjeto;
    }
    
    return cantidad;
}

int** matrizPosiciones(struct Objeto* objetos){
    int filas = cantidadObjetos(objetos);
    int **posiciones;
    int i;
    posiciones = (int**)malloc(filas*sizeof(int));
    
    for(i = 0; i < filas; i +=1){
        posiciones[i] = (int*) malloc(objetos->numeroMovs*sizeof(int));
        posiciones[i] = objetos->posiblesMovimientos;
        objetos = objetos->siguienteObjeto;
    }
    
    return posiciones;
}

char* movimiento180Grados(char* figura){    
    char* fig90 = girar90G(figura);
    char* fig180 = girar90G(fig90);
    
    return fig180;
}

char* movimiento270Grados(char* figura){
    char* fig90 = girar90G(figura);
    char* fig180 = girar90G(fig90);
    char* fig270 = girar90G(fig180);
    
    return fig270;
}

char* moverFigura(char* figura, int rotacion){
    char* figuraMovida = NULL;
    int listaRotaciones[] = {0, 90, 180, 270};
    
    if(rotacion == 0){
        figuraMovida = strdup(figura);
    }
    else if(rotacion == 90){
        figuraMovida = girar90G(figura);
    }
    else if(rotacion == 180){
        figuraMovida = movimiento180Grados(figura);
    }
    else if(rotacion == 270){
        figuraMovida = movimiento270Grados(figura);
    }
    else if(rotacion == 117){
        int numRand =  rand() % 4;
        figuraMovida = moverFigura(figura, listaRotaciones[numRand]);
    }
    
    return figuraMovida;
}

char* objetoParseado(char filaObjeto[]){
    char objeto[5];
    char* objetoParseado = NULL;
    
    int i;
    for(i = 0; i < strlen(filaObjeto); i +=1){
        char caracterAct = filaObjeto[i];
        if(caracterAct == '-'){
            objeto[i] = ' ';
        }
        else{
            objeto[i] = caracterAct;
        }
    }
    
    objetoParseado = malloc(sizeof(char)*strlen(objeto));
    strcpy(objetoParseado, objeto);
    
    return objetoParseado;
}

void imprimirObjetos(struct Objeto* objetos){
    while(objetos != NULL){
        printf("%s [%d->%d] %dG - Inicio (%d,%d) - Fin (%d,%d) - Tiempo %d\n",objetos->tipo, objetos->scheduler, objetos->tiquetes, objetos->rotacion
                ,objetos->posXIni,objetos->posYIni,objetos->posXFin,objetos->posYFin,objetos->tiempoEntrada);
        objetos = objetos->siguienteObjeto;
    }
}

//Extraer figura del archivo
char* extraerFigura(char* nombreObjeto){
    FILE* archivo = fopen("data/objetos.txt","r");
    char buffer[255];
    char buffcpy[255];
    
    char* nombre;
    char* figura;
    
    if(archivo == NULL){
        printf("El archivo no existe!!\n");
    }    
    
    while(fgets(buffer, 255, (FILE*) archivo)){
        strcpy(buffcpy, buffer);
        
        nombre = splitCadena(buffer,",", 0);
        
        if(strcmp(nombreObjeto, nombre) == 0){
            figura = splitCadena(buffcpy,",",1);    
            break;
        }
    }
    fclose(archivo); 
    
    return figura;
}

struct Objeto* extraerObjetosArchivo(char* rutaArchivo){
    FILE* archivo = fopen(rutaArchivo,"r");
    char buffer[255];
    char buffcpy[255];
    
    char* nombre;
    struct Objeto* objetos = NULL;
        
    while(fgets(buffer, 255, (FILE*) archivo)){
        strcpy(buffcpy, buffer);
        
        nombre = splitCadena(buffer,",", 0);
        
        if(strcmp(nombre, "objeto") == 0){
            inicializarObjeto(&objetos, buffcpy); 
        }
    }
    fclose(archivo); 
      
    return objetos;
}

void inicializarObjeto(struct Objeto** objetos, char* descripcionMonitor){
    char* dividirCadena = strtok(descripcionMonitor, ",");
    char* tipo;
    int scheduler = 0;
    int i = 0;
    
    struct Objeto* objeto = (struct Objeto*)malloc(sizeof(struct Objeto));
    struct Objeto* ultimoObjeto = *objetos;
            
    while(dividirCadena != NULL){
        if(i == 1){
            strcpy(tipo, dividirCadena);
            objeto->tipo = tipo;
        }
        else if(i == 2){
            scheduler = atoi(dividirCadena);
            objeto->scheduler = scheduler;
            
        }
        else if(i > 2){
            if(scheduler == 1){
                if(i == 3){
                    objeto->tiquetes = atoi(dividirCadena);
                }
                else if(i == 4){
                    objeto->posXIni = atoi(dividirCadena); 
                    objeto->posXAct = atoi(dividirCadena);
                }
                else if(i == 5){
                    objeto->posYIni = atoi(dividirCadena); 
                    objeto->posYAct = atoi(dividirCadena);
                }
                else if(i == 6){
                    objeto->posXFin = atoi(dividirCadena); 
                }
                else if(i == 7){
                    objeto->posYFin = atoi(dividirCadena); 
                }
                else if(i == 8){
                    objeto->rotacion = atoi(dividirCadena); 
                }
                else if(i == 9){
                    objeto->tiempoEntrada = atoi(dividirCadena); 
                }
            }
            else if(scheduler == 0){
                if(i == 3){
                    objeto->posXIni = atoi(dividirCadena); 
                    objeto->posXAct = atoi(dividirCadena);
                }
                else if(i == 4){
                    objeto->posYIni = atoi(dividirCadena);
                    objeto->posYAct = atoi(dividirCadena);
                }
                else if(i == 5){
                    objeto->posXFin = atoi(dividirCadena); 
                }
                else if(i == 6){
                    objeto->posYFin = atoi(dividirCadena); 
                }
                else if(i == 7){
                    objeto->rotacion = atoi(dividirCadena); 
                }
                else if(i == 8){
                    objeto->tiempoEntrada = atoi(dividirCadena); 
                }
            }
        }      
        
        dividirCadena = strtok(NULL, ",");
        i += 1;
    }
    objeto->figura = extraerFigura(objeto->tipo);
    objeto->siguienteObjeto = NULL;
    
    if(*objetos == NULL){   
        *objetos = objeto; 
    }
    else{
        while(ultimoObjeto->siguienteObjeto != NULL){
            ultimoObjeto = ultimoObjeto->siguienteObjeto;
        }
        
        ultimoObjeto->siguienteObjeto = objeto;
    }
}