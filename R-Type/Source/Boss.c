#include <SDL.h>
#include <stdio.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Animation.h"
#include "../Include/Collision.h"
#include "../Include/Projectile.h"
#include "../Include/Utility.h"


Boss CreateBoss(SDL_Texture** animation)
{
    Boss boss = {
        CreateAnime(animation, 7, 150, (SDL_Rect) { SCREEN_WIDTH,
    INITIAL_BOSS_Y, BOSS_WIDTH, BOSS_HEIGHT}),
        -1, 0, BOSS_SPEED, LEVEL_COUNT * 20,
        2000 * LEVEL_COUNT, false
    };
    return boss;
}

SDL_Rect BossAsRect(Boss boss)
{
    return boss.animation.rect;
}

void DrawBoss(GameArgs* gameArgs)
{
    Boss* boss = &gameArgs->Boss;
    RunAnimation(gameArgs->SDL, &boss->animation);
    if (boss->animation.curFrame == 7) { boss->animation.curFrame = 0; }
}

void UpdateBoss(GameArgs* args, Scene* scene)
{
    Boss* boss = &args->Boss;

    if (boss->animation.rect.x <= BOSS_TARGET_POS) {
        boss->dirX = 0;
    }
    boss->animation.rect.x += boss->dirX * boss->Speed * args->State.DeltaTime;
    boss->animation.rect.y = INITIAL_BOSS_Y + sin(
        args->State.CurrentTime * BOSS_Y_MOVEMENT_SPEED) * BOSS_MOVEMENT_RANGE;

    if (boss->HP > 0) {
        args->State.Score += CheckBossProjCollision(
            args->State, boss, scene, &args->SDL);
    }

    if (boss->LastTimeShot + BOSS_SHOOTING_RATE < args->State.CurrentTime)
    {
        Player* players = scene->Players;
        for (int i = -1; i < 2; i++) {
            ShootBossProjectile(*boss,
                scene->Projectiles, *args, i * BOSS_PROJECTILES_Y_OFFSET);
        }
        boss->LastTimeShot = args->State.CurrentTime;
    }
}