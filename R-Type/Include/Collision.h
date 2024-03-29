#pragma once

#include "Structs.h"


void CheckEnemyPlayerCollision(GameState state, Enemy* enemy, Player* players);
int CheckEnemyProjCollision(GameState state, Enemy* enemy, 
	Scene* scene, SDL* sdl);
void CheckPickupBonus(Player* players, Bonus* bonus);
int CheckBossProjCollision(GameState state, Boss* boss, 
	Scene* scene, SDL* sdl);
void CheckPlayerProjCollision(GameState state,
	Player* players, Scene* scene, SDL* sdl);
