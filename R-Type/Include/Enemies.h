#include <SDL.h>
#include <stdio.h>

#include "Constants.h"
#include "Structs.h"


static EnemyQueue AllocateMemory(int nbrEnemies, SDL sdl);
EnemyQueue CreateEnemyQueue(int nbrEnemies, Enemy base, SDL sdl);
Enemy* UpdateQueue(EnemyQueue queue, SDL sdl);
void SpawnEnemies(Scene* scene);
//Enemy* FindIdleEnemy(Enemy* enemies);
//void SpawnEnemies(GameArgs gameArgs);
//void SetupEnemy(Enemy* enemy);
