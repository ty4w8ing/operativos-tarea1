#include "stdio.h"
#include "tiempo_real_lista.h"
#include "simpeThread.h"

#define NULL ((void*)0)

void tiempoReal_end_quantum(int _signal){
    tiempoReal_switch_context();
}

void tiempoReal_initialize(int tiempoSalida, thread_attributes* elemento){
    /* LISTA */
    tiempoReal_lista_thread = malloc(sizeof(trlista));
    tiempoReal_lista_thread->tamano = 1;
    tiempoReal_lista_thread->head = malloc(sizeof(trelemento)); //------ asignamos memoria para el nodo inicial
    tiempoReal_lista_thread->tail = tiempoReal_lista_thread->head; //------ decimos que el primero es el ultimo
    tiempoReal_lista_thread->head->next = tiempoReal_lista_thread->tail;//- hacemos la lista ciclica
    tiempoReal_lista_thread->head->hilo = NULL; //--------------------- decimos que la cabeza no tiene informacion
   
    tiempoReal_insert(elemento, tiempoSalida); //------------------------------------ insertamos el elemento inicial
    set_Timer(treal_quantum, tiempoReal_end_quantum);
}

//Insertar el elemento según su tiempo de salida
void tiempoReal_insert(thread_attributes* hilo, int tiempoSalida){
    if(tiempoReal_lista_thread->head->hilo != NULL){ //-------------------- si la lista no esta vacia
        trelemento* nuevoThread = malloc(sizeof(trelemento)); //------------ asignamos memoria para el nuevo elemento
        nuevoThread->hilo = hilo; //-------------------------------------- le damos la info del hilo al nuevo espacio 
        
        tiempoReal_lista_thread->tail->next = nuevoThread; //----------------- ponemos el elemento al final de la cola
        tiempoReal_lista_thread->tail = nuevoThread; //----------------------- decimos que el nuevo elemento es el ultimo
        tiempoReal_lista_thread->tail->next = tiempoReal_lista_thread->head;//- mantenemos la lista ciclica
        tiempoReal_lista_thread->tamano = tiempoReal_size_list() + 1; //------- incrementamos el tama;o de la lista
        tiempoReal_lista_thread->tail->tiempoSalida = tiempoSalida; //---- asignamos los tiquetes del hilo
        
    } else{
        tiempoReal_lista_thread->head->hilo = hilo; //--------------------- si la lista esta vacia meto el hilo en la cabeza de la cola
        tiempoReal_lista_thread->head->tiempoSalida = tiempoSalida;// ---- asigno los tiquetes del hilo
        tiempoReal_lista_thread->tamano = 1;
    }
}

void tiempoReal_next(){
    int tiempo = get_Timer();
    
    puntero_actual = posicionEntrada(tiempo, tiempoReal_size_list(), tiempoReal_tiempo_por_thread);
    
    trelemento* temporal = tiempoReal_busqueda(puntero_actual);
    if (temporal->hilo->thread_state == DONE){
        trelemento* temp2 = tiempoReal_busqueda_anterior(puntero_actual);
        temp2->next = temporal->next;
        tiempoReal_delete(temporal);
    }
    set_Timer(tiempo, tiempoReal_end_quantum);
    trelemento* siguiente = tiempoReal_busqueda(puntero_actual);
    if(!(siguiente->hilo->thread_state == READY && siguiente->hilo->joined_to == NULL)){
        tiempoReal_next();
    }
    
}

void tiempoReal_switch_context(){
    trelemento* actual = tiempoReal_get_current(); //----- tiro un puntero al elemento actual
    if (sigsetjmp(actual->hilo->environment, 1) != 0){ // - se guarda el contexto del elemento actual
        return;
    }
    tiempoReal_next(); //--------------------------------- pasamos al siguiente hilo
    actual = tiempoReal_get_current();
    if(actual != NULL){ 
        set_Timer(treal_quantum, tiempoReal_end_quantum); //-- setiamos su tiempo
        siglongjmp(actual->hilo->environment, 1); //------- brincamos a la se;al salvada
    }
    exit(-1);
}

void tiempoReal_end_of_execution(){
    stop_Timer();
    if(tiempoReal_lista_thread->head == tiempoReal_lista_thread->tail){
        tiempoReal_delete(tiempoReal_lista_thread->head);
    } 
    else{
        trelemento* temporal = tiempoReal_lista_thread->head;
        /* voy de uno en  uno en la lista borrando */
        while (temporal->next != tiempoReal_lista_thread->tail){
            trelemento* siguiente = temporal->next;
            tiempoReal_delete(temporal);
            temporal = siguiente;
        }
        tiempoReal_delete(tiempoReal_lista_thread->tail);
    }
}

void tiempoReal_delete(trelemento* hilo){
    tiempoReal_lista_thread->tamano = tiempoReal_size_list() - 1;
    thread_attributes* muerto = hilo->hilo;
    muerto->joined_to = NULL;
    if (muerto != NULL){
        muerto->joined_thread->joined_to = NULL;
    }
    hilo->next = NULL;
    hilo->hilo = NULL;
    hilo->tiempoSalida = 0;
    free(hilo);
    hilo = NULL;
}

int tiempoReal_size_list(){
    return tiempoReal_lista_thread->tamano;
}

thread_attributes tiempoReal_get_current(){
    int indice = 0; //-------------------------------- saco un indice temporal para comparar
    trelemento* actual = tiempoReal_lista_thread->head;//-- saco un puntero temporal para iterar
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

trelemento tiempoReal_busqueda(int posicionLista){
    int indice = 0; //-------------------------------- saco un indice temporal para comparar
    trelemento* actual = tiempoReal_lista_thread->head;//-- saco un puntero temporal para iterar
    /*
     * se hace un ciclo hasta que me ubico sobre el puntero con el indice
     * igual al puntero_actual que se encuentra ejecutando y retorno ese hilo
     */
    while(indice < posicionLista){
        indice = indice + 1;
        actual = actual->next;
    }
    return actual;
}

int tiempoReal_tiempo_por_thread(int indice){
    return  tiempoReal_busqueda(indice)->tiempoSalida;
}

trelemento tiempoReal_busqueda_anterior(int indice){
    if (indice != 0){
        return tiempoReal_busqueda(indice);
    } else {
        return tiempoReal_lista_thread->tail;
    }
}

int posicionEntrada(int tiempo, int total_hilos, int (foo)(int)){
	int i = 0;
	int tiempoThread;
        while (i < total_hilos){
            tiempoThread = foo(i);
            if(tiempo >= tiempoThread && tiempo <= tiempoThread*2){
                int j = i + 1;
                int esMenor = 1;
                
                while(j < total_hilos){
                    if(tiempo >= foo(j) && tiempo <= foo(j)*2 && foo(j) < tiempoThread){
                        esMenor = 0;
                        break;
                    }
                    j +=1;
                }
                
                if(esMenor == 1){
                    return i;
                }
            }
            i +=1;
	}
	exit(-1);
}

