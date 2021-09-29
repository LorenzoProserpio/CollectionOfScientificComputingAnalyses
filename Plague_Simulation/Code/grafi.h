#ifndef __grafi_h
#define __grafi_h
#include <stdlib.h>
#include <stdio.h>
#include "strutture.h"

/* Alloca righe del grafo (che sono i nodi)*/
void alloca_friends(amici* friends[], int npersone);
/* Alloca vettore di adiacenza e vettore pesi */
void alloca_who(int* who[], float* frequenza[], int n_amici);

/* Funzioni ausiliarie per gestire l'input da file correttamente */
void alloca_formato(char* formato[]);
void flush_amici(char* formato, int n_amici);

/* Funzione che dato il nome associa l'indirizzo del nodo nel vettore di indirizzi */
int cerca_nome(char* nome, persona** aux_nodi, int npersone);

/* Carica il grafo da file come forward star */
void carica_who(FILE* fp, char* riga, int npersone, int index, persona** aux_nodi, int* who, float* frequenza);

/* Alloca il vettore ausiliario per le componenti connesse, che poi verrà usato ancora in fase di simulazione con altro scopo */
void alloca_controllo(int* controllo[], int npersone);

/* Funzione ausiliaria per trovare il massimo tra due float */
float massimo(float rho1, float rho2);

/* Visita del grafo in profondità */
void visita_amici(amici sorgente, amici* friends, persona** aux_nodi, int* controllo, int marcatore);

/* Calcolo delle componenti connesse usando la visita in profondità */
int componenti_connesse(amici* friends, persona** aux_nodi, int* controllo, int npersone);

/* Stampa delle componenti connesse in ordine */
void carica_stampa_cc(persona** aux_nodi, int* controllo, int n_cc, int npersone);

#endif