#include <SDL.h>

#include <stdio.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Utility.h"
#include "../Include/HandleSDL.h"


Animation CreateAnime(SDL_Texture** Tex, int nbrFrames,
	int wait, SDL_Rect rect)
{
	Animation animation = {
		nbrFrames, 0, 1000 / nbrFrames, NULL,
		rect, Tex
	};

	return animation;
}

Animation* AddAnimation(SDL sdl, SDL_Texture** Tex,
	int nbrFrames, int wait, SDL_Rect rect)
{
	int nbrAnimation = sdl.nbrAnimation;

	Animation anime = CreateAnime(Tex, nbrFrames, wait, rect);

	Animation* newAnimes = malloc(nbrAnimation * sizeof(Animation));
	CheckPointerKill(newAnimes, "Error Allocating memory for add animations", sdl);

	for (int index = 0; index < nbrAnimation - 1; index++)
	{
		newAnimes[index] = sdl.animes[index];
	}

	newAnimes[nbrAnimation - 1] = anime;

	return newAnimes;
}


Animation* DeleteAnimation(SDL sdl, int delPos)
{
	int nbrAnimation = sdl.nbrAnimation;

	Animation* oldAnimes = sdl.animes;
	Animation* newAnimes = malloc(nbrAnimation * sizeof(Animation));
	CheckPointerKill(newAnimes, "Error Allocating memory for delete animation", sdl);

	bool skipOne = false;

	for (int index = 0; index < nbrAnimation; index++)
	{
		if (index == delPos) { skipOne = true; }
		newAnimes[index] = oldAnimes[index + skipOne];
	}

	free(oldAnimes);
	return newAnimes;
}

void RunAnimation(SDL sdl, Animation* anim)
{
	SDL_Rect animRect = anim->rect;
	SDL_Texture** f = anim->Frames;
	SDL_Texture* a = f[anim->curFrame];
	SDL_RenderCopy(sdl.renderer, a, NULL, &animRect);

	if (anim->LastPlayed + anim->TimeBetweenFrames <= SDL_GetTicks()) { // 69 :) Nice
		anim->LastPlayed = SDL_GetTicks();
		anim->curFrame++;
	}
}

void RunAnimations(SDL* sdl)
{
	for (int index = 0; index < sdl->nbrAnimation; index++)
	{
		Animation* anime = &sdl->animes[index];
		if (anime->curFrame < anime->nbrFrames) { RunAnimation(*sdl, anime); }
		else {
			sdl->nbrAnimation--;
			sdl->animes = DeleteAnimation(*sdl, index);
		}
	}
}
