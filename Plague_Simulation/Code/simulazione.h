#ifndef __simulazione_h
#define __simulazione_h
#include <stdlib.h>
#include <stdio.h>
#include "strutture.h"

/* Alloca la matrice di simulazione npersone x T */
void alloca_mat_sim(char** mat_simulation[], int npersone, int T);
/* La setta con un carattere arbitrario ('N' nel nostro caso) */
void set_mat_sim(char** mat_simulation, int npersone, int T);

/* Alloca il primo elemento dell'ospedale (è ausiliario, non una persona) */
void first_ospedale(ospedale* FIRST[]);

/* Funzione che azzera i pesi degli archi di chi finisce in quarantena o in ospedale */
void azzera_contatti(amici* friends, persona** aux_nodi, int index_whose);

/* Funzione che aggiunge una persona direttamente in ospedale senza passare dalla quarantena (serve per il giorno zero) */
void add_hosp_direct(ospedale* FIRST, int index, int* posti_liberi, int* controllo);
/* Funzione che aggiunge una persona dalla quarantena all'ospedale */
void add_hosp_from_quarantine(ospedale* FIRST, int index, int* posti_liberi, int* controllo, int* len_quarantena);
/* Rimuove una persona dall'ospedale */
void rem_hosp(ospedale* nodo_prec, int* posti_liberi, int* controllo);

/* Traduce il valore di controllo in un carattere da mettere nella mat_simulation */
char traduci_carattere(int codice);

/* Gestisce il giorno zero */
void day_zero(int npersone, int g, persona** aux_nodi, int* controllo, int* permutation, ospedale* FIRST, amici* friends, int* posti_liberi, int* len_quarantena, int* contagiati, int* ricoverati, int* in_attesa);
/* Gestisce uno qualsiasi degli altri giorni */
void day(int npersone, int g, int r, char** mat_simulation, persona** aux_nodi, int* controllo, int* permutation, ospedale* FIRST, amici* friends, int* posti_liberi, int* len_quarantena, int t, int* contagiati, int* ricoverati, int* in_attesa, int* giorni_degenza, int* giorni_quarantena);

/* Stampe */
void stampa_sim(persona** aux_nodi, int* permutation, char** mat_simulation, int npersone, int T);
void stampa_statistiche(int contagiati, int ricoverati, int rimasti, int individui_attesa, int giorni_degenza, int giorni_quarantena, float giorni_attesa);

/* Libera l'ospedale distruggendo la lista */
void del_ospedale(ospedale* FIRST, int* posti_liberi);

#endif