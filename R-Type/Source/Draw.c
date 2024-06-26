#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Utility.h"
#include "../Include/HandleSDL.h"
#include "../Include/Text.h"
#include "../Include/Rect.h"
#include "../Include/Animation.h"
#include "../Include/Bonus.h"
#include "../Include/Boss.h"


static void DrawPlayer(Player* players, SDL sdl)
{
	for (int i = 0; i < PLAYER_CNT; i++)
	{
		if (!players[i].Active) continue;
		Player curPlayer = players[i];
		SDL_Rect playerRect = PlayerAsRect(curPlayer);

		SDL_RenderCopy(sdl.renderer, curPlayer.Tex, NULL, &playerRect);
	}
}

static void DrawProjectiles(Projectile* projectiles,  SDL sdl)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		Projectile curProjectile = projectiles[i];
		if (!curProjectile.Active) { continue; }
		SDL_Rect projRect = ProjectileAsRect(curProjectile);
		SDL_RenderCopy(sdl.renderer, sdl.Tex.Projectiles, NULL, &projRect);
	}
}

static void DrawEnemies(Scene scene, SDL sdl)
{
	/*for (int enemy = 0; enemy < scene.EnemyCount; enemy++)
	{

		Enemy curEnemy = scene.Enemies[enemy];
		if (!curEnemy.Active) continue;

		SDL_Rect enemyRect = EnemyAsRect(curEnemy);
		SDL_RenderCopy(sdl.renderer, curEnemy.Tex, NULL, &enemyRect);
	}*/
	for (int enemyIndex = 0; enemyIndex < scene.ActiveEnemies; enemyIndex++)
	{
		Enemy curEnemy = scene.Queue.Enemies[enemyIndex];
		SDL_Rect enemyRect = EnemyAsRect(curEnemy);

		SDL_RenderCopy(sdl.renderer, curEnemy.Tex, NULL, &enemyRect);
	}
}

void Draw(GameArgs* gameArgs, Scene curScene)
{
	SDL* sdl = &gameArgs->SDL;
	SDL_Renderer* renderer = sdl->renderer;

	SDL_RenderCopy(renderer, curScene.Background, NULL, NULL);

	DrawPlayer(curScene.Players, *sdl);
	DrawEnemies(curScene, *sdl);
	DrawProjectiles(curScene.Projectiles, *sdl);
	DrawBonuses(*sdl, curScene.Bonuses);
	if (gameArgs->State.CurLVL == LEVEL_COUNT &&
		gameArgs->Levels->Queue.nbrEnemies == 0) {
		DrawBoss(gameArgs);
	}

	RunAnimations(sdl);

	RenderText(*sdl, "Score : ", gameArgs->State.Score, SCREEN_WIDTH / 2, SCORE_Y);
	RenderText(*sdl, "Shots fired : ", gameArgs->State.ShotFired,
		SCREEN_WIDTH / 2, SHOTS_FIRED_Y);
	RenderText(*sdl, "HighScore : ", gameArgs->State.HighScore, SCREEN_WIDTH / 2,
		HIGHSCORE_Y);
	RenderText(*sdl, "Level : ", gameArgs->State.CurLVL,
		SCREEN_WIDTH / 2, LEVEL_Y);
	RenderText(*sdl, "Enemies killed : ", gameArgs->State.EnemyKilled,
		SCREEN_WIDTH / 2, ENEMY_KILLED_Y);
	SDL_RenderPresent(renderer); // update display
}
