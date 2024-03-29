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
#include "../Include/HandleJoystick.h"
#include "../Include/Menu.h"
#include "../Include/Music.h"
#include "../Include/StartMenu.h"
#include "../Include/Levels.h"
#include "../Include/Enemies.h"
#include "../Include/Utility.h"
#include "../Include/Text.h"
#include "../Include/SaveAndLoad.h"


int QuitGame(GameArgs gameArgs)
{
	GameState state = gameArgs.State;
	SaveGameData(state.Score > state.HighScore ? state.Score : state.HighScore);
	printf("Thanks for playing");
	CloseSDL(gameArgs);
	exit(EXIT_SUCCESS);
	return 0;
}

static int CheckEndGame(Scene scene, SDL sdl) // -1 lost | 0 in progress | 1 won
{
	int result = 0;
	if (!scene.Players[0].Active && !scene.Players[1].Active) result = -1; // lost bc both dead
	
	if (scene.ActiveEnemies <= 0 && scene.waveEnd) result = 1;

	if (result != 0) ClearScene(scene, sdl);

	return result;
}

int EndScreen(GameArgs args)
{
	SDL sdl = args.SDL;
	GameState state = args.State;
	SDL_Event event;
	bool loop = true;
	while (loop) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) loop = false;
			//else if (event.type == SDL_KEYDOWN) loop = false;
			else if (event.type == SDL_MOUSEBUTTONDOWN) loop = false;
		}
		SDL_RenderCopy(sdl.renderer, sdl.Tex.Background, NULL, NULL);
		RenderText(sdl, "HighScore: ",
			state.Score > state.HighScore ? state.Score : state.HighScore,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25);
		RenderText(sdl, "Score: ", state.Score,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		RenderText(sdl, "Shots fired: ", state.ShotFired,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 25);
		SDL_RenderPresent(sdl.renderer);
	}
	return QuitGame(args);
}

void Tick(GameState* state)
{
	state->DeltaTime = (SDL_GetTicks() - state->CurrentTime) / 1000;
	state->CurrentTime = SDL_GetTicks();
}

int main(int argc, char* argv[])
{
	SDL sdlStruct = StartSDL();
	Scene* Levels = CreateLevels(LEVEL_COUNT, sdlStruct);
	GameArgs gameArgs = {sdlStruct, InitGameState(sdlStruct), Levels };

	StartMenu(gameArgs);
	Tick(&gameArgs.State);
	PlaySound(SONG, gameArgs.SDL);

	for (int i = 0; i < LEVEL_COUNT; i++) {
		gameArgs.Levels[i].Time = gameArgs.State.CurrentTime;
		int endGame;

		while (gameArgs.State.Continue)
		{
			Tick(&gameArgs.State);

			HandleInputs(&gameArgs);
			Update(&gameArgs.State, &gameArgs.Levels[i], sdlStruct, gameArgs);
			Draw(gameArgs, gameArgs.Levels[i]);
			SDL_Delay(FRAMERATE);

			endGame = CheckEndGame(gameArgs.Levels[i], gameArgs.SDL);
			if (endGame > 0) { break; }
			else if (endGame < 0) { gameArgs.State.Continue = false; }
		}
	}

	return EndScreen(gameArgs);
}





	



