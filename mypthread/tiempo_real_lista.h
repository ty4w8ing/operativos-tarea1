/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tiempo_real.h
 * Author: mauricio
 *
 * Created on 25 de abril de 2017, 11:01 PM
 */

#ifndef TIEMPO_REAL_H
#define TIEMPO_REAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tiempoReal_lista trlista;
typedef struct tiempoReal_elemento trelemento;


struct tiempoReal_lista {
    trelemento* head;
    trelemento* tail;
    int tamano;
};

struct tiempoReal_elemento {
    thread_attributes* hilo;
    trelemento* next;
    int tiempoSalida;
};

#ifdef __cplusplus
}
#endif

#endif /* TIEMPO_REAL_H */

