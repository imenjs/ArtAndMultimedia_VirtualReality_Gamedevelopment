#include <stdio.h>
#include <stdlib.h>
#include "moitierIndividus.h"

void moitieIndividu(long nbIndividu, long *moitieIndiv){


	(*moitieIndiv)=nbIndividu/2;
	//Si l'nbIndividu est impair, on garde la moitié + 1.
	if(nbIndividu%2!=0){
		(*moitieIndiv)++;
	}
#ifdef DBUG
	printf("\nLes %ld meilleur individis de la population precedente.\n", (*moitieIndiv));
#endif
}
