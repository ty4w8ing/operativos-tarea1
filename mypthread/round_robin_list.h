/* 
 * File:   round_robin_list.h
 * Author: gustavo
 *
 * Created on 18 de abril de 2017, 04:58 PM
 */

#ifndef ROUND_ROBIN_LIST_H
#define ROUND_ROBIN_LIST_H

#include "simpeThread.h"
/******************************************************************************/

/*
 * elementos del round robin
 */
typedef struct round_robin_lista rrlista;
typedef struct round_robin_elemento rrelemento;


struct round_robin_lista {
    rrelemento* head;
    rrelemento* tail;
    int tamano;
};

struct round_robin_elemento {
    thread_attributes *hilo;
    rrelemento *next;
};

#endif /* ROUND_ROBIN_LIST_H */
