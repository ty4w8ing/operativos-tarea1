/* 
 * File:   myTimer.h
 * Author: gustavo
 *
 * Created on 22 de abril de 2017, 08:11 PM
 */

#ifndef MYTIMER_H
#define MYTIMER_H

#include <sys/time.h>
#include <signal.h>

#define NULL ((void*)0)

/******************************************************************************/

void set_Timer(int quantum, void (*sign) (int));

void get_Timer();

void stop_Timer();



#endif /* MYTIMER_H */
