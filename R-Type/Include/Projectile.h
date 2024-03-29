#pragma once

#include "Structs.h"

void ShootPlayerProjectile(Player player, Projectile* projs,
	GameState* state, GameArgs gameArgs);
void ShootBossProjectile(Boss boss, Projectile* projs,
	GameArgs args, int yOffset);