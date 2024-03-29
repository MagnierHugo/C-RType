#include <SDL.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Bonus.h"


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

SDL_Rect BonusAsRect(Bonus bonus)
{
    return (SDL_Rect) { bonus.X, bonus.Y, BONUS_WIDTH, BONUS_HEIGHT };
}