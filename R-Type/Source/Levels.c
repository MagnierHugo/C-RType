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
		levels[levelIndex] = InitScene(sdl, 5, -1, 0, levelIndex);
	}

	return levels;
}

void ClearScene(Scene scene, SDL sdl)
{
	if (scene.Players) { free(scene.Players); }
	if (scene.Projectiles) { free(scene.Projectiles); }
	if (scene.Bonuses) { free(scene.Bonuses); }
	if (scene.Queue.Enemies) { free(scene.Queue.Enemies); }
	printf("cleared scene");
}
