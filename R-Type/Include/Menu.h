#pragma once
#include <SDL.h>
#include "Constants.h"

bool PointInRect(int x, int y, SDL_Rect rect);
void DrawButton(SDL_Renderer* renderer, Button button);
SDL_Scancode GetKeyPressed();