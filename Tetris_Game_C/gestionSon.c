
#include "includes.h"


struct SSfxGene
{
	unsigned char	nInit;		// Son initialisé (1) ou pas (0).
	SDL_AudioSpec	sAudioSpec;
    SDL_AudioCVT	pCvt[e_Sfx_LAST];

};
struct SSfxGene	gSfx;


#define SFX_MAX_SOUNDS	2
struct SSample
{
	unsigned char	*pData;
	unsigned long	nDPos;
	unsigned long	nDLen;
	unsigned char	nPrio;	// Priorité du son en cours.

}gpSounds[SFX_MAX_SOUNDS];


// Mixer, appelé par SDL.
void Sfx_MixAudio(void *unused, unsigned char *stream, int len)
{
    unsigned long	i;
    unsigned long	amount;

    for (i = 0; i < SFX_MAX_SOUNDS; i++)
    {
        amount = (gpSounds[i].nDLen - gpSounds[i].nDPos);
        if (amount > (unsigned long)len)
        {
            amount = len;
        }
        SDL_MixAudio(stream, &gpSounds[i].pData[gpSounds[i].nDPos], amount, SDL_MIX_MAXVOLUME);
        gpSounds[i].nDPos += amount;
    }
}

// Nettoyage des canaux.
void Sfx_ClearChannels(void)
{
	unsigned long	i;
    for (i = 0; i < SFX_MAX_SOUNDS; i++)
    {
		gpSounds[i].nDPos = 0;
		gpSounds[i].nDLen = 0;
	}

}

// Sound, initialisation. A appeler 1 fois.
void Sfx_SoundInit(void)
{
	gSfx.nInit = 0;

	// Set 16-bit stereo audio at 22Khz.
	gSfx.sAudioSpec.freq = 22050;
	gSfx.sAudioSpec.format = AUDIO_S16;
	gSfx.sAudioSpec.channels = 2;
	gSfx.sAudioSpec.samples = 512;        // A good value for games.
	gSfx.sAudioSpec.callback = Sfx_MixAudio;
	gSfx.sAudioSpec.userdata = NULL;

	// Open the audio device and start playing sound!
	if (SDL_OpenAudio(&gSfx.sAudioSpec, NULL) < 0)
	{
		//fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
		//exit(1);
		printf("Unable to open audio: %s\n", SDL_GetError());
		printf("Sound disabled.\n");
		return;
	}

	gSfx.nInit = 1;		// Ok.

	Sfx_ClearChannels();	// Nettoyage des structures.

}

// Sound on.
void Sfx_SoundOn(void)
{
	if (!gSfx.nInit) return;
	SDL_PauseAudio(0);

}

// Sound off.
void Sfx_SoundOff(void)
{
	if (!gSfx.nInit) return;
	SDL_CloseAudio();

}


// Chargement de tous les fichiers WAV.
void Sfx_LoadWavFiles(void)
{
	unsigned long	i;

    SDL_AudioSpec sWave;
    unsigned char	*pData;
    Uint32	nDLen;

	char	*pSfxFilenames[e_Sfx_LAST] = {
		"son/_menu_click.wav", "son/_menu_validate.wav", "son/_explosion2.wav",
		"son/_level_up.wav", "son/_piece_sticks.wav", "son/_piece_rotate.wav",
	};

	if (!gSfx.nInit) return;

	for (i = 0; i < e_Sfx_LAST; i++)
	{
		// Load the sound file and convert it to 16-bit stereo at 22kHz
		if (SDL_LoadWAV(pSfxFilenames[i], &sWave, &pData, &nDLen) == NULL)
		{
			fprintf(stderr, "Couldn't load %s: %s\n", pSfxFilenames[i], SDL_GetError());
			return;
		}
		SDL_BuildAudioCVT(&gSfx.pCvt[i], sWave.format, sWave.channels, sWave.freq,
			gSfx.sAudioSpec.format, gSfx.sAudioSpec.channels, gSfx.sAudioSpec.freq);

		gSfx.pCvt[i].buf = (unsigned char*)malloc(nDLen * gSfx.pCvt[i].len_mult);
		memcpy(gSfx.pCvt[i].buf, pData, nDLen);
		gSfx.pCvt[i].len = nDLen;
		SDL_ConvertAudio(&gSfx.pCvt[i]);
		SDL_FreeWAV(pData);

	}

}

// Libère les ressources occupées par les fichiers WAV.
void Sfx_FreeWavFiles(void)
{
	unsigned long	i;

	if (!gSfx.nInit) return;

	for (i = 0; i < e_Sfx_LAST; i++)
	{
		free(gSfx.pCvt[i].buf);
	}

}


// Joue un son.
// Le minimum :
// On commence par chercher un canal vide.
// Si il n'y en a pas, on note celui qui à la priorité la plus faible.
// Si plusieurs ont la même priorité, on note celui qui est le plus proche de la fin.
// Enfin, si la prio du son à jouer est ok, on le joue dans le canal noté.
void Sfx_PlaySfx(unsigned long nSfxNo, unsigned long nSfxPrio)
{
	unsigned long	index;

	unsigned char nPrioMinVal = 255;
	unsigned long	nPrioMinPos = 0;
	unsigned long	nPrioMinDiff = (unsigned long)-1;

	if (!(graphikVar.nOptFlags & OPT_Sound)) return;	// Pas si sound off.

	if (nSfxNo >= e_Sfx_LAST) return;	// Sécurité.

    // Look for an empty (or finished) sound slot.
    for (index = 0; index < SFX_MAX_SOUNDS; index++)
    {
        if (gpSounds[index].nDPos == gpSounds[index].nDLen)
        {
            break;
        }
        //
        if (gpSounds[index].nPrio < nPrioMinVal)
        {
			nPrioMinVal = gpSounds[index].nPrio;
			nPrioMinPos = index;
        	nPrioMinDiff = gpSounds[index].nDLen - gpSounds[index].nDPos;
		}
		else if (gpSounds[index].nPrio == nPrioMinVal)
		{
			if (gpSounds[index].nDLen - gpSounds[index].nDPos < nPrioMinDiff)
			{
				//nPrioMinVal = sounds[index].nPrio;
				nPrioMinPos = index;
				nPrioMinDiff = gpSounds[index].nDLen - gpSounds[index].nDPos;
			}
		}

    }

	// On a trouvé un emplacement libre ?
    if (index == SFX_MAX_SOUNDS)
    {
    	// Non, la prio demandée est > ou == à la prio mini en cours ?
		if (nSfxPrio < nPrioMinVal) return;
		index = nPrioMinPos;
    }

    // Put the sound data in the slot (it starts playing immediately).
    SDL_LockAudio();
    gpSounds[index].pData = gSfx.pCvt[nSfxNo].buf;
    gpSounds[index].nDLen = gSfx.pCvt[nSfxNo].len_cvt;
    gpSounds[index].nDPos = 0;
    gpSounds[index].nPrio = (unsigned char)nSfxPrio;
    SDL_UnlockAudio();

}
