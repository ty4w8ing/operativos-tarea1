/* 
 * File:   simpeThread.h
 * Author: gustavo
 *
 * Created on 19 de abril de 2017, 06:46 PM
 */

#ifndef SIMPETHREAD_H
#define SIMPETHREAD_H

#include <setjmp.h>

#define STACK_SIZE 8388608 //http://www.linuxquestions.org/questions/linux-newbie-8/default-stack-size-on-linux-glibc-pthreads-358438/

/*********************************************************************************/

typedef unsigned long int thread_id;            /* ID del thread */
typedef struct attributes thread_attributes;    /* atributos del thread */

struct attributes {
    thread_id my_thread_id;             /* ID del thread */
    int thread_state;                   /* estado del thread (DONE, READY, BLOCKED) */
    char stack[STACK_SIZE];             /* Tama;o del hilo */
    void *(*thread_function)(void*);    /* Funcion que recibe el hilo */
    void *arguments;                    /* Argumento de esa funcion */
    jmp_buf environment;                /* para almacenar el contexto del hilo https://es.wikipedia.org/wiki/Setjmp.h */
};


#endif /* SIMPETHREAD_H */
