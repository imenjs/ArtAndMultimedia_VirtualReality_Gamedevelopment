#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "enregistrementSolution.h"



int enregistrerSolution(double coutOptimale, long nbVille, long* solutionOptimale,long maxComputationTime,long temps,long startNode,double maxCost,char* nomFichier,char** argv,int argc){


char ligne[100],mot[50];
int i=0;
char* idInstance;

FILE* fileIn;
FILE* fileOut;

// *p, *res : des pointeur auxilière utiliser pour passer
char *sortie, *p, *res, *nomF; 
char *chaine=".tour";// extension de notre fichier (.tour)
char *optAppXXX="appXXXXXXXXXX";//chaine qu'on va l'ajouter au nom du fichier avec le cout du solution.

//des pointeur sur chaine oû en va sauvgarder les convertion (Float --> String), en a réservé pour ce la (10 case).
char convertString[10], convertVille[10],*convertMaxComputation, convertMaxCost[20]="NOT_AVAILABLE";
char convertStartNod[20]="NOT_AVAILABLE";

//convertMaxComputation2 : pointeur qui prend pour valeur la fonction (convertirTempString).
char* convertMaxComputation2;

char* type="TYPE : TOUR\n";  			    // ligne 2 ds le fichier a créer
char* dimension="DIMENSION :";			   // ligne 3 ds le fichier a créer
char* maxComputation="\nMAX_COMPUTATION_TIME : "; // ligne 4 ds le fichier a créer
char* computationTime="\nCOMPUTATION_TIME : ";   // ligne 5 ds le fichier a créer
char* maxCostli="\nMAX_COST : "; 		// ligne 6 ds le fichier a créer
char* costli="\nCOST : "; 	               // ligne 7 ds le fichier a créer
char* startNod="\nSTART_NODE : "; 	      // ligne 8 ds le fichier a créer





      // création du nom du fichier pour l'enregistrement

	nomF = nomFichier;
	sortie = (char*)malloc(strlen(nomFichier)*sizeof(char));
	for(i=0;i<strlen(nomFichier);i++){
		sortie[i] = nomF[i];
	}

#ifdef DBUG
printf("\n----------> le nom sans extension : %s\n",sortie);
#endif

	res = (char*)malloc((strlen(sortie) + 10 + strlen(chaine)) * sizeof(char));
	p = res;
	for(i=0;i<(strlen(nomFichier)-4);i++){
		*p++ = sortie[i];
	}

	// convertir le coutOptimale en chaine (gcvt) pour l'intégré ds le nom du fichier.
	gcvt(round(coutOptimale),15,convertString);

#ifdef DBUG
printf("\n----------> coutOptimale en formatage string : %s\n",convertString);
#endif

	// ajouter la partie (opt ou appXXX) au nom du fichier.
	if((temps<maxComputationTime) || (coutOptimale<maxCost)){
		optAppXXX=".opt";
		for(i=0;i<strlen(optAppXXX);i++){
			*p++ = optAppXXX[i];
		}
	}else{
		optAppXXX = ".app";
		for(i=0;i<strlen(optAppXXX);i++){
			*p++ = optAppXXX[i];
		}
		//optAppXXX = convertString;
		for(i=0;i<strlen(convertString);i++){
			*p++ = convertString[i];
		}
	}
	
	// ajouter l'extension du fichier (.tour)
	for(i=0;i<strlen(chaine);i++){
		*p++ = chaine[i];
	}
	*p++ = '\0';  // c'est pour arrété le pointeur.
	sortie = res;


#ifdef DBUG
printf("---------> concatenation des partie du nom de fichier : %s\n",sortie);
#endif


	      /********************** ouvrir le fichier (.tsp) pour copier la 1 ère ligne ********************/

	if((fileIn = fopen(nomFichier,"r")) == NULL){
		fprintf(stderr,"\n erreur lors de l'ouverture du fichier : %s\n",nomFichier);
		return(EXIT_FAILURE);
	}else{
		while(fgets(ligne,sizeof ligne,fileIn) != NULL){

			idInstance = ligne;
			break;
		}
	}
	fclose(fileIn);

#ifdef DBUG
printf("\n------------> la 1 ére ligne --> %s\n",idInstance);
#endif

		/***************************** enregistrement du fichier **********************************/

	if((fileOut = fopen(sortie,"w")) == NULL){

		fprintf(stderr,"\n erreur lors de l'ouverture du fichier : %s\n",sortie);
		return(EXIT_FAILURE);
	}else{


		/************************  1 ere ligne du fichier  *****************************/
		fputs(idInstance,fileOut);

		/************************  2 ere ligne du fichier  *****************************/
		fputs(type,fileOut);


		/************************  3 ere ligne du fichier  *****************************/
		res = (char*)malloc((strlen(dimension) + 10) * sizeof(char));
		p=res;
		gcvt(nbVille,10,convertVille);
		for(i=0;i<strlen(dimension);i++){
			*p++ = dimension[i];
		}
		for(i=0;i<strlen(convertVille);i++){
			*p++ = convertVille[i];
		}
		dimension=res;
		fputs(dimension,fileOut);


		/************************  4 ere ligne du fichier  *****************************/
		res = (char*)malloc((strlen(maxComputation) + 10) * sizeof(char));
		p=res;
		int test=0;

		for(i=0;i<argc;i++){
			if(strcmp(argv[i],"-t") == 0){
				//convertMaxComputation2 : pointeur qui prend pour valeur la fonction (convertirTempString).
				convertMaxComputation2 = (char*)malloc(20 * sizeof(char));
				convertMaxComputation2 = convertirTempString(maxComputationTime);
				test=1;
			}
		}
		if(test == 0){
			convertMaxComputation2 = (char*)malloc(20 * sizeof(char));
			convertMaxComputation2 = "NOT_AVAILABLE";
		}
		for(i=0;i<strlen(maxComputation);i++){
			*p++ = maxComputation[i];
		}
		for(i=0;i<strlen(convertMaxComputation2);i++){
			*p++ = convertMaxComputation2[i];
		}
		maxComputation=res;
		fputs(maxComputation,fileOut);


		/************************  5 ere ligne du fichier  *****************************/
		res = (char*)malloc((strlen(computationTime) + 10) * sizeof(char));
		p=res;
		for(i=0;i<strlen(computationTime);i++){
			*p++ = computationTime[i];
		}
		convertMaxComputation2 = convertirTempString(temps);
		for(i=0;i<strlen(convertMaxComputation2);i++){
			*p++ = convertMaxComputation2[i];
		}
		computationTime=res;
		fputs(computationTime,fileOut);


		/************************  6 ere ligne du fichier  *****************************/
		res = (char*)malloc((strlen(maxCostli) + 10) * sizeof(char));
		p=res;

		for(i=0;i<argc;i++){
			if(strcmp(argv[i],"-c") == 0){
				gcvt(maxCost,10,convertMaxCost);
			}
		}
		for(i=0;i<strlen(maxCostli);i++){
			*p++ = maxCostli[i];
		}
		for(i=0;i<strlen(convertMaxCost);i++){
			*p++ = convertMaxCost[i];
		}
		maxCostli=res;
		fputs(maxCostli,fileOut);


		/************************  7 ere ligne du fichier  *****************************/
		res = (char*)malloc((strlen(costli) + 10) * sizeof(char));
		p=res;
		for(i=0;i<strlen(costli);i++){
			*p++ = costli[i];
		}
		gcvt(coutOptimale,10,convertMaxCost);
		for(i=0;i<strlen(convertMaxCost);i++){
			*p++ = convertMaxCost[i];
		}
		maxCostli=res;
		fputs(maxCostli,fileOut);


		/************************  8 ere ligne du fichier  *****************************/
		res = (char*)malloc((strlen(startNod) + 10) * sizeof(char));
		p=res;

		for(i=0;i<argc;i++){
			if(strcmp(argv[i],"-s") == 0){
				gcvt(startNode,10,convertStartNod);
			}
		}
		for(i=0;i<strlen(startNod);i++){
			*p++ = startNod[i];
		}
		for(i=0;i<strlen(convertStartNod);i++){
			*p++ = convertStartNod[i];
		}
		startNod=res;
		fputs(startNod,fileOut);


		/************************  9 ere ligne du fichier  *****************************/
		fputs("\nTOUR_SECTION\n",fileOut);


		/************************  i ème ligne du fichier  *****************************/
		char solutionCC[10],*retour=" \n";
		for(i=0;i<nbVille;i++){
			gcvt(solutionOptimale[i]+1,10,solutionCC);
			fputs(solutionCC,fileOut);
			fputs(retour,fileOut);
		}


		/************************  N ème ligne du fichier  *****************************/
		fputs("EOF",fileOut);


	}
	fclose(fileOut);
return(EXIT_SUCCESS);
}




//**************************** fonction pour traduire le temps on mode textuelle *************************************/


char* convertirTempString(long seconde){

char *h,*m,*s,*resConvert, convertMaxComputation[10],convertMaxComputation2[10],convertMaxComputation3[10];
char *p1,*res;
int i;


	if(seconde < 60){
		h="00h00mn";s="s";
		gcvt(seconde,10,convertMaxComputation);
		res = (char*)malloc(strlen(convertMaxComputation) * sizeof(char));
		p1 = res;
		for(i=0;i<strlen(h);i++){
			*p1++ = h[i];
		}
		for(i=0;i<strlen(convertMaxComputation);i++){
			*p1++ = convertMaxComputation[i];
		}
		for(i=0;i<strlen(s);i++){
			*p1++ = s[i];
		}
	resConvert=res;
	}


	if((seconde>=60) && (seconde<3600)){

		h="00h";m="mn";s="s";
		int minute = seconde / 60;
		gcvt(minute,10,convertMaxComputation);

		int second = seconde % 60;
		gcvt(second,10,convertMaxComputation2);


		res = (char*)malloc(strlen(convertMaxComputation) * sizeof(char));
		p1 = res;
		for(i=0;i<strlen(h);i++){
			*p1++ = h[i];
		}
		for(i=0;i<strlen(convertMaxComputation);i++){
			*p1++ = convertMaxComputation[i];
		}
		for(i=0;i<strlen(m);i++){
			*p1++ = m[i];
		}
		for(i=0;i<strlen(convertMaxComputation2);i++){
			*p1++ = convertMaxComputation2[i];
		}
		for(i=0;i<strlen(s);i++){
			*p1++ = s[i];
		}
	resConvert=res;
	}


	if(seconde >= 3600){

		h="h";m="mn";s="s";

		int second = seconde % 60;
		gcvt(second,10,convertMaxComputation2);

		int minute = (seconde / 60) % 60;
		gcvt(minute,10,convertMaxComputation);

		int heur = (seconde / 60) / 60;
		gcvt(heur,10,convertMaxComputation3);


		res = (char*)malloc(strlen(convertMaxComputation) * sizeof(char));
		p1 = res;
		for(i=0;i<strlen(convertMaxComputation3);i++){
			*p1++ = convertMaxComputation3[i];
		}
		for(i=0;i<strlen(h);i++){
			*p1++ = h[i];
		}
		for(i=0;i<strlen(convertMaxComputation);i++){
			*p1++ = convertMaxComputation[i];
		}
		for(i=0;i<strlen(m);i++){
			*p1++ = m[i];
		}
		for(i=0;i<strlen(convertMaxComputation2);i++){
			*p1++ = convertMaxComputation2[i];
		}
		for(i=0;i<strlen(s);i++){
			*p1++ = s[i];
		}
	resConvert = res;
	}

return resConvert;
}
