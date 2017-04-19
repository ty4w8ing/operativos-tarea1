#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "funcionesExtra.h"
#include "objeto.h"

//Se imprime la posicion inicial de los objetos
void iniciarAnimacion(struct Objeto* objetos, struct Monitor* monitores){
    char* movimiento;
    while(objetos != NULL){
        movimiento = moverFigura(objetos->figura, objetos->rotacion);
        strcpy(objetos->figura, movimiento);
        mostrarFigura(monitores, movimiento, objetos->posXIni, objetos->posYIni);
        objetos = objetos->siguienteObjeto;
    }
}

int* siguientesPosiciones(int xAct,int yAct,int xFin,int yFin){
    static int posiciones[2];
    
    if(xAct > xFin && yAct < yFin){
        posiciones[0] = xAct - 1;
        posiciones[1] = yAct + 1;
    }
    else if(xAct == xFin && yAct < yFin){
        posiciones[0] = xAct;
        posiciones[1] = yAct + 1;
    }
    else if(xAct < xFin && yAct < yFin){
        posiciones[0] = xAct + 1;
        posiciones[1] = yAct + 1;
    }
    else if(xAct > xFin && yAct == yFin){
        posiciones[0] = xAct - 1;
        posiciones[1] = yAct;
    }
    else if(xAct < xFin && yAct == yFin){
        posiciones[0] = xAct + 1;
        posiciones[1] = yAct;
    } 
    else if(xAct > xFin && yAct > yFin){
        posiciones[0] = xAct - 1;
        posiciones[1] = yAct - 1;
    }
    else if(xAct == xFin && yAct > yFin){
        posiciones[0] = xAct;
        posiciones[1] = yAct - 1;
    }
    else if(xAct < xFin && yAct > yFin){
        posiciones[0] = xAct + 1;
        posiciones[1] = yAct - 1;
    }
    
    return posiciones;
}

int ejecutarAnimacion(struct Objeto* objetos, struct Monitor* monitores){
    char* movimiento;
    int recorridoObjetosTerminado = 1;
    
    while(objetos != NULL){
        if(objetos->posXAct != objetos->posXFin || objetos->posYAct != objetos->posYFin){
            recorridoObjetosTerminado = 0;
            
            int* nuevasPosiciones = siguientesPosiciones(objetos->posXAct, objetos->posYAct,objetos->posXFin, objetos->posYFin);
            
            int x = *(nuevasPosiciones);
            int y = *(nuevasPosiciones+1);
            
            objetos->posXAct = x;
            objetos->posYAct = y;
            
            movimiento = moverFigura(objetos->figura, objetos->rotacion);
            strcpy(objetos->figura, movimiento);
            mostrarFigura(monitores, movimiento, x, y);
        }
        objetos = objetos->siguienteObjeto;
    }
   
    return recorridoObjetosTerminado;
}

void limpiarMonitores(struct Monitor* monitores){
    char* limpiar = "\033c";
    while(monitores != NULL){
        int idConexion = monitores->idConexion;
        write(idConexion, limpiar, strlen(limpiar));
        monitores = monitores->siguienteMonitor;
    }
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

void imprimirObjetos(struct Objeto* objetos){
    while(objetos != NULL){
        printf("%s [%d->%d] %dG - Inicio (%d,%d) - Fin (%d,%d) - Tiempo (I: %d, O:%d)\n",objetos->tipo, objetos->scheduler, objetos->tiquetes, objetos->rotacion
                ,objetos->posXIni,objetos->posYIni,objetos->posXFin,objetos->posYFin,objetos->tiempoEntrada,objetos->tiempoSalida);
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
                else if(i == 10){
                    objeto->tiempoSalida = atoi(dividirCadena); 
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
                else if(i == 9){
                    objeto->tiempoSalida = atoi(dividirCadena); 
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
