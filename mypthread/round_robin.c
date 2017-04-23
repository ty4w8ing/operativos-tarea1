/* 
 * File:   round_robin.c
 * Author: gustavo
 * 
 * Created on 22 de abril de 2017, 09:01 PM
 */

#include "round_robin.h"
#include "round_robin_list.h"

#define NULL ((void*)0)



void round_robin_end_quatum(int _signal){
    round_robin_cambio_contexto();
}

void round_robin_cambio_contexto(){
    //yolo
}

/* Funcion que inicializa la lista de hilos junto a su respectivo quantum*/
void round_robin_init(int quantum, thread_attributes* elemento){
    /* LISTA */
    rr_lista_thread = malloc(sizeof(rrlista)); //-------------- asigno la memoria
    rr_lista_thread->tamano = 0; //---------------------------- seteamos su tama;o por defecto
    rr_lista_thread->head =  malloc(sizeof(rrelemento)); // --- signamos memoria para el nodo inicial
    rr_lista_thread->tail = rr_lista_thread->head; //---------- decimos que el el primero es el ultimo
    rr_lista_thread->head->next = rr_lista_thread->tail; // --- decimos que el siguiente elemento es la cola
    rr_lista_thread->head->hilo = NULL; //--------------------- damos el valor NULL al thread asociado al head
    round_robin_insert(elemento); //--------------------------- se agrega el thread principal    
    /* QUATUM */
    rr_quatum = quantum;
    set_Timer(rr_quatum, round_robin_end_quatum());
}


void round_robin_insert(thread_attributes *hilo){
    if (rr_lista_thread->head->hilo == NULL){
        rr_lista_thread->head->hilo = hilo; //----------------- si la lista esta vacia insertamos el elemento
    } else {
        rrelemento temporal = malloc(sizeof(rrelemento)); //--- crr_lista_threadreamos un temporal para el elemento a insertar
        temporal->hilo = hilo; //------------------------------ asignamos los valores del hilo al temporal
        rr_lista_thread->tail->next =  temporal; //------------ ponemos el elemento nuevo al final de la lista (despues del tail)
        rr_lista_thread->tail = temporal; //------------------- ahora el tail tiene el valor del nuevo elemento
        rr_lista_thread->tail->next = rr_lista_thread->head; // hacemos la lista circular
        rr_lista_thread->tamano = (rr_lista_thread->tamano) + 1; // sumamos uno al tama;o de la lista 
    }
    
}
/*void round_robin_next();
void round_robin_delete(rrelemento *hilo);

thread_attributes round_robin_get_current();
void round_robin_end_of_execution();
void round_robin_switch_context();*/