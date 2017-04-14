#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

#include "monitor.h"

int puerto = 8080;
int numeroMonitores = 0;
int conexionesMaxima = 200;

void imprimirEjemplos(struct Monitor* monitores){
    while(monitores != NULL){
        int conexion = monitores->idConexion;
        char* msn = "\033[8;5HHola Mundo\n";
        
        write(conexion, msn, strlen(msn));
        
        monitores = monitores->siguienteMonitor;
    }
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
    
    numeroMonitores = cantidadMonitores(archivo);
    
    struct Monitor* monitores = extraerMonitoresArchivo(archivo, numeroMonitores);
        
    printf("Se han detectado %d monitores!!\n",numeroMonitores);
    
    
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
           // terminarConexiones(idMonitores);
           // animacionRealizada = 1;
           
           insertarConexiones(&monitores, idMonitores, numeroMonitores);
           
           imprimirMonitores(monitores);
           printf("\n");
           printf("Iniciando Animación!!\n");  
           imprimirEjemplos(monitores);
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

