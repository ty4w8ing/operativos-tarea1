#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monitor.h"
#include "funcionesExtra.h"

struct Monitor* extraerMonitoresArchivo(char* rutaArchivo, int cantidadMonitores){
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
       
    //nodoMonitor* monitoresOrdenados = ordenarMonitores(monitores, cantidadMonitores);
    
    return monitores;
}

int cantidadMonitores(char* rutaArchivo){
    FILE* archivo = fopen(rutaArchivo,"r");
    char buffer[255];
    
    char* nombre;
    
    int cantidad = 0;
    
    while(fgets(buffer, 255, (FILE*) archivo)){
        nombre = splitCadena(buffer,",", 0);
        
        if(strcmp(nombre, "monitor") == 0){
            cantidad += 1;
        }
    }
    fclose(archivo); 

    return cantidad;
}

void inicializarMonitor(struct Monitor** monitores, char* descripcionMonitor){
    char* dividirCadena = strtok(descripcionMonitor, ",");
    int i = 0;
    
    struct Monitor* monitor = (struct Monitor*)malloc(sizeof(struct Monitor)+1);
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
        printf("%s[%d](%d,%d)-connec %d\n",monitores->nombre, monitores->id, monitores->largo, monitores->ancho,monitores->idConexion);
        monitores = monitores->siguienteMonitor;
    }
}

void insertarConexiones(struct Monitor** monitores, int idConexiones[], int numeroConexiones){
    struct Monitor* monitoresDetectados = *monitores;
    int indiceMonitor;
    
    while(monitoresDetectados != NULL){
        indiceMonitor = monitoresDetectados->id - 1;
        monitoresDetectados->idConexion = idConexiones[indiceMonitor];
        monitoresDetectados = monitoresDetectados->siguienteMonitor;
    }
}