#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Utility.h"
#include "../Include/Wave.h"


static EnemyQueue AllocateMemory(int nbrEnemies)
{
	Enemy* enemies = malloc(nbrEnemies * sizeof(Enemy));

	EnemyQueue queue = {
		enemies,
		nbrEnemies
	};

	return queue;
}

EnemyQueue CreateEnemyQueue(int nbrEnemies, Enemy base)
{
	EnemyQueue queue = AllocateMemory(nbrEnemies);

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
	if (scene.Time + scene.WaitTime <= SDL_GetTicks()) {
		Wave wave = PopWave(scene);
		printf("Wave head : %d / Wave nbrEnemies : %d\n", scene.waveHead, wave.nbrEnemies);

		scene.ActiveEnemies += wave.nbrEnemies;
		scene.WaitTime = wave.Wait;
		scene.Time = SDL_GetTicks();
	}
}