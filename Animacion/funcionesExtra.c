#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
