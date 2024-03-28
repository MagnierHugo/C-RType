#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/RemapMenu.h"
#include "../Include/HandleJoystick.h"



void ActionJoystick(GameArgs* args, SDL_Event event) {

    InputsSummary* inputs = &args->State.Inputs;

    int axis = event.jaxis.axis;
    if (axis % 2 == 0) {
        if (abs(event.jaxis.value) > DEADZONE) {
            /*J1.x += event.jaxis.value / JOY_POS * SENSITIVITY;*/
            PlayerInput* playerInput = &inputs->PlayerInput[axis / 2];
            playerInput->DirX = event.jaxis.value / abs(event.jaxis.value);
        }
    }
    else if (axis % 2 == 1) {
        if (abs(event.jaxis.value) > DEADZONE) {
            /*J1.y += event.jaxis.value / JOY_POS * SENSITIVITY;*/
            PlayerInput* playerInput = &inputs->PlayerInput[(axis - 1) / 2];
            playerInput->DirY = event.jaxis.value / abs(event.jaxis.value);
        }
    }
}


void HandleKeystrokes(InputsSummary* inputs, Uint8* keys)
{
    for (int i = 0; i < PLAYER_CNT; i++)
    {
        PlayerInput* playerInput = &inputs->PlayerInput[i]; // get the player inputs
        InputMap* inputMap = &inputs->InputMap[i]; // retrieve the player key mapping
        playerInput->DirY = keys[inputMap->Down] - keys[inputMap->Up];
        playerInput->DirX = keys[inputMap->Right] - keys[inputMap->Left];
        playerInput->Shooting = keys[inputMap->Shoot];
    }
}

void HandleControllerStrokes(InputsSummary* inputs, int side) {
    PlayerInput* playerInput = &inputs->PlayerInput[side];
    playerInput->Shooting = true;
}

void HandleInputs(GameArgs* args)
{
    InputsSummary* inputs = &args->State.Inputs;
    Uint8* keystrokes = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                args->State.Continue = false;
                return;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    RemapMenu(*args);
                    return;
                }
                break;

            case SDL_JOYAXISMOTION:
                printf("been there\n");
                ActionJoystick(args, event);
                break;

            case SDL_JOYBUTTONDOWN:
                printf("been there\n");
                if (event.jbutton.button == 4) {
                    HandleControllerStrokes(inputs, 0);
                }
                else if (event.jbutton.button == 5) {
                    HandleControllerStrokes(inputs, 1);
                }
                break;

            default:
                break;
        }
    }
    HandleKeystrokes(inputs, keystrokes);
}






