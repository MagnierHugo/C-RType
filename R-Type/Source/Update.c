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


static void UpdatePlayers(GameState* state, Scene scene)
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
                ShootPlayerProjectile(players[i], scene.Projectiles, state);
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

static void UpdateEnemies(GameState* state, Scene scene)
{
    Enemy* enemies = scene.Enemies;
    Player* players = scene.Players;
    Projectile* projs = scene.Projectiles;
    for (int i = 0; i < scene.EnemyCount; i++)
    {
        Enemy* enemy = &enemies[i];
        if (!enemy->Active) continue;
        enemy->X -= enemy->Speed * state->DeltaTime;

        if (enemy->X + ENEMIES_WIDTH < 0)
        {
            enemy->X = SCREEN_WIDTH + RdmInt(
                MIN_RESET_X_OFFSET, MAX_RESET_X_OFFSET, false);
            enemy->Y = RdmInt(0, SCREEN_HEIGHT - ENEMIES_HEIGHT, false);
        }

        CheckEnemyPlayerCollision(*state, *enemy, players);

        state->Score += CheckEnemyProjCollision(*state, enemy, projs);
    }
}

static void UpdateProjectiles(GameState state, Scene scene)
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

void Update(GameState* state, Scene scene)
{
    UpdatePlayers(state, scene);
    UpdateEnemies(state, scene);
    UpdateProjectiles(*state, scene);
}

