#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Utility.h"
#include "../Include/HandleSDL.h"
#include "../Include/Draw.h"


void RenderLevel(SDL sdl, GameState state)
{
	char textBuffer[20];
	snprintf(textBuffer, 20, "Level : %d", state.CurrentLevel);
	SDL_Rect textRect;
	SDL_Surface* levelSurface = TTF_RenderText_Solid(sdl.Font, textBuffer, (SDL_Color) { 255, 255, 255, 255 });
	if (levelSurface == NULL) {
		ErrorHandling("Erreur texte score", sdl);
	}


	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl.renderer, levelSurface);
	if (texture == NULL) {
		SDL_FreeSurface(levelSurface);
		ErrorHandling("Erreur texture de texte", sdl);
	}

	textRect.w = levelSurface->w;
	textRect.h = levelSurface->h;
	textRect.x = (SCREEN_WIDTH - levelSurface->w) / 1.5;
	textRect.y = LEVEL_Y - levelSurface->h / 2;

	SDL_RenderCopy(sdl.renderer, texture, NULL, &textRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(levelSurface);
}

void Decoration(SDL sdl, GameState state) {

}