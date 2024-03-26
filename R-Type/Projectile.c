#include <SDL.h>
#include "Constants.h"

void ShootPlayerProjectile(struct Player player, struct Projectile* projs)
{
	for (int i = 0; i < MAX_PROJECTILE_AMOUNT; i++)
	{
		if (projs[i].Active) { continue; }

		projs[i].X = player.X + player.Width;
		projs[i].Y = player.Y + player.Height / 2;
		projs[i].DirY = 0;
		projs[i].DirX = 1;
		projs[i].Active = true;

		return;
	}
}