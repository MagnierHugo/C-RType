#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Rect.h"
#include "../Include/Animation.h"
#include "../Include/Player.h"
#include "../Include/Bonus.h"
#include "../Include/Music.h"
#include "../Include/Utility.h"


void CheckEnemyPlayerCollision(GameState state, Enemy* enemy, Player* players)
{
	SDL_Rect enemyRect = EnemyAsRect(*enemy);
	for (int player = 0; player < PLAYER_CNT; player++)
	{
		if (!players[player].Active) continue;
		SDL_Rect playerRect = PlayerAsRect(players[player]);
		if (SDL_HasIntersection(&playerRect, &enemyRect))
		{
			TakeHit(&players[player], state);
		}
	}
}

// returns how much point for the kill else 0 as no kill
int CheckEnemyProjCollision(GameState state, Enemy* enemy,
	Scene* scene, SDL* sdl)
{
	EnemyQueue* queue = &scene->Queue;
	Projectile* projs = scene->Projectiles;

	SDL_Rect enemyRect = EnemyAsRect(*enemy);
	for (int proj = 0; proj < MAX_PROJECTILES; proj++)
	{
		Projectile* curProj = &projs[proj];
		if (!curProj->Active) { continue; }
		SDL_Rect projRect = ProjectileAsRect(*curProj);
		if (SDL_HasIntersection(&projRect, &enemyRect) && curProj->ShotByPlayer)
		{
			curProj->Active = false;
			enemy->HP -= 1;
			if (enemy->HP <= 0) { 
				SDL_Rect rect = { enemy->X, enemy->Y, BOOM_WIDTH, BOOM_HEIGTH };
				PlaySound(KABOOM, *sdl);
				sdl->nbrAnimation++;
				sdl->animes = AddAnimation(*sdl, sdl->Tex.Boom, BOOM_FRAMES,
					BOOM_WAIT_BETWEEN_FRAMES, rect);
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

int CheckBossProjCollision(GameState state, Boss* boss, Scene* scene, SDL* sdl)
{
	Projectile* projs = scene->Projectiles;

	SDL_Rect bossRect = boss->animation.rect;
	for (int proj = 0; proj < MAX_PROJECTILES; proj++){
		Projectile* curProj = &projs[proj];
		if (!curProj->Active) { continue; }
		SDL_Rect projRect = ProjectileAsRect(*curProj);
		if (SDL_HasIntersection(&projRect, &bossRect) && curProj->ShotByPlayer) {
			curProj->Active = false;
			if (--boss->HP <= 0) {
				for (int i = 0; i < BOSS_BOOM_COUNT; i++) {
				SDL_Rect rect = { boss->animation.rect.x +
					RdmInt(-BOSS_BOOM_OFFSET, BOSS_BOOM_OFFSET, false), 
					boss->animation.rect.y +
					RdmInt(-BOSS_BOOM_OFFSET, BOSS_BOOM_OFFSET, false),
					BOOM_WIDTH, BOOM_HEIGTH};
				PlaySound(KABOOM, *sdl);
				sdl->nbrAnimation++;
				sdl->animes = AddAnimation(*sdl, sdl->Tex.Boom, BOOM_FRAMES,
					BOOM_WAIT_BETWEEN_FRAMES, rect);
				}
				return boss->AwardedPoints;

			}
		}
	}
	return 0;
}

void CheckPlayerProjCollision(GameState state,
	Player* players, Scene* scene, SDL* sdl)
{
	Projectile* projs = scene->Projectiles;
	for (int i = 0; i < PLAYER_CNT; i++)
	{
		SDL_Rect playerRect = PlayerAsRect(players[i]);
		for (int proj = 0; proj < MAX_PROJECTILES; proj++)
		{
			Projectile* curProj = &projs[proj];
			if (!curProj->Active) { continue; }

			SDL_Rect projRect = ProjectileAsRect(*curProj);
			if (SDL_HasIntersection(&projRect, &playerRect) && !curProj->ShotByPlayer)
			{
				curProj->Active = false;
				TakeHit(&players[i], state);
			}
		}
	}
}

