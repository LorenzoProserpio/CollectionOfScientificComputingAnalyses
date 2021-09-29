#ifndef __heapsort_h
#define __heapsort_h

#include <stdlib.h>
#include "strutture.h"

/* Alloca e setta i vettori di permutazione che mi serviranno per gli ordinamenti alfabetici e rho */
void alloca_permutation(int* permutation[], int* permutation2[], int npersone);
void set_permutation(int* permutation, int* permutation2, int npersone);

/* Funzioni ausiliarie di swap di interi (la prima) e di puntatori a struct (la seconda) */
void Swap_int(int* permutation, int i, int j);
void Swap(persona** aux_nodi, int i, int j);

/* Heapsort e ausiliarie necessarie per l'ordinamento per età e caratteristiche indicate nel progetto */
void Aggiorna_heap_eta(persona** aux_nodi, int i, int j, int npersone);
void HeapSort_eta(persona** aux_nodi, int npersone);

void Aggiorna_heap_salute(persona** aux_nodi, int i, int j, int npersone);
void HeapSort_salute(persona** aux_nodi, int npersone);
void Parita_salute(persona** aux_nodi, int npersone);

void Aggiorna_heap_alfabetico(persona** aux_nodi, int i, int j, int npersone);
void HeapSort_alfabetico(persona** aux_nodi, int npersone);
void Parita_alfabetico_salute(persona** aux_nodi, int npersone);

/* Heapsort e ausiliarie necessarie per l'ordinamento per rho e ordine alfabetico in versione in cui si tiene traccia della permutazione */
void Aggiorna_heap_alfabetico_perm(int* permutation, persona** aux_nodi, int i, int j, int npersone);
void HeapSort_alfabetico_perm(int* permutation, persona** aux_nodi, int npersone);
void Parita_alfabetico_rho(int* permutation, persona** aux_nodi, int npersone);

void Aggiorna_heap_rho_perm(int* permutation, persona** aux_nodi, int i, int j, int npersone);
void HeapSort_rho_perm(int* permutation, persona** aux_nodi, int npersone);

/* Stampe */
void Stampa_ordine_eta(persona** aux_nodi, int npersone);
void Stampa_ordine_rho(int* permutation, persona** aux_nodi, int npersone);


#endif