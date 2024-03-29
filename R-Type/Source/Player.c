#include <SDL.h>
#include <stdio.h>
#include "../Include/Constants.h"
#include "../Include/Structs.h"

void TakeHit(Player* player, GameState state)
{
	if (player->LastTimeWasShot + IMMUNITY_DURATION > state.CurrentTime)
	{
		return;
	}
	player->LastTimeWasShot = state.CurrentTime;
	player->X = SCREEN_WIDTH * .125;
	player->Y = (SCREEN_HEIGHT - PLAYER_HEIGHT) * .5;
	player->Health--;
	player->Active = player->Health > 0;
}

void ResetScene(Scene* scene)
{
	for (int i = 0; i < PLAYER_CNT; i++)
	{
		scene->Players[i].X = SCREEN_WIDTH * .125;
		scene->Players[i].Y = SCREEN_HEIGHT * .25 * (2 * i + 1);
	}
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		scene->Projectiles[i].Active = false;
	}
	for (int i = 0; i < scene->ActiveEnemies; i++)
	{
		scene->Queue.Enemies->X += SCREEN_WIDTH; // simply shift all of them to the side
		// if alive they ll come back else we dont care
	}
}