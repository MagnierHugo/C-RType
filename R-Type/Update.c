#include <SDL.h>

#include <stdio.h>
#include <stdbool.h>

#include "Constants.h"
#include "HandleSDL.h"
#include "Projectile.h"


static void UpdatePlayers(struct GameState state, struct Scene scene)
{
    struct Player* players = scene.Players;
    for (int i = 0; i < PLAYER_CNT; i++)
    {
        struct PlayerInput inputs = state.Inputs.PlayerInput[i];
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

static void UpdateProjectiles(struct GameState state, struct Scene scene)
{
    //printf("Updated at: %f\n", state.CurrentTime);
    struct Projectile* proj = scene.Projectiles;
    for (int i = 0; i < MAX_PROJECTILE_AMOUNT; i++)
    {
        if (!proj[i].Active) { continue; }
        proj[i].X += proj[i].DirX * proj[i].Speed * state.DeltaTime;
        proj[i].Y += proj[i].DirY * proj[i].Speed * state.DeltaTime;

        if (proj[i].X > SCREEN_WIDTH) { proj[i].Active = false; }
    }
}

void Update(struct GameState state, struct Scene scene)
{
    UpdatePlayers(state, scene);
    UpdateProjectiles(state, scene);
}