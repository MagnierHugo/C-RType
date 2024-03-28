#pragma once
#include <SDL.h>

#include "Constants.h"
#include "Structs.h"

int GetJoystickCount();
SDL_Joystick** DetectJoystick(int numJoysticks);
void CheckForJoystick(GameArgs* args);