#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Rect.h"
#include "../Include/Animation.h"
#include "../Include/Player.h"
#include "../Include/Bonus.h"


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
		}
	}
}

// returns how much point for the kill else 0 as no kill
int CheckEnemyProjCollision(GameState state, Enemy* enemy, Scene* scene, SDL* sdl)
{
	EnemyQueue* queue = &scene->Queue;
	Projectile* projs = scene->Projectiles;

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
			if (enemy->HP <= 0) { 
				int pos[2] = { enemy->X, enemy->Y };
				sdl->nbrAnimation++;
				sdl->animes = AddAnimation(*sdl, sdl->Tex.Boom, BOOM_FRAMES, pos);
				if (enemy->DropBoost) SpawnBonus(scene->Bonuses, enemy->X, enemy->Y);
				return enemy->AwardedPoints;
			}
		}
	}
	return 0;
}

void CheckPickupBonus(Player* players, Bonus* bonus) {
	
	SDL_Rect bonusRect = BonusAsRect(*bonus);
	for (int player = 0; player < PLAYER_CNT; player++) {
		if (!players[player].Active) continue;
		SDL_Rect playerRect = PlayerAsRect(players[player]);
		if (SDL_HasIntersection(&playerRect, &bonusRect)) {
		printf("been there\n");
			switch (bonus->DoWhat) {
				case HEALTH_BONUS:
					players[player].Health++;
					break;

				case SPEED_BONUS:
					players[player].Speed += 200;
					break;
			}
			bonus->Active = false;
		}
	}
}