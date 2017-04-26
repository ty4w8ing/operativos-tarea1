/* 
 * File:   round_robin.h
 * Author: gustavo
 *
 * Created on 22 de abril de 2017, 09:01 PM
 */

#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

/***********************************************************************************/

/* Lista de Threads tipo RR */
rrlista* rr_lista_thread;

/* Quatum del round robin*/
int rr_quantum;

void round_robin_end_quantum(int _signal);
void round_robin_initialize(int quantum, thread_attributes* elemento);
void round_robin_next();
void round_robin_delete(rrelemento* hilo);
void round_robin_insert(thread_attributes* hilo);
thread_attributes round_robin_get_current();
void round_robin_end_of_execution();
void round_robin_switch_context();
int round_robin_size_list();


#endif /* ROUND_ROBIN_H */
