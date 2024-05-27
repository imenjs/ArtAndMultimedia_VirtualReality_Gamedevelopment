#include <stdio.h>
#include <stdlib.h>
#include "creationIndividus.h"
#include "algorithmeGenetique.h"
#include "distanceIndividus.h"
#include "classerDistances.h"
#include "meilleurIndividu.h"
#include "methodeSelection.h"
#include "accouplementIndividus.h"
#include "mutationIndividus.h"


double genetiqueAlgo(long startNode, double** matDistance, long* solutionCourante, long nbVille){

		/********************* déclaration des différent variable et tableaux **************************/

long vDepart = startNode-1;
long moitieIndiv=-1;
long meilleurIndiv;
int i,j;

//En provenance des paramètres de l'algorithme.
//nbIndividu doit etre <nbIndividu<infini et paire --> paire = Modulo-4.
long nbIndividu = 10;   //nbIndividu --> PAIR
double tauxMutation=0.5;

//La population sera un tableau à 2dim de taille [nbIndividu][nbVilles].
long population1[nbIndividu][nbVille];
long population2[nbIndividu][nbVille];

//Tableau contenant les distances des individus.
double distancesIndividus[nbIndividu];

//Tableau contenant les indices des individus classés par ordre décroissant.
long classementDistances[nbIndividu];

// indiceIndividu : c'est l'indice du meileur individu (qui a le meilleur cout) dans la matrice population.
long indiceIndiv;


		/********************* appelle des différent fonction et procédure **************************/


	//Création des individus.
	creerIndividus(vDepart, nbVille, nbIndividu, *population1);


	//attraper la distance apartir de la matrice des distances.
	attrapeDistance(matDistance, *population1, nbVille, nbIndividu, distancesIndividus);


	//Classement des distances par ordre décroissant.
	classerDistances(distancesIndividus, nbIndividu, classementDistances);


	//Stockage de l'indice du meilleur individu.
	meilleurIndividu(classementDistances, nbIndividu, &meilleurIndiv);


	//Calcul de la moitié des individus.
	moitieIndividu(nbIndividu, &moitieIndiv);


        //Selection par la méthode élitiste.
        selectionElitiste(*population1, nbVille, nbIndividu, moitieIndiv, classementDistances, *population2);


	//Croisement des individus dans la population 2.
	accouplement(*population1, nbVille, nbIndividu, meilleurIndiv, moitieIndiv, classementDistances, *population2);


	//attraper la distance apartir de la matrice des distances.
	attrapeDistance(matDistance, *population2, nbVille, nbIndividu, distancesIndividus);


	//Classement des distances par ordre décroissant.
	classerDistances(distancesIndividus, nbIndividu, classementDistances);


	//Stockage de l'indice du meilleur individu.
	meilleurIndividu(classementDistances, nbIndividu, &meilleurIndiv);


	//Mutation des individus de la population 2.
	mutationIndividu(*population2, tauxMutation, nbVille, nbIndividu, meilleurIndiv);


	//attraper la distance apartir de la matrice des distances.
	attrapeDistance(matDistance, *population2, nbVille, nbIndividu, distancesIndividus);


	//Classement des distances des individus de la poulation 2.
	classerDistances(distancesIndividus, nbIndividu, classementDistances);


	//Remplir le tableau solutionCourante .
	indiceIndiv = classementDistances[nbIndividu-1];
	for(i=0;i<nbVille;i++){
		*(solutionCourante+i) = population2[indiceIndiv][i];
	}


return distancesIndividus[classementDistances[nbIndividu-1]];
}
