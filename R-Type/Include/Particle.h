#pragma once

#include <SDL.h>

#include "Structs.h"

//void UpdateParticles(Particle* particles, float deltaTime);
SDL_Rect ParticleAsRect(Particle particle);
void DrawParticles(Particle* particles, SDL sdl);
void ParticlesBurst(Particle* particles, int directionX);
void KillParticles(Particle* particles);