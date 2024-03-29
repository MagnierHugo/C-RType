#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "../Include/Structs.h"
#include "../Include/Init.h"
#include "../Include/HandleSDL.h"
#include "../Include/Utility.h"
#include "../Include/Levels.h"


Scene* CreateLevels(int nbrLevels, SDL sdl)
{
	Scene* levels = malloc(nbrLevels * sizeof(Scene));
	CheckPointerKill(levels, "Error Allocating Memory for levels", sdl);

	for (int levelIndex = 0; levelIndex < nbrLevels; levelIndex++)
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

void ClearScene(Scene scene, SDL sdl)
{
	if (scene.Players) { free(scene.Players); }
	if (scene.Projectiles) { free(scene.Projectiles); }
	if (scene.Queue.Enemies) { free(scene.Queue.Enemies); }
	printf("cleared scene");
}
