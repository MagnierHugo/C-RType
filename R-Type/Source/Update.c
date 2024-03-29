#include <SDL.h>

#include <stdio.h>
#include <stdbool.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/HandleSDL.h"
#include "../Include/Projectile.h"
#include "../Include/Utility.h"
#include "../Include/Player.h"
#include "../Include/Enemies.h"
#include "../Include/Collision.h"


static void UpdatePlayers(GameState* state, Scene scene, GameArgs gameArgs)
{
    Player* players = scene.Players;
    for (int i = 0; i < PLAYER_CNT; i++)
    {
        if (!players[i].Active) continue;

        PlayerInput inputs = state->Inputs.PlayerInput[i];
        players[i].X += inputs.DirX * players[i].Speed * state->DeltaTime;
        players[i].Y += inputs.DirY * players[i].Speed * state->DeltaTime;
        if (state->Inputs.PlayerInput[i].Shooting)
        {
            if (players[i].LastTimeShot + SHOOTING_RATE < state->CurrentTime)
            {
                ShootPlayerProjectile(players[i], scene.Projectiles, state, gameArgs);
                players[i].LastTimeShot = state->CurrentTime;
            }
        }

        if (players[i].Y < 0) players[i].Y = 0;
        else if (players[i].Y + players[i].Height > SCREEN_HEIGHT)
        {
            players[i].Y = SCREEN_HEIGHT - players[i].Height;
        }

        if (players[i].X < 0) players[i].X = 0;
        else if (players[i].X + players[i].Width > SCREEN_WIDTH)
        {
            players[i].X = SCREEN_WIDTH - players[i].Width;
        }
    }
}

//static void UpdateEnemies(GameState* state, Scene scene)
//{
//    Enemy* enemies = scene.Enemies;
//    Player* players = scene.Players;
//    Projectile* projs = scene.Projectiles;
//    for (int i = 0; i < scene.EnemyCount; i++)
//    {
//        Enemy* enemy = &enemies[i];
//        if (!enemy->Active) continue;
//        enemy->X -= enemy->Speed * state->DeltaTime;
//
//        if (enemy->X + ENEMIES_WIDTH < 0)
//        {
//            enemy->X = SCREEN_WIDTH + RdmInt(
//                MIN_RESET_X_OFFSET, MAX_RESET_X_OFFSET, false);
//            enemy->Y = RdmInt(0, SCREEN_HEIGHT - ENEMIES_HEIGHT, false);
//        }
//
//        CheckEnemyPlayerCollision(*state, *enemy, players);
//
//        state->Score += CheckEnemyProjCollision(*state, enemy, projs);
//    }
//}

static void UpdateEnemies(GameState* state, Scene* scene, SDL sdl)
{
    SpawnEnemies(scene);

    EnemyQueue* queue = &scene->Queue;
    Player* players = scene->Players;
    Projectile* projs = scene->Projectiles;

    for (int i = 0; i < scene->ActiveEnemies; i++)
    {
        Enemy* enemy = &queue->Enemies[i];

        enemy->X += enemy->dirX * enemy->Speed * state->DeltaTime;
        enemy->Y += enemy->dirY * enemy->Speed * state->DeltaTime;

        if (enemy->X + ENEMIES_WIDTH < 0)
        {
            enemy->HP = 0;
        }

        if (enemy->HP == 0) {
            queue->nbrEnemies -= 1;
            scene->ActiveEnemies -= 1;
            queue->Enemies = UpdateQueue(*queue, sdl);
        }
        
        CheckEnemyPlayerCollision(*state, enemy, players);
        
        int scoreBefore = state->Score;
        state->Score += CheckEnemyProjCollision(enemy, queue, projs, sdl);

        if (scoreBefore < state->Score) state->EnemyKilled++;
    }
}

static void UpdateProjectiles(GameState state, Scene scene, GameArgs gameArgs)
{
    Projectile* proj = scene.Projectiles;
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
        if (!proj[i].Active) { continue; }
        proj[i].X += proj[i].DirX * proj[i].Speed * state.DeltaTime;
        proj[i].Y += proj[i].DirY * proj[i].Speed * state.DeltaTime;

        if (proj[i].X > SCREEN_WIDTH) { proj[i].Active = false; }
    }
}

void Update(GameState* state, Scene* scene, SDL sdl, GameArgs gameArgs)
{
    UpdatePlayers(state, *scene, gameArgs);
    UpdateEnemies(state, scene, sdl);
    UpdateProjectiles(*state, *scene, gameArgs);
}

