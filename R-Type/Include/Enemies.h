#include <SDL.h>
#include <stdio.h>

#include "Constants.h"
#include "Structs.h"


Enemy* FindIdleEnemy(Enemy* enemies);
void SpawnEnemies(GameArgs gameArgs);
void SetupEnemy(Enemy* enemy);