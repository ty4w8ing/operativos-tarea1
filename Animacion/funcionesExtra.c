#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strdup(const char* cadena){
    char* duplicado = malloc(strlen(cadena) + 1);
    
    strcpy(duplicado, cadena);
    
    return duplicado;
}

char* splitCadena(char cadena[], char separador[], int posicion){
    char* dividirCadena = strtok(cadena, separador);
    char* elementoExtraido;
    int i = 0;

    while(dividirCadena != NULL){
        if(i == posicion){
            elementoExtraido = malloc(strlen(dividirCadena)+1);
            strcpy(elementoExtraido, dividirCadena);
            break;
        }
        dividirCadena = strtok(NULL, separador);
        i += 1;
    }

    return elementoExtraido;  
}

int cantidadElementos(char* rutaArchivo, char* tipo){
    FILE* archivo = fopen(rutaArchivo,"r");
    char buffer[255];
    
    char* nombre;
    
    int cantidad = 0;
    
    while(fgets(buffer, 255, (FILE*) archivo)){
        nombre = splitCadena(buffer,",", 0);
        
        if(strcmp(nombre, tipo) == 0){
            cantidad += 1;
        }
    }
    fclose(archivo); 

    return cantidad;
}

char* girar90G(char* figura){
    static char figuraAct[31];
    static char figuraResultante[31];
    
    sprintf(figuraResultante,"%s",figura);
    sprintf(figuraAct,"%s",figura);
    
    int fila = 0;
    
    while(fila < 5){
        int j = 0;
        int topJ = 4;
        
        while(j < 5){
            int idAct = fila*6+j;
            int idNuevo = fila + topJ*6;
             
            figuraResultante[idNuevo] = figuraAct[idAct]; 
                      
            j +=1;
            topJ -= 1;
        }
        
        fila += 1;
    }
         
    return figuraResultante;
}
