#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/HandleSDL.h"
#include "../Include/Utility.h"

void RenderText(SDL sdl, char* text, int toRender, int x, int y)
{
	char textBuffer[30];
	if (toRender != DONT_RENDER_FLAG) snprintf(textBuffer, 30, "%s%d", text, toRender); // Mettre � jour le texte avec la nouvelle valeur
	else snprintf(textBuffer, 30, "%s", text); // same
	
	SDL_Surface* surface = TTF_RenderText_Solid(sdl.Font, textBuffer,
		(SDL_Color) { 255, 255, 255, 255 });
	CheckPointer(surface, "Erreur lors de la creation du texte", sdl);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl.renderer, surface); // Convertir la surface en texture
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		ErrorHandling("Erreur lors de la cr�ation de la texture de texte", sdl);
	}

	SDL_Rect textRect = { x - surface->w / 2, y - surface->h / 2,
		surface->w, surface->h
	};

	SDL_RenderCopy(sdl.renderer, texture, NULL, &textRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

