#include <SDL.h>
#include <stdio.h>
#include "../Include/Constants.h"
#include "../Include/Structs.h"


void TakeHit(Player* player, GameState state)
{
	if (player->LastTimeWasShot + IMMUNITY_DURATION > state.CurrentTime)
	{
		printf("was hit while immune: %f, %f\n", player->LastTimeWasShot, state.CurrentTime);
		return;
	}
	player->LastTimeWasShot = state.CurrentTime;
	player->Health--;
	printf("was hit\n");
}