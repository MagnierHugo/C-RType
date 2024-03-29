#pragma once

#include <stdbool.h>
#include "Structs.h"

int RdmInt(int min, int max, bool nonZero);
void Swap(void* element1, void* element2);
void CheckPointerKill(void* pointer, char* errorMessage, SDL sdl);
void CheckPointer(void* pointer);
int ControllerAxisToInt(SDL_GameController* controller, int axis);