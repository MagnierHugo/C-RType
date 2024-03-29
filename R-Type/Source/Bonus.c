#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Rect.h"
#include "../Include/Collision.h"
#include "../Include/Utility.h"


void UpdateBonuses(GameState state, Bonus* bonuses, Player* players) {
	for (int i = 0; i < MAX_BONUSES; i++) {
		if (!bonuses[i].Active) continue;
		bonuses[i].X -= BONUS_SPEED * state.DeltaTime;
		CheckPickupBonus(players, &bonuses[i]);
	}
}

void SpawnBonus(Bonus* bonuses, int x, int y) {
	for (int i = 0; i < MAX_BONUSES; i++) {
		if (!bonuses[i].Active) {
			bonuses[i].Active = true;
			bonuses[i].X = x;
			bonuses[i].Y = y;
			bonuses[i].DoWhat = RdmInt(1, 2, false);
			return;
		}
	}
}

void DrawBonuses(SDL sdl, Bonus* bonuses) {
	for (int i = 0; i < MAX_BONUSES; i++) {
		if (!bonuses[i].Active) continue;

		SDL_Rect bonusRect = BonusAsRect(bonuses[i]);
		SDL_RenderCopy(sdl.renderer, bonuses[i].Tex, NULL, &bonusRect);
	}
}

Bonus* InitBonuses(SDL_Texture* tex) {
	Bonus* bonuses = malloc(MAX_BONUSES * sizeof(Bonus));

	for (int i = 0; i < MAX_BONUSES; i++) {
		bonuses[i] = (Bonus){ 0, 0, BLANK_BONUS, false, tex };
	}

	return bonuses;
}