#pragma once

#include <SDL.h>

#include "Structs.h"


Animation CreateAnime(SDL_Texture** Tex, int nbrFrames, int wait, int pos[2]);
Animation* AddAnimation(SDL sdl, AnimeArgs args);
Animation* DeleteAnimation(SDL sdl, int delPos);
void RunAnimations(SDL* sdl);