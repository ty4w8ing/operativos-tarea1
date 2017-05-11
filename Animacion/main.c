#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "administrarObjetos.h"
#include "monitor.h"
#include "funcionesExtra.h"
#include "conexionesPC.h"

int main(int argc, char** argv) {
    if(argc == 1){
        printf("Debe agregar parametros al ejecutar el programa!!\nAgregue -c para administrar objetos o -e archivo.txt para ejecutar la animación.\n");
    }
    else{
        if(strcmp(argv[1], "-c") == 0){
            menuObjetos();
        }
        else if(strcmp(argv[1], "-e") == 0){
            iniciarSocket(argv[2]);
        }
    }
    return (EXIT_SUCCESS);
}

