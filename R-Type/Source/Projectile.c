#include <SDL.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Music.h"

void ShootPlayerProjectile(Player player, Projectile* projs, GameState* state, GameArgs gameArgs)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projs[i].Active) { continue; }

		PlaySound(BLASTER, gameArgs.SDL);
		projs[i].X = player.X + player.Width;
		projs[i].Y = player.Y + player.Height / 2;
		projs[i].DirY = 0;
		projs[i].DirX = 1;
		projs[i].Active = true;

		state->ShotFired++;

		return;
	}
}