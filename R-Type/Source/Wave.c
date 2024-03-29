#include <stdio.h>
#include <stdlib.h>

#include "../Include/Structs.h"
#include "../Include/Utility.h"
#include "../Include/HandleSDL.h"


Wave* CreateWaves(int nbrEnemies, int maxEnemiesPerWave, int baseWait, SDL sdl)
{
	int size = nbrEnemies;
	int* enemies = malloc(size * sizeof(int));
	CheckPointerKill(enemies, "Error Allocating Memory for enemies in Wave", sdl);

	int enemiesInWave;
	int waveNumber = 0;

	while (nbrEnemies > 0) {
		if (nbrEnemies > maxEnemiesPerWave) {
			enemiesInWave = RdmInt(1, maxEnemiesPerWave, true);
		}
		else { enemiesInWave = RdmInt(1, nbrEnemies, true); }
		if (waveNumber < size) {
			enemies[waveNumber] = enemiesInWave;
			nbrEnemies -= enemiesInWave;
			waveNumber++;
		}
	}

	Wave* waves = malloc(waveNumber * sizeof(Wave));
	CheckPointerKill(enemies, "Error Allocating Memory for waves", sdl);
	for (int waveIndex = 0; waveIndex < waveNumber; waveIndex++) {
		waves[waveIndex] = (Wave){ enemies[waveIndex], 
			baseWait + baseWait / 3 * enemies[waveIndex],
			waveIndex == waveNumber - 1 ? true : false };
	}

	free(enemies);
	return waves;
}

Wave PopWave(Scene* scene)
{
	Wave wave = scene->waves[scene->waveHead];
	scene->waveHead++;

	return wave;
}
