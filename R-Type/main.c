#include <SDL.h>

#include <stdio.h>
#include <stdbool.h>


#include "HandleSDl.h"
#include "Constants.h"
#include "Init.h"
#include "Update.h"
#include "Draw.h"
#include "Inputs.h"
#include "Menu.h"



int main(int argc, char* argv[])
{
	 GameArgs gameArgs =
	{
		StartSDL(),
		InitGameState(),
		InitScene(),
	};
	StartMenu(gameArgs);
	while (gameArgs.State.Continue)
	{
		gameArgs.State.DeltaTime = (SDL_GetTicks() - gameArgs.State.CurrentTime) / 1000;
		gameArgs.State.CurrentTime = SDL_GetTicks();

		HandleInputs(gameArgs.State, gameArgs.Scene);
		Update(gameArgs.State, gameArgs.Scene);
		Draw(gameArgs);

		SDL_Delay(FRAMERATE);
	}

	return 1;
}

void QuitGame( GameArgs gameArgs)
{
	free(gameArgs.Scene.Players);
	free(gameArgs.Scene.Projectiles);
	ErrorHandling("Thanks for playing", gameArgs.SDL); // not an error but actually cleans so convenient

}