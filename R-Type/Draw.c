#include <SDL.h>
#include <stdio.h>

#include "Constants.h"
#include "Utility.h"
#include "HandleSDL.h"

void DrawPlayer(Scene scene, SDL sdl)
{
	for (int i = 0; i < PLAYER_CNT; i++)
	{
		SDL_Rect playerRect = PlayerAsRect(scene.Players[i]);
		if (i) SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 255, 255);
		else SDL_SetRenderDrawColor(sdl.renderer, 0, 255, 0, 255);

		SDL_RenderFillRect(sdl.renderer, &playerRect);
	}
}

void DrawProjectiles(Scene scene,  SDL sdl)
{

	for (int i = 0; i < MAX_PROJECTILE_AMOUNT; i++)
	{
		if (!scene.Projectiles[i].Active) { continue; }
		SDL_Rect projRect = ProjectileAsRect(scene.Projectiles[i]);
		SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 255);

		SDL_RenderFillRect(sdl.renderer, &projRect);
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

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(scoreSurface);
}

void Draw( GameArgs gameArgs)
{
	SDL_SetRenderDrawColor(gameArgs.SDL.renderer, 0, 0, 0, 255);
	SDL_RenderClear(gameArgs.SDL.renderer);
	DrawPlayer(gameArgs.Scene, gameArgs.SDL);
	DrawProjectiles(gameArgs.Scene, gameArgs.SDL);
	RenderScore(gameArgs.SDL, gameArgs.State);
	SDL_RenderPresent(gameArgs.SDL.renderer); // update display
}
