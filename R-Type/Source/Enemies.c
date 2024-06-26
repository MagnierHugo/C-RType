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

	for (int index = 0; index < queue.nbrEnemies; index++)
	{
		if (oldQueue[index].HP <= 0) { skipOne = true; }
		newQueue[index] = oldQueue[index + skipOne];
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

