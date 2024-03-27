#pragma once

#include <SDL.h>

#include "Structs.h"

SDL_Texture* CreateTexture(SDL sdlStruct, char* path);
void DestroyTextures(Textures textures);