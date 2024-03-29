#include <SDL.h>

#include "../Include/Structs.h"
#include "../Include/Init.h"
#include "../Include/HandleSDL.h"
#include "../Include/Utility.h"


Scene* CreateLevels(int nbrLevels, SDL sdl)
{
	Scene* Levels = malloc(nbrLevels * sizeof(Scene));
	CheckPointer(Levels, "Error Allocating Memory for levels", sdl);

	for (int LevelIndex = 0; LevelIndex < nbrLevels; LevelIndex++)
	{
		SDL_Texture* background;
		if (LevelIndex % nbrLevels < (int) (nbrLevels / 2)) {
			background = sdl.Tex.Background;
		}
		else {
			background = sdl.Tex.Background2;
		}
		Levels[LevelIndex] = InitScene(sdl, background, 9 * (LevelIndex + 1), 
			2 + LevelIndex, -1, 0);
	}

	return Levels;
}