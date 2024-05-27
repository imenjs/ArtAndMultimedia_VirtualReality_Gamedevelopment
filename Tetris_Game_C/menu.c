#include "includes.h"

#define NBELEM(tab) (sizeof(tab) / sizeof(tab[0]))
#define CURS_Acc 0x200

enum
{
	MENU_State_FadeIn = 0,
	MENU_State_Input,
	MENU_State_FadeOut,
};

#define OPT_Filename "tetris.txt"
#define	MENU_SFX_VALIDATION	e_Sfx_MenuValidate
#define	MENU_SFX_CLIC	e_Sfx_MenuClic
#define HISC_Nb	8
#define HISC_NameLg (10+1)
#define HISC_Filename "high.txt"

struct SScore
{
	char pName[HISC_NameLg];
	unsigned long	nScore;
};

struct SScore	M_Score[HISC_Nb];

struct SMenu
{
	unsigned long	nChoix;
	unsigned long	nState;		// Etat (fade in...).

	signed long	nFadeVal;

	unsigned char nSin;		// Pour bouffoner le titre.

	signed short	nCursPos;	// Pour faire bouger le curseur.
	signed short	nCursAccel;

	// Variables pour saisie du nom.
	unsigned long	nScIdx;			// Pos dans la chaîne. / Pas remis à 0 !
	char	pScName[HISC_NameLg];	// Nom saisi. / Pas remis à 0 !

	unsigned char pScKeyDown;	// Pour pseudo trigger.
	unsigned long nScRank;	// Rang de classement.

};
struct SMenu gMenu;

struct SMenuItm
{
	unsigned long	nRval;		// Valeur renvoyée. MENU_Null => Pas une ligne à valider.
	unsigned long	*pVal;		// Si valeur à afficher dans une ligne, un ptr dessus.
	unsigned long	nValMin, nValMax;	// Bornes de la valeur ci dessus.
	char pStr[16];	// Texte affiché. On remplace le @ par la valeur.
};

void MenuMainInit(void)
{

	gMenu.nChoix = 0;

	gMenu.nState = MENU_State_FadeIn;
	gMenu.nFadeVal = 0;

	gMenu.nSin = 0;
//	CurseurInit();

}

// Menu - Init misc.
void MenuInitMisc(void)
{
	MenuMainInit();

	char pEmptyName[HISC_NameLg] = "..........";
	gMenu.nScIdx = 0;
	strcpy(gMenu.pScName, pEmptyName);

}

// Menu principal.
#define	MENUMAIN_INTERLIGNE	28
unsigned long MenuMain(void){
	// >>> Possibilité de sortir ça pour faire un autre menu du même type.
	struct SMenuItm pItems[] =
	{
		{ MENU_Game, NULL, 0, 0, "JOUER" },
		{ MENU_HallOfFame, NULL, 0, 0, "MEILLEUR SCORES" },
		{ MENU_Options, NULL, 0, 0, "OPTIONS" },
		{ MENU_Quit, NULL, 0, 0, "QUIT" },
	};
	unsigned long	nNbLines = NBELEM(pItems);


	unsigned long	nRet = MENU_Null;
	unsigned long	i;
	unsigned long	nPosX, nPosY;


	// Selon l'état.
	switch (gMenu.nState){

        case MENU_State_FadeIn :
            gMenu.nFadeVal += 4;
            if (gMenu.nFadeVal > 256){
                gMenu.nState = MENU_State_Input;
                gMenu.nFadeVal = -1;
            }
            break;

        case MENU_State_FadeOut :
            gMenu.nFadeVal -= 4;
            if (gMenu.nFadeVal < 0){
                nRet = pItems[gMenu.nChoix].nRval;	// Valeur choisie par l'utilisateur.
            }
            break;

        case MENU_State_Input :
            // Gestion du clavier.
            if (graphikVar.pKeysTrig[TRIG_UP])
            {
                if (--gMenu.nChoix >= nNbLines) gMenu.nChoix = nNbLines - 1;
                Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
            }
            if (graphikVar.pKeysTrig[TRIG_DOWN])
            {
                if (++gMenu.nChoix >= nNbLines) gMenu.nChoix = 0;
                Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
            }

            // Une valeur numérique à changer ?
            if (pItems[gMenu.nChoix].pVal != NULL)
            {
                if (graphikVar.pKeysTrig[TRIG_RIGHT])
                {
                    if (++*pItems[gMenu.nChoix].pVal > pItems[gMenu.nChoix].nValMax)
                        *pItems[gMenu.nChoix].pVal = pItems[gMenu.nChoix].nValMax;
                    else
                        Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
                }
                if (graphikVar.pKeysTrig[TRIG_LEFT])
                {
                    if (--*(signed long *)pItems[gMenu.nChoix].pVal < (signed long)pItems[gMenu.nChoix].nValMin)
                        *pItems[gMenu.nChoix].pVal = pItems[gMenu.nChoix].nValMin;
                    else
                        Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
                }
            }

            // Validation.
            if ((graphikVar.pKeysTrig[TRIG_Return] || graphikVar.pKeysTrig[TRIG_Space]) && pItems[gMenu.nChoix].nRval != MENU_Null)
            {
                gMenu.nState = MENU_State_FadeOut;
                gMenu.nFadeVal = 256;
                Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
            }
            break;
	}

	// Affichage des lignes.
	nPosX = 40;
	nPosY = (SCR_Height - ((nNbLines * MENUMAIN_INTERLIGNE) - (MENUMAIN_INTERLIGNE / 2))) / 2;
	for (i = 0; i < nNbLines; i++)
	{
		// Une valeur numérique ?
		if (pItems[i].pVal != NULL)
		{
			char *pPtr = strchr(pItems[i].pStr, '@');
			if (pPtr != NULL) *pPtr = (char)(0x30 + *pItems[i].pVal);
		}

		// Print.
		Ecriture((SCR_Width * (nPosY + (i * MENUMAIN_INTERLIGNE))) + nPosX, pItems[i].pStr);
		// Curseur.
		if (i == gMenu.nChoix)
		{
			Ecriture((SCR_Width * (nPosY + (i * MENUMAIN_INTERLIGNE))) + (nPosX - 24) - (gMenu.nCursPos >> 8), ">");
		}
	}
	return (nRet);		// Renvoie le choix.
}


// Menu options des elements
struct SOptMenuItm
{
	unsigned long	nRval;		// Valeur renvoyée. MENU_Null => Pas une ligne à valider.
	unsigned long	nBit;		// Bit à XORer.
	char	pStr[16];	// Texte affiché.
	unsigned char nSkipLn;	// Sauter ligne ou pas.
	char	pStrBit0[10];	// Texte affiché quand bit = 0.
	char	pStrBit1[10];	// Texte affiché quand bit = 1.
};

// Menu des options.
#define	MENUOPT_INTERLIGNE	28
#define	MENUOPT_INTERLIGNE2	20
unsigned long MenuOptions(void)
{
	struct SOptMenuItm pItems[] = {
		{ MENU_Null, OPT_Ghost, "OMBRE:", 0, "OFF", "ON" },
		{ MENU_Null, OPT_Sound, "SON:", 0, "OFF", "ON" },
		{ MENU_Main, 0, "RETOUR", 0, "", "" },
};
	unsigned long	nNbLines = NBELEM(pItems);

	unsigned long	nRet = MENU_Null;
	unsigned long	i;
	unsigned long	nPosX, nPosY;


	// Selon l'état.
	switch (gMenu.nState)
	{

	case MENU_State_FadeIn :
		gMenu.nFadeVal += 4;
		if (gMenu.nFadeVal > 256)
		{
			gMenu.nState = MENU_State_Input;
			gMenu.nFadeVal = -1;
		}
		break;

	case MENU_State_FadeOut :
		gMenu.nFadeVal -= 4;
		if (gMenu.nFadeVal < 0)
		{
			Opt_Save();
			nRet = pItems[gMenu.nChoix].nRval;	// Valeur choisie par l'utilisateur.
		}
		break;

	case MENU_State_Input :
		// Gestion du clavier.
		if (graphikVar.pKeysTrig[TRIG_UP])
		{
			if (--gMenu.nChoix >= nNbLines) gMenu.nChoix = nNbLines - 1;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}
		if (graphikVar.pKeysTrig[TRIG_DOWN])
		{
			if (++gMenu.nChoix >= nNbLines) gMenu.nChoix = 0;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}

		// Une valeur à changer ?
		if (pItems[gMenu.nChoix].nBit != 0)
		{
			if (graphikVar.pKeysTrig[TRIG_Return] || graphikVar.pKeysTrig[TRIG_Space] || graphikVar.pKeysTrig[TRIG_LEFT]   || graphikVar.pKeysTrig[TRIG_RIGHT])
			{
				graphikVar.nOptFlags ^= pItems[gMenu.nChoix].nBit;
				Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
			}
		}

		// Validation.
		if ((graphikVar.pKeysTrig[TRIG_Return] || graphikVar.pKeysTrig[TRIG_Space]) && pItems[gMenu.nChoix].nRval != MENU_Null)
		{
			gMenu.nState = MENU_State_FadeOut;
			gMenu.nFadeVal = 256;
			Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
		}
		break;
	}
		// Titre.
	char	pTitle[] = "OPTIONS";
	Ecriture((SCR_Width * 8) + ((SCR_Width - (strlen(pTitle) * 16)) / 2), pTitle);

	// Affichage des lignes.
	nPosX = 40;
	nPosY = 45;
	for (i = 0; i < nNbLines; i++)
	{
		// Curseur.
		if (i == gMenu.nChoix)
		{
			Ecriture((SCR_Width * nPosY) + (nPosX - 24) - (gMenu.nCursPos >> 8), ">");
		}
		// Print.
		Ecriture((SCR_Width * nPosY) + nPosX, pItems[i].pStr);
		// Valeur du bit.
		if (pItems[i].nBit)
		{
			char* pStr = (graphikVar.nOptFlags & pItems[i].nBit ? pItems[i].pStrBit1 : pItems[i].pStrBit0);
			if (pItems[i].nSkipLn) nPosY += MENUOPT_INTERLIGNE2;
			Ecriture((SCR_Width * nPosY) + SCR_Width - (strlen(pStr) * 16) - 16, pStr);
		}
		nPosY += MENUOPT_INTERLIGNE;
	}

	//Fade(gMenu.nFadeVal, graphikVar.pBkgMenu);

	return (nRet);		// Renvoie le choix.
}
// Menu de Meilleurs scores
unsigned long MenuHighScores(void)
{
	unsigned long	nRet = MENU_Null;
	unsigned long	i;
	unsigned long	nPosX, nPosY;


	// Selon l'état.
	switch (gMenu.nState)
	{
	case MENU_State_FadeIn :
		gMenu.nFadeVal += 4;
		if (gMenu.nFadeVal > 256)
		{
			gMenu.nState = MENU_State_Input;
			gMenu.nFadeVal = -1;
		}
		break;

	case MENU_State_FadeOut :
		gMenu.nFadeVal -= 4;
		if (gMenu.nFadeVal < 0)
		{
			nRet = MENU_Main;	// Sortie.
		}
		break;

	case MENU_State_Input :
		// Gestion du clavier.
		if (graphikVar.pKeysTrig[TRIG_Return] || graphikVar.pKeysTrig[TRIG_Space])
		{
			gMenu.nState = MENU_State_FadeOut;
			gMenu.nFadeVal = 256;
			Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
		}
		break;
	}

	// Titre.
	char	pTitle[] = "NOM JOUEURS";
	Ecriture((SCR_Width * 8) + ((SCR_Width - (strlen(pTitle) * 16)) / 2), pTitle);

	// Affichage des lignes.
	nPosX = 8;
	nPosY = 40;
	for (i = 0; i < HISC_Nb; i++)
	{
		char	pStr[] = "       ";

		// Nom.
		Ecriture((SCR_Width * (nPosY + (i * 24))) + nPosX, M_Score[i].pName);
		// Score.
		Sortie_texte(M_Score[i].nScore, pStr);
		Ecriture((SCR_Width * (nPosY + (i * 24))) + SCR_Width - (7 * 16) - 8, pStr);

//		/// Curseur. / Voir plus tard, pour marquer le score qui vient d'être fait ?
		if (i == gMenu.nChoix)
		{
			Ecriture((SCR_Width * (nPosY + (i * 32))) + (nPosX - 24) - (gMenu.nCursPos >> 8), ">");
		}
	}

	return (nRet);
}

// Scores - Check si un score entre au Hall of Fame.
// Out : -1, pas dedans / >= 0, rang.
signed long Scr_CheckHighSc(unsigned long nScorePrm)
{
	signed long	i, nRank;

	nRank = -1;
	for (i = HISC_Nb - 1; i >= 0; i--)
	{
		if (nScorePrm >= M_Score[i].nScore)
		{
			nRank = i;
		}
	}

	return (nRank);
}

// Insère un nom dans la table.
void Nom_joueur(char *pName, unsigned long nScore)
{
	signed long	nRank = Scr_CheckHighSc(nScore);
	signed long	i;

	if (nRank < 0) return;		// Ne devrait pas arriver.

	// Décalage de la table.
	for (i = HISC_Nb - 2; i >= nRank; i--)
	{
		strcpy(M_Score[i + 1].pName, M_Score[i].pName);
		M_Score[i + 1].nScore = M_Score[i].nScore;
	}
	// Le score à insérer.
	strcpy(M_Score[nRank].pName, pName);
	M_Score[nRank].nScore = nScore;

}


// RAZ de la table des high scores.
void Scr_RazTable(void)
{
	char	pDefault[HISC_NameLg] = "..........";
	unsigned long	i;

	for (i = 0; i < HISC_Nb; i++)
	{
		strcpy(M_Score[i].pName, pDefault);
		M_Score[i].nScore = 0;
	}

}

// Calcule le checksum de la table des scores.
unsigned long Scr_CalcChecksum(void)
{
	unsigned long	i, j;
	unsigned long	nChk = 0;

	for (i = 0; i < HISC_Nb; i++)
	{
		nChk += M_Score[i].nScore;
		for (j = 0; j < HISC_NameLg; j++) nChk += ((unsigned long)M_Score[i].pName[j]) << (8 * (j & 3));
	}
	return (nChk);
}

// Lecture du fichier des high scores.
void Scr_Load(void){

	FILE *pFile;
	unsigned long nChk;

	if ((pFile = fopen(HISC_Filename, "rb")) != NULL)
	{
		// Le fichier existe, lecture.
		fread(M_Score, sizeof(struct SScore), HISC_Nb, pFile);
		fread(&nChk, sizeof(unsigned long), 1, pFile);
		fclose(pFile);
		// Checksum ok ?
		if (nChk != Scr_CalcChecksum())
		{
			// Wrong checksum, RAZ table.
			printf("Scr_Load: Wrong checksum! Resetting table.\n");
			Scr_RazTable();
		}
	}
	else
	{
		// Le fichier n'existe pas, RAZ table.
		Scr_RazTable();
	}

}

// Sauvegarde du fichier des high scores.
void Scr_Save(void)
{
	FILE	*pFile;
	unsigned long nChk;

	if ((pFile = fopen(HISC_Filename, "wb")) == NULL)
	{
		printf("erreur de sauvgarder les scores.\n");
		return;
	}
	// Sauvegarde des enregistrements.
	fwrite(M_Score, sizeof(struct SScore), HISC_Nb, pFile);
	// Checksum.
	nChk = Scr_CalcChecksum();
	fwrite(&nChk, sizeof(unsigned long), 1, pFile);
	fclose(pFile);
}

// Lecture du fichier des options.
void Opt_Load(void)
{
	FILE	*pFile;

	if ((pFile = fopen(OPT_Filename, "rb")) != NULL)
	{
		// Le fichier existe, lecture.
		fread(&graphikVar.nOptFlags, sizeof(graphikVar.nOptFlags), 1, pFile);
		fclose(pFile);
	}
	else
	{
		// Le fichier n'existe pas, raz flags.
		graphikVar.nOptFlags = OPT_Rotation | OPT_Sound;
	}
}

// Sauvegarde du fichier des options.
void Opt_Save(void)
{
	FILE	*pFile;

	if ((pFile = fopen(OPT_Filename, "wb")) == NULL)
	{
		printf("Unable to save options.\n");
		return;
	}
	// Sauvegarde des flags.
	fwrite(&graphikVar.nOptFlags, sizeof(graphikVar.nOptFlags), 1, pFile);
	fclose(pFile);

}

// Init.
void MenuGetNameInit(void)
{
	MenuMainInit();
	gMenu.pScKeyDown = 0;	// Pseudo trigger pour saisie du nom.
	gMenu.nScRank = Scr_CheckHighSc(gExg.nScore);	// Rang.
}

// Saisie du nom quand high-score.
unsigned long MenuGetName(void)
{
	unsigned long	nRet = MENU_Null;
	unsigned long	i;
	static unsigned char nCligno = 0;	// POur clignotement du curseur.

	// Selon l'état.
	switch (gMenu.nState)
	{
	case MENU_State_FadeIn :
		gMenu.nFadeVal += 4;
		if (gMenu.nFadeVal > 256)
		{
			gMenu.nState = MENU_State_Input;
			gMenu.nFadeVal = -1;
		}
		break;

	case MENU_State_FadeOut :
		gMenu.nFadeVal -= 4;
		if (gMenu.nFadeVal < 0)
		{
			// Si pas de nom, mettre John Doe.
			char	pDefName[] = "JOHN DOE..";
			if (gMenu.nScIdx == 0)
			{
				strcpy(gMenu.pScName, pDefName);
				gMenu.nScIdx = strlen(pDefName);
			}
			// Rajoute le nom à la table.
			Nom_joueur(gMenu.pScName, gExg.nScore);
			Scr_Save();		// Sauvegarde du fichier.

			nRet = MENU_Main;	// Sortie.
		}
		break;

	case MENU_State_Input :
		// Gestion du clavier.
		if (graphikVar.pKeysTrig[TRIG_Return])
		{
			gMenu.nState = MENU_State_FadeOut;
			gMenu.nFadeVal = 256;
			Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
			break;
		}

		// On regarde quelle touche est enfoncée.
		unsigned long	nChr = 0;

		if (graphikVar.pKeys[SDLK_SPACE]) nChr = ' ';
		for (i = SDLK_a; i <= SDLK_z; i++)
		{
			if (graphikVar.pKeys[i])
			{
				nChr = i - SDLK_a + 'A';
				break;
			}
		}
		for (i = SDLK_0; i <= SDLK_9; i++)
		{
			if (graphikVar.pKeys[i])
			{
				nChr = i - SDLK_0 + '0';
				break;
			}
		}
		if (graphikVar.pKeys[SDLK_BACKSPACE])
		{
			nChr = SDLK_BACKSPACE;
		}

		// Pseudo trigger.
		if (gMenu.pScKeyDown == 0 && nChr)
		{
			if (nChr == SDLK_BACKSPACE)
			{
				if (gMenu.nScIdx) gMenu.pScName[--gMenu.nScIdx] = '.';
			}
			else if (gMenu.nScIdx < strlen(gMenu.pScName))
			{
				gMenu.pScName[gMenu.nScIdx++] = nChr;
			}
			gMenu.pScKeyDown = 1;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}
		else if (gMenu.pScKeyDown == 1 && nChr == 0)
		{
			gMenu.pScKeyDown = 0;		// Release.
		}
		break;
	}


	// Message à la fin du jeu si l'utilisateur arrive au moin à completer une ligne
	char pWin[][20] =
	{
		"BRAVO!",
		"VOTRE SCORE #@",
		"ENTRER VOTRE NOM:"
	};

	// On rajoute le rank dans sa ligne.
	char *pPtr = strchr(pWin[1], '@');
	if (pPtr != NULL) *pPtr = (char)(0x31 + gMenu.nScRank);

    Ecriture((SCR_Width * (8+16+16)) + ((SCR_Width - (strlen(pWin[0]) * 16)) / 2), pWin[0]);
	Ecriture((SCR_Width * (40+40+16)) + ((SCR_Width - (strlen(pWin[1]) * 16)) / 2), pWin[1]);
	Ecriture((SCR_Width * (72+64+16)) + ((SCR_Width - (strlen(pWin[2]) * 16)) / 2), pWin[2]);
	Ecriture((SCR_Width * (104+64+16)) + ((SCR_Width - (strlen(gMenu.pScName) * 16)) / 2), gMenu.pScName);

	// Curseur.
	if (nCligno & 16)

        Ecriture((SCR_Width * (104+64+28)) + ((SCR_Width - (strlen(gMenu.pScName) * 16)) / 2) + (gMenu.nScIdx * 16), "-");
        nCligno++;

		return (nRet);
}



