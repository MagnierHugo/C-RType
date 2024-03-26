#pragma once

#include <stdbool.h>
#include <SDL.h>
#include "HandleSDL.h"
#include "Constants.h"
#include "Utility.h"

//void UpdateParticles(Particle* particles, float deltaTime);
SDL_Rect ParticleAsRect(Particle particle);
void DrawParticles(Particle* particles, SDL_Renderer* renderer, SDL_Texture* texture);
void ParticlesBurst(Particle* particles, int directionX);
void KillParticles(Particle* particles);