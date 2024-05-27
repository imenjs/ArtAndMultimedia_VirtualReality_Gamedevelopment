#include <stdio.h>
#include <stdlib.h>
#include "croisementIndividus.h"


void croisement(long maman, long papa, long fille, long fils, long debutCroisement, long largeurCroisement, long nbVille,  												long nbIndividu, long *population2){

long i, j, k, l;
long villeDouble;

if(population2 != 0){

	//On commence par copier les gênes des parents dans les cellules de leurs enfants.
	for(i=0 ; i<nbVille ; i++){
		//Dabord la maman offre ses gènes à sa fille (galanterie oblige)
		*(population2+(fille*nbVille)+i) = *(population2+(maman*nbVille)+i);
		//Puis papa en fait de même avec son fils (tel père tel fils !)
		*(population2+fils*nbVille+i) = *(population2+papa*nbVille+i);
	}


#ifdef DBUG
	printf("\n papa et maman ont donnes leurs genes :\n");
	for (i=0;i<nbIndividu;i++){
		printf(" Individu %i: ",i);
		for (j=0;j<nbVille;j++){
			printf("\t%ld",*(population2+i*nbVille+j));
		}
		printf("\n");
	}
#endif


	//On opère ensuite au croisement des gènes.
	for (i=debutCroisement ; i<(debutCroisement+largeurCroisement) ; i++){
		*(population2+fille*nbVille+i)=*(population2+papa*nbVille+i);
		*(population2+fils*nbVille+i)=*(population2+maman*nbVille+i);
	}



#ifdef DBUG
	printf("\n\nPopulation d'individus 2 croises :\n");
	for (i=0;i<nbIndividu;i++){
		printf(" Individu %i: ",i);
		for (j=0;j<nbVille;j++){
			printf("\t%ld",*(population2+i*nbVille+j));
		}
		printf("\n");
	}
#endif


	//On recherche les villes en double et on les remplace par celles manquantes.
	for(i=debutCroisement ; i<(debutCroisement+largeurCroisement) ; i++){
		for(j=0 ; j<nbVille ; j++){
			if((*(population2+fils*nbVille+i)==*(population2+fils*nbVille+j))&&((j<debutCroisement)||(j>=(debutCroisement+largeurCroisement)))){
				for(k=debutCroisement ; k<(debutCroisement+largeurCroisement) ; k++){
					for(l=0 ; l<nbVille ; l++){
						if(((*(population2+fille*nbVille+k))==(*(population2+fille*nbVille+l)) ) && ((l<debutCroisement) || (l>=(debutCroisement+largeurCroisement)))){
							 villeDouble=*(population2+fille*nbVille+l);
							 *(population2+fille*nbVille+l)=*(population2+fils*nbVille+j);
							 *(population2+fils*nbVille+j)=villeDouble;
						}
					}
				}
			}
		}
	}


#ifdef DBUG
	printf("\n\nPopulation d'individus 2 croisee :\n");
	for (i=0;i<nbIndividu;i++){
		printf(" Individu %i: ",i);
		for (j=0;j<nbVille;j++){
			printf("\t%ld",*(population2+i*nbVille+j));
		}
		printf("\n");
	}
#endif

}else{
#ifdef DBUG
	printf("matrice vide !!!");    
#endif
}
}
