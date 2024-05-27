CFLAGS=

install:all
	cp ResolveTSP /bin

all: ResolveTSP clean

ResolveTSP:listesChainees.o remplirListeVil.o matriceDistances.o main.o algorithmeGenetique.o creationIndividus.o tirageAleatoire.o distanceIndividus.o classerDistances.o meilleurIndividu.o moitierIndividus.o methodeSelection.o accouplementIndividus.o croisementIndividus.o mutationIndividus.o ligneCommande.o enregistrementSolution.o
	gcc listesChainees.o remplirListeVil.o matriceDistances.o main.o algorithmeGenetique.o creationIndividus.o tirageAleatoire.o distanceIndividus.o classerDistances.o meilleurIndividu.o moitierIndividus.o methodeSelection.o accouplementIndividus.o croisementIndividus.o mutationIndividus.o ligneCommande.o enregistrementSolution.o -o $@ -lm



enregistrementSolution.o: enregistrementSolution.c enregistrementSolution.h
	gcc -c $(CFLAGS) enregistrementSolution.c

ligneCommande.o:ligneCommande.c ligneCommande.h
	gcc -c $(CFLAGS) ligneCommande.c

mutationIndividus.o:mutationIndividus.c mutationIndividus.h
	gcc -c $(CFLAGS) mutationIndividus.c

croisementIndividus.o:croisementIndividus.c croisementIndividus.h
	gcc -c $(CFLAGS) croisementIndividus.c

accouplementIndividus.o:accouplementIndividus.c accouplementIndividus.h
	gcc -c $(CFLAGS) accouplementIndividus.c

methodeSelection.o:methodeSelection.c methodeSelection.h
	gcc -c $(CFLAGS) methodeSelection.c

moitierIndividus.o:moitierIndividus.c moitierIndividus.h
	gcc -c $(CFLAGS) moitierIndividus.c

meilleurIndividu.o:meilleurIndividu.c meilleurIndividu.h
	gcc -c $(CFLAGS) meilleurIndividu.c

classerDistances.o:classerDistances.c classerDistances.h
	gcc -c $(CFLAGS) classerDistances.c

distanceIndividus.o:distanceIndividus.c distanceIndividus.h
	gcc -c $(CFLAGS) distanceIndividus.c

algorithmeGenetique.o:algorithmeGenetique.c algorithmeGenetique.h
	gcc -c $(CFLAGS) algorithmeGenetique.c

creationIndividus.o:creationIndividus.c creationIndividus.h
	gcc -c $(CFLAGS) creationIndividus.c

tirageAleatoire.o:tirageAleatoire.c tirageAleatoire.h
	gcc -c $(CFLAGS) tirageAleatoire.c

listesChainees.o:listesChainees.c listesChainees.h
	gcc -c $(CFLAGS) listesChainees.c 

remplirListeVil.o:remplirListeVil.c remplirListeVil.h
	gcc -c $(CFLAGS) remplirListeVil.c

matriceDistances.o: matriceDistances.c matriceDistances.h
	gcc -c $(CFLAGS) matriceDistances.c

main.o:main.c
	gcc -c $(CFLAGS) main.c

clean:
	rm *.o
