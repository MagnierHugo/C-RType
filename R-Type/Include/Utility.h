#pragma once

#include <stdbool.h>
#include "Structs.h"

int RdmInt(int min, int max, bool nonZero);
void Swap(void* element1, void* element2);
SDL_Rect PlayerAsRect(Player player);
SDL_Rect ProjectileAsRect(Projectile proj);
SDL_Rect EnemyAsRect(Enemy enemy);
void CheckPointer(void* pointer, char* errorMessage, SDL sdl);
//void CheckPointer(void* pointer);