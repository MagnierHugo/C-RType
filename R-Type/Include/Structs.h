#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdbool.h>


typedef struct {
	SDL_Texture* Tex;

	float X;
	float Y;
	int DirX;
	int DirY;

	float Speed;

	int Width;
	int Height;
	bool Active;
} Projectile;

typedef struct {
	SDL_Texture* Tex;

	float X;
	float Y;
	int Width;
	int Height;
	float Speed;

	float LastTimeShot;
	float LastTimeWasShot;

	int Health;
	int ImmunityDuration;
} Player;

typedef struct {
	int DirX;
	int DirY;
	bool Shooting;
} PlayerInput;

typedef struct {
	SDL_Scancode Right;
	SDL_Scancode Left;
	SDL_Scancode Up;
	SDL_Scancode Down;
	SDL_Scancode Shoot;
} InputMap;

typedef struct {
	PlayerInput* PlayerInput;
	InputMap* InputMap;
} InputsSummary;

typedef struct {
	SDL_Texture* Background;
	SDL_Texture* Player1;
	SDL_Texture* Player1Hurt;
	SDL_Texture* Player2;
	SDL_Texture* EnemyType1;
	SDL_Texture* Boss1;
	SDL_Texture* Projectiles;
	// BonusType1
} Textures;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Textures Tex;
	TTF_Font* Font;
} SDL;

typedef struct {
	float DeltaTime;
	float CurrentTime;
	int Score;
	bool Continue;
	bool Paused;
	bool ScreenWrappinActive;
	int CurrentLevel;
	InputsSummary Inputs;

} GameState;

typedef struct {
	SDL_Texture* Tex;
	float X;
	float Y;
	int Width;
	int Height;
	int HP;
	float Speed;
	bool DropBoost;
	bool Active;
} Enemy;

typedef struct {
	Enemy* Enemies;
	int nbrEnemies;
} EnemyQueue;

typedef struct {
	int nbrEnemies;
	int Wait;
} Wave;

typedef struct {
	SDL_Texture* Background;
	Player* Players;
	Enemy* Enemies;
	Projectile* Projectiles;
	//EnemyQueue Queue;
	//int ActiveEnemies;
	//struct Wave* waves;
	int EnemyCount;
	//int waveHead;
	//int WaitTime;
	//struct Particle* Particles;
	//struct Bonus* Bonuses;
	bool ScreenWrappingActive;
} Scene;

typedef struct {
	SDL SDL;
	GameState State;
	Scene* Levels;
} GameArgs;

typedef struct {
	int X;
	int Y;

	int DirX;
	int DirY;

	float Size;
	int Opacity;

	bool Active;
} Particle;

typedef struct {
	SDL_Rect Rect;  // Rectangle representing button's position and size
	SDL_Color Color; // Color of the button
	bool Clicked;
} Button;