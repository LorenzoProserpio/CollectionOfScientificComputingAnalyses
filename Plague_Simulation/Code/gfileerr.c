#include <string.h>
#include "gfileerr.h"

/* Gestione errori linea di comando */
void error_command_line (int argc, char *argv[]){
  if (argc != 2)
  {
    fprintf(stderr,"Errore nella linea di comando!\n");
    exit(EXIT_FAILURE);
  }
}

/* Carica la prima riga del file con i parametri e si assicura non ci siano errori*/
void carica_par(FILE* fp, char* riga, int* npersone, int* T, int* g, int* gmax, int* r){
	fgets(riga, 999, fp);
	if(sscanf(riga, "%d %d %d %d %d", npersone, T, g, gmax, r) < 5){
		fprintf(stderr, "Errore nella lettura dei parametri!");
		exit(EXIT_FAILURE);
	}
	if(npersone == 0){
		fprintf(stdout, "Ho gia' finito...");
		exit(0);
	}
}

/* Alloca lo spazio per il database e per i nodi visti come indirizzi  */
void alloca_person(persona* person[], persona** aux_nodi[], int npersone){	
	*person = (persona*) malloc(npersone * sizeof(persona));
	if(*person == NULL){
		free(*person);
		fprintf(stderr, "Errore di allocazione della memoria!");
		exit(EXIT_FAILURE);
	}
	
	*aux_nodi = (persona**) calloc(npersone, sizeof(persona*));
	if(*aux_nodi == NULL){
		free(*aux_nodi);
		fprintf(stderr, "Errore di allocazione della memoria!");
		exit(EXIT_FAILURE);
	}
}

/* Legge il file caricando le persone e i rispettivi dati e completa i campi della struct persona calcolando rho e recovery time */
void carica_pop(FILE* fp, char* riga, int npersone, persona* person, int gmax, int g){
	int i = 0;
	
	while(fgets(riga, 999, fp) != NULL || i < npersone){
		if(sscanf(riga, "%s %d %f %d %d", person[i].nome, &(person[i].eta), &(person[i].salute), &(person[i].infect_time), &(person[i].n_amici)) < 5){
			fprintf(stderr, "Errore nella lettura della %d riga!", i+1);
			exit(EXIT_FAILURE);
		}	
		person[i].rho = frho(person[i].eta,person[i].salute);	
		person[i].rec_time = gmax*(1 - person[i].rho) + g + 1;
		i++;
	}
	
}

/* Setta i nodi nello stesso ordine del database */
void set_nodi(persona** aux_nodi, persona* person, int npersone){
	int i;
	for(i = 0; i < npersone; i++){
		aux_nodi[i] = &(person[i]);
	}
}




