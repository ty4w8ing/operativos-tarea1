#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "administrarObjetos.h"
#include "conexionesPC.h"

void ejecucionANimacion();
void menuPruincipal();
void menuObjetos();

void ejecucionAnimacion(char* archivo){
    iniciarSocket(archivo);
}

void menuObjetos(){
    printf("\nAdministrar Objetos\nOpciones\n1 Agregar Objeto\n2 Eliminar Objeto\n3 Ver Objeto\n4 Movimiento Objeto\n5 Objetos Almacenados\n6 Salir\n");
    
    int opcion;
    char nombre[25];
    char movimiento[10];
    char figura[50];
   
    scanf("%d",&opcion);
    
    switch(opcion){
        case 1:
            printf("\nIngrese el nombre del objeto\n");
            scanf("%s", nombre);
        
            printf("\nIngrese la figura\nImportante:\n*Describa la figura en una sola linea\n*Es una matriz de 5x5\n*Para los espacios en blanco, agregue un -\n"
                "*Para una nueva fila, agregue al final |\nEjemplo: *****|-----|*****|-----|*****|\n");
            scanf("%s", figura);
        
            agregarObjeto(nombre,figura);
            menuObjetos();
            break;
        case 2:
            printf("\nIngrese el nombre del objeto\n");
            scanf("%s", nombre);

            printf("\n");
            eliminarObjeto(nombre);
            menuObjetos();
            
            break;
        case 3:
            printf("\nIngrese el nombre del objeto\n");
            scanf("%s", nombre);

            printf("\n");
            Figura objeto = extraerObjeto(nombre);
            mostrarObjeto(objeto.figura);
            menuObjetos();
            
            break;
        case 4:
            printf("\nIngrese el nombre del objeto\n");
            scanf("%s", nombre);

            printf("\nIngrese la rotación deseada para el objeto(0,90,180,270)\n");
            scanf("%s", movimiento);

            if(strcmp(movimiento, "0") == 0){
                movimiento0G(nombre);
            }
            else if(strcmp(movimiento, "90") == 0){
                movimiento90G(nombre);
            }
            else if(strcmp(movimiento, "180") == 0){
                movimiento180G(nombre);
            }
            else if(strcmp(movimiento, "270") == 0){
                movimiento270G(nombre);
            }
            else{
                printf("Número de rotación invalida!!");
            }
            menuObjetos();
            break;
            
        case 5:
            printf("\n");
            imprimirListaObjetosAlmacenados();

            menuObjetos();
            break;
            
        case 6:
            exit(0);
            break;
            
        default:
            printf("\nOpción incorrecta!!\n\n");
            menuObjetos();
    }
}

int main(int argc, char** argv) {
    if(argc == 1){
        printf("Debe agregar parametros al ejecutar el programa!!\nAgregue -c para administrar objetos o -e archivo.txt para ejecutar la animación.\n");
    }
    else{
        if(strcmp(argv[1], "-c") == 0){
            menuObjetos();
        }
        else if(strcmp(argv[1], "-e") == 0){
            ejecucionAnimacion(argv[2]);
        }
    }
    return (EXIT_SUCCESS);
}

