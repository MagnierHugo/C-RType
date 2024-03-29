#include <SDL.h>

#include <stdio.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Utility.h"
#include "../Include/HandleSDL.h"


Animation CreateAnime(SDL_Texture** Tex, int nbrFrames, int wait, int* pos)
{
	Animation animation = {
		nbrFrames, 0, wait, NULL,
		(SDL_Rect) {pos[0], pos[1], BOOM_WIDTH, BOOM_HEIGTH},
		Tex
	};

	return animation;
}

Animation* AddAnimation(SDL sdl, AnimeArgs* args)
{
	int nbrAnimation = sdl.nbrAnimation;

	Animation anime = CreateAnime(args->Tex, args->nbrFrames, args->Wait, &args->pos);

	Animation* newAnimes = malloc(nbrAnimation * sizeof(Animation));
	CheckPointer(newAnimes, "Error Allocating memory for add animations", sdl);

	for (int index = 0; index < nbrAnimation - 1; index++)
	{
		newAnimes[index] = sdl.animes[index];
	}

	newAnimes[nbrAnimation - 1] = anime;

	return newAnimes;
}

//Animation CreateAnime(SDL_Texture** Tex, int nbrFrames, int posX, int posY)
//{
//	Animation animation = {
//		nbrFrames, 0, 1000 / nbrFrames, NULL,
//		(SDL_Rect) { posX, posY, BOOM_WIDTH, BOOM_HEIGTH },
//		Tex
//	};
//
//	return animation;
//}
//
//Animation* AddAnimation(SDL sdl, SDL_Texture** Tex, int nbrFrames, int pos[2])
//{
//	int nbrAnimation = sdl.nbrAnimation;
//
//	Animation anime = CreateAnime(Tex, nbrFrames, pos[0], pos[1]);
//
//	Animation* newAnimes = malloc(nbrAnimation * sizeof(Animation));
//	CheckPointer(newAnimes, "Error Allocating memory for add animations", sdl);
//
//	for (int index = 0; index < nbrAnimation - 1; index++)
//	{
//		newAnimes[index] = sdl.animes[index];
//	}
//
//	newAnimes[nbrAnimation - 1] = anime;
//
//	return newAnimes;
//}

Animation* DeleteAnimation(SDL sdl, int delPos)
{
	int nbrAnimation = sdl.nbrAnimation;

	Animation* oldAnimes = sdl.animes;
	Animation* newAnimes = malloc(nbrAnimation * sizeof(Animation));
	CheckPointer(newAnimes, "Error Allocating memory for delete animation", sdl);

	bool skipOne = false;

	for (int index = 0; index < nbrAnimation; index++)
	{
		if (index == delPos) { skipOne = true; }
		newAnimes[index] = oldAnimes[index + skipOne];
	}

	free(oldAnimes);
	return newAnimes;
}

static void RunAnimation(SDL sdl, Animation* anim)
{
	SDL_Rect animRect = anim->rect;
	SDL_RenderCopy(sdl.renderer, anim->Frames[anim->curFrame], NULL, &animRect);

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
