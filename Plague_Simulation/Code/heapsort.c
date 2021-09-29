#include "heapsort.h"
#include "strutture.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* Alloca i due vettori in cui tenere traccia delle permutazioni rho e alfabetica (la seconda servirà per la parte di simulazione) */
void alloca_permutation(int* permutation[], int* permutation2[], int npersone){
	*permutation = (int*) calloc(npersone, sizeof(int));
	*permutation2 = (int*) calloc(npersone, sizeof(int));
	if(*permutation == NULL || *permutation2 == NULL ){
		free(*permutation);
		free(*permutation2);
		fprintf(stderr, "Errore nell'allocazione di permutation!");
		exit(EXIT_FAILURE);
	}
}

/* Inizializza con ordinamento naturale i vettori delle permutazioni */
void set_permutation(int* permutation, int* permutation2, int npersone){
	int i = 0;
	for(; i < npersone; i++){
		permutation[i] = i;
		permutation2[i] = i;
	}
}

/* Funzione di scambio di interi */
void Swap_int(int* permutation, int i, int j){
	int aux = permutation[i];
	permutation[i] = permutation[j];
	permutation[j] = aux;
}
/* Funzione di scambio di puntatori a struct persona */
void Swap(persona** aux_nodi, int i, int j){
	persona* aux = aux_nodi[i];
	aux_nodi[i] = aux_nodi[j];
	aux_nodi[j] = aux;
}

/* Heapsort eta' */

void Aggiorna_heap_eta(persona** aux_nodi, int i, int j, int npersone){
	int k;
	int index = 2*i;
	if(index == j && (*(aux_nodi[i])).eta > (*(aux_nodi[j])).eta){
		Swap(aux_nodi, i, j);
	}
	if(index < j){
		if((*(aux_nodi[index])).eta < (*(aux_nodi[index+1])).eta){
			k = index;
		} else {
			k = index + 1;
		}
		if((*(aux_nodi[i])).eta > (*(aux_nodi[k])).eta){
			Swap(aux_nodi, i, k);
			Aggiorna_heap_eta(aux_nodi, k, j, npersone);
		}
	}
}

void HeapSort_eta(persona** aux_nodi, int npersone){
	int j = 0, i = 0;
	j = npersone-1;
	i = floor(j/2);
	for(; i >= 0; i--){
		Aggiorna_heap_eta(aux_nodi, i, j, npersone);
	}
	for(i = j; i >= 1; i--){
		Swap(aux_nodi, 0, i);
		Aggiorna_heap_eta(aux_nodi, 0, i-1, npersone);
	}
}

/* Heapsort salute */

void Aggiorna_heap_salute(persona** aux_nodi, int i, int j, int npersone){
	int k;
	int index = 2*i;
	if(index == j && (*(aux_nodi[i])).salute < (*(aux_nodi[j])).salute){
		Swap(aux_nodi, i, j);
	}
	if(index < j){
		if((*(aux_nodi[index])).salute > (*(aux_nodi[index+1])).salute){
			k = index;
		} else {
			k = index + 1;
		}
		if((*(aux_nodi[i])).salute < (*(aux_nodi[k])).salute){
			Swap(aux_nodi, i, k);
			Aggiorna_heap_salute(aux_nodi, k, j, npersone);
		}
	}
}

void HeapSort_salute(persona** aux_nodi, int npersone){
	int j = 0, i = 0;
	j = npersone-1;
	i = floor(j/2);
	for(; i >= 0; i--){
		Aggiorna_heap_salute(aux_nodi, i, j, npersone);
	}
	for(i = j; i >= 1; i--){
		Swap(aux_nodi, 0, i);
		Aggiorna_heap_salute(aux_nodi, 0, i-1, npersone);
	}
}

/* Parita' eta' */

void Parita_salute(persona** aux_nodi, int npersone){
	int i = 0, from = 0, len = 1;
	for(; i < npersone - 1; i++){
		if((*(aux_nodi[i])).eta == (*(aux_nodi[i+1])).eta){
			from = i;
			len++;
			i++;
			while(i < npersone-1 && (*(aux_nodi[i])).eta == (*(aux_nodi[i+1])).eta){
				len++;
				i++;
			}
		}
		HeapSort_salute(&(aux_nodi[from]),len);
		from = 0;
		len = 1;		
	}
}

/* Heapsort alfabetico */

void Aggiorna_heap_alfabetico(persona** aux_nodi, int i, int j, int npersone){
	int k;
	int index = 2*i;
	if(index == j && strcmp((*(aux_nodi[i])).nome,(*(aux_nodi[j])).nome) < 0){
		Swap(aux_nodi, i, j);
	}
	if(index < j){
		if(strcmp((*(aux_nodi[index])).nome,(*(aux_nodi[index+1])).nome) > 0){
			k = index;
		} else {
			k = index + 1;
		}
		if(strcmp((*(aux_nodi[i])).nome,(*(aux_nodi[k])).nome) < 0){
			Swap(aux_nodi, i, k);
			Aggiorna_heap_alfabetico(aux_nodi, k, j, npersone);
		}
	}
}

void HeapSort_alfabetico(persona** aux_nodi, int npersone){
	int j = 0, i = 0;
	j = npersone-1;
	i = floor(j/2);
	for(; i >= 0; i--){
		Aggiorna_heap_alfabetico(aux_nodi, i, j, npersone);
	}
	for(i = j; i >= 1; i--){
		Swap(aux_nodi, 0, i);
		Aggiorna_heap_alfabetico(aux_nodi, 0, i-1, npersone);
	}
}

/* Parita' alfabetico */

void Parita_alfabetico_salute(persona** aux_nodi, int npersone){
	int i = 0, from = 0, len = 1;
	for(; i < npersone - 1; i++){
		if((*(aux_nodi[i])).salute == (*(aux_nodi[i+1])).salute && (*(aux_nodi[i])).eta == (*(aux_nodi[i+1])).eta){
			from = i;
			len++;
			i++;
			while(i < npersone-1 && (*(aux_nodi[i])).salute == (*(aux_nodi[i+1])).salute && (*(aux_nodi[i])).eta == (*(aux_nodi[i+1])).eta){
				len++;
				i++;
			}
		}
		HeapSort_alfabetico(&(aux_nodi[from]), len);
		from = 0;
		len = 1;		
	}
}

/* Heapsort alfabetico permutazioni (stesso heapsort di prima, ma stavolta non scambio i nodi ma gli indici del vettore di permutazione) */

void Aggiorna_heap_alfabetico_perm(int* permutation, persona** aux_nodi, int i, int j, int npersone){
	int k;
	int index = 2*i;
	if(index == j && strcmp((*(aux_nodi[(permutation[i])])).nome,(*(aux_nodi[(permutation[j])])).nome) < 0){
		Swap_int(permutation, i, j);
	}
	if(index < j){
		if(strcmp((*(aux_nodi[(permutation[index])])).nome,(*(aux_nodi[(permutation[index+1])])).nome) > 0){
			k = index;
		} else {
			k = index + 1;
		}
		if(strcmp((*(aux_nodi[(permutation[i])])).nome,(*(aux_nodi[(permutation[k])])).nome) < 0){
			Swap_int(permutation, i, k);
			Aggiorna_heap_alfabetico_perm(permutation, aux_nodi, k, j, npersone);
		}
	}
}

void HeapSort_alfabetico_perm(int* permutation, persona** aux_nodi, int npersone){
	int j = 0, i = 0;
	j = npersone-1;
	i = floor(j/2);
	for(; i >= 0; i--){
		Aggiorna_heap_alfabetico_perm(permutation, aux_nodi, i, j, npersone);
	}
	for(i = j; i >= 1; i--){
		Swap_int(permutation, 0, i);
		Aggiorna_heap_alfabetico_perm(permutation, aux_nodi, 0, i-1, npersone);
	}
}

/* Parita' rho */

void Parita_alfabetico_rho(int* permutation, persona** aux_nodi, int npersone){
	int i = 0, from = 0, len = 1;
	for(; i < npersone - 1; i++){
		if((*(aux_nodi[permutation[i]])).rho == (*(aux_nodi[permutation[i+1]])).rho){
			from = i;
			len++;
			i++;
			while(i < npersone-1 && ((*(aux_nodi[permutation[i]])).rho == (*(aux_nodi[permutation[i+1]])).rho)){
				len++;
				i++;
			}
		}
		HeapSort_alfabetico_perm(&(permutation[from]), aux_nodi, len);
		from = 0;
		len = 1;		
	}
}

/* Heapsort rho tenendo traccia delle permutazioni */

void Aggiorna_heap_rho_perm(int* permutation, persona** aux_nodi, int i, int j, int npersone){
	int k;
	int index = 2*i;
	if(index == j && (*(aux_nodi[(permutation[i])])).rho < (*(aux_nodi[(permutation[j])])).rho){
		Swap_int(permutation, i, j);
	}
	if(index < j){
		if((*(aux_nodi[(permutation[index])])).rho > (*(aux_nodi[(permutation[index+1])])).rho){
			k = index;
		} else {
			k = index + 1;
		}
		if((*(aux_nodi[(permutation[i])])).rho < (*(aux_nodi[(permutation[k])])).rho){
			Swap_int(permutation, i, k);
			Aggiorna_heap_rho_perm(permutation, aux_nodi, k, j, npersone);
		}
	}
}

void HeapSort_rho_perm(int* permutation, persona** aux_nodi, int npersone){
	int j = 0, i = 0;
	j = npersone-1;
	i = floor(j/2);
	for(; i >= 0; i--){
		Aggiorna_heap_rho_perm(permutation, aux_nodi, i, j, npersone);
	}
	for(i = j; i >= 1; i--){
		Swap_int(permutation, 0, i);
		Aggiorna_heap_rho_perm(permutation, aux_nodi, 0, i-1, npersone);
	}
}

/* Stampe */

void Stampa_ordine_eta(persona** aux_nodi, int npersone){
	int i = 0;
	printf("Ordine per eta':\n");
	for(; i < npersone; i++){
		printf("%s %d %1.3f\n",(*(aux_nodi[i])).nome, (*(aux_nodi[i])).eta, (*(aux_nodi[i])).salute);
	}
}

void Stampa_ordine_rho(int* permutation, persona** aux_nodi, int npersone){
	int i = 0;
	printf("Ordine per refrattarieta':\n");
	for(; i < npersone; i++){
		printf("%s %1.3f\n",(*(aux_nodi[permutation[i]])).nome, (*(aux_nodi[permutation[i]])).rho);
	}
}




