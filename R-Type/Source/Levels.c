#include <SDL.h>

#include "../Include/Structs.h"
#include "../Include/Init.h"


struct Scene* CreateLevels(int nbrLevels, Textures Tex)
{
	Scene* Levels = malloc(nbrLevels * sizeof(Scene));

	for (int LevelIndex = 0; LevelIndex < nbrLevels; LevelIndex++)
	{
		Levels[LevelIndex] = InitScene(Tex);
	}

	return Levels;
}