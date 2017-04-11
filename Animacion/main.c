#include <stdio.h>
#include <stdlib.h>
#include "administrarObjetos.h"

void ejecucionANimacion();
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
        ejecucionAnimacion();
    }
    else if(strcmp(opcion,"3") == 0){
        exit(0);
    }
    else{
        printf("Opción incorrecta!!\n\n");
        menuPrincipal();
    }   
}

void ejecucionAnimacion(){
    printf("Diseño de la animación:\n");
    printf("*Se va a manejar a base de un archivo de entrada.\n");
    printf("*Los monitores deberán tener la etiqueta 'monitor' junto a su nombre,largo,ancho,prioridad. \n\n"
            "monitor,m1,100,50,1\n\n");
    printf("*Los objetos se definirán en el mismo archivo del monitor y tendrán la siguiente forma.\n\nobjeto,flecha,rr,0,50,100,50,90\n");
    printf("\n*Las secciones del objeto son: etiqueta,tipoObjeto,tipoScheduler,posicionInicialX,posicionInicialY,posicionFinalX,posicionFinalY,angulo\n"
            "*En el caso del angulo sería 0,90,180,270 y algún otro número(como 117) para tener un random de los angulos mientras se mueve entre alguna posicion."
            "\n*El tipo de scheduler sera rr para RoundRobbin o st para sorteo\n\n");
    
    menuPrincipal();
}

void menuObjetos(){
    printf("\nAdministrar Objetos\nOpciones\n1 Agregar Objeto\n2 Eliminar Objeto\n3 Ver Objeto\n4 Movimiento Objeto\n5 Objetos Almacenados\n6 Atras\n7 Salir\n");
    
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
        Figura obj = extraerObjeto(nombre);
        mostrarObjeto(obj.figura);
        menuObjetos();
    }
    else if(strcmp(opcion,"4") == 0){
        char nombre[25];
        char movimiento[10];
        
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
    }
    else if(strcmp(opcion,"5") == 0){
        printf("\n");
        imprimirListaObjetosAlmacenados();
        
        menuObjetos();
    }
    else if(strcmp(opcion,"6") == 0){
        menuPrincipal();
    }
    else if(strcmp(opcion,"7") == 0){
        exit(0);
    }
    else{
        printf("\nOpción incorrecta!!\n\n");
        menuObjetos();
    } 
}

