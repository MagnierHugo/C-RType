#pragma once

#include "Structs.h"

EnemyQueue CreateEnemyQueue(int nbrEnemies, Enemy base, SDL sdl);
Enemy* UpdateQueue(EnemyQueue queue, SDL sdl);
void SpawnEnemies(Scene* scene);