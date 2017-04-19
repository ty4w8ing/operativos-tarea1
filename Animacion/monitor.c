#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "monitor.h"
#include "funcionesExtra.h"

void posicionarCursor(struct Monitor* monitores){
    char* inicio = "\033[0;0H\n";
    while(monitores != NULL){
        int idConexion = monitores->idConexion;
        write(idConexion, inicio, strlen(inicio));
        monitores = monitores->siguienteMonitor;
    }
}

struct Monitor* extraerMonitoresArchivo(char* rutaArchivo){
    FILE* archivo = fopen(rutaArchivo,"r");
    char buffer[255];
    char buffcpy[255];
    
    char* nombre;
    struct Monitor* monitores = NULL;
        
    while(fgets(buffer, 255, (FILE*) archivo)){
        strcpy(buffcpy, buffer);
        
        nombre = splitCadena(buffer,",", 0);
        
        if(strcmp(nombre, "monitor") == 0){
            inicializarMonitor(&monitores, buffcpy); 
        }
    }
    fclose(archivo); 
      
    return monitores;
}

void inicializarMonitor(struct Monitor** monitores, char* descripcionMonitor){
    char* dividirCadena = strtok(descripcionMonitor, ",");
    int i = 0;
    
    struct Monitor* monitor = (struct Monitor*)malloc(sizeof(struct Monitor));
    struct Monitor* ultimoMonitor = *monitores;
            
    while(dividirCadena != NULL){
        if(i == 1){
            char* nombre;
            strcpy(nombre, dividirCadena);
            monitor->nombre = nombre;
        }
        else if(i == 2){
            monitor->largo = atoi(dividirCadena);
        }
        else if(i == 3){
            monitor->ancho = atoi(dividirCadena);
        }
        else if(i == 4){
            monitor->posXIni = atoi(dividirCadena);
        }
        else if(i == 5){
            monitor->posYIni = atoi(dividirCadena);
        }
        else if(i == 6){
            monitor->id = atoi(dividirCadena);
        }
        dividirCadena = strtok(NULL, ",");
        i += 1;
    }
    monitor->siguienteMonitor = NULL;
    
    if(*monitores == NULL){   
        *monitores = monitor; 
    }
    else{
        while(ultimoMonitor->siguienteMonitor != NULL){
            ultimoMonitor = ultimoMonitor->siguienteMonitor;
        }
        
        ultimoMonitor->siguienteMonitor = monitor;
    }
}

void imprimirMonitores(struct Monitor* monitores){
    while(monitores != NULL){
        printf("%s[%d](%d,%d)-connexión %d\n",monitores->nombre, monitores->id, monitores->largo, monitores->ancho,monitores->idConexion);
        monitores = monitores->siguienteMonitor;
    }
}

void insertarConexiones(struct Monitor** monitores, int idConexiones[]){
    struct Monitor* monitoresDetectados = *monitores;
    int indiceMonitor;
    
    while(monitoresDetectados != NULL){
        indiceMonitor = monitoresDetectados->id - 1;                       
        monitoresDetectados->idConexion = idConexiones[indiceMonitor];      //Se le asignan a los monitores descritos en el archivo(por su id) 
        monitoresDetectados = monitoresDetectados->siguienteMonitor;        //el tipo de conexión que le corresponde. Debe iniciar en 1 los id del archivo
    }                                                                       //y al monitor que tenga el id 1 se le asigna la primer conexion    
}