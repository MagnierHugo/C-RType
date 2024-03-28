#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#include "../Include/HandleSDl.h"
#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Init.h"
#include "../Include/Update.h"
#include "../Include/Draw.h"
#include "../Include/Inputs.h"
#include "../Include/Menu.h"
#include "../Include/StartMenu.h"
#include "../Include/Levels.h"
#include "../Include/Enemies.h"
#include "../Include/Utility.h"
#include "../Include/Text.h"


static void ClearScene(Scene scene, SDL sdl)
{
	/*
	CheckPointer(scene.Players, "no player", sdl);
	CheckPointer(scene.Enemies, "no enemies", sdl);
	CheckPointer(scene.Projectiles, "no projectiles", sdl);
	CheckPointer(scene.Players);
	CheckPointer(scene.Enemies);
	CheckPointer(scene.Projectiles);*/
	if (scene.Players) { free(scene.Players); }
	if (scene.Projectiles) { free(scene.Projectiles); }
	if (scene.Queue.Enemies) { free(scene.Queue.Enemies); }
	printf("cleared scene");
}

static void QuitGame(GameArgs gameArgs)
{
	// clear textures
	printf("Thanks for playing"); // not an error but actually cleans so it s convenient
	CloseSDL(gameArgs);
	exit(EXIT_SUCCESS);
}

// -1 lost | 0 in progress | 1 won
static int CheckEndGame(Scene scene)
{
	if (!scene.Players[0].Active && !scene.Players[1].Active) return -1; // lost bc both dead

	/*for (int i = 0; i < MAX_ENEMY_CNT; i++)
	{
		if (scene.Enemies[i].Active) return 0;
	}*/

	if (scene.ActiveEnemies > 0 || !scene.waveEnd) return 0;

	return 1;
}

void EndScreen(GameArgs args) {
	SDL sdl = args.SDL;
	SDL_Event event;
	bool loop = true;
	while (loop) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) loop = false;
			//else if (event.type == SDL_KEYDOWN) loop = false;
			else if (event.type == SDL_MOUSEBUTTONDOWN) loop = false;
		}
		SDL_RenderCopy(sdl.renderer, sdl.Tex.Background, NULL, NULL);
		RenderText(sdl, "Score: ", args.State.Score,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		RenderText(sdl, "Shots fired: ", args.State.ShotFired,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 25);
	}
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	SDL sdlStruct = StartSDL();
	Scene* Levels = CreateLevels(LEVEL_COUNT, sdlStruct);

	GameArgs gameArgs =
	{
		sdlStruct,
		InitGameState(),
		Levels,
	};

	StartMenu(gameArgs);
	gameArgs.State.DeltaTime = (SDL_GetTicks() - gameArgs.State.CurrentTime) / 1000;
	gameArgs.State.CurrentTime = SDL_GetTicks();
	//SpawnEnemies(gameArgs);

	for (int i = 0; i < LEVEL_COUNT; i++)
	{
		gameArgs.Levels[i].Time = gameArgs.State.CurrentTime;
		int endGame;
		while (gameArgs.State.Continue)
		{
			gameArgs.State.DeltaTime = (SDL_GetTicks() - gameArgs.State.CurrentTime) / 1000;
			gameArgs.State.CurrentTime = SDL_GetTicks();

			HandleInputs(gameArgs.State, gameArgs.Levels[i]);
			Update(&gameArgs.State, &gameArgs.Levels[i], sdlStruct);
			Draw(gameArgs, gameArgs.Levels[i]);

			SDL_Delay(FRAMERATE);

			endGame = CheckEndGame(gameArgs.Levels[i]);
			if (endGame > 0)
			{
				ClearScene(gameArgs.Levels[i], gameArgs.SDL);
				break;
			}
			else if (endGame < 0)
			{
				ClearScene(gameArgs.Levels[i], gameArgs.SDL);
				gameArgs.State.Continue = false;
			}
		}
	}

	EndScreen(gameArgs);
	QuitGame(gameArgs);

	return 0;
}





	



