#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "remplirListeVil.h"
#include "matriceDistances.h"
#include "algorithmeGenetique.h"
#include "ligneCommande.h"
#include "enregistrementSolution.h"



int main(int argc,char* argv[]){

		/********************* déclaration des différent variable et tableaux **************************/

//les options de notre outil qui sont passe comme paramètre sur la ligne de commande.
long startNode = 1;
long maxComputationTime = 1;
double maxCost = 10;
char* nomFichier=NULL;

//liste chainée contient les villes(num,x,y).
liste vil=NULL;
long nbVille=0;
int i,j;

//matrice distance entre les différents villes.
double** matDistance = NULL;

//le cout trouvé par l'algorithme génétique et le tableau solution contient le chemin.
long *solutionCourante, *solutionOptimale;
double coutSolutionCourante, coutOptimale;

//variable utilisé pour calculer le temps d'execution.
clock_t start,end;
double temps;

		/********************* appelle des différent fonction et procédure **************************/



	//Bienvenu
	printf("\n Bienvenue, cher utilisateur !!!\n");
	printf(" Recherche du chemin en cours ...\n");


	//Analyser la ligne de commande.
	analyseLigneCommande(argc, argv, &nomFichier, &startNode, &maxComputationTime, &maxCost);

#ifdef DBUG
printf("\n--->startNode: %ld,\n--->maxComputationTime: %ld,\n--->maxCost: %lf,	\n",startNode,maxComputationTime,maxCost);
#endif


	//Allocation d'une liste de Ville et la remplir avec les coors des villes, et déduire le nombre de ville.
	vil = remplirListeVille(nomFichier, vil, &nbVille);

#ifdef DBUG
	printf("\n le nb des ville est : %ld\n",nbVille);
#endif


	//Afficher la liste des villes.
#ifdef DBUG
	afficherListe(vil);
#endif



	//Allocation de la matrice des distances entre les villes.
	matDistance = (double**)malloc((nbVille)*sizeof(double*));
	for(i=0;i<nbVille;i++)
	{
		matDistance[i] = (double*)calloc((nbVille),sizeof(double));
	}



	//Calcule de les distances entre les villes et les stoké ds le matrice.
	matDistance = calculMatriceDistance(matDistance, vil, nbVille);



	//liberer la liste
	free(vil);



	//Allocation de la tableau ou on va stocké la solution.
	solutionCourante = (long*)malloc(nbVille*sizeof(long));
	solutionOptimale = (long*)malloc(nbVille*sizeof(long));
	//Initialisation du coutOptimale  et solutionOptimale.
	coutOptimale = genetiqueAlgo(startNode,matDistance, &(*solutionCourante), nbVille);
	for(i=0;i<nbVille;i++){
		solutionOptimale[i] = solutionCourante[i];
	}



	//Appel de l'algorithme génétique.
	do{

		start = clock();

			coutSolutionCourante = genetiqueAlgo(startNode,matDistance, &(*solutionCourante), nbVille);

		end = clock();
		temps += (((double) end-start) / CLOCKS_PER_SEC);

		if(coutSolutionCourante < coutOptimale){
			coutOptimale = coutSolutionCourante;
			for(i=0;i<nbVille;i++){
				solutionOptimale[i] = solutionCourante[i];
			}
		}

#ifdef ANALYSE
printf("\n%lf",temps);
printf("\n%lf",coutSolutionCourante);
#endif

	}while((temps < maxComputationTime) && (coutSolutionCourante > maxCost));



//Enregistrer la solution dans un fichier (.tour).
enregistrerSolution(coutOptimale,nbVille,solutionOptimale,maxComputationTime,temps,startNode,maxCost,nomFichier,argv,argc);


#ifdef DBUG
	printf("\n ------------> cout de la solution courante : %lf \n",coutSolution);
#endif
printf("\n Merci d'utilisé notre application.\n\n");

return 0;
}
