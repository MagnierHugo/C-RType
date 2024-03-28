#pragma once

#include "../Include/Structs.h"

Wave* CreateWaves(int nbrEnemies, int maxEnemiesPerWave, int baseWait, SDL sdl);
Wave PopWave(Scene* scene);