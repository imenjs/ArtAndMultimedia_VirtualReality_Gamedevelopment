#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methodeSelection.h"

void selectionElitiste(long *population1, long nbVille, long nbIndividu, long moitieIndiv, long *classementDistances, long *population2){

int i, j;

	//On place La mailleure moitié des individus dans la population 2.
	for (i=0;i<moitieIndiv;i++){
		for (j=0;j<nbVille;j++){
		       *(population2+(i*nbVille)+(j)) = *(population1+((*(classementDistances+(moitieIndiv)+i))*nbVille)+j);
		       //printf("\t%ld",*(population2+(i*nbVille)+(j)));
		}
		//printf("\n");
	}

	//On remplit les individus suivants avec -1.
	for (i=moitieIndiv;i<nbIndividu;i++){
		for (j=0;j<nbVille;j++){
			*(population2+i*nbVille+j)=-1;
		}
	}


	//Affichage de la Population2 d'individus 2 après selection elististe.
#ifdef DBUG
	printf("\n\n******* Population2 d'individus 2, après selection elitiste ********\n\n");
	for (i=0;i<nbIndividu;i++){
		printf(" Individu %i: ",i);
		for (j=0;j<nbVille;j++){
			printf("\t%i",*(population2+i*nbVille+j));
		}
		printf("\n");
	}
#endif
}
