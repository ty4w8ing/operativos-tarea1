/* 
 * File:   sorteo_list.h
 * Author: gustavo
 *
 * Created on 25 de abril de 2017, 04:01 PM
 */

#ifndef SORTEO_LIST_H
#define SORTEO_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * elementos del scheduling sorteo
 */
typedef struct sorteo_lista slista;
typedef struct sorteo_elemento selemento;


struct sorteo_lista {
    selemento* head;
    selemento* tail;
    int tamano;
};

struct sorteo_elemento {
    thread_attributes *hilo;
    selemento *next;
    int cantidad_tiquetes;
};


#ifdef __cplusplus
}
#endif

#endif /* SORTEO_LIST_H */

