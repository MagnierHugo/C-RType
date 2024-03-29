#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Music.h"
#include "../Include/Structs.h"

static Projectile* SeekAvailableProjectile(Projectile* projs) {
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (!projs[i].Active) return &projs[i];
	}
	return &projs[0];
	// in case on available for some reason keep the game in a somewhat healthy state by kidnapping an active projectile
}

void ShootPlayerProjectile(Player player, Projectile* projs,
	GameState* state, GameArgs args)
{
	/*for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projs[i].Active) { continue; }*/
	PlaySound(BLASTER, args.SDL);
	Projectile* projectile = SeekAvailableProjectile(projs);
	projectile->X = player.X + player.Width;
	projectile->Y = player.Y + player.Height / 2;
	projectile->DirY = 0;
	projectile->DirX = 1;
	projectile->Active = true;
	projectile->ShotByPlayer = true;

	state->ShotFired++;

	//return;
	//}
}
void ShootBossProjectile(Boss boss,
	Projectile* projs, GameArgs args, int yOffset)
{
	/*for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projs[i].Active) { continue; }*/
		PlaySound(BLASTER, args.SDL);

		Projectile* projectile = SeekAvailableProjectile(projs);
		projectile->X = boss.animation.rect.x;
		projectile->Y = boss.animation.rect.y +
			boss.animation.rect.h / 2 + yOffset;

		
		projectile->DirX = -1;
		projectile->DirY = 0;

		projectile->Active = true;
		projectile->ShotByPlayer = false;

		//return;
	//}
}

