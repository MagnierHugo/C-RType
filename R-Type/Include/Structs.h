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
	int ID;
	bool Active;
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
	SDL_Texture* Background2;
	SDL_Texture* Player1;
	SDL_Texture* Player1Hurt;
	SDL_Texture* Player2;
	SDL_Texture* EnemyType1;
	SDL_Texture* Boss1;
	SDL_Texture* Projectiles;
	SDL_Texture** Boom;
	// BonusType1
} Textures;

typedef struct {
	int nbrFrames;
	int curFrame;
	int TimeBetweenFrames;
	int LastPlayed;
	SDL_Rect rect;
	SDL_Texture** Frames;
} Animation;

typedef struct {
	SDL_Texture** Tex;
	int nbrFrames;
	int Wait;
	int pos[2];
} AnimeArgs;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Textures Tex;
	TTF_Font* Font;
	Animation* animes;
	int nbrAnimation;
} SDL;

typedef struct {
	float DeltaTime;
	float CurrentTime;
	int Score;
	int ShotFired;
	bool Continue;
	bool Paused;
	bool ScreenWrappinActive;
	int CurLVL;
	InputsSummary Inputs;

} GameState;

typedef struct {
	SDL_Texture* Tex;

	float X;
	float Y;
	int dirX;
	int dirY;

	int Width;
	int Height;

	float Speed;

	int HP;
	int AwardedPoints;
	bool DropBoost;
} Enemy;

typedef struct {
	Enemy* Enemies;
	int nbrEnemies;
} EnemyQueue;

typedef struct {
	Enemy boss;
	bool isAlive;
} Boss;

typedef struct {
	int nbrEnemies;
	int Wait;
	bool isEnd;
} Wave;

typedef struct {
	SDL_Texture* Background;
	Player* Players;
	Projectile* Projectiles;
	EnemyQueue Queue;
	int ActiveEnemies;
	Wave* waves;
	int waveHead;
	bool waveEnd;
	int WaitTime;
	int Time;
	Boss Boss;
	//Bonus* Bonuses;
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