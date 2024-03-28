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

#define PLAYER_INITIAL_HEALTH 1
#define PLAYER_MAX_HEALTH 5
#define IMMUNITY_DURATION 5000

// Combat
#define MAX_PROJECTILES 100
#define PROJECTILE_BASE_SPEED 1000
#define PROJECTILE_WIDTH 25
#define PROJECTILE_HEIGHT 10

#define LEVEL_COUNT 1
// Music & Sound
#define NUMBER_OF_CHANNELS 3

// audio paths can be here
#define SONG "../Music/BlueNavi-Starcade.mp3"
#define BLASTER "../Music/blaster.mp3"

// Particles

#define MAX_PARTICLE_AMOUNT 100

// buttons

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100
#define BUTTON_SIZE 100
#define BUTTON_SPACING 25


#define SCORE_Y 700
#define SHOTS_FIRED_Y 725


// Some Constants for the enemies
#define ENEMIES_WIDTH 120
#define ENEMIES_HEIGHT ENEMIES_WIDTH * 0.81

#define MAX_ENEMY_CNT 20
#define INITIAL_ENEMY_HEALTH 20
#define ENEMY_SPEED 150
#define MAX_SPAWN_X_OFFSET 3500
#define MIN_RESET_X_OFFSET 1000
#define MAX_RESET_X_OFFSET 3500
#define BASE_ENEMY_AWARDED_POINTS 100
