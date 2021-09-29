#include "strutture.h"
#include <math.h>

/* Calcola rho */
float frho(int eta, float salute){
	return salute*pow((1.-eta/100.),3.);
}