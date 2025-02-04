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

#define PLAYER_INITIAL_HEALTH 3
#define IMMUNITY_DURATION 1000

// Combat
#define MAX_PROJECTILES 100
#define PROJECTILE_BASE_SPEED 1000
#define PROJECTILE_WIDTH 25
#define PROJECTILE_HEIGHT 10

#define LEVEL_COUNT 4
// Music & Sound
#define NUMBER_OF_CHANNELS 3

// audio paths can be here
#define SONG "Assets/Music/BlueNavi-Starcade.mp3"
#define BLASTER "Assets/Music/blaster.mp3"
#define KABOOM "Assets/Music/medium-explosion.mp3"


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
#define BOOM_WAIT_BETWEEN_FRAMES 150

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
#define SPEED_BONUS 500
#define BONUS_WIDTH 100
#define BONUS_HEIGHT 100

#define BOSS_WIDTH 250
#define BOSS_HEIGHT (int)(BOSS_WIDTH * 0.75)
#define BOSS_SPEED 60
#define BOSS_TARGET_POS SCREEN_WIDTH - BOSS_WIDTH - 50
#define INITIAL_BOSS_Y (SCREEN_HEIGHT - BOSS_HEIGHT) / 2
#define BOSS_BOOM_COUNT 100
#define BOSS_BOOM_OFFSET 100
#define BOSS_SHOOTING_RATE 750
#define BOSS_MOVEMENT_RANGE 100
#define BOSS_Y_MOVEMENT_SPEED .001
#define BOSS_PROJECTILES_Y_OFFSET 50