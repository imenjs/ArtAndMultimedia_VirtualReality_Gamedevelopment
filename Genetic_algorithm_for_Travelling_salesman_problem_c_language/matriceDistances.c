#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"matriceDistances.h"



double** calculMatriceDistance(double** matDistance,liste vil,long nbVille){
int i,j;
double x1,x2,y1,y2;

	for(i=0;i<nbVille;i++){
		for(j=0;j<nbVille;j++){
			if(i!=j){
				x1=getAbscisse(vil,i);
				x2=getAbscisse(vil,j);
				y1=getOrdonnee(vil,i);
				y2=getOrdonnee(vil,j);
				matDistance[i][j] = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
			}else{
				matDistance[i][j] = 0;
			}
		}
	}

return matDistance;
}


double getAbscisse(liste vil,int k){
liste p;
	p = vil;
	while(p->num != k+1){
		p = p->suivant;
	}
return(p->x);
}


double getOrdonnee(liste vil,int k){
liste p;
	p = vil;
	while(p->num != k+1){
		p = p->suivant;
	}
return(p->y);
}
