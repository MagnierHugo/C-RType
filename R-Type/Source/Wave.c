#include "../Include/Structs.h"
#include "../Include/Utility.h"


Wave* CreateWaves(int nbrEnemies, int maxEnemiesPerWave, int baseWait)
{
	int* enemies = malloc(nbrEnemies * sizeof(int));
	int enemiesInWave;

	int waveNumber = 0;

	while (nbrEnemies > 0) {
		if (nbrEnemies > maxEnemiesPerWave) {
			enemiesInWave = RdmInt(1, maxEnemiesPerWave, true);
		}
		else {
			enemiesInWave = RdmInt(1, nbrEnemies, true);
		}

		enemies[waveNumber] = enemiesInWave;
		nbrEnemies -= enemiesInWave;
		waveNumber++;
	}

	Wave* waves = malloc(waveNumber * sizeof(Wave));

	for (int waveIndex = 0; waveIndex < waveNumber; waveIndex++) {
		waves[waveIndex] = (Wave){
			enemies[waveIndex],
			baseWait + baseWait / 2 * enemies[waveIndex]
		};
	}

	free(enemies);
	return waves;
}

Wave PopWave(Scene scene)
{
	Wave wave = scene.waves[scene.waveHead];
	scene.waveHead++;

	return wave;
}