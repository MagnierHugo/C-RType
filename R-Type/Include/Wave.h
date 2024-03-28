#pragma once

struct Wave* CreateWaves(int nbrEnemies, int maxEnemiesPerWave, int baseWait);
struct Wave PopWave(struct Scene scene);