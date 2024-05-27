#include <stdlib.h>
#include <unistd.h>
#include "SDL.h"
#include "SDL_image.h"
#include <time.h>

#include <math.h>
#define PI 3.1415927

#include "menu.h"
#include "game.h"
#include "frame.h"
#include "font.h"
#include "gestionSon.h"

// Define.
#define SCR_Width 320
#define SCR_Height 240


enum{

	TRIG_UP = 0,
	TRIG_DOWN,	// Trig down et return => pour le menu.
	TRIG_RIGHT,
	TRIG_LEFT,
	TRIG_Return,
	TRIG_Space,
	TRIG_KeyP,
	TRIG_MaxKeys
};

enum{

	MENU_Null = 0,		// Codes de sortie du menu.
	MENU_Main,
	MENU_Quit,
	MENU_Game,
	MENU_Options,
	MENU_HallOfFame,
	MENU_MaxItem
};

enum
{
	GAME_Null = 0,		// Codes de sortie du jeu.
	GAME_GameOver,
	GAME_Quit,
	GAME_MaxItem
};

enum
{
	OPT_Ghost = 1,
	OPT_Rotation = 1 << 1,
	OPT_BlocksSet = 1 << 2,
	OPT_Sound = 1 << 3,
};

// Types de variables.// des pointeurs sur les images importer dans les interface du jeu
struct ecranParam //parametre d'ecron
{
	SDL_Surface *pEcran;	        // Ptr sur le buffer écran.
	unsigned char *pKeys;		    // Buffer clavier (ira pointer une table fournie par SDL).
	unsigned char pKeysTrig[TRIG_MaxKeys];	// Trigger.
	SDL_Surface *pBackground;	// Ptr sur l'image de décor.
	SDL_Surface *pBkgMenu;		// L'image de fond du menu.
	SDL_Surface *pFont1616;		// Ptr sur l'image contenant la fonte.
	SDL_Surface *pCurBkg;		// Ptr sur l'image de fond courante.
	unsigned long nOptFlags;		        // Options.
};

struct SExchange	// Echanges entre les modules.
{
	unsigned long	nStartingLevel;		// Niveau de départ.
	unsigned long	nHandicap;		// Handicap de départ.
	unsigned long	nScore;		// Score en sortie.
};

// Variables générales.
struct ecranParam graphikVar; // graphikvar = variable de manipulation de graphique du jeu
struct SExchange gExg;
