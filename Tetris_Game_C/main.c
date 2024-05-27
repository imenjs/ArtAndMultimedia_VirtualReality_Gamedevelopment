#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "includes.h"


// Variables générales.
struct ecranParam graphikVar;
struct SExchange gExg;


// Gestionnaire d'évènements.
int gestionClavier(void){

	static unsigned char nFullScreen = 0;
	SDL_Event event;

	while (SDL_PollEvent(&event)){

		switch (event.type){

            case SDL_KEYDOWN: graphikVar.pKeys = SDL_GetKeyState(NULL);

                // Triggers.
                if (event.key.keysym.sym == SDLK_UP) graphikVar.pKeysTrig[TRIG_UP] = 1;
                if (event.key.keysym.sym == SDLK_DOWN) graphikVar.pKeysTrig[TRIG_DOWN] = 1;
                if (event.key.keysym.sym == SDLK_RIGHT) graphikVar.pKeysTrig[TRIG_RIGHT] = 1;
                if (event.key.keysym.sym == SDLK_LEFT) graphikVar.pKeysTrig[TRIG_LEFT] = 1;
                if (event.key.keysym.sym == SDLK_p) graphikVar.pKeysTrig[TRIG_KeyP] = 1;
                if (event.key.keysym.sym == SDLK_RETURN) graphikVar.pKeysTrig[TRIG_Return] = 1;
                if (event.key.keysym.sym == SDLK_SPACE) graphikVar.pKeysTrig[TRIG_Space] = 1;

                if (graphikVar.pKeys[SDLK_ESCAPE]){
                    // Arrêt d'urgence et sortir du boucle while !
                    exit(0);//return (1);
                }

                // fullscreen.
                if (graphikVar.pKeys[SDLK_F10]){

                    SDL_Surface *pTmp = graphikVar.pEcran;
                    graphikVar.pEcran = SDL_SetVideoMode(SCR_Width, SCR_Height, 8, SDL_HWSURFACE | SDL_DOUBLEBUF | ((nFullScreen ^ 1) ? SDL_FULLSCREEN : 0));

                    if (graphikVar.pEcran == NULL){
                        // Raté.
                        fprintf(stderr, "erreur d'activé le mode video : %sn",SDL_GetError());
                        graphikVar.pEcran = pTmp;	// Récupère l'ancien.
                    }else{
                    //SDL_SetPalette(graphikVar.pEcran, SDL_LOGPAL | SDL_PHYSPAL, graphikVar.pCurBkg->format->palette->colors, 8, graphikVar.pCurBkg->format->palette->ncolors);
                        SDL_FreeSurface(pTmp);	// Libère l'ancien.
                        nFullScreen ^= 1;
                    }
                }
                break;

            case SDL_KEYUP:
                graphikVar.pKeys = SDL_GetKeyState(NULL);
                break;

            case SDL_QUIT:		// Fermeture de la fenêtre.
                exit(0);
                break;
            }
	}
	return (0);
}

// chargement de l'image.
void Charger_image(SDL_Surface **pDst, char *imageName){

	*pDst = SDL_LoadBMP(imageName);
	if (*pDst == NULL) {
		fprintf(stderr, "errer lors du chargement de l'image '%s': %s\n", imageName, SDL_GetError());
		exit(1);
	}
}

// Le Menu (générique).
unsigned long menu(void (*pFctInit)(void), unsigned long (*pFctMain)(void)){

	unsigned long	i;
	unsigned long	numMenuVal = MENU_Null;

	// Sets up palette.
	SDL_SetColors(graphikVar.pEcran, graphikVar.pBkgMenu->format->palette->colors, 0, graphikVar.pBkgMenu->format->palette->ncolors);
    SDL_SetPalette(graphikVar.pEcran, SDL_LOGPAL, graphikVar.pBkgMenu->format->palette->colors, 0, graphikVar.pBkgMenu->format->palette->ncolors);
	graphikVar.pCurBkg = graphikVar.pBkgMenu;

	// Main loop.
	(*pFctInit)();
	graphikVar.pKeys = SDL_GetKeyState(NULL);		// Lecture dans le vide, pour init du ptr.
   FrameInit();

	while (numMenuVal == MENU_Null){

        fprintf(stdout,"----------> %d",MENU_Null);
		// Nettoyage du trigger.
		for (i = 0; i < TRIG_MaxKeys; i++){
		    graphikVar.pKeysTrig[i] = 0;
		}

		// Gestion des évenements.
		gestionClavier();

		// Recopie le décor.
		if (SDL_BlitSurface(graphikVar.pBkgMenu, NULL, graphikVar.pEcran, NULL) < 0){

       		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
			exit(1);
		}

		// Menu Main.
		numMenuVal = (*pFctMain)();

		// Wait for frame.
		FrameWait();
		// => Refresh écran.
		SDL_Flip(graphikVar.pEcran);
	}
	return (numMenuVal);
}

// Le jeu.
void game(void){

	unsigned long	i;
	unsigned long	nTetVal = GAME_Null;

	// Sets up palette.
	SDL_SetColors(graphikVar.pEcran, graphikVar.pBackground->format->palette->colors, 0, graphikVar.pBackground->format->palette->ncolors);
	SDL_SetPalette(graphikVar.pEcran, SDL_LOGPAL, graphikVar.pBackground->format->palette->colors, 0, graphikVar.pBackground->format->palette->ncolors);
	graphikVar.pCurBkg = graphikVar.pBackground;

	// Main loop.
	TetrisInit();
	graphikVar.pKeys = SDL_GetKeyState(NULL);		// Lecture dans le vide, pour init du ptr.
	FrameInit();

	while (nTetVal == GAME_Null){

		// Nettoyage du trigger.
		for (i = 0; i < TRIG_MaxKeys; i++) graphikVar.pKeysTrig[i] = 0;

		// Gestion des évenements.
		gestionClavier();

		// Recopie le décor. (possible optim => seulement l'aire de jeu).
		if(SDL_BlitSurface(graphikVar.pBackground, NULL, graphikVar.pEcran, NULL) < 0)
		{
       		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
			exit(1);
		}

		// Game.
		nTetVal = TetrisMain();

		// Wait for frame.
		FrameWait();
		SDL_Flip(graphikVar.pEcran);		// => Refresh écran.
	}

	// test si c'est le m
	if (nTetVal == GAME_GameOver)
	{
		if (Scr_CheckHighSc(gExg.nScore) >= 0)
		{
			// Saisie du nom.
			menu(MenuGetNameInit, MenuGetName);
			// Affichage de la table des high scores.
			menu(MenuMainInit, MenuHighScores);	// !!! Même init que main !!!
		}
	}
}

// Point d'entrée.
int main(int argc, char *argv[]){

	unsigned long	nLoop = 1;
	unsigned long	nMenuVal;


	// SDL Init.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	// atexit : Quand on quittera (exit, return...), SDL_Quit() sera appelée.
	atexit(SDL_Quit);

	//------------------> nb de bit pour codé les couleurs = 24.
	//Video mode init.
	graphikVar.pEcran = SDL_SetVideoMode(SCR_Width, SCR_Height, 8, SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF);

	if (graphikVar.pEcran == NULL){
		fprintf(stderr, "ne peut pas afiché: %sn",SDL_GetError());
		exit(1);
	}

	SDL_WM_SetCaption("Abidi & Abidi (Tetris)", NULL);	//Nom de la fenêtre.

	// Load backgound picture.
	Charger_image(&graphikVar.pBackground, "images/bkg.bmp");
	// Load menu backgound picture.
	Charger_image(&graphikVar.pBkgMenu, "images/bkg_menu.bmp");
	// Load bitmap 16x16 font.
	Charger_image(&graphikVar.pFont1616, "images/fnt.bmp");

	// Init sound.
	Sfx_SoundInit();
	Sfx_LoadWavFiles();
	Sfx_SoundOn();	// Starts playback.

	Scr_Load();		// Lecture du fichier des high scores.
	Opt_Load();		// Lecture des options.

	MenuInitMisc();

    // Cache le pointeur de la souris.
	// SDL_ShowCursor(SDL_DISABLE);

	// Boucle infinie.
	gExg.nStartingLevel = 1;
	gExg.nHandicap = 0;
	nMenuVal = MENU_Main;

	while (nLoop){

		switch (nMenuVal){

            case MENU_Main :	// Main menu.
                nMenuVal = menu(MenuMainInit, MenuMain);
                break;

            case MENU_Game :	// Jeu.
                game();
                nMenuVal = MENU_Main;
                break;

            case MENU_HallOfFame :	// High scores.
                menu(MenuMainInit, MenuHighScores);	// !!! Même init que main !!!
                nMenuVal = MENU_Main;
                break;

            case MENU_Options :	// Options.
                menu(MenuMainInit, MenuOptions);	// !!! Même init que main !!!
                nMenuVal = MENU_Main;
                break;

            case MENU_Quit :	// Sortie.
                nLoop = 0;
                break;
            }
	}

	//SDL_ShowCursor(SDL_ENABLE);		// Réautorise l'affichage du curseur de la souris.

	Sfx_SoundOff();		// Stops playback.
	Sfx_FreeWavFiles();	// Libère les ressources des fx.

	// Free the allocated BMP surfaces.
	SDL_FreeSurface(graphikVar.pBackground);
	SDL_FreeSurface(graphikVar.pBkgMenu);
	SDL_FreeSurface(graphikVar.pFont1616);

	return (0);
}
