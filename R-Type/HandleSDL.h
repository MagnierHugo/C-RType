#pragma once

#include <SDL.h>
#include "Constants.h"

int ErrorHandling(char* message, SDL sdlStruct);

struct SDL StartSDL();

void CloseSDL(GameArgs gameArgs);

void WindowClear(SDL_Renderer* renderer, SDL_Texture* texture);