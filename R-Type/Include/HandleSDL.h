#pragma once

#include <SDL.h>
#include "Structs.h"

void ErrorHandling(char* message, SDL sdlStruct);

SDL StartSDL();

void CloseSDL(GameArgs gameArgs);

void WindowClear(SDL_Renderer* renderer, SDL_Texture* texture);