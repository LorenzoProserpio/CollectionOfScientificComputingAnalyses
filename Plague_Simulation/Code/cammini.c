#include "cammini.h"
#include <stdlib.h>
#include <string.h>

/* Serve per l'algoritmo dei cammini minimi, come sostituto a piu' infinito */
#define HUGE (10000)

/* Valuta se esiste tale arco nel grafo */
bool is_edge(amici* friends, int index_nodi, int index_amici){
	int i = 0;
	for(; i < (*((friends[index_nodi]).whose)).n_amici ; i++){
		if(index_amici == ((friends[index_nodi]).who)[i]){
			return TRUE;
		}
	}
	return FALSE;
}

/* Trova il minimo tra due interi */
int min(int cammino_1, int cammino_2){
	if(cammino_1 <= cammino_2)
		return cammino_1;
	return cammino_2;
}

/* Alloca la matrice dei cammini minimi */
void alloca_matpath(int** matpath[], int npersone){
	int i = 0;
	*matpath = (int**) calloc(npersone, sizeof(int*));
	if(*matpath == NULL){
		fprintf(stderr, "Errore di allocazione nella matrice dei cammini!");
		exit(EXIT_FAILURE);
	}
	for(; i < npersone; i++){
		(*matpath)[i] = (int*) calloc(npersone, sizeof(int));
		if((*matpath)[i] == NULL){
			fprintf(stderr, "Errore di allocazione nella matrice dei cammini!");
			exit(EXIT_FAILURE);
		}
	}
}

/* Algoritmo per trovare i cammini minimi senza tener traccia dei predecessori */
void load_matpath(amici* friends, int** matpath, int npersone){
	int i = 0, j = 0, k = 0;
	
	for(i = 0; i < npersone; i++){
		for(j = 0; j < npersone; j++){
			if(i == j){
				matpath[i][j] = 0;
			} else if(is_edge(friends, i, j) == TRUE){
				matpath[i][j] = 1;
			} else{
				matpath[i][j] = HUGE;
			}
		}
	}
	
	for(k = 0; k < npersone; k++){
		for(i = 0; i < npersone; i++){
			for(j = 0; j < npersone; j++){
				if((matpath[i][k]+matpath[k][j]) < matpath[i][j]){
					matpath[i][j] = matpath[i][k]+matpath[k][j];
				}
			}
		}
	}
}

/* Ordina in modo alfabetico una coppia */
void ordina_coppia(int* coppia, persona** aux_nodi, int i, int j){
	if(strcmp((*(aux_nodi[i])).nome,(*(aux_nodi[j])).nome) < 0){
		coppia[0] = i;
		coppia[1] = j;
 	} else {
		coppia[0] = j;
		coppia[1] = i;
	}
}

/* Ricerca del cammino di lunghezza massima con le caratteristiche richieste, funziona semplicemente confrontando una coppiaaux per volta con la coppiamax corrente, e valuta se sostituirla con la coppiamax, ritorna la lunghezza del cammino massimo */
int maxpath(persona** aux_nodi, int** matpath, int npersone, int* coppiamax){
	int i = 0, j = 0, maxlength = 0;
	int coppiaaux[2] = {0,0};
	
	for(i = 0; i < npersone; i++){
		for(j = i; j < npersone; j++){
			if(matpath[i][j] >= maxlength){
				if(matpath[i][j] == maxlength){
					coppiaaux[0] = i;
					coppiaaux[1] = j;
					ordina_coppia(coppiaaux, aux_nodi, i, j);
					/* Valuta se coppiaaux viene prima di coppiamax in ordine alfabetico */
					if(strcmp((*(aux_nodi[(coppiaaux[0])])).nome,(*(aux_nodi[(coppiamax[0])])).nome) <= 0){
						if(strcmp((*(aux_nodi[(coppiaaux[0])])).nome,(*(aux_nodi[(coppiamax[0])])).nome) == 0){
							if(strcmp((*(aux_nodi[(coppiaaux[1])])).nome,(*(aux_nodi[(coppiamax[1])])).nome) < 0){
								coppiamax[0] = coppiaaux[0];
								coppiamax[1] = coppiaaux[1];
							}
						} else{
							coppiamax[0] = coppiaaux[0];
							coppiamax[1] = coppiaaux[1];
						}
					}  
				} else{
					maxlength = matpath[i][j];
					coppiamax[0] = i;
					coppiamax[1] = j;
					ordina_coppia(coppiamax, aux_nodi, i, j);
				}
			}
		}
	}
	
	return maxlength;
}

/* Stampa della coppia trovata in precedenza */
void stampa_matpath(persona** aux_nodi, int** matpath, int npersone, int* coppiamax){
	printf("%d giorni: ", maxpath(aux_nodi, matpath, npersone, coppiamax));
	printf("%s %s\n", (*(aux_nodi[(coppiamax[0])])).nome,(*(aux_nodi[(coppiamax[1])])).nome);
}