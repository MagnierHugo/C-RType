#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Utility.h"
#include "../Include/HandleSDL.h"


static void DrawPlayer(Player* players, SDL sdl)
{
	for (int i = 0; i < PLAYER_CNT; i++)
	{
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

static void RenderScore( SDL sdl,  GameState state)
{
	char textBuffer[20];
	snprintf(textBuffer, 20, "Texte : %d", state.Score); // Mettre à jour le texte avec la nouvelle valeur
	SDL_Rect textRect;
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(sdl.Font, textBuffer, ( SDL_Color) { 255, 255, 255, 255 });
	if (scoreSurface == NULL) {
		ErrorHandling("Erreur lors de la creation du texte score", sdl);
	}


	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl.renderer, scoreSurface); // Convertir la surface en texture
	if (texture == NULL) {
		SDL_FreeSurface(scoreSurface);
		ErrorHandling("Erreur lors de la création de la texture de texte", sdl);
	}

	textRect.w = scoreSurface->w;
	textRect.h = scoreSurface->h;
	textRect.x = (SCREEN_WIDTH - scoreSurface->w) / 2;
	textRect.y = SCORE_Y  - scoreSurface->h / 2;

	SDL_RenderCopy(sdl.renderer, texture, NULL, &textRect);

	SDL_FreeSurface(scoreSurface);
	SDL_DestroyTexture(texture);
}

//static void DrawEnemies(Scene scene, SDL sdlStruct)
//{
//	for (int enemyIndex = 0; enemyIndex < scene.ActiveEnemies; enemyIndex++)
//	{
//		Enemy curEnemy = scene.Queue.Enemies[enemyIndex];
//		SDL_RenderCopy(sdlStruct.renderer, curEnemy.Tex, NULL, &curEnemy.rect);
//	}
//}
// 
static void DrawEnemies(Scene scene, SDL sdl)
{
	for (int enemy = 0; enemy < scene.EnemyCount; enemy++)
	{

		Enemy curEnemy = scene.Enemies[enemy];
		if (!curEnemy.Active) continue;

		SDL_Rect enemyRect = EnemyAsRect(curEnemy);
		SDL_RenderCopy(sdl.renderer, curEnemy.Tex, NULL, &enemyRect);
	}
}
//{
//	for (int enemyIndex = 0; enemyIndex < scene.ActiveEnemies; enemyIndex++)
//	{
//		Enemy curEnemy = scene.Queue.Enemies[enemyIndex];
//		SDL_RenderCopy(sdlStruct.renderer, curEnemy.Tex, NULL, &curEnemy.rect);
//	}
//}

void Draw( GameArgs gameArgs, Scene curScene)
{
	SDL sdl = gameArgs.SDL;
	SDL_Renderer* renderer = sdl.renderer;

	SDL_Texture* background = curScene.Background;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	DrawPlayer(curScene.Players, sdl);
	DrawEnemies(curScene, sdl);
	DrawProjectiles(curScene.Projectiles, sdl);
	RenderScore(sdl, gameArgs.State);
	SDL_RenderPresent(renderer); // update display
}
