#pragma once

#include "Structs.h"

EnemyQueue CreateEnemyQueue(int nbrEnemies, Enemy base);
Enemy* UpdateQueue(EnemyQueue queue);
void SpawnEnemies(Scene scene);