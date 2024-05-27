#include <stdio.h>
#include <stdlib.h>
#include "mutationIndividus.h"
#include "tirageAleatoire.h"


void mutationIndividu(long *population2, double tauxMutation, long nbVille, long nbIndividu, long meilleurIndiv){

long i,j,villeMut1,villeMut2,villeTemp;
long nbIndividuAMuter=(tauxMutation*nbIndividu);
long indiceAMuter[nbIndividuAMuter];


#ifdef DBUG
	printf("\nTaux de mutation : %lf\nNombre Individus : %ld\n", tauxMutation, nbIndividu);
	printf("Nombre de villes a muter : %ld\n\n", nbIndividuAMuter);
#endif

	for(i=0;i<nbIndividuAMuter;i++){

		do{
		    indiceAMuter[i]=tirageAlea(nbIndividuAMuter);
#ifdef DBUG
		    printf("i=%ld ; Indice a muter : %ld\n", i, indiceAMuter[i]);
#endif
		}while(indiceAMuter[i]==meilleurIndiv);
	}



	for(i=0;i<nbIndividuAMuter;i++){
		do{
			villeMut1=(tirageAlea((nbVille)));
			villeMut2=(tirageAlea((nbVille)));
#ifdef DBUG
			printf("%ld - ville-mut1= %ld - ville-mut2= %ld\n", i, villeMut1, villeMut2);
#endif
		}while((villeMut1==villeMut2) &&(villeMut1=0) || (villeMut2=0));
	}
}
