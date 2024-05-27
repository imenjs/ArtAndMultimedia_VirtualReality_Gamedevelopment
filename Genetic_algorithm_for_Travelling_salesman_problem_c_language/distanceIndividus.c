//distance.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "distanceIndividus.h"

void attrapeDistance(double** matDistance,long *population1,long nbVille,long nbIndividu,double* distancesIndividus){

double aux;
int i,j;

	//Initialisation des distances à 0.0 (double).
	for (i=0;i<nbIndividu;i++){
		distancesIndividus[i]=0.0;
	}


	for(i=0;i<nbIndividu;i++){
        //Calcul de la distance de la ville de départ à la dernière ville.
	        for(j=1;j<nbVille;j++){
			aux = matDistance[*(population1+i*nbVille+j-1)][*(population1+i*nbVille+j)];
			distancesIndividus[i] += aux;
		}
			aux = matDistance[*(population1+i*nbVille+(nbVille-1))][*(population1+i*nbVille)];
			distancesIndividus[i] += aux;
	}


#ifdef DBUG
	printf("\nCalcul des distances des individus de la population 1 :\n\n");
	for (i=0 ; i<nbIndividu ; i++){
		printf("Distance individu %i : %lf\n", i, distancesIndividus[i]);
	}
#endif
    
}
