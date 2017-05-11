#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "administrarObjetos.h"
#include "funcionesExtra.h"

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

//Ingresar un objeto al archivo
void agregarObjeto(char* nombre, char* figura){ 
    static char cadenaEntrada[1];
    sprintf(cadenaEntrada,"%s,%s\n",nombre,figura);
    
    Figura objetoExiste = extraerObjeto(nombre);
    
    FILE* archivo = fopen("data/objetos.txt", "a");
    
    if(objetoExiste.nombre == NULL){
        fputs(cadenaEntrada, archivo);
        printf("El objeto se ha ingresado exitosamente!!\n");
    }
    else if(objetoExiste.nombre != NULL){
        printf("El nombre del objeto digitado ya existe!!\n");
    }
    
    fclose(archivo);
    
}

//Eliminar objeto del archivo
void eliminarObjeto(char* nombreObjeto){
    FILE* archivo = fopen("data/objetos.txt","r");
    FILE* archivoTemp = fopen("data/objetosTemp.txt","a");
    char buffer[255];
    char buffcpy[255];
    char* nombre;
    
    int objetoEliminado = 0;
    
    while(fgets(buffer, 255, (FILE*) archivo)){
        strcpy(buffcpy,buffer);
        nombre = splitCadena(buffer,",", 0);
        
        if(strcmp(nombreObjeto, nombre) != 0){
            fputs(buffcpy, archivoTemp);
        }
        else{
            objetoEliminado = 1;
        }
    }
    
    fclose(archivo);
    fclose(archivoTemp);  
    
    remove("data/objetos.txt");
    rename("data/objetosTemp.txt","data/objetos.txt");
    
    if(objetoEliminado){
        printf("Se ha eliminado el objeto!!\n");
    }
    else{
        printf("No se ha eliminado el objeto, ya que no existe!!\n");
    }
}

//Extraer Objeto del archivo
Figura extraerObjeto(char* nombreObjeto){
    FILE* archivo = fopen("data/objetos.txt","r");
    char buffer[255];
    char buffcpy[255];
    
    char* nombre;
    Figura objeto;
    int objetoAlmacenado = 0;
    
    if(archivo == NULL){
        printf("El archivo no existe!!\n");
    }    
    
    while(fgets(buffer, 255, (FILE*) archivo)){
        strcpy(buffcpy, buffer);
        
        nombre = splitCadena(buffer,",", 0);
        
        if(strcmp(nombreObjeto, nombre) == 0){
            objeto.nombre = nombre;
            objeto.figura = splitCadena(buffcpy,",",1);
            objetoAlmacenado = 1;
            
            break;
        }
    }
    fclose(archivo); 
    
    if(objetoAlmacenado == 0){
        objeto.figura = NULL;
        objeto.nombre = NULL;
    }
    
    return objeto;
}

//Busca un objeto en el archivo y muestra la figura
void mostrarObjeto(char* figura){    
    int i;
        
    for(i = 0; i < strlen(figura); i++){        
        char caracterAct = *(figura+i);
                
        if(caracterAct == '-'){
            printf(" "); 
        }
        else if(caracterAct == '|'){
            printf("\n");
        }       
        else if(caracterAct != '\n' ){
            printf("%c",caracterAct);
        }
    }
}

//Listado de Objetos almacenados
void imprimirListaObjetosAlmacenados(){
    FILE* archivo = fopen("data/objetos.txt","r");
    char buffer[255];
    char* nombre;
    
    if(archivo == NULL){
        printf("El archivo no existe!!\n");
    }    
    
    while(fgets(buffer, 255, (FILE*) archivo)){
        nombre = splitCadena(buffer,",", 0);
        printf("%s\n",nombre);
    }
    
    fclose(archivo);      
}

void movimiento0G(char* nombreObj){
    Figura obj = extraerObjeto(nombreObj); 
    
    mostrarObjeto(obj.figura);
    
    printf("\nMovimiento 0 grados\n\n");
    
    mostrarObjeto(obj.figura);
}

void movimiento90G(char* nombreObj){
    Figura obj = extraerObjeto(nombreObj); 
    
    mostrarObjeto(obj.figura);
    
    printf("\nMovimiento 90 grados\n\n");
    
    char* fig90 = girar90G(obj.figura);   
    
    mostrarObjeto(fig90);
}

void movimiento180G(char* nombreObj){
    Figura obj = extraerObjeto(nombreObj); 
    
    mostrarObjeto(obj.figura);
    
    printf("\nMovimiento 180 grados\n\n");
    
    char* fig90 = girar90G(obj.figura);
    char* fig180 = girar90G(fig90);
    
    mostrarObjeto(fig180);
}

void movimiento270G(char* nombreObj){
    Figura obj = extraerObjeto(nombreObj); 
    
    mostrarObjeto(obj.figura);
    
    printf("\nMovimiento 270 grados\n\n");
    
    char* fig90 = girar90G(obj.figura);
    char* fig180 = girar90G(fig90);
    char* fig270 = girar90G(fig180);
    
    mostrarObjeto(fig270);
}