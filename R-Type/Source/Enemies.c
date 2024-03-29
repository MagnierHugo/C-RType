#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Enemies.h"
#include "../Include/Utility.h"
#include "../Include/Wave.h"
#include "../Include/Player.h"
#include "../Include/HandleSDL.h"


static EnemyQueue AllocateMemory(int nbrEnemies, SDL sdl)
{
	Enemy* enemies = malloc(nbrEnemies * sizeof(Enemy));
	if (enemies == NULL) {
		ErrorHandling("Error Allocating Memory for enemies", sdl);
	}

	EnemyQueue queue = {
		enemies,
		nbrEnemies
	};

	return queue;
}

EnemyQueue CreateEnemyQueue(int nbrEnemies, Enemy base, SDL sdl)
{
	EnemyQueue queue = AllocateMemory(nbrEnemies, sdl);

	for (int queueIndex = 0; queueIndex < nbrEnemies; queueIndex++)
	{
		Enemy enemy = base;

		enemy.DropBoost = RdmInt(0, 4, true) % 4 == 0 ? true : false;
		enemy.X += RdmInt(0, 300, false);
		enemy.Y = RdmInt(0, SCREEN_HEIGHT - ENEMIES_HEIGHT, false);

		if (queueIndex > nbrEnemies * 0.25) {
			if (queueIndex < nbrEnemies * 0.75) {
				enemy.HP += RdmInt(0, enemy.HP / 2, true);
			}
			else {
				enemy.HP += RdmInt(enemy.HP / 2, enemy.HP, false);
			}
		}

		queue.Enemies[queueIndex] = enemy;
	}

	return queue;
}

Enemy* UpdateQueue(EnemyQueue queue, SDL sdl)
{
	Enemy* oldQueue = queue.Enemies;
	Enemy* newQueue = malloc(queue.nbrEnemies * sizeof(Enemy));
	if (newQueue == NULL) {
		ErrorHandling("Error Allocating Memory for newQueue", sdl);
	}

	bool skipOne = false;

	for (int Index = 0; Index < queue.nbrEnemies; Index++)
	{
		if (oldQueue[Index].HP <= 0) { skipOne = true; }
		newQueue[Index] = oldQueue[Index + skipOne];
	}

	free(oldQueue);
	return newQueue;
}

void SpawnEnemies(Scene* scene)
{
	if ((scene->Time + scene->WaitTime) <= SDL_GetTicks() && !scene->waveEnd) {
		Wave wave = PopWave(scene);
		scene->ActiveEnemies += wave.nbrEnemies;
		scene->WaitTime = wave.Wait;
		scene->Time = SDL_GetTicks();
		scene->waveEnd = wave.isEnd;
	}
}

//Enemy* FindIdleEnemy(Enemy* enemies)
//{
//	for (int i = 0; i < MAX_ENEMY_CNT; i++)
//	{
//		if (!enemies[i].Active) return &enemies[i];
//	}
//	printf("No available enemy expand the buffer");
//	return &enemies[0]; // wont compile otherwise
//}
//
//void SetupEnemy(Enemy* enemy)
//{
//	enemy->Active = true;
//	enemy->X += RdmInt(0, MAX_SPAWN_X_OFFSET, false);
//	enemy->Y = RdmInt(0, SCREEN_HEIGHT - ENEMIES_HEIGHT, false);
//	enemy->DropBoost = rand() % 2;
//}
//
//void SpawnEnemies(GameArgs gameArgs)
//{
//	int currentLevel = gameArgs.State.CurLVL;
//	for (int i = 0; i < gameArgs.Levels[currentLevel].EnemyCount; i++)
//	{
//		SetupEnemy(FindIdleEnemy(gameArgs.Levels[currentLevel].Enemies));
//	}
//}

