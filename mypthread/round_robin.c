/* 
 * File:   round_robin.c
 * Author: gustavo
 * 
 * Created on 22 de abril de 2017, 09:01 PM
 */

#include "round_robin.h"
#include "round_robin_list.h"

#define NULL ((void*)0)


/* Funcion que me inica el fin del quantum */
void round_robin_end_quantum(int _signal){
    round_robin_switch_context();
}

/* Funcion que inicializa la lista de hilos junto a su respectivo quantum*/
void round_robin_initialize(int quantum, thread_attributes* elemento){
    /* LISTA */
    rr_lista_thread = malloc(sizeof(rrlista)); //-------------- asigno la memoria
    rr_lista_thread->tamano = 1; //---------------------------- seteamos su tama;o por defecto
    rr_lista_thread->head =  malloc(sizeof(rrelemento)); // --- asignamos memoria para el nodo inicial
    rr_lista_thread->tail = rr_lista_thread->head; //---------- decimos que el el primero es el ultimo
    rr_lista_thread->head->next = rr_lista_thread->tail; // --- decimos que el siguiente elemento es la cola
    rr_lista_thread->head->hilo = NULL; //--------------------- damos el valor NULL al thread asociado al head
    /* QUATUM */
    rr_quantum = quantum;
    round_robin_insert(elemento); //--------------------------- se agrega el thread principal   
    set_Timer(rr_quantum, round_robin_end_quantum());
}


/* Funcion que inserta un hilo en la lista */
void round_robin_insert(thread_attributes* hilo){
    if (rr_lista_thread->head->hilo == NULL){
        rr_lista_thread->head->hilo = hilo; //----------------- si la lista esta vacia insertamos el elemento
    } else {
        rrelemento* temporal = malloc(sizeof(rrelemento)); //-- crr_lista_threadreamos un temporal para el elemento a insertar
        temporal->hilo = hilo; //------------------------------ asignamos los valores del hilo al temporal
        rr_lista_thread->tail->next =  temporal; //------------ ponemos el elemento nuevo al final de la lista (despues del tail)
        rr_lista_thread->tail = temporal; //------------------- ahora el tail tiene el valor del nuevo elemento
        rr_lista_thread->tail->next = rr_lista_thread->head; // hacemos la lista circular
        rr_lista_thread->tamano = round_robin_size_list() + 1; // sumamos uno al tama;o de la lista 
    }
    
}

/* Funcion que pasa al siguiente hilo en ejecucion */
void round_robin_next(){
    rrelemento* actual = rr_lista_thread->head; //-------------- seteamos un puntero temporal con el elemento actual 
    rr_lista_thread->head = rr_lista_thread->head->next; //----- pasamos al siguiente elemento como el elemento actual
    if (actual->hilo->thread_state = DONE){ //------------------ preguntamos si el actual tiene como estado DONE osea si esta finalizado
        rr_lista_thread->tail = rr_lista_thread->head; //------- de ser asi cambiamos el final del arreglo al nuevo head
        round_robin_delete(actual); //-------------------------- eliminamos el hilo
    } else {
        rr_lista_thread->tail =  actual; //--------------------- de no ser asi solo cambiamos el final de la lista
    }
    rrelemento* siguiente = rr_lista_thread->head; //---------- creo otro temporal para ver si el actual esta listo o no
    int ciclo = 1;
    while (ciclo){ //------------------------------------------ mientras el siguiente no este en READY o no este en join
        if (!(siguiente->hilo->thread_state == READY && siguiente->hilo->joined_to == NULL)){
            /* Paso al siguiente y busco */
            rr_lista_thread->head = siguiente->next;
            rr_lista_thread->tail = siguiente;
            siguiente = rr_lista_thread->head;
        } else {
            ciclo = 0;
        }
    }
}


/* Funcion que elimina un hilo de la lista RR */
void round_robin_delete(rrelemento *hilo){
    rr_lista_thread->tamano = round_robin_size_list() - 1; // - quito uno al tama;o de la lista
    thread_attributes* muerto = hilo->hilo; //------------------- creo un temporal con los atributos del hilo
    /* A continuacion paso a liberar la memoria y setear en NULL todos los atributos del hilo */
    muerto->joined_to = NULL;
    if (muerto != NULL){
        muerto->joined_thread = NULL;
    }
    hilo->next = NULL;
    hilo->hilo = NULL;
    free(hilo);
    hilo = NULL;
}

/* Funcion que devuelve el hilo actual */
thread_attributes round_robin_get_current(){
    return rr_lista_thread->head->hilo;
}

/* Funcion que para todo y libera la memoria */
void round_robin_end_of_execution(){
    stop_Timer(); //------------------------------------------- Detengo el timer
    if (rr_lista_thread->head != rr_lista_thread->tail){ //---- pregunto si la lista es de un solo elemento
        rrelemento* temporal = rr_lista_thread->head; //------- de no ser asi creo un temporal para ir borrando
        /* voy de uno en  uno en la lista borrando */
        while (temporal->next != rr_lista_thread->tail){
            rrelemento* siguiente = temporal->next;
            round_robin_delete(temporal);
            temporal = siguiente;
        }
        round_robin_delete(rr_lista_thread->tail);
    } else { //------------------------------------------------ de no ser asi borro el unico elemento
        round_robin_delete(rr_lista_thread->head);
    }
    free(rr_lista_thread); //---------------------------------- libero la memoria asociada a la lista
}


/* Se guarda el estado del hilo actual y se pasa a ejecutar el el siguiente hilo */
void round_robin_switch_context(){
    rrelemento* actual = round_robin_get_current(); //----- tiro un puntero al elemento actual
    if (sigsetjmp(actual->hilo->environment, 1) != 0){ // - se guarda el contexto del elemento actual
        return;
    }
    round_robin_next(); //--------------------------------- pasamos al siguiente hilo
    actual = round_robin_get_current();
    if(actual != NULL){ 
        set_Timer(rr_quantum, round_robin_end_quantum); //-- setiamos su tiempo
        siglongjmp(actual->hilo->environment, 1); //------- brincamos a la se;al salvada
    }
    exit(-1);
}

/* Funcion que devuelve el tama;o de la lista */
int round_robin_size_list(){
    return rr_lista_thread->tamano;
}