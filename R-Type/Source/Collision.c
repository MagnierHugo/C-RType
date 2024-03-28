#include <SDL.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Rect.h"


void CheckEnemyPlayerCollision(GameState state, Enemy* enemy, Player* players)
{
	SDL_Rect enemyRect = EnemyAsRect(*enemy);
	for (int player = 0; player < PLAYER_CNT; player++)
	{
		if (!players[player].Active) continue;
		SDL_Rect playerRect = PlayerAsRect(players[player]);
		if (SDL_HasIntersection(&playerRect, &enemyRect))
		{
			if (TakeHit(&players[player], state)) { ResetPlayer(&players[player]); }
			//ResetScene(scene);
		}
	}
}

// returns how much point for the kill else 0 as no kill
int CheckEnemyProjCollision(GameState state, Enemy* enemy, EnemyQueue* queue, Projectile* projs, SDL sdl)
{
	SDL_Rect enemyRect = EnemyAsRect(*enemy);
	for (int proj = 0; proj < MAX_PROJECTILES; proj++)
	{
		Projectile* curProj = &projs[proj];
		if (!curProj->Active) { continue; }
		SDL_Rect projRect = ProjectileAsRect(*curProj);
		if (SDL_HasIntersection(&projRect, &enemyRect))
		{
			curProj->Active = false;
			enemy->HP -= 1;
			if (enemy->HP <= 0) { return enemy->AwardedPoints; }
		}
	}
	return 0;
}