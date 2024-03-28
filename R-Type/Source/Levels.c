#include <SDL.h>

#include "../Include/Structs.h"
#include "../Include/Init.h"


Scene* CreateLevels(int nbrLevels, SDL sdl)
{
	Scene* levels = malloc(nbrLevels * sizeof(Scene));
	if (levels == NULL) {
		ErrorHandling("Error Allocating Memory for levels", sdl);
	}

	for (int levelIndex = 0; levelIndex < nbrLevels; levelIndex++)
	{
		levels[levelIndex] = InitScene(sdl, 5, -1, 0);
	}

	return levels;
}