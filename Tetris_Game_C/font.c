#include "includes.h"

// itoa.
void Sortie_texte(unsigned long nNb, char *pDst)
{
	char *pPtr;
	unsigned long nTmp;

	pPtr = pDst + strlen(pDst) - 1;
	nTmp = nNb;
	do
	{
		*pPtr-- = (char)((nTmp % 10) + '0');
	}while (pPtr >= pDst && (nTmp /= 10) > 0);

}

// Affichage avec une fonte 16x16.
void Ecriture(unsigned long nOffset, char *pStr)
{
	unsigned long nOffTmp;
	unsigned long nOffFnt;
	unsigned long y;
	char cChr;
	unsigned char	*pScr, *pFnt;

	pScr = (unsigned char *)graphikVar.pEcran->pixels;
	pFnt = (unsigned char *)graphikVar.pFont1616->pixels;

	SDL_LockSurface(graphikVar.pEcran);

	nOffTmp = nOffset;
	while (*pStr)
	{
		cChr = *pStr++;
		if (cChr != ' ')
		{
			nOffFnt = (((unsigned long)cChr) - ' ') << 4;
			for (y = 0; y < 16; y++)
			{
				// On fait un OR + la fonte est en couleur 255 : Transparence.
				*(unsigned long *)(pScr + nOffTmp + (y * SCR_Width))    |=  *(unsigned long *)(pFnt + nOffFnt + (y * 1024));
				*(unsigned long *)(pScr + nOffTmp + (y * SCR_Width)+4)  |=  *(unsigned long *)(pFnt + nOffFnt + (y * 1024) + 4);
				*(unsigned long *)(pScr + nOffTmp + (y * SCR_Width)+8)  |=  *(unsigned long *)(pFnt + nOffFnt + (y * 1024) + 8);
				*(unsigned long *)(pScr + nOffTmp + (y * SCR_Width)+12) |=  *(unsigned long *)(pFnt + nOffFnt + (y * 1024) + 12);
			}
		}
		nOffTmp += 16;
	}
	SDL_UnlockSurface(graphikVar.pEcran);
}
