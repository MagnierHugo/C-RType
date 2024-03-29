#pragma once

#include "../Include/Constants.h"
#include "../Include/Structs.h"

void UpdateBonuses(GameState state, Bonus* bonuses, Player* players);
void SpawnBonus(Bonus* bonuses, int x, int y);
void DrawBonuses(SDL sdl, Bonus* bonuses);
Bonus* InitBonuses(SDL_Texture* tex);