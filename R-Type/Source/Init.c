#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Textures.h"
#include "../Include/Enemies.h"
#include "../Include/Wave.h"
#include "../Include/Utility.h"
#include "../Include/HandleJoystick.h"
#include "../Include/SaveAndLoad.h"
#include "../Include/Bonus.h"


GameState InitGameState(SDL sdl)
{
	GameState gState;
	gState.DeltaTime = 0;
	gState.CurrentTime = SDL_GetTicks();
	gState.Continue = true;
	gState.Score = 0;
	gState.HighScore = LoadGameData();
	gState.ShotFired = 0;
	gState.EnemyKilled = 0;
	gState.CurLVL = 0;
	gState.Inputs.PlayerInput = malloc(PLAYER_CNT * sizeof(PlayerInput));
	gState.Inputs.InputMap = malloc(PLAYER_CNT * sizeof(InputMap));
	gState.Joysticks = DetectJoystick(GetJoystickCount(), sdl);
	for (int i = 0; i < PLAYER_CNT; i++)
	{
		gState.Inputs.PlayerInput[i].DirX = 0;
		gState.Inputs.PlayerInput[i].DirY = 0;
		gState.Inputs.PlayerInput[i].Shooting = false;
		// default key mapping
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
			SCREEN_WIDTH * .125, SCREEN_HEIGHT * .25 * (2 * i + 1), PLAYER_WIDTH,
			PLAYER_HEIGHT, PLAYER_INITIAL_SPEED,
			0, 0, PLAYER_INITIAL_HEALTH, IMMUNITY_DURATION, i, true
		};
	}

	return players;
}

//static Enemy* InitEnemies(SDL_Texture* tex)
//{
//	Enemy* enemies = malloc(MAX_ENEMY_CNT * sizeof(Enemy));
//
//	for (int i = 0; i < MAX_ENEMY_CNT; i++)
//	{
//		enemies[i] = (Enemy){
//			tex, SCREEN_WIDTH, 0, ENEMIES_WIDTH, ENEMIES_HEIGHT,
//			INITIAL_ENEMY_HEALTH, ENEMY_SPEED, RdmInt(0, 1, false), false,
//			BASE_ENEMY_AWARDED_POINTS
//		};
//	}
//
//	return enemies;
//}

static Projectile* InitProjectiles(SDL_Texture* tex)
{
	Projectile* projs = malloc(MAX_PROJECTILES * sizeof(Projectile));

	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projs[i] = (Projectile){
			tex, 10, 10, 0, 0,
			PROJECTILE_BASE_SPEED, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, false
		};
	}

	return projs;
}

Scene InitScene(SDL sdl, int baseHp, int  dirX, int dirY)
{
	Enemy baseEnemy = {
		sdl.Tex.EnemyType1, SCREEN_WIDTH, 0, dirX, dirY,
		ENEMIES_WIDTH, ENEMIES_HEIGHT,
		ENEMY_SPEED, baseHp, BASE_ENEMY_AWARDED_POINTS, false
	};

	Scene scene = {
		sdl.Tex.Background,
		InitPlayers((SDL_Texture * [2]) { sdl.Tex.Player1, sdl.Tex.Player2 }),
		//InitEnemies(sdl.Tex.EnemyType1),
		InitProjectiles(sdl.Tex.Projectiles),
		InitBonuses(sdl.Tex.Bonus),
		CreateEnemyQueue(45, baseEnemy, sdl), 0,
		CreateWaves(45, 5, 1000, sdl), 0, false, 3000,
		0, false
		/*10,
		false*/
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
	tex.Bonus = CreateTexture(sdl, "..\\Sprites\\Bonus.png");
	tex.TitleScreen = CreateTexture(sdl, "..\\Sprites\\Fond_menu.png");

	for (int frame = 0; frame < 10; frame++) {
		char path[256]; // Make sure path buffer is large enough
		snprintf(path, sizeof(path), "../Sprites/Boom%d.png", frame + 1);
		tex.Boom[frame] = CreateTexture(sdl, path);
	}

	return tex;
}
