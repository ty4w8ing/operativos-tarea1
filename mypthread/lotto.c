/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lotto.c
 * Author: gustavo
 * 
 * Created on 25 de abril de 2017, 07:31 PM
 */

#include "lotto.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int ganador(int total_tiquetes, int total_hilos, int (foo)(int)){
	srand(time(NULL));
	double random = (double)(rand()%1001)/1000;
	int i = 0;
	double tamano_particiones = (float)1/total_tiquetes;
	double total = 0;
	while (i < total_hilos){
		int temp = 0;
		while (temp < foo(i)){
			if (i+1 != total_hilos) total = total + tamano_particiones;
			else { total = 1; }
			temp = temp + 1;
		}
		if (random < total) return i;
		else { i = i + 1; }
	}
	exit(-1);
}