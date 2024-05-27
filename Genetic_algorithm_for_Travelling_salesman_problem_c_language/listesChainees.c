#include<stdio.h>
#include<stdlib.h>
#include"listesChainees.h"

liste ajouterEnFin(liste L, long num,double x,double y){

	liste nouvListe=NULL;
	nouvListe=(liste)malloc(sizeof(ville));
	nouvListe->num = num;
	nouvListe->x = x;
	nouvListe->y = y;
	nouvListe->suivant = NULL;
	liste p = L;

	if(L == NULL){
		L = nouvListe;
	}else{
		while (p->suivant != NULL){
			p = p->suivant;
		}
		p->suivant = nouvListe;
	}
return L;
}


liste supprimerElementEnFin(liste L){

	if(L != NULL){
		liste p;
		liste q;
		liste Li;
		p = L;
		q = L;
		while(p->suivant != NULL){
			q = p;
			p = p->suivant;
		}

		q->suivant = NULL;
		free(p);
	}
return L;
}


void afficherListe(liste L){
	liste p;
	p = L;
	while(p != NULL){
		printf("\n%d %6.6f %6.6f\n",p->num,p->x,p->y);
		p = p->suivant;
	}
}
