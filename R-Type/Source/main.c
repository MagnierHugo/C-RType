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
#include "../Include/Levels.h"
#include "../Include/Enemies.h"


int main(int argc, char* argv[])
{
	SDL sdlStruct = StartSDL();
	Scene* Levels = CreateLevels(1, sdlStruct.Tex);

	GameArgs gameArgs =
	{
		sdlStruct,
		InitGameState(),
		Levels,
	};

	StartMenu(gameArgs);

	while (gameArgs.State.Continue)
	{
		gameArgs.State.DeltaTime = (SDL_GetTicks() - gameArgs.State.CurrentTime) / 1000;
		gameArgs.State.CurrentTime = SDL_GetTicks();

		HandleInputs(gameArgs.State, gameArgs.Levels[0]);
		Update(gameArgs.State, gameArgs.Levels[0]);
		Draw(gameArgs, gameArgs.Levels[0]);

		SDL_Delay(FRAMERATE);
	}

	return 1;
}

void QuitGame(GameArgs gameArgs)
{
	free(gameArgs.Levels[0].Players);
	free(gameArgs.Levels[0].Projectiles);
	ErrorHandling("Thanks for playing", gameArgs.SDL); // not an error but actually cleans so convenient

}