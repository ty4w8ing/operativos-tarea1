#include <stdio.h>
#include <stdlib.h>
#include "objeto.h"

void menuPruincipal();
void menuObjetos();

int main(int argc, char** argv) {
    
    menuPrincipal();
    return (EXIT_SUCCESS);
}

void menuPrincipal(){
    printf("Animación de Objetos\nOpciones\n1 Administrar Objetos \n2 Ejecutar Animación\n3 Salir\n");
    
    char opcion[25];
    scanf("%s",opcion);
    
    if(strcmp(opcion,"1") == 0){
        menuObjetos();
    }
    else if(strcmp(opcion,"2") == 0){
        printf("Ejecución de la Animación\n");
    }
    else if(strcmp(opcion,"3") == 0){
        exit(0);
    }
    else{
        printf("Opción incorrecta!!\n\n");
        menuPrincipal();
    }   
}

void menuObjetos(){
    printf("\nAdministrar Objetos\nOpciones\n1 Agregar Objeto\n2 Eliminar Objeto\n3 Ver Objeto\n4 Objetos Almacenados\n5 Atras\n6 Salir\n");
    
    char opcion[25];
    scanf("%s",opcion);
    
    if(strcmp(opcion,"1") == 0){
        char nombre[25];
        char figura[50];
        
        printf("\nIngrese el nombre del objeto\n");
        scanf("%s", nombre);
        
        printf("\nIngrese la figura\nImportante:\n*Describa la figura en una sola linea\n*Es una matriz de 5x5\n*Para los espacios en blanco, agregue un -\n"
                "*Para una nueva fila, agregue al final |\nEjemplo: *****|-----|*****|-----|*****|\n");
        scanf("%s", figura);
        
       agregarObjeto(nombre,figura);
       menuObjetos(); 
    }
    else if(strcmp(opcion,"2") == 0){
        char nombre[25];
        
        printf("\nIngrese el nombre del objeto\n");
        scanf("%s", nombre);
        
        printf("\n");
        eliminarObjeto(nombre);
        menuObjetos();
    }
    else if(strcmp(opcion,"3") == 0){
        char nombre[25];
        
        printf("\nIngrese el nombre del objeto\n");
        scanf("%s", nombre);
        
        printf("\n");
        mostrarObjeto(nombre);
        menuObjetos();
    }
    else if(strcmp(opcion,"4") == 0){
        printf("\n");
        imprimirListaObjetosAlmacenados();
        
        menuObjetos();
    }
    else if(strcmp(opcion,"5") == 0){
        menuPrincipal();
    }
    else if(strcmp(opcion,"6") == 0){
        exit(0);
    }
    else{
        printf("\nOpción incorrecta!!\n\n");
        menuObjetos();
    } 
}

