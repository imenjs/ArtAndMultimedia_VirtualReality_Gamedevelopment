#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creationIndividus.h"
#include "tirageAleatoire.h"

void creerIndividus(long vDepart, long nbVille, long nbIndividu, long *population1){

int i,j,tempVerif;
//Tableau où l'on mettra 1 si la ville a déja été positionnée.
long verifDoublon[nbIndividu][nbVille];


	//Initialisation du tableau de vérifications à 0.
	for (i=0;i<nbIndividu;i++){
		for (j=0;j<nbVille;j++){
			verifDoublon[i][j]=0;
		}
	}


	//On place la ville de départ en première position de l'individu.
	for (i=0 ; i<nbIndividu ; i++){
		*(population1+i*nbVille)=vDepart;
		verifDoublon[i][vDepart]=1;
	}


	//Tirage aléatoire des villes suivantes des individus.
	for (i=0 ; i<nbIndividu ; i++){
		for (j=1 ; j<nbVille ; j++){

			do{
				tempVerif = tirageAlea(nbVille);
			}while(verifDoublon[i][tempVerif]!=0);

			*(population1+i*nbVille+j)=tempVerif;            
			verifDoublon[i][tempVerif]=1;
		}
	}


	//Affichage de la Population1 d'individus 1.
#ifdef DBUG
	printf("*************** Population1 d'individus 1 *************** :\n\n");
	for (i=0 ; i<nbIndividu ; i++){
		printf(" Individu %i: ",i);
		for (j=0 ; j<nbVille ; j++){
			printf("\t%i",*(population1+i*nbVille+j));
		}
		printf("\n");
	}
#endif

}
