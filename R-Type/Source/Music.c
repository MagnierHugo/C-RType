#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../Include/HandleSDL.h"
#include "../Include/Constants.h"
#include "../Include/Structs.h"


// Fonction pour charger le fichier audio
Mix_Chunk* LoadSound(char songWAV[20],  SDL sdl) {
    Mix_Chunk* sound = Mix_LoadWAV(songWAV);

    if (!sound) {
        ErrorHandling("Error while loading audio file", sdl);
    }

    return sound;
}

void PlaySound(char songWAV[20], SDL sdl) {

    Mix_Chunk* sound = LoadSound(songWAV, sdl);

    Mix_PlayChannel(-1, sound, 0);
}



