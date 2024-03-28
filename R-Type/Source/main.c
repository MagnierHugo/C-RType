#include <SDL.h>

#include <stdio.h>
#include <stdbool.h>


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
	ErrorHandling("Thanks for playing", gameArgs.SDL); // not an error but actually cleans so it s convenient

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
		RenderText(sdl, args.State.Score, "Score: ",
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		RenderText(sdl, args.State.ShotFired, "Shots fired: ",
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 25);
	}
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	SDL sdlStruct = StartSDL();
	Scene* Levels = CreateLevels(1, sdlStruct);

	GameArgs gameArgs =
	{
		sdlStruct,
		InitGameState(),
		Levels,
	};

	StartMenu(gameArgs);
	gameArgs.State.DeltaTime = (SDL_GetTicks() - gameArgs.State.CurrentTime) / 1000;
	gameArgs.State.CurrentTime = SDL_GetTicks();
	gameArgs.Levels[0].Time = gameArgs.State.CurrentTime;
	//SpawnEnemies(gameArgs);
	int endGame;

	while (gameArgs.State.Continue)
	{
		gameArgs.State.DeltaTime = (SDL_GetTicks() - gameArgs.State.CurrentTime) / 1000;
		gameArgs.State.CurrentTime = SDL_GetTicks();

		HandleInputs(gameArgs.State, gameArgs.Levels[gameArgs.State.CurLVL]);
		Update(&gameArgs.State, &gameArgs.Levels[gameArgs.State.CurLVL], sdlStruct);
		Draw(gameArgs, gameArgs.Levels[gameArgs.State.CurLVL]);

		SDL_Delay(FRAMERATE);

		endGame = CheckEndGame(gameArgs.Levels[gameArgs.State.CurLVL]);
		if (endGame > 0)
		{
			gameArgs.State.CurLVL++;
			ClearScene(gameArgs.Levels[gameArgs.State.CurLVL], gameArgs.SDL);
			if (gameArgs.State.CurLVL + 1 == LEVEL_COUNT) break;
		}
		else if (endGame < 0)
		{
			gameArgs.State.CurLVL = -1;
			ClearScene(gameArgs.Levels[gameArgs.State.CurLVL], gameArgs.SDL);
			break;
		}
	}

	EndScreen(gameArgs);
	SDL_Delay(50000);
	QuitGame(gameArgs);
	return 1;
}





	



