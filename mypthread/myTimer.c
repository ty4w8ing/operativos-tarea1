/* 
 * File:   myTimer.c
 * Author: gustavo
 * 
 * Created on 22 de abril de 2017, 08:11 PM
 */

#include "myTimer.h"


/*******************************************************************************/

struct itimerval my_itimerval;//https://www.gnu.org/software/libc/manual/html_node/Setting-an-Alarm.html


/*
 * Funcion que envia una se;al en un intervalo de tiempo
 */
void set_Timer(int quantum, void (*sign) (int)){
    int sec = quantum / 1000; //segundos
    int usec = (quantum % 1000) * 1000; //milisegundos
    my_itimerval.it_interval.tv_sec = 0;
    my_itimerval.it_interval.tv_usec = 0;
    my_itimerval.it_value.tv_sec = sec; 
    my_itimerval.it_value.tv_usec = usec;
    if (sign != NULL)
        signal(SIGALRM, sign);
    setitimer(ITIMER_REAL, &my_itimerval, 0);
}


/*
 * Funcion que retorna el tiempo transcurrido y para la alarma
 */
void get_Timer(){
    getitimer(ITIMER_REAL, &my_itimerval);
    int faltante = my_itimerval.it_value.tv_usec;
    stop_Timer();
return (faltante/1000);
}

/*
 * Funcion que detiene el timer 
 */
void stop_Timer(){
    set_Timer(0, NULL);
}
