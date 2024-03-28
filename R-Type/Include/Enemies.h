#include <SDL.h>
#include <stdio.h>

#include "Constants.h"
#include "Structs.h"


Enemy* FindIdleEnemy(Enemy* enemies);
void SpawnEnemies(GameArgs gameArgs);
void SetupEnemy(Enemy* enemy);
void CheckEnemyPlayerCollision(GameState state, Enemy enemy, Player* players);
int CheckEnemyProjCollision(GameState state, Enemy* enemy, Projectile* projs);
EnemyQueue CreateEnemyQueue(int nbrEnemies, Enemy base, SDL sdl);
Enemy* UpdateQueue(EnemyQueue queue, SDL sdl);
void SpawnEnemies(Scene* scene);
