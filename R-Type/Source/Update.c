#include <SDL.h>

#include <stdio.h>
#include <stdbool.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/HandleSDL.h"
#include "../Include/Projectile.h"
#include "../Include/Enemies.h"


static void UpdatePlayers(GameState state, Scene scene)
{
    Player* players = scene.Players;
    for (int i = 0; i < PLAYER_CNT; i++)
    {
        PlayerInput inputs = state.Inputs.PlayerInput[i];
        players[i].X += inputs.DirX * players[i].Speed * state.DeltaTime;
        players[i].Y += inputs.DirY * players[i].Speed * state.DeltaTime;
        if (state.Inputs.PlayerInput[i].Shooting)
        {
            if (players[i].LastTimeShot + SHOOTING_RATE < state.CurrentTime)
            {
                ShootPlayerProjectile(players[i], scene.Projectiles);
                players[i].LastTimeShot = state.CurrentTime;
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

static void UpdateProjectiles(GameState state, Scene scene)
{
    //printf("Updated at: %f\n", state.CurrentTime);
    Projectile* proj = scene.Projectiles;
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
        if (!proj[i].Active) { continue; }
        proj[i].X += proj[i].DirX * proj[i].Speed * state.DeltaTime;
        proj[i].Y += proj[i].DirY * proj[i].Speed * state.DeltaTime;

        if (proj[i].X > SCREEN_WIDTH) { proj[i].Active = false; }
    }
}

static void UpdateEnemies(GameState state, Scene* scene)
{
    SpawnEnemies(scene);

    EnemyQueue* queue = &scene->Queue;

    for (int i = 0; i < scene->ActiveEnemies; i++)
    {
        Enemy* enemy = &queue->Enemies[i];

        enemy->X += enemy->dirX * enemy->Speed * state.DeltaTime;
        enemy->Y += enemy->dirY * enemy->Speed * state.DeltaTime;
    }
}

void Update(GameState state, Scene* scene)
{
    UpdatePlayers(state, *scene);
    UpdateProjectiles(state, *scene);
    UpdateEnemies(state, scene);
}