#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligneCommande.h"


void analyseLigneCommande(int argc, char** argv, char** nomFichier, long* startNode, long* maxComputationTime, double* maxCost){

int i;

	if(argc < 3){

		fprintf(stderr,"\nErreur : Nombre invalide d'arguments\n");
		fprintf(stderr,"Usage : %s char* char* char* [char* char*] [char* char*] [char* char*] \n\n",argv[0]);
	}else{

		if(strcmp(argv[1],"-f") == 0){
			*nomFichier = argv[2];
		}


		switch (argc){

			case 5:{
				if(strcmp(argv[3],"-t") == 0){
					*maxComputationTime = atol(argv[4]);
				}else if(strcmp(argv[3],"-c")==0){
					*maxCost = atof(argv[4]);
				}else if(strcmp(argv[3],"-s")==0){
					*startNode = atol(argv[4]);
				}
				break;
			}

			case 7:{
				for(i=3;i<=5;i++){
					if(strcmp(argv[i],"-t")==0){
						*maxComputationTime = atol(argv[i+1]);
					}else if(strcmp(argv[i],"-c")==0){
						*maxCost = atof(argv[i+1]);
					}else if(strcmp(argv[i],"-s")==0){
						*startNode = atol(argv[i+1]);
					}
				}
				break;
			}

			case 9:{
				for(i=3;i<=7;i++){
					if(strcmp(argv[i],"-t")==0){
						*maxComputationTime = atol(argv[i+1]);
					}else if(strcmp(argv[i],"-c")==0){
						*maxCost = atof(argv[i+1]);
					}else if(strcmp(argv[i],"-s")==0){
						*startNode = atol(argv[i+1]);
					}
				}
				break;
			}
		}
	}
}
