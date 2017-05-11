/* 
 * File:   sorteo.c
 * Author: gustavo
 * 
 * Created on 25 de abril de 2017, 04:05 PM
 */

#include "sorteo.h"
#include "sorteo_list.h"
#include "simpeThread.h"
#include "lotto.h"

#define NULL ((void*)0)

/* Funcion que me inica el fin del quantum */
void sorteo_end_quantum(int _signal){
    sorteo_switch_context();
}

/* Funcion que inicializa la lista de hilos junto a su respectivo quantum*/
void sorteo_initialize(int quantum, thread_attributes* elemento){
    /* LISTA */
    sorteo_lista_thread = malloc(sizeof(slista)); //--------------- asigno la memoria de la lista 
    sorteo_lista_thread->tamano = 1; //---------------------------- asigno el tama;o de la lista inicial
    sorteo_lista_thread->head = malloc(sizeof(selemento)); //------ asignamos memoria para el nodo inicial
    sorteo_lista_thread->tail = sorteo_lista_thread->head; //------ decimos que el el primero es el ultimo
    sorteo_lista_thread->head->next = sorteo_lista_thread->tail;//- hacemos la lista ciclica
    sorteo_lista_thread->head->hilo = NULL; //--------------------- decimos que la cabeza no tiene informacion
    /* QUATUM */
    sorteo_quantum = quantum;
    sorteo_insert(elemento); //------------------------------------ insertamos el elemento inicial
    set_Timer(sorteo_quantum, sorteo_end_quantum); //-------------- iniciamos el timer
}

void sorteo_next(){
    int tiempo = get_Timer();
    puntero_actual = ganador(total_tiquetes, sorteo_size_list(), sorteo_tiquetes_por_thread);
    selemento* temporal = sorteo_busqueda(puntero_actual);
    if (temporal->hilo->thread_state == DONE){
        selemento* temp2 = sorteo_busqueda_anterior(puntero_actual);
        temp2->next = temporal->next;
        sorteo_delete(temporal);
    }
    set_Timer(tiempo, sorteo_end_quantum);
    selemento* siguiente = sorteo_busqueda(puntero_actual);
    if(!(siguiente->hilo->thread_state == READY && siguiente->hilo->joined_to == NULL)){
        sorteo_next();
    }
    
}



void sorteo_delete(selemento* hilo){
    sorteo_lista_thread->tamano = sorteo_size_list() - 1; // -- quito uno al tama;o de la lista
    thread_attributes* muerto = hilo->hilo; //----------------- creo un temporal con los atributos del hilo
    /* A continuacion paso a liberar la memoria y setear en NULL todos los atributos del hilo */
    muerto->joined_to = NULL;
    if (muerto != NULL){
        muerto->joined_thread->joined_to = NULL;
    }
    total_tiquetes = total_tiquetes - (hilo->cantidad_tiquetes);
    hilo->next = NULL;
    hilo->hilo = NULL;
    hilo->cantidad_tiquetes = 0;
    free(hilo);
    hilo = NULL;
}

/* Funcion que a;ade un nuevo hilo a la cola */
void sorteo_insert(thread_attributes* hilo, int tiquetes){
    if(sorteo_lista_thread->head->hilo != NULL){ //-------------------- si la lista no esta vacia
        selemento* temporal = malloc(sizeof(selemento)); //------------ asignamos memoria para el nuevo elemento
        temporal->hilo = hilo; //-------------------------------------- le damos la info del hilo al nuevo espacio 
        sorteo_lista_thread->tail->next = temporal; //----------------- ponemos el elemento al final de la cola
        sorteo_lista_thread->tail = temporal; //----------------------- decimos que el nuevo elemento es el ultimo
        sorteo_lista_thread->tail->next = sorteo_lista_thread->head;//- mantenemos la lista ciclica
        sorteo_lista_thread->tamano = sorteo_size_list() + 1; //------- incrementamos el tama;o de la lista
        sorteo_lista_thread->tail->cantidad_tiquetes = tiquetes; //---- asignamos los tiquetes del hilo
    } else{
        sorteo_lista_thread->head->hilo = hilo; //--------------------- si la lista esta vacia meto el hilo en la cabeza de la cola
        sorteo_lista_thread->head->cantidad_tiquetes = tiquetes;// ---- asigno los tiquetes del hilo
    }
    total_tiquetes = total_tiquetes + tiquetes;
}

/* funcion que me brinda el thread que se esta ejecutando en este momento */
thread_attributes sorteo_get_current(){
    int indice = 0; //-------------------------------- saco un indice temporal para comparar
    selemento* actual = sorteo_lista_thread->head;//-- saco un puntero temporal para iterar
    /*
     * se hace un ciclo hasta que me ubico sobre el puntero con el indice
     * igual al puntero_actual que se encuentra ejecutando y retorno ese hilo
     */
    while(indice < puntero_actual){
        indice = indice + 1;
        actual = actual->next;
    }
    return actual->hilo;
}

/* funcion que me brinda el thread segun su indice en la lista */
selemento sorteo_busqueda(int list_index){
     int indice = 0; //-------------------------------- saco un indice temporal para comparar
    selemento* actual = sorteo_lista_thread->head;//---s saco un puntero temporal para iterar
    /*
     * se hace un ciclo hasta que me ubico sobre el puntero con el indice
     * igual al puntero_actual que se encuentra ejecutando y retorno ese hilo
     */
    while(indice < list_index){
        indice = indice + 1;
        actual = actual->next;
    }
    return actual;
}

void sorteo_end_of_execution(){
    stop_Timer();
    if(sorteo_lista_thread->head == sorteo_lista_thread->tail){
        sorteo_delete(sorteo_lista_thread->head);
    } else{
        selemento* temporal = sorteo_lista_thread->head;
        /* voy de uno en  uno en la lista borrando */
        while (temporal->next != sorteo_lista_thread->tail){
            selemento* siguiente = temporal->next;
            sorteo_delete(temporal);
            temporal = siguiente;
        }
        sorteo_delete(rr_lista_thread->tail);
    }
}

void sorteo_switch_context(){
    selemento* actual = sorteo_get_current(); //----------- tiro un puntero al elemento actual
    if (sigsetjmp(actual->hilo->environment, 1) != 0){ //-- se guarda el contexto del elemento actual
        return;
    }
    sorteo_next(); //-------------------------------------- pasamos al siguiente hilo
    actual = sorteo_get_current();
    if(actual != NULL){ 
        set_Timer(sorteo_quantum, sorteo_end_quantum); //- setiamos su tiempo
        siglongjmp(actual->hilo->environment, 1); //------- brincamos a la signal salvada
    }
    exit(-1);
}

/* funcion que me da el tama;o de la lista */
int sorteo_size_list(){
    return sorteo_lista_thread->tamano;
}

int sorteo_tiquetes_por_thread(int indice){
    return sorteo_busqueda(indice)->cantidad_tiquetes;
}

selemento sorteo_busqueda_anterior(int indice){
    if (indice != 0){
        return sorteo_busqueda(indice);
    } else {
        return sorteo_lista_thread->tail;
    }
}

