#include <SDL.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"


Boss CreateBoss()
{
	Boss boss = {
		(Enemy) {SCREEN_WIDTH, (SCREEN_HEIGHT - BOSS_HEIGHT) / 2, -1, 0,
		BOSS_WIDTH, BOSS_HEIGHT, BOSS_SPEED, LEVEL_COUNT * 20,
		2000 * LEVEL_COUNT, false },
		true
	};

	return boss;
}

