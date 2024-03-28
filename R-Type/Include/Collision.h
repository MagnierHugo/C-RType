#pragma once

#include "Structs.h"


void CheckEnemyPlayerCollision(GameState state, Enemy* enemy, Player* players);
int CheckEnemyProjCollision(Enemy* enemy, EnemyQueue* queue, Projectile* projs, SDL sdl);