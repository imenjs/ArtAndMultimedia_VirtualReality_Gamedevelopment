#include <stdio.h>
#include <stdlib.h>
#include "tirageAleatoire.h"
#include "croisementIndividus.h"
#include "accouplementIndividus.h"


void accouplement(long* population1, long nbVille, long nbIndividu, long meilleurIndiv, long moitieIndiv,long  *classementDistances, long *population2){

long debutCroisement=-1;
long largeurCroisement=-1;
long maman,papa,fille=moitieIndiv, fils=moitieIndiv+1 ;
int i,j;

//Nombre d'individus à créer afin de réétablir le nombre fixé au paramétrage.
long indivACreer=nbIndividu-moitieIndiv;

/*
On met de coté l'indice du meilleur individu afin de la préserver.
*meilleurIndiv=*(classementDistances+nbIndividu-1)
*/


	//Tant qu'on a un nombre plus de deux individus à créer.
	for (i=0;i<(indivACreer/2);i++){

		//random de la valeur d'indice de début ; comprise entre 1 et (nbVilles-2).
		debutCroisement=tirageAlea(nbVille-3)+1;

		//random de la largeur de croisement.
		largeurCroisement=tirageAlea(nbVille-debutCroisement)+1;

		//répartition des individus parents en couples.
		//Tirage aléatoire des parents utilisés pour effectuer le croisement.
		do{
	
			maman = tirageAlea(moitieIndiv-1);
			papa  = tirageAlea(moitieIndiv-1);       

		}while(maman==papa);

#ifdef DBUG
	printf("\nLancement de l'operateur de croisement :\n");
	printf("itération %i - Maman : %ld ; Papa : %ld ; Fille : %ld ; Fils : %ld \n",i,maman,papa,fille,fils);
	printf("itération %i - Début du croisement : %ld ; Largeur du croisement : %ld.\n",i,debutCroisement, 			largeurCroisement);
#endif

		//Appelle a la procedure croisement.
		croisement(maman,papa,fille,fils,debutCroisement,largeurCroisement,nbVille,nbIndividu,&(*population2));

		//Incrémentation de l'indice des enfants dans la population 2 pour la prochaine itération.
		fils += 2;
		fille += 2;	}


	//Si indivACreer est impaire, on rajoute le dernier individu.
	//Nous choisirons de recopier notre meilleur individu à l'emplacement vide.
	if ((indivACreer%2) != 0){
		for(i=0;i<nbVille;i++){
			*(population2+((nbIndividu-1)*nbVille+i)) = *(population1+((meilleurIndiv*nbVille)+i));
		}
	}

#ifdef DBUG
	printf("\nNombre d'individus a creer : %ld.\n", indivACreer);
	printf("Meilleur individu : indice %ld de la population 1.\n", meilleurIndiv);
	printf("\nPopulation d'individus 2 :\n");
	for (i=0;i<nbIndividu;i++){
		printf(" Individu %i: ",i);
		for (j=0;j<nbVille;j++){
			printf("\t%ld",*(population2+i*nbVille+j));
		}
		printf("\n");
	}
#endif
}
