#ifndef __cammini_h
#define __cammini_h
#include <stdlib.h>
#include <stdio.h>
#include "strutture.h"

/* Valuta se esiste tale arco nel grafo */
bool is_edge(amici* friends, int index_nodi, int index_amici);

/* Trova il minimo tra due interi */
int min(int cammino_1, int cammino_2);

/* Alloca la matrice dei cammini minimi */
void alloca_matpath(int** matpath[], int npersone);

/* Algoritmo per trovare i cammini minimi senza tener traccia dei predecessori */
void load_matpath(amici* friends, int** matpath, int npersone);

/* Ordina in modo alfabetico una coppia */
void ordina_coppia(int* coppia, persona** aux_nodi, int i, int j);

/* Ricerca del cammino di lunghezza massima con le caratteristiche richieste */
int maxpath(persona** aux_nodi, int** matpath, int npersone, int* coppiamax);

/* Stampa della coppia trovata in precedenza */
void stampa_matpath(persona** aux_nodi, int** matpath, int npersone, int* coppiamax);

#endif