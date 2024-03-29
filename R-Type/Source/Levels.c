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
		Levels[LevelIndex] = InitScene(sdl, 5, -1, 0);
	}

	return Levels;
}