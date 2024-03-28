#include <SDL.h>

#include "../Include/Structs.h"
#include "../Include/Init.h"


Scene* CreateLevels(int nbrLevels, SDL sdl)
{
	Scene* Levels = malloc(nbrLevels * sizeof(Scene));
	if (Levels == NULL) {
		ErrorHandling("Error Allocating Memory for levels", sdl);
	}

	for (int LevelIndex = 0; LevelIndex < nbrLevels; LevelIndex++)
	{
		Levels[LevelIndex] = InitScene(sdl);
	}

	return Levels;
}