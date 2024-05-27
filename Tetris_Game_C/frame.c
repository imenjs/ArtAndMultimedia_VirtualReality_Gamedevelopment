#include "includes.h"

#define FPS_Default 1000 / 70

unsigned long nTimer1, nTimer2;

// Init timers.
void FrameInit(void){
	nTimer1 = SDL_GetTicks();
}

// Attente de la frame.
void FrameWait(void){
	// S'assurer que l'on ne va pas trop vite...
	while (1){

		nTimer2 = SDL_GetTicks() - nTimer1;
		if (nTimer2 >= FPS_Default) break;
		SDL_Delay(3);
	}
	nTimer1 = SDL_GetTicks();
}
