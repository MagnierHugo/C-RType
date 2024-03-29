#pragma once

#include "Structs.h"

GameState InitGameState(SDL sdl);
Scene InitScene(SDL sdl, int baseHp, int  dirX, int dirY);
Textures InitTextures(SDL sdl);