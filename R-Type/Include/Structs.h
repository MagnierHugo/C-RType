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
	bool ShotByPlayer;
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
	int JoysticksAvailable;
} InputsSummary;

typedef struct {
	SDL_Texture* Background;
	SDL_Texture* SecondBackground;
	SDL_Texture* Player1;
	SDL_Texture* Player1Hurt;
	SDL_Texture* Player2;
	SDL_Texture* EnemyType1;
	SDL_Texture* Boss1;
	SDL_Texture* Projectiles;
	SDL_Texture* Bonus;
	SDL_Texture* TitleScreen;
	SDL_Texture** Boss;
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
	int HighScore;
	int ShotFired;
	int EnemyKilled;
	bool Continue;
	bool Paused;
	bool ScreenWrappinActive;
	int CurLVL;
	InputsSummary Inputs;
	SDL_Joystick** Joysticks;

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
	int nbrEnemies;
	int Wait;
	bool isEnd;
} Wave;

typedef struct {
	int X;
	int Y;
	int DoWhat;
	bool Active;
	SDL_Texture* Tex;
} Bonus;

typedef struct {
	SDL_Texture* Background;
	
	Player* Players;
	//Enemy* Enemies;
	Projectile* Projectiles;
	Bonus* Bonuses;
	//int EnemyCount;
	EnemyQueue Queue;
	int ActiveEnemies;
	Wave* waves;
	int waveHead;
	bool waveEnd;
	int WaitTime;
	int Time;
	//Particle* Particles;
	//Bonus* Bonuses;
	bool ScreenWrappingActive;
} Scene;

typedef struct {
	Animation animation;

	int dirX;
	int dirY;

	float Speed;

	int HP;
	int AwardedPoints;
	bool DropBoost;
	int LastTimeShot;
} Boss;

typedef struct {
	SDL SDL;
	GameState State;
	Scene* Levels;
	Boss Boss;
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

