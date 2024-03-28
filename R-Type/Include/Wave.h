#pragma once

Wave* CreateWaves(int nbrEnemies, int maxEnemiesPerWave, int baseWait, SDL sdl);
struct Wave PopWave(Scene* scene);