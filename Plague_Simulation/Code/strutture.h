#ifndef __strutture_h
#define __strutture_h
#include <stdlib.h>
#include <stdio.h>

/* Definizione di bool */
typedef int bool;
enum { FALSE, TRUE};

/* Definizione struct persona (elemento database) */
typedef struct persona{
	char nome [16];
	int eta;	
	int infect_time;
	int n_amici;
	float salute;
	float rho;	
	float rec_time;
} persona; 

/* Definizione grafo degli amici */
typedef struct amici{
	persona* whose;
	int* who;
	float* frequenza;
} amici;

/* Elemento della lista ospedale */
typedef struct ospedale{
	int who;
	struct ospedale* next;
} ospedale;

/* Calcola rho */
float frho(int eta, float salute);

#endif