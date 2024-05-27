#include "tirageAleatoire.h"
#include <stdlib.h>

//Une graine pour randomiser correctement et avoir des valeur toujours differentes
int graineRandom = 0;

int tirageAlea(long valeurMax){
int resultat;

    //On fabrique une nouvelle graine pour le tirage au sort
    srand(graineRandom += time(NULL));
    //On soustrait 1 à nbVilles car le tableu démarre à 0.
    resultat=((rand()+1)%(valeurMax--));

return resultat;
}
