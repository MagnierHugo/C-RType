#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

// Global
#define SCREEN_WIDTH 1020
#define SCREEN_HEIGHT 766
#define FRAMERATE 1000/60

// Player

#define PLAYER_CNT 2
#define PLAYER_WIDTH 120
#define PLAYER_HEIGHT 50
#define PLAYER_INITIAL_SPEED 500
#define SHOOTING_SLOWDOWN_COEF 300


#define SHOOTING_RATE 100

#define PLAYER_INITIAL_HEALTH 1
#define IMMUNITY_DURATION 5000

// Combat
#define MAX_PROJECTILES 100
#define PROJECTILE_BASE_SPEED 1000
#define PROJECTILE_WIDTH 25
#define PROJECTILE_HEIGHT 10

#define LEVEL_COUNT 3
// Music & Sound
#define NUMBER_OF_CHANNELS 3

// audio paths can be here
#define SONG "../Music/BlueNavi-Starcade.mp3"
#define BLASTER "../Music/blaster.mp3"
#define KABOOM "../Music/medium-explosion.mp3"


// Particles

#define MAX_PARTICLE_AMOUNT 100

// buttons

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100
#define BUTTON_SIZE 100
#define BUTTON_SPACING 25


#define ENEMY_KILLED_Y 625
#define SHOTS_FIRED_Y 650
#define LEVEL_Y 675
#define SCORE_Y 700
#define HIGHSCORE_Y 725


// Some Constants for the enemies
#define ENEMIES_WIDTH 120
#define ENEMIES_HEIGHT (int)(ENEMIES_WIDTH * 0.81)

#define ENEMY_SPEED 150

#define BASE_ENEMY_AWARDED_POINTS 100

// Animation
#define BOOM_FRAMES 10
#define BOOM_WIDTH 120
#define BOOM_HEIGTH (int)(BOOM_WIDTH * 1.13)
// Inputs

#define DEADZONE 5000
#define ACTIVATION_THRESHOLD 8000
#define JOY_MAX_VALUE 32767
#define SENSITIVITY 5

#define DONT_RENDER_FLAG -999

#define BONUS_SPEED 100
#define MAX_BONUSES 3
#define BLANK_BONUS 0
#define HEALTH_BONUS 1
#define SPEED_BONUS 2
#define BONUS_WIDTH 100
#define BONUS_HEIGHT 100

