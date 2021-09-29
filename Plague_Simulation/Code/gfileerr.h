#ifndef __gfileerr_h
#define __gfileerr_h
#include <stdlib.h>
#include <stdio.h>
#include "strutture.h"

/* Gestione errori linea di comando */
void error_command_line(int argc, char *argv[]);

/* Carica la prima riga del file con i parametri */
void carica_par(FILE* fp, char* riga, int* npersone, int* T, int* g, int* gmax, int* r);

/* Alloca e carica il database delle persone e dei nodi visti come indirizzi */
void alloca_person(persona* person[],persona** aux_nodi[],int npersone);
void carica_pop(FILE* fp, char* riga, int npersone, persona* person, int gmax, int g);

/* Mette i nodi nello stesso ordine del database  */
void set_nodi(persona** aux_nodi, persona* person, int npersone);

#endif