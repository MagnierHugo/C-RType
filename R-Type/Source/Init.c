#include <SDL.h>

#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Textures.h"
#include "../Include/Enemies.h"
#include "../Include/Utility.h"
#include "../Include/Wave.h"


GameState InitGameState()
{
	GameState gState;
	gState.DeltaTime = 0;
	gState.CurrentTime = SDL_GetTicks();
	gState.Continue = true;
	gState.Score = 0;
	gState.Inputs.PlayerInput = malloc(PLAYER_CNT * sizeof( PlayerInput));
	gState.Inputs.InputMap = malloc(PLAYER_CNT * sizeof( InputMap));
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

static Player* InitPlayers(SDL_Texture* Tex[2])
{
	Player* players = malloc(PLAYER_CNT * sizeof(Player));

	for (int i = 0; i < PLAYER_CNT; i++)
	{
		players[i] = (Player){
			Tex[i],
			SCREEN_WIDTH * .5, SCREEN_HEIGHT * .5, PLAYER_WIDTH, PLAYER_HEIGHT,
			PLAYER_INITIAL_SPEED, 0, PLAYER_INITIAL_HEALTH, IMMUNITY_DURATION
		};
	}

	return players;
}

static Projectile* InitProjectiles(SDL_Texture* Tex)
{
	Projectile* proj = malloc(MAX_PROJECTILES * sizeof(Projectile));

	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		proj[i] = (Projectile){
			Tex, 10, 10, 0, 0,
			PROJECTILE_BASE_SPEED, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, false
		};
	}

	return proj;
}

static Enemy InitBaseEnemy(int baseHp, float baseSpeed, SDL_Texture* Tex)
{
	Enemy baseEnemy = {
		Tex, SCREEN_WIDTH, 0,
		ENEMIES_WIDTH, ENEMIES_HEIGHT,
		baseHp, baseSpeed, NULL
	};

	return baseEnemy;
}

Scene InitScene(Textures Tex)
{
	Enemy baseEnemy = InitBaseEnemy(5, 20, Tex.EnemyType1);

	Scene scene = {
		Tex.Background,
		InitPlayers((SDL_Texture* [2]) { Tex.Player1, Tex.Player2 }),
		InitProjectiles(Tex.Projectiles),
		CreateEnemyQueue(7, baseEnemy), 0,
		CreateWaves(7, 3, 1000), 0, 2000,
		SDL_GetTicks(),
		false
	};

	return scene;
}

Textures InitTextures(SDL sdl)
{
	Textures tex;

	tex.Background = CreateTexture(sdl, "..\\Sprites\\Fond1.png");
	tex.Player1 = CreateTexture(sdl, "..\\Sprites\\Player1.png");
	tex.Player1Hurt = CreateTexture(sdl, "..\\Sprites\\Player1_hurt.png");
	tex.Player2 = CreateTexture(sdl, "..\\Sprites\\Player2.png");
	tex.EnemyType1 = CreateTexture(sdl, "..\\Sprites\\Mobs1.png");
	tex.Boss1 = CreateTexture(sdl, "..\\Sprites\\Boss1.png");
	tex.Projectiles = CreateTexture(sdl, "..\\Sprites\\Soot1.png");

	return tex;
}