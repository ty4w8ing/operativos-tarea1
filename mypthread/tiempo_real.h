/* 
 * File:   tiempo_real.h
 * Author: estudiante
 *
 * Created on 26 de abril de 2017, 12:07 PM
 */

#ifndef TIEMPO_REAL_H
#define TIEMPO_REAL_H

trlista* tiempoReal_lista_thread;

int treal_quantum;
int puntero_actual;

void tiempoReal_initialize(int tiempoSalida, thread_attributes* elemento);
void tiempoReal_insert(thread_attributes* hilo, int tiempoSalida);
int tiempoReal_size_list();
void tiempoReal_next();
thread_attributes tiempoReal_get_current();
trelemento tiempoReal_busqueda();
void tiempoReal_switch_context();
void tiempoReal_delete(trelemento* hilo);
int tiempoReal_tiempo_por_thread(int indice);
trelemento tiempoReal_busqueda_anterior(int indice);

#endif /* TIEMPO_REAL_H */

