/* 
 * File:   sorteo.h
 * Author: gustavo
 *
 * Created on 25 de abril de 2017, 04:05 PM
 */

#ifndef SORTEO_H
#define SORTEO_H

/***********************************************************************************/

/* Lista de Threads tipo sorteo */
slista* sorteo_lista_thread;
/* indice del elemento en ejecucion actualmente */
int puntero_actual;
int total_tiquetes;
/* Quatum del round robin*/
int sorteo_quantum;

void sorteo_end_quantum(int _signal);
void sorteo_initialize(int quantum, thread_attributes* elemento);
void sorteo_next();
void sorteo_delete(selemento* hilo);
void sorteo_insert(thread_attributes* hilo, int tiquetes);
thread_attributes sorteo_get_current();
selemento sorteo_busqueda(int indice);
void sorteo_end_of_execution();
void sorteo_switch_context();
int sorteo_size_list();
int sorteo_tiquetes_por_thread(int indice);
selemento sorteo_busqueda_anterior(int indice);



#endif /* SORTEO_H */
