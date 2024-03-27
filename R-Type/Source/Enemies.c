#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Enemies.h"
#include "../Include/Utility.h"
#include "../Include/Wave.h"

/*
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
*/

Enemy* FindIdleEnemy(Enemy* enemies)
{
	for (int i = 0; i < MAX_ENEMY_CNT; i++)
	{
		if (!enemies[i].Active) return &enemies[i];
	}
	printf("No available enemy expand the buffer");
	return &enemies[0]; // wont compile otherwise
}

void SetupEnemy(Enemy* enemy)
{
	enemy->Active = true;
	enemy->X += RdmInt(0, MAX_SPAWN_X_OFFSET, false);
	enemy->Y = RdmInt(0, SCREEN_HEIGHT - ENEMIES_HEIGHT, false);
	enemy->DropBoost = rand() % 2;
}

void SpawnEnemies(GameArgs gameArgs)
{
	int currentLevel = gameArgs.State.CurrentLevel;
	for (int i = 0; i < gameArgs.Levels[currentLevel].EnemyCount; i++)
	{
		SetupEnemy(FindIdleEnemy(gameArgs.Levels[currentLevel].Enemies));
	}
}

