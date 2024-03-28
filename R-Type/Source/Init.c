#include <SDL.h>

#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Textures.h"
#include "../Include/Enemies.h"
#include "../Include/Utility.h"
#include "../Include/Wave.h"
#include "../Include/HandleSDL.h"


GameState InitGameState(SDL sdl)
{
	GameState gState;
	gState.DeltaTime = 0;
	gState.CurrentTime = SDL_GetTicks();
	gState.Continue = true;
	gState.Score = 0;
	gState.ShotFired = 0;
	gState.CurLVL = 0;
	gState.Inputs.PlayerInput = malloc(PLAYER_CNT * sizeof( PlayerInput));
	if (gState.Inputs.PlayerInput == NULL) {
		ErrorHandling("Error Allocating Memory for PlayerInputs", sdl);
	}
	gState.Inputs.InputMap = malloc(PLAYER_CNT * sizeof( InputMap));
	if (gState.Inputs.InputMap == NULL) {
		ErrorHandling("Error Allocating Memory for InputMap", sdl);
	}
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

static Player* InitPlayers(SDL_Texture* Tex[2], SDL sdl)
{
	Player* players = malloc(PLAYER_CNT * sizeof(Player));
	if (players == NULL) {
		ErrorHandling("Error Allocating Memory for players", sdl);
	}

	for (int i = 0; i < PLAYER_CNT; i++)
	{
		players[i] = (Player){
			Tex[i],
			SCREEN_WIDTH * .125, SCREEN_HEIGHT * .25 * (2 * i + 1), PLAYER_WIDTH,
			PLAYER_HEIGHT, PLAYER_INITIAL_SPEED,
			0, 0, PLAYER_INITIAL_HEALTH, IMMUNITY_DURATION, i, true
		};
	}

	return players;
}


static Enemy* InitEnemies(SDL_Texture* tex)
{
	Enemy* enemies = malloc(MAX_ENEMY_CNT * sizeof(Enemy));

	for (int i = 0; i < MAX_ENEMY_CNT; i++)
	{
		enemies[i] = (Enemy){
			tex, SCREEN_WIDTH, 0, ENEMIES_WIDTH, ENEMIES_HEIGHT,
			INITIAL_ENEMY_HEALTH, ENEMY_SPEED, RdmInt(0, 1, false), false,
			BASE_ENEMY_AWARDED_POINTS
		};
	}

	return enemies;
}

static Projectile* InitProjectiles(SDL_Texture* Tex, SDL sdl)
{
	Projectile* proj = malloc(MAX_PROJECTILES * sizeof(Projectile));
	if (proj == NULL) {
		ErrorHandling("Error Allocating Memory for projectiles", sdl);
	}

	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projs[i] = (Projectile){
			tex, 10, 10, 0, 0,
			PROJECTILE_BASE_SPEED, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, false
		};
	}

	return projs;
}

static Enemy InitBaseEnemy(int baseHp, int  dirX, int dirY, SDL_Texture* Tex)
{
	Enemy baseEnemy = {
		Tex, SCREEN_WIDTH, 0, dirX, dirY,
		ENEMIES_WIDTH, ENEMIES_HEIGHT,
		ENEMIES_BASE_SPEED, baseHp, NULL
	};

	return baseEnemy;
}

Scene InitScene(SDL sdl)
{
	Enemy baseEnemy = InitBaseEnemy(5, -1, 0, sdl.Tex.EnemyType1);

	Scene scene = {
		sdl.Tex.Background,
		InitPlayers((SDL_Texture* [2]) { sdl.Tex.Player1, sdl.Tex.Player2 }, sdl),
		InitProjectiles(sdl.Tex.Projectiles, sdl),
		CreateEnemyQueue(7, baseEnemy, sdl), 0,
		CreateWaves(7, 3, 1000, sdl), 0, false, 2000,
		0, false
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