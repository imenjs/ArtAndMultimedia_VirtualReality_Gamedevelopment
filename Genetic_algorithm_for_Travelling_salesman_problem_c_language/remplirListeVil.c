#include <stdio.h>
#include <stdlib.h>
#include"remplirListeVil.h"


liste remplirListeVille(char* nomFichier,liste vil,long *nbVille){

char ligne[100];
char mot[30];
int i=0;
long tampon_1;
double tampon_2,tampon_3;

//Pointeur sur le fichier geoFile.
FILE *geoFile;

	if((geoFile = fopen(nomFichier,"r")) == NULL){
		fprintf(stderr,"Erreur lors de l'ouverture du fichier : %s\n",nomFichier);
	}else{
		while(fgets(ligne,sizeof ligne,geoFile) != NULL){

			fscanf(geoFile,"%s",mot);
			if(strcmp(mot,"NODE_COORD_SECTION")==0){
				fgets(ligne,sizeof ligne,geoFile);
				while(*ligne != 'E'){
					fscanf(geoFile,"%ld %lf %lf",&tampon_1,&tampon_2,&tampon_3);
					vil = ajouterEnFin(vil,tampon_1,tampon_2,tampon_3);
					i++;
					fgets(ligne,sizeof ligne,geoFile);
				}
				*nbVille = i-1;
				vil = supprimerElementEnFin(vil);
				break;
			}
		}
	}
	fclose(geoFile);
return vil;
}
