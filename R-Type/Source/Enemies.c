#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Utility.h"
#include "../Include/Wave.h"
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

Enemy* UpdateQueue(EnemyQueue queue, SDL sdl)
{
	Enemy* oldQueue = queue.Enemies;
	Enemy* newQueue = malloc(queue.nbrEnemies * sizeof(Enemy));
	if (newQueue == NULL) {
		ErrorHandling("Error Allocating Memory for newQueue", sdl);
	}

	for (int Index = 0; Index < queue.nbrEnemies; Index++)
	{
		if (oldQueue[Index].HP <= 0) {
			oldQueue[Index], oldQueue[Index + 1] = oldQueue[Index + 1], oldQueue[Index];
		}
		if (Index < queue.nbrEnemies) {
			newQueue[Index] = oldQueue[Index];
		}
	}

	free(oldQueue);
	return newQueue;
}

void SpawnEnemies(Scene* scene)
{
	if (scene->Time + scene->WaitTime <= SDL_GetTicks() && !scene->waveEnd) {
		printf("Wave head : %d\n", scene->waveHead);
		Wave wave = PopWave(scene);
		printf("Enemies in wave : %d\n", wave.nbrEnemies);
		scene->ActiveEnemies += wave.nbrEnemies;
		scene->WaitTime = wave.Wait;
		scene->Time = SDL_GetTicks();
		scene->waveEnd = wave.isEnd;
	}
}