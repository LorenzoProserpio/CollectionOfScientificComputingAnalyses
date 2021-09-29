#include <string.h>
#include "strutture.h"
#include "heapsort.h"

/* Alloca righe del grafo (che sono i nodi)*/
void alloca_friends(amici* friends[], int npersone){
	*friends = (amici*) calloc(npersone, sizeof(amici));
	if(*friends == NULL){
		free(*friends);
		fprintf(stderr, "Errore di allocazione della memoria per gli amici whose!");
		exit(EXIT_FAILURE);
	}    
}

/* Alloca vettore di adiacenza e vettore pesi */
void alloca_who(int* who[], float* frequenza[], int n_amici){
	*who = (int*) calloc(n_amici, sizeof(int));
	if(*who == NULL){
		free(*who);
		fprintf(stderr, "Errore di allocazione della stringa who!");
		exit(EXIT_FAILURE);
	}
	*frequenza = (float*) calloc(n_amici, sizeof(float));
	if(*frequenza == NULL){
		free(*frequenza);
		fprintf(stderr, "Errore di allocazione della stringa who!");
		exit(EXIT_FAILURE);
	}
}

/* Funzioni ausiliarie per gestire l'input da file correttamente */
/* Cambia la stringa di formato per la sscanf */
void alloca_formato(char* formato[]){
	*formato = (char*) malloc(1000 * sizeof(char));
	if(*formato == NULL){
		free(*formato);
		fprintf(stderr, "Errore di allocazione della stringa formato!");
		exit(EXIT_FAILURE);
	}
}
/* Flusha le parti già lette in precedenza dalla fgets */
void flush_amici(char* formato, int n_amici){
	int i;
	strcpy(formato,"%*s %*d %*f %*d %*d ");
	for(i = 0; i < n_amici; i++){
		strcat(formato, "%*s %*f ");
	}
	strcat(formato, "%s %f");
}

/* Funzione che dato il nome associa l'indirizzo del nodo nel vettore di indirizzi */
int cerca_nome(char* name, persona** aux_nodi, int npersone){
	int i = 0;
	for(; i < npersone; i++){
		if(strcmp(name, (*aux_nodi[i]).nome) == 0){
			return i;
		}
	}
	return -1;
}

/* Carica il grafo da file come forward star */
void carica_who(FILE* fp, char* riga, int npersone, int index, persona** aux_nodi, int* who, float* frequenza){
	int i = 0;
	char temp[15];
	char* formato = NULL;
	for(; i < ((*(aux_nodi[index])).n_amici); i++){
		alloca_formato(&formato);
		flush_amici(formato, i);
		sscanf(riga, formato, temp, &(frequenza[i]));		
		who[i] = cerca_nome(temp, aux_nodi, npersone);
		free(formato);
	}
}

/* Alloca il vettore ausiliario per le componenti connesse, che poi verrà usato ancora in fase di simulazione con altro scopo */
void alloca_controllo(int* controllo[], int npersone){
	*controllo = (int*) calloc(npersone, sizeof(int));
	if(*controllo == NULL){
		free(*controllo);
		fprintf(stderr, "Errore di allocazione del vettore di controllo!");
		exit(EXIT_FAILURE);
	}
}

/* Funzione ausiliaria per trovare il massimo tra due float */
float massimo(float rho1, float rho2){
	if(rho1 < rho2)
		return rho2;
	return rho1;
}

/* Visita del grafo in profondità */
void visita_amici(amici sorgente, amici* friends, persona** aux_nodi, int* controllo, int marcatore){
	int max = (*(sorgente.whose)).n_amici;
	int index = 0;
	int i = 0;
	for(; i < max; i++){
		index = (sorgente.who)[i];
		if(controllo[index] == 0 && (sorgente.frequenza)[i] >= massimo((*(sorgente.whose)).rho, (*(aux_nodi[index])).rho)){
			controllo[index] = marcatore;
			visita_amici(friends[index], friends, aux_nodi, controllo, marcatore);
		}
	}
}

/* Calcolo delle componenti connesse usando la visita in profondità, restituisce il numero di componenti connesse */
int componenti_connesse(amici* friends, persona** aux_nodi, int* controllo, int npersone){
	int marcatore = 1;
	int i = 0;
	for(; i < npersone; i++){
		if(controllo[i] == 0){
			controllo[i] = marcatore;
			visita_amici(friends[i], friends, aux_nodi, controllo, marcatore);
			marcatore++;
		}
	}
	return --marcatore;
}

/* Stampa delle componenti connesse in ordine alfabetico usando heapsort e salvandole temporaneamente come grafo forward star*/
void carica_stampa_cc(persona** aux_nodi, int* controllo, int n_cc, int npersone){
	int i = 0, j = 0, index = 0;
	int* len = NULL;
	int* lencpy = NULL;
	persona*** cc = NULL;
	persona** first = NULL;
	
	len = (int*) calloc(n_cc, sizeof(int));
	lencpy = (int*) calloc(n_cc, sizeof(int));
	cc = (persona***) calloc(n_cc, sizeof(persona**));
	first = (persona**) calloc(n_cc, sizeof(persona*));
	
	if(cc == NULL || len == NULL || lencpy == NULL){
		fprintf(stderr, "Errore in carica_stampa_cc!");
		free(cc);
		free(len);
		free(lencpy);
		free(first);
		exit(EXIT_FAILURE);
	}
	
	for(; i < npersone; i++){
		len[(controllo[i]-1)]++;
		lencpy[(controllo[i]-1)]++;
	}
	
	for(i = 0; i < n_cc; i++){
		cc[i] = (persona**) calloc(len[i], sizeof(persona*));
		if(cc[i] == NULL){
			fprintf(stderr, "Errore in carica_stampa_cc!");
			for(j = 0; j < i; j++){
				free(cc[i]);
			}
			exit(EXIT_FAILURE);
		}
	}
	
	for(i = 0; i < npersone; i++){
		index = (controllo[i]) - 1;
		(cc[index])[lencpy[index] - 1] = aux_nodi[i];
		lencpy[index]--;		
	}
	
	for(i = 0; i < n_cc; i++){
		HeapSort_alfabetico(cc[i], len[i]);
	}	
	for(i = 0; i < n_cc; i++){
		first[i] = cc[i][0];
	}	
	HeapSort_alfabetico(first, n_cc);
	
	index = 0;
	
	for(i = 0; i < n_cc; i++){
		index = cerca_nome((*(first[i])).nome, aux_nodi, npersone);
		index = controllo[index] - 1;
		for(j = 0; j < len[index]; j++){
			printf("%s ", (*((cc[index])[j])).nome);
		}
		printf("\n");
	}
	
	for(i = 0; i < n_cc; i++){
		free(cc[i]);
	}
	free(cc);
	free(first);
	free(len);
	free(lencpy);
}