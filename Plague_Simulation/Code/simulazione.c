#include "simulazione.h"
#include <string.h>
#include <math.h>

/* Alloca la matrice di simulazione npersone x T */
void alloca_mat_sim(char** mat_simulation[], int npersone, int T){
	int i = 0;
	*mat_simulation = (char**) malloc(npersone*sizeof(char*));
	if(*mat_simulation == NULL){
		free(*mat_simulation);
		fprintf(stderr, "Errore nell'allocazione della mat_simulation!");
		exit(EXIT_FAILURE);
	}
	for(; i < npersone; i++){
		(*mat_simulation)[i] = (char*) malloc(T*sizeof(char));
		if((*mat_simulation)[i] == NULL){
			fprintf(stderr, "Errore nell'allocazione della mat_simulation!");
			for(i = 0; i < npersone; i++){
				free(*(mat_simulation[i]));
			}
			free(*mat_simulation);
			exit(EXIT_FAILURE);
		}
	}
}
/* La setta con un carattere arbitrario ('N' nel nostro caso) */
void set_mat_sim(char** mat_simulation, int npersone, int T){
	int i = 0, j = 0;
	for(i = 0; i < npersone; i++){
		for(j = 0; j < T; j++){
			mat_simulation[i][j] = 'N';
		}
	}
}

/* Alloca il primo elemento dell'ospedale (è ausiliario, non una persona) */
void first_ospedale(ospedale* FIRST[]){
	*FIRST = (ospedale*) malloc(sizeof(ospedale));
	if(*FIRST == NULL){
		fprintf(stderr, "Errore allocazione FIRST!");
		free(*FIRST);
		exit(EXIT_FAILURE);
	}
}


/* Funzione che azzera i pesi degli archi di chi finisce in quarantena o in ospedale (azzera anche il peso degli archi dei suoi amici rispetto a lui)*/
void azzera_contatti(amici* friends, persona** aux_nodi, int index_whose){
	int i = 0, j = 0, index = 0;
	for(; i < (*(aux_nodi[index_whose])).n_amici; i++){
		((friends[index_whose]).frequenza)[i] = 0;
		index = ((friends[index_whose]).who)[i];
		for(j = 0; j < (*(aux_nodi[index])).n_amici; j++){
			if(((friends[index]).who)[j] == index_whose){
				((friends[index]).frequenza)[j] = 0;
			}
		}
	}
}

/* Funzione che aggiunge una persona direttamente in ospedale senza passare dalla quarantena (serve per il giorno zero) */
void add_hosp_direct(ospedale* FIRST, int index, int* posti_liberi, int* controllo){
	ospedale* add = NULL;
	add = (ospedale*) malloc(sizeof(ospedale));
	if(add == NULL){
		fprintf(stderr, "Errore allocazione ospedale!");
		free(add);
		exit(EXIT_FAILURE);
	}
	add -> who = index;
	add -> next = FIRST -> next;
	FIRST -> next = add;
	controllo[index] = 3;
	(*posti_liberi) --;
}
/* Funzione che aggiunge una persona dalla quarantena all'ospedale */
void add_hosp_from_quarantine(ospedale* FIRST, int index, int* posti_liberi, int* controllo, int* len_quarantena){
	ospedale* add = NULL;
	add = (ospedale*) malloc(sizeof(ospedale));
	if(add == NULL){
		fprintf(stderr, "Errore allocazione ospedale!");
		free(add);
		exit(EXIT_FAILURE);
	}
	add -> who = index;
	add -> next = FIRST -> next;
	FIRST -> next = add;
	controllo[index] = 3;
	(*posti_liberi) --;
	(*len_quarantena) --;
}
/* Rimuove una persona dall'ospedale sapendo l'indirizzo dell'elemento precedente che punta all'elemento che vogliamo eliminare */
void rem_hosp(ospedale* nodo_prec, int* posti_liberi, int* controllo){
	int index = (nodo_prec -> next) -> who;
	ospedale* rem = nodo_prec -> next;
	nodo_prec -> next = (nodo_prec -> next) -> next;
	free(rem);
	controllo[index] = 4;
	(*posti_liberi)++;
}

/* Traduce il valore di controllo in un carattere da mettere nella mat_simulation, i valori di controllo 4 e 5 stampano comunque un puntino */
char traduci_carattere(int codice){
	switch(codice){
		case 0:
			return '.';
		case 1:
			return 'I';
		case 2:
			return 'Q';
		case 3: 
			return 'O';
	}
	return '.';
}

/* Gestisce il giorno zero */
void day_zero(int npersone, int g, persona** aux_nodi, int* controllo, int* permutation, ospedale* FIRST, amici* friends, int* posti_liberi, int* len_quarantena, int* contagiati, int* ricoverati, int* in_attesa){
	int i = 0;
	for(i = 0; i < npersone; i++){
		if(((aux_nodi[permutation[i]]) -> infect_time) > g && ((aux_nodi[permutation[i]]) -> infect_time) <= ((aux_nodi[permutation[i]]) -> rec_time)){
			if(*(posti_liberi) > 0){
				/* Se ci sono posti liberi manda la persona direttamente in ospedale e azzera i contatti */
				add_hosp_direct(FIRST, permutation[i], posti_liberi, controllo);
				azzera_contatti(friends, aux_nodi, permutation[i]);
				(*ricoverati)++;
			} else{
				/* Altrimenti manda in quarantena e azzera i contatti */
				controllo[permutation[i]] = 2;
				azzera_contatti(friends, aux_nodi, permutation[i]);
				(*len_quarantena)++;
				(*in_attesa)++;
			}
		} else if(((aux_nodi[permutation[i]]) -> infect_time) > ((aux_nodi[permutation[i]]) -> rec_time)){
			/* Controlla lo strano caso in cui una persona all'inizio dell'orizzonte temporale sia già guarita (non credo nei file di prova possa succedere qualcosa del genere) */
			controllo[permutation[i]] = 4;
			azzera_contatti(friends, aux_nodi, permutation[i]);
			((aux_nodi[permutation[i]]) -> infect_time) = 0;
		} else if(((aux_nodi[permutation[i]]) -> infect_time) <= g && ((aux_nodi[permutation[i]]) -> infect_time) > 0){
			/* Altrimenti mette la persona infetta non rilevata */
			controllo[permutation[i]] = 1;
			(*contagiati)++;
		}
	}	
}

/* Gestisce uno qualsiasi degli altri giorni */
void day(int npersone, int g, int r, char** mat_simulation, persona** aux_nodi, int* controllo, int* permutation, ospedale* FIRST, amici* friends, int* posti_liberi, int* len_quarantena, int t, int* contagiati, int* ricoverati, int* in_attesa, int* giorni_degenza, int* giorni_quarantena){
	
	int i = 0, j = 0, index = 0, index2 = 0;
	float sommafij = 0;
	ospedale* aux = FIRST;
	
	/* Controlla le persone in ospedale e fa progredire il tempo, rimuovendo chi è guarito */
	while((aux -> next) != NULL && r - *(posti_liberi) > 0){
		index = (aux -> next) -> who;
		((aux_nodi[index]) -> infect_time) += 2;
		if(((aux_nodi[index]) -> infect_time) > ((aux_nodi[index]) -> rec_time)){
			rem_hosp(aux, posti_liberi, controllo);
			((aux_nodi[index]) -> infect_time) = 0; 
		} else {
			aux = aux -> next;
			(*giorni_degenza) ++;
		}
		
	} 
	
	i = 0;
	
	/* Gestisce chi guarisce dalla quarantena, chi entra degli infetti non rilevati in quarantena e gli individui infettati il giorno precedente che iniziano ad essere infetti non rilevati da oggi */
	for(i = 0; i < npersone; i++){
		if(controllo[i] == 2){
			(*giorni_quarantena)++;
			aux_nodi[i] -> infect_time += 1;
			if(((aux_nodi[i]) -> infect_time) > ((aux_nodi[i]) -> rec_time)){
				controllo[i] = 4;
				len_quarantena--;
				aux_nodi[i] -> infect_time = 0;
			} 
		} else if(controllo[i] == 1){
			aux_nodi[i] -> infect_time += 1;
			if(((aux_nodi[i]) -> infect_time) > g){
				azzera_contatti(friends, aux_nodi, i);
				controllo[i] = 2;
			}
		} else if(controllo[i] == 5){
			controllo[i] = 1;
			aux_nodi[i] -> infect_time += 1;
		}
		
	}
	
	i = 0;
	
	/* Manda in ospedale gli individui della quarantena ordinati (siccome li visito in ordine permutation_rho) in base ai posti disponibili */
	while(*(posti_liberi) > 0 && i < npersone){
		index = permutation[i];
		if(controllo[index] == 2){
			add_hosp_from_quarantine(FIRST, index, posti_liberi, controllo, len_quarantena);
			(*giorni_degenza) ++;
			(*ricoverati)++;
		}
		i++;
	}
	
	i = 0;
	
	for(i = 0; i < npersone; i++){
		/* Le persone sane frequentano i loro amici e nel caso si ammalano, ma risultano infette non rilevate dal giorno successivo, per quello temporaneamente il loro controllo viene posto uguale a 5, nella giornata successiva sara' impostato su 1 */
		sommafij = 0;
		index = permutation[i];
		if(controllo[index] == 0){
			for(j = 0; j < ((aux_nodi[index]) -> n_amici); j++){
				index2 = (friends[index].who) [j];
				if(controllo[index2] == 1){
					sommafij += (friends[index].frequenza) [j];
				}				
			}
			if(sommafij > ((aux_nodi[index]) -> rho)){
				controllo[index] = 5;
				(*contagiati)++;
			}
			index2 = 0;
		} 	
		
		/* Carica i controlli della giornata nella matrice e calcola gli individui in attesa */
		mat_simulation[index][t] = traduci_carattere(controllo[index]);
		if(t > 1 && mat_simulation[index][t] == 'Q' && mat_simulation[index][t-1] == 'I'){
			(*in_attesa)++;
		}
	}	
	
}

/* Stampe */
void stampa_sim(persona** aux_nodi, int* permutation,char** mat_simulation, int npersone, int T){
	int i = 0, j = 0;
	for(i = 0; i < npersone; i++){
		printf("%-15s", (*(aux_nodi[permutation[i]])).nome);
		for(j = 0; j < T; j++){
			printf("%c", mat_simulation[permutation[i]][j]);
		}
		printf("\n");
	}
}

void stampa_statistiche(int contagiati, int ricoverati, int rimasti, int individui_attesa, int giorni_degenza, int giorni_quarantena, float giorni_attesa){
	printf("%d contagiati\n", contagiati);
	printf("%d ricoverati\n", ricoverati);
	printf("%d rimasti\n", rimasti);
	printf("%d individui in attesa\n", individui_attesa);
	printf("%d giorni di degenza\n", giorni_degenza);
	printf("%d giorni di quarantena\n", giorni_quarantena);
	if(giorni_attesa != 0){
		printf("%1.3f giorni in attesa\n", giorni_attesa);
	}
}

/* Libera l'ospedale distruggendo la lista */
void del_ospedale(ospedale* FIRST, int* posti_liberi){
	ospedale* rem = FIRST -> next;
	FIRST -> next = (FIRST -> next) -> next;
	free(rem);
	(*posti_liberi)++;
}