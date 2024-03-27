#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdbool.h>


typedef struct Projectile
{
	SDL_Texture* tex;

	float X;
	float Y;
	int DirX;
	int DirY;

	float Speed;

	int Width;
	int Height;
	bool Active;
} Projectile;

typedef struct Player
{
	SDL_Texture* tex;

	float X;
	float Y;
	int Width;
	int Height;
	float Speed;

	float LastTimeShot;

	int Health;
	int ImmunityDuration;
} Player;

typedef struct PlayerInput
{
	int DirX;
	int DirY;
	bool Shooting;
} PlayerInput;

typedef struct InputMap
{
	SDL_Scancode Right;
	SDL_Scancode Left;
	SDL_Scancode Up;
	SDL_Scancode Down;
	SDL_Scancode Shoot;
} InputMap;

typedef struct InputsSummary
{
	PlayerInput* PlayerInput;
	InputMap* InputMap;
} InputsSummary;

typedef struct Textures
{
	SDL_Texture* Background;
	SDL_Texture* Player1;
	SDL_Texture* Player1Hurt;
	SDL_Texture* Player2;
	SDL_Texture* EnemyType1;
	SDL_Texture* Boss1;
	SDL_Texture* Projectiles;
	// BonusType1
} Textures;

typedef struct SDL
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Textures Tex;
	TTF_Font* Font;
} SDL;

typedef struct GameState
{
	float DeltaTime;
	float CurrentTime;
	int Score;
	bool Continue;
	bool Paused;
	bool ScreenWrappinActive;
	InputsSummary Inputs;

} GameState;

typedef struct Enemy
{
	SDL_Texture* Tex;

	float X;
	float Y;
	int Width;
	int Height;

	float Speed;

	int HP;
	bool DropBoost;
} Enemy;

typedef struct EnemyQueue
{
	Enemy* Enemies;
	int nbrEnemies;
} EnemyQueue;

typedef struct Wave
{
	int nbrEnemies;
	int Wait;
} Wave;

typedef struct Scene
{
	SDL_Texture* background;
	Player* Players;
	Projectile* Projectiles;
	EnemyQueue Queue;
	int ActiveEnemies;
	Wave* waves;
	int waveHead;
	int WaitTime;
	int Time;
	//Particle* Particles;
	//Bonus* Bonuses;
	bool ScreenWrappingActive;
} Scene;

typedef struct GameArgs
{
	SDL SDL;
	GameState State;
	Scene* Levels;
} GameArgs;

typedef struct Particle {
	int X;
	int Y;

	int DirX;
	int DirY;

	float Size;
	int Opacity;

	bool Active;
}Particle;

typedef struct Button {
	SDL_Rect Rect;  // Rectangle representing button's position and size
	SDL_Color Color; // Color of the button
	bool Clicked;
}Button;