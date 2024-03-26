#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

// EVERY SINGLE CONSTANT SHOULD BE FULL_CAP
// 
// Global
#define SCREEN_WIDTH 1020
#define SCREEN_HEIGHT 766
#define FRAMERATE 1000/60

#define OUT_OF_BOUNDS_THRESHOLD 100

// Player

#define PLAYER_CNT 2
#define PLAYER_WIDTH 120
#define PLAYER_HEIGHT 50
#define PLAYER_INITIAL_SPEED 500
#define SHOOTING_SLOWDOWN_COEF 300


#define SHOOTING_RATE 100

#define PLAYER_INITIAL_HEALTH 3
#define PLAYER_MAX_HEALTH 5
#define IMMUNITY_DURATION 1

// Combat
#define MAX_PROJECTILE_AMOUNT 100
#define PROJECTILE_BASE_SPEED 1000
#define PROJECTILE_WIDTH 25
#define PROJECTILE_HEIGHT 10

// Music & Sound
#define NUMBER_OF_CHANNELS 3

// audio paths can be here


// Particles

#define MAX_PARTICLE_AMOUNT 100



// Sprites
#define PLAYER1 "..\\Sprites\\Player1.png"
#define PLAYER2 "..\\Sprites\\Player2.png"
#define PLAYER1_HURT "..\\Sprites\\Player1_hurt.png"
#define FOND1 "..\\Sprites\\Fond1.png"
#define FOND2 "..\\Sprites\\Fond2.png"
#define BOSS1 "..\\Sprites\\Boss1.png"
#define MOB1 "..\\Sprites\\Mobs1.png"
#define SHOOT_PLAYER "..\\Sprites\\Soot1.png"
#define EXPLOSION "..\\Sprites\\Boom.gif"


// buttons

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100
#define BUTTON_SIZE 100
#define BUTTON_SPACING 25



#define SCORE_Y 700

struct Projectile
{
	float X;
	float Y;
	int DirX;
	int DirY;

	float Speed;

	int Width;
	int Height;
	bool Active;
};

struct Player
{
	float X;
	float Y;
	int Width;
	int Height;
	float Speed;

	float LastTimeShot;

	int Health;
	int ImmunityDuration;
};


struct PlayerInput
{
	int DirX;
	int DirY;
	bool Shooting;
};

struct InputMap
{
	SDL_Scancode Right;
	SDL_Scancode Left;
	SDL_Scancode Up;
	SDL_Scancode Down;
	SDL_Scancode Shoot;
};

struct InputsSummary
{
	struct PlayerInput* PlayerInput;
	struct InputMap* InputMap;
};



struct Textures
{
	int needContent;
	//SDL_Texture* Background;
	// Background
	// Player1
	// Player2
	// EnemyType1
	// BonusType1
};

struct SDL
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	struct Textures Tex;
	TTF_Font* Font;
};

struct GameState
{
	float DeltaTime;
	float CurrentTime;
	int Score;
	bool Continue;
	bool Paused;
	bool ScreenWrappinActive;
	struct InputsSummary Inputs;

};

struct Scene
{
	struct Player* Players;
	struct Projectile* Projectiles;
	//struct Enemies* Enemies;
	//struct Particle* Particles;
	//struct Bonus* Bonuses;
};



struct GameArgs
{
	struct SDL SDL;
	struct GameState State;
	struct Scene Scene;
};

