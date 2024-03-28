#pragma once

#include <stdbool.h>
#include "Structs.h"

int RdmInt(int min, int max, bool nonZero);
SDL_Rect PlayerAsRect(Player player);
SDL_Rect ProjectileAsRect(Projectile proj);
SDL_Rect EnemyAsRect(Enemy enemy);