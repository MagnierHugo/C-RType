#include <SDL.h>

#include <stdio.h>
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
#include "../Include/Menu.h"
#include "../Include/Levels.h"
#include "../Include/Enemies.h"


int main(int argc, char* argv[])
{
	srand(time(NULL));
	SDL sdlStruct = StartSDL();
	Scene* Levels = CreateLevels(1, sdlStruct);

	GameArgs gameArgs =
	{
		sdlStruct,
		InitGameState(sdlStruct),
		Levels,
	};

	StartMenu(gameArgs);
	gameArgs.Levels[0].Time = SDL_GetTicks();

	while (gameArgs.State.Continue)
	{
		gameArgs.State.DeltaTime = (SDL_GetTicks() - gameArgs.State.CurrentTime) / 1000;
		gameArgs.State.CurrentTime = SDL_GetTicks();

		HandleInputs(gameArgs.State, gameArgs.Levels[gameArgs.State.CurrentLevel]);
		Update(gameArgs.State, &gameArgs.Levels[gameArgs.State.CurrentLevel]);
		Draw(gameArgs, gameArgs.Levels[gameArgs.State.CurrentLevel]);

		SDL_Delay(FRAMERATE);
	}

	return 1;
}

void QuitGame(GameArgs gameArgs)
{
	for (int level = 0; level < LEVEL_COUNT; level++) // better to handle it level by level
	{
		free(gameArgs.Levels[level].Players);
		free(gameArgs.Levels[level].Projectiles);
	}
	
	ErrorHandling("Thanks for playing", gameArgs.SDL); // not an error but actually cleans so convenient

}