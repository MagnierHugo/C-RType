#pragma once

#include <stdbool.h>

int RdmInt(int min, int max, bool nonZero);
SDL_Rect PlayerAsRect(struct Player player);
SDL_Rect ProjectileAsRect(struct Projectile proj);