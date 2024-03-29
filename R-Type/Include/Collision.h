#pragma once

#include "Structs.h"


void CheckEnemyPlayerCollision(GameState state, Enemy* enemy, Player* players);
int CheckEnemyProjCollision(GameState state, Enemy* enemy, Scene* scene, SDL* sdl);