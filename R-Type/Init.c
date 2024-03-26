#include <SDL.h>
#include <stdio.h>
#include "Constants.h"

struct GameState InitGameState()
{
	struct GameState gState;
	gState.DeltaTime = 0;
	gState.CurrentTime = SDL_GetTicks();
	gState.Continue = true;
	gState.Score = 0;
	gState.Inputs.PlayerInput = malloc(PLAYER_CNT * sizeof(struct PlayerInput));
	gState.Inputs.InputMap = malloc(PLAYER_CNT * sizeof(struct InputMap));
	for (int i = 0; i < PLAYER_CNT; i++)
	{
		gState.Inputs.PlayerInput[i].DirX = 0;
		gState.Inputs.PlayerInput[i].DirY = 0;
		gState.Inputs.PlayerInput[i].Shooting = false;

		gState.Inputs.InputMap[i].Right = i ? SDL_SCANCODE_RIGHT : SDL_SCANCODE_D;
		gState.Inputs.InputMap[i].Left = i ? SDL_SCANCODE_LEFT : SDL_SCANCODE_A;
		gState.Inputs.InputMap[i].Up = i ? SDL_SCANCODE_UP : SDL_SCANCODE_W;
		gState.Inputs.InputMap[i].Down = i ? SDL_SCANCODE_DOWN : SDL_SCANCODE_S;
		gState.Inputs.InputMap[i].Shoot = i ? SDL_SCANCODE_KP_0 : SDL_SCANCODE_SPACE;
	}
	
	return gState;
}

struct Scene InitScene()
{
	struct Scene scene = {
		malloc(PLAYER_CNT * sizeof(struct Player)),
		malloc(MAX_PROJECTILE_AMOUNT * sizeof(struct Projectile))
	};
	for (int i = 0; i < PLAYER_CNT; i++)
	{
		scene.Players[i] = (struct Player){
		SCREEN_WIDTH * .5, SCREEN_HEIGHT * .5, PLAYER_WIDTH, PLAYER_HEIGHT,
		PLAYER_INITIAL_SPEED, 0, PLAYER_INITIAL_HEALTH, IMMUNITY_DURATION
		};
	}

	for (int i = 0; i < MAX_PROJECTILE_AMOUNT; i++)
	{
		scene.Projectiles[i] = (struct Projectile){
		10, 10, 0, 0, PROJECTILE_BASE_SPEED, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, false
		};
	}
	
	// more to come
	
	return scene;
}

struct Textures InitTextures()
{
	struct Textures textures;
	textures.needContent = 0;
	return textures;
}