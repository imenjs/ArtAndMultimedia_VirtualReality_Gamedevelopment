#include <stdio.h>
#include <stdlib.h>
#include "classerDistances.h"


void classerDistances(double* distancesIndividus,long nbIndividu,long *classementDistances){

int i, j;
double maxTemp=0;
long indiceTemp=0;
//Tableau de vérification des distances déjà classées.
int verifDoublon[nbIndividu];

	//Initialisation des tableaux de classement et de vérification à 0.
	for(i=0;i<nbIndividu;i++){
		classementDistances[i]=0;
	}
	for(i=0;i<nbIndividu;i++){
		verifDoublon[i]=0;
	}

	for(i=0;i<nbIndividu;i++){
		for(j=0;j<nbIndividu;j++){
			if((distancesIndividus[j]>=maxTemp) && (verifDoublon[j]!=1)){
				maxTemp=distancesIndividus[j];
				indiceTemp=j;
			}
		}
		classementDistances[i]=indiceTemp;
		verifDoublon[indiceTemp]=1; 
		maxTemp=0;
		indiceTemp=0;
	}

#ifdef DBUG
printf("\nDistances classees par ordre decroissant :\n");
printf("(dernier chiffre correspond à l'indice de l'individu dans la population 1).\n\n");
for(i=0;i<nbIndividu;i++){
	printf("Individu %i : %lf - %ld\n", i, distancesIndividus[classementDistances[i]], classementDistances[i]);
}
#endif

}
