#include <SDL.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Utility.h"
#include "../Include/Wave.h"


EnemyQueue CreateEnemyQueue(int nbrEnemies, Enemy base)
{
	EnemyQueue queue = {
		malloc(nbrEnemies * sizeof(Enemy)),
		nbrEnemies
	};

	for (int queueIndex = 0; queueIndex < nbrEnemies; queueIndex++)
	{
		Enemy enemy = base;

		enemy.DropBoost = RdmInt(0, 4, true) % 4 == 0 ? true : false;
		enemy.rect = (SDL_Rect){
			RdmInt(0, SCREEN_WIDTH - ENEMIES_WIDTH, false), RdmInt(0, SCREEN_HEIGHT - ENEMIES_HEIGHT, false),
			ENEMIES_WIDTH, ENEMIES_HEIGHT
		};

		if (queueIndex < nbrEnemies * 0.75) {
			enemy.HP += RdmInt(0, enemy.HP / 2, true);
		}
		else if (queueIndex < nbrEnemies - 1) {
			enemy.HP += RdmInt(enemy.HP / 2, enemy.HP, false);
		}
		else {
			enemy.HP *= 4;
			enemy.DropBoost = false;
		}

		queue.Enemies[queueIndex] = enemy;
	}

	return queue;
}

Enemy* UpdateQueue(EnemyQueue queue)
{
	Enemy* oldQueue = queue.Enemies;
	Enemy* newQueue = malloc(queue.nbrEnemies * sizeof(Enemy));

	for (int Index = 0; Index < queue.nbrEnemies; Index++)
	{
		if (oldQueue[Index].HP <= 0) {
			oldQueue[Index], oldQueue[Index + 1] = oldQueue[Index + 1], oldQueue[Index];
		}
		newQueue[Index] = oldQueue[Index];
	}

	free(oldQueue);
	return newQueue;
}

void SpawnEnemies(Scene scene)
{
	scene.ActiveEnemies += PopWave(scene).nbrEnemies;
}