#pragma once

#include <SDL.h>

#include "Structs.h"


SDL_Rect PlayerAsRect(Player player);
SDL_Rect ProjectileAsRect(Projectile proj);
SDL_Rect EnemyAsRect(Enemy enemy);