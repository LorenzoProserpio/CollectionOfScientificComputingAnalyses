/* Direttive */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "strutture.h"
#include "gfileerr.h"
#include "heapsort.h"
#include "grafi.h"
#include "cammini.h"
#include "simulazione.h"

/* Main */

int main(int argc, char* argv[]){
		
	/* Dichiarazioni Variabili*/
	int npersone = 0, T = 0, g = 0, gmax = 0, r = 0, i = 0;
	int n_cc = 0;
	int contagiati = 0, ricoverati = 0, rimasti = 0, individui_attesa = 0, giorni_degenza = 0, giorni_quarantena = 0;
	int posti_liberi = 0, len_quarantena = 0;
	float giorni_attesa = 0.;
	char riga[1000];	
	persona* person = NULL;	
	persona** aux_nodi = NULL;
	FILE* fp = NULL;
	amici* friends = NULL;
	int* controllo = NULL;
	int** matpath = NULL;
	int coppiamax[2] = {0,0};
	int* permutation_rho = NULL;
	int* permutation_alf = NULL;	
	char** mat_simulation = NULL;
	ospedale* FIRST = NULL;	
	
	/* Apre il file */
	error_command_line(argc, argv);
	fp = fopen(argv[1], "r");	
	if(fp == NULL){
		fprintf(stderr, "Errore nell'apertura del file!");
		exit(EXIT_FAILURE);
	}	
	/* Carica i parametri */
	carica_par(fp, riga, &npersone, &T, &g, &gmax, &r);	
	posti_liberi = r;
	/* Carica la popolazione */
	alloca_person(&person, &aux_nodi, npersone);
	carica_pop(fp, riga, npersone, person, gmax, g);	
	/* Prepara vettore ausiliario nodi*/
	set_nodi(aux_nodi, person, npersone);
	alloca_permutation(&permutation_alf, &permutation_rho, npersone);
	set_permutation(permutation_alf, permutation_rho, npersone);	
			
	/* Ordina e stampa per eta' */
	HeapSort_eta(aux_nodi, npersone);
	Parita_salute(aux_nodi, npersone);
	Parita_alfabetico_salute(aux_nodi, npersone);
	Stampa_ordine_eta(aux_nodi, npersone);
	set_nodi(aux_nodi, person, npersone);
	
	/* Ordina e stampa per rho */
	HeapSort_rho_perm(permutation_rho, aux_nodi, npersone);
	Parita_alfabetico_rho(permutation_rho, aux_nodi, npersone);
	Stampa_ordine_rho(permutation_rho, aux_nodi, npersone);	
	
	/* Riavvolge il file*/
	rewind(fp);	
	/* Alloca lo spazio necessario per il grafo */
	alloca_friends(&friends, npersone);
	for(i = 0; i < npersone; i++){
		alloca_who(&(friends[i].who), &(friends[i].frequenza), (*(aux_nodi[i])).n_amici);
	}
	/* Carica amici e frequenze */
	fgets(riga, 999, fp);
	for(i = 0; i < npersone; i++){
		friends[i].whose = aux_nodi[i];
		fgets(riga, 999, fp);
		carica_who(fp, riga, npersone, i, aux_nodi, friends[i].who, friends[i].frequenza);
	}
	/* Chiude il file */
	fclose(fp);	
	
	/* Alloca e inizializza a zero il vettore per marcare */
	alloca_controllo(&controllo, npersone);
	/* Calcola la componenti connesse e stampa*/
	n_cc = componenti_connesse(friends, aux_nodi, controllo, npersone);
	printf("%d gruppi\n", n_cc);
	carica_stampa_cc(aux_nodi, controllo, n_cc, npersone);
	free(controllo);
	
	/* Cammini minimi */
	alloca_matpath(&matpath, npersone);
	load_matpath(friends, matpath, npersone);
	stampa_matpath(aux_nodi, matpath, npersone, coppiamax);
	for(i = 0; i < npersone; i++){
		free(matpath[i]);
	}
	free(matpath);
	
	/* Allocazioni necessarie per simulazione */	
	alloca_mat_sim(&mat_simulation, npersone, T);
	set_mat_sim(mat_simulation, npersone, T);	
 	alloca_controllo(&controllo, npersone);
	first_ospedale(&FIRST);
	FIRST -> who = -1;
	FIRST -> next = NULL;
	
	/* Simulazione */
	
	/* Giorno zero */
	day_zero(npersone, g, aux_nodi, controllo, permutation_rho, FIRST, friends, &posti_liberi, &len_quarantena, &contagiati, &ricoverati, &individui_attesa);
	for(i = 0; i < T; i++){
		day(npersone, g, r, mat_simulation, aux_nodi, controllo, permutation_rho,  FIRST, friends, &posti_liberi, &len_quarantena, i, &contagiati, &ricoverati, &individui_attesa, &giorni_degenza, &giorni_quarantena);
	}	
	
	/* Gli altri giorni */
	for(i = 0; i < npersone; i++){
		if(mat_simulation[i][T-1] != '.'){
			rimasti++;
		}
	}
	if(individui_attesa != 0){
		giorni_attesa = (float) giorni_quarantena / individui_attesa; 
	}
	
	/* Stampa dei risultati e delle statistiche*/
	HeapSort_alfabetico_perm(permutation_alf, aux_nodi, npersone);
	stampa_sim(aux_nodi, permutation_alf, mat_simulation, npersone, T);	
	stampa_statistiche(contagiati, ricoverati, rimasti, individui_attesa, giorni_degenza, giorni_quarantena, giorni_attesa);
	
	/* Free & exit*/
	free(person);
	free(aux_nodi);
	for(i = 0; i < npersone; i++){
		free(friends[i].who);
		free(friends[i].frequenza);
		free(mat_simulation[i]);
	}
	free(friends);
	free(mat_simulation);
	free(permutation_alf);
	free(permutation_rho);
	free(controllo);
	while(posti_liberi != r){
		del_ospedale(FIRST, &posti_liberi);
	}
	free(FIRST);	
	
	exit(0);
}








		
