#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objeto.h"
#include "funcionesExtra.h"

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
void mostrarObjeto(char* nombre){
    Figura objeto = extraerObjeto(nombre);
    char* figura = objeto.figura;
    int i;
    
    for(i = 0; i < strlen(figura); i++){        
        char caracterAct = figura[i];
                
        /*if(caracterAct == '-'){
            printf("|   "); 
        }
        else if(caracterAct == '|'){
            printf("%c\n",caracterAct); //Mejor impresion del objeto 
        }       
        else if(caracterAct != '\n' ){
            printf("| %c ",caracterAct);
        }*/
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