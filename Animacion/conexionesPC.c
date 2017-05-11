#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <pthread.h>

#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

#include "monitor.h"
#include "funcionesExtra.h"
#include "matrizCanvas.h"
#include "objeto.h"

int puerto = 8080;
int numeroMonitores = 0;
int conexionesMaxima = 200;
int numeroObjetos = 0;

int ejecutarHilos(struct Objeto* objetos, struct Monitor* monitores, struct Canvas* canvas, int numeroObjetos, pthread_t hilos[]){
    int i;
    int animacionCompletada = 1;
    
    
    for(i = 0; i < numeroObjetos; i+=1){
        struct elementosHilo* arg = malloc(sizeof(struct elementosHilo*));
        arg->monitores = monitores;
        arg->objeto = objetos;
        arg->canvas = canvas;

        if(objetos->posXAct != objetos->posXFin || objetos->posYAct != objetos->posYFin){
            animacionCompletada = 0;
            pthread_create(&hilos[i],NULL, iniciarObjeto, arg);
               
            pthread_join(hilos[i], NULL);
        }
        objetos = objetos->siguienteObjeto;
    }
 
    return animacionCompletada;
}
void terminarConexiones(int* idConexiones){
    int i;
    
    for(i = 0; i < sizeof(idConexiones); i+=1){
        close(idConexiones[i]);
    }
    
    printf("Conexiones terminada!!\n");
}

void iniciarSocket(char* archivo){
    int one = 1, cliente = 1;
    struct sockaddr_in svr_addr, cli_addr;
    socklen_t sin_len = sizeof(cli_addr);

    //Se crea el socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0){
        printf("No se creo el socket\n");
    }
    else{
        printf("Servidor de la Animación Iniciado!!\n");
    }
                    
    numeroMonitores = cantidadElementos(archivo, "monitor");
    numeroObjetos = cantidadElementos(archivo, "objeto");
    
    struct Monitor* monitores = extraerMonitoresArchivo(archivo);
    struct Objeto* objetos = extraerObjetosArchivo(archivo);
       
    printf("Se han detectado %d monitores!!\n",numeroMonitores);
    printf("Se han detectado %d objetos!!\n",numeroObjetos);
    
    printf("Detalles Objetos\n\n");
    imprimirObjetos(objetos);
    printf("\n");
    
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,&one, sizeof(int));

    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = INADDR_ANY;
    svr_addr.sin_port = htons(puerto);

    //Se asigna el socket a una dirección
    if(bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1){
        close(sock);
        printf("No se pudo crear la conexión!!\n");
    }

    //Socket escucha las conexiones ingresadas
    listen(sock, conexionesMaxima);
    int idMonitores[numeroMonitores];
    int pos = 0;
    int animacionRealizada = 0;   
    
    int* dim = dimensionCanvas(monitores);
    struct 
    
    
    Canvas* canvas = crearMatriz(dim[1], dim[0]);
   

    while (!animacionRealizada) {
        //Se acepta la conexión
        cliente = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);

        if (cliente < 0) {
            printf("No se aceptó la conexión\n");
            continue;
        }
        else if(pos == numeroMonitores-1){
           printf("Monitor detectado\n\nDetalles de los Monitores\n");
           idMonitores[pos] = cliente;
                       
           insertarConexiones(&monitores, idMonitores);
           
           imprimirMonitores(monitores);
           printf("\n");
           printf("Iniciando Animación!!\n");  
           
           limpiarMonitores(monitores);
           
           pthread_t hilos[numeroObjetos];
           
                     
           int finAnimacion = 0;
           while(finAnimacion == 0){
               finAnimacion = ejecutarHilos(objetos, monitores, canvas, numeroObjetos, hilos);
           }
           
           pthread_exit(NULL);
           //Generar matriz[xCanvas][yCanvas]
                      
           
           //iniciarObjeto( monitores);
           
           sleep(1);
           limpiarMonitores(monitores);
                      
           terminarConexiones(idMonitores);
           animacionRealizada = 1;
        }
        else if(pos < numeroMonitores){
            printf("Monitor detectado\n");
            idMonitores[pos] = cliente;
        }
        else if(pos > numeroMonitores){
           char* mensaje = "Ya se asignaron los monitores para realizar la animación!!\n";
           write(cliente, mensaje, strlen(mensaje));
           close(cliente);
        }
        
        pos += 1;
    }
    printf("Animación Terminada!!\n");
}

