#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Include/Structs.h"

int RdmInt(int min, int max, bool nonZero)
{
    int rdm;
    do
    {
        rdm = min + rand() % (max - min + 1);
    } while (nonZero && rdm == 0);

    return rdm;
}

SDL_Rect PlayerAsRect(Player player)
{
    return (SDL_Rect) { player.X, player.Y, player.Width, player.Height };
}

SDL_Rect ProjectileAsRect(Projectile proj) // polymorphism would ve been great
{
    return (SDL_Rect) { proj.X, proj.Y, proj.Width, proj.Height };
}

SDL_Rect EnemyAsRect(Enemy enemy)
{
    return (SDL_Rect) { enemy.X, enemy.Y, enemy.Width, enemy.Height };
}