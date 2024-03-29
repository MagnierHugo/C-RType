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

#define PLAYER_INITIAL_HEALTH 5
#define IMMUNITY_DURATION 2000

// Combat
#define MAX_PROJECTILES 100
#define PROJECTILE_BASE_SPEED 1000
#define PROJECTILE_WIDTH 25
#define PROJECTILE_HEIGHT 10

#define LEVEL_COUNT 3
// Music & Sound
#define NUMBER_OF_CHANNELS 3

// audio paths can be here


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
#define ENEMIES_HEIGHT (int)(ENEMIES_WIDTH * 0.81)

#define ENEMY_SPEED 150

#define BASE_ENEMY_AWARDED_POINTS 100

// Animation
#define BOOM_FRAMES 10
#define BOOM_WAIT_BETWEEN_FRAMES 150

#define BOOM_WIDTH 120
#define BOOM_HEIGTH (int)(BOOM_WIDTH * 1.13)
