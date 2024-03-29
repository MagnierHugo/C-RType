#pragma once

#include <SDL.h>

#include "Structs.h"


Animation CreateAnime(SDL_Texture** Tex, int nbrFrames, int wait,
    SDL_Rect rect);
Animation* AddAnimation(SDL sdl, SDL_Texture** Tex, int nbrFrames,
    int wait, SDL_Rect rect);
Animation* DeleteAnimation(SDL sdl, int delPos);
void RunAnimations(SDL* sdl);
void RunAnimation(SDL sdl, Animation* anim);