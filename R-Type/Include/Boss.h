#pragma once

#include <SDL.h>

#include "Structs.h"


Boss CreateBoss(SDL_Texture** animation);
SDL_Rect BossAsRect(Boss boss);
void DrawBoss(GameArgs* gameArgs);
void UpdateBoss(GameArgs* args, Scene* scene);