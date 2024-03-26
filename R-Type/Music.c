#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "HandleSDL.h"
#include "Constants.h"


// Fonction pour charger le fichier audio
Mix_Chunk* LoadSound(char songWAV[20], struct SDL sdl) {
    Mix_Chunk* sound = Mix_LoadWAV(songWAV);

    if (!sound) {
        ErrorHandling("Error while loading audio file", sdl);
    }

    return sound;
}

void PlaySound(char songWAV[20], struct SDL sdl) {

    Mix_Chunk* sound = LoadSound(songWAV, sdl);

    Mix_PlayChannel(-1, sound, 0);
}



