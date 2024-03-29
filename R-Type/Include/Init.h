#pragma once

#include "Structs.h"

GameState InitGameState(SDL sdl);
Scene InitScene(SDL sdl, SDL_Texture* background, int enemiesInWave, // 69 :) Nice
	int baseHp, int  dirX, int dirY);
Textures InitTextures(SDL sdl);