#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/RemapMenu.h"
#include "../Include/HandleJoystick.h"
#include "../Include/main.h"

void HandleJoystick(InputsSummary* inputs)
{
    SDL_GameController* controller = SDL_GameControllerOpen(0);

    for (int i = 0; i < PLAYER_CNT; i++) {
        PlayerInput* playerInput = &inputs->PlayerInput[i];
        if (playerInput->DirX == 0) {
            playerInput->DirX = ControllerAxisToInt(controller,
                i ? SDL_CONTROLLER_AXIS_RIGHTX : SDL_CONTROLLER_AXIS_LEFTX);
        }

        if (playerInput->DirY == 0) {
            playerInput->DirY = ControllerAxisToInt(controller,
                i ? SDL_CONTROLLER_AXIS_RIGHTY : SDL_CONTROLLER_AXIS_LEFTY);
        }

    }
}

void ResetKeystrokes(InputsSummary* inputs)
{
    for (int i = 0; i < PLAYER_CNT; i++)
    {
        PlayerInput* playerInput = &inputs->PlayerInput[i]; // get the player inputs
        playerInput->DirY = 0;
        playerInput->DirX = 0;
        playerInput->Shooting = false;
    }
}

void HandleKeystrokes(InputsSummary* inputs)
{
    Uint8* keys = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < PLAYER_CNT; i++)
    {
        PlayerInput* playerInput = &inputs->PlayerInput[i]; // get the player inputs
        InputMap* inputMap = &inputs->InputMap[i]; // retrieve the player key mapping
        if (playerInput->DirY == 0) {
            playerInput->DirY = keys[inputMap->Down] - keys[inputMap->Up];
        }
        if (playerInput->DirY == 0) {
            playerInput->DirX = keys[inputMap->Right] - keys[inputMap->Left];
        }
        
        playerInput->Shooting |= keys[inputMap->Shoot];
    }
}

void HandleControllerStrokes(InputsSummary* inputs)
{
    SDL_GameController* controller = SDL_GameControllerOpen(0); // Open the first connected controller
    if (controller) {
        if (SDL_GameControllerGetButton(controller,
            SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
            PlayerInput* playerInput = &inputs->PlayerInput[0];
            playerInput->Shooting = true;
        }

        if (SDL_GameControllerGetButton(controller,
            SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
            PlayerInput* playerInput = &inputs->PlayerInput[1];
            playerInput->Shooting = true;
        }
    }
}

void HandleInputs(GameArgs* args)
{
    CheckForJoystick(args);
    InputsSummary* inputs = &args->State.Inputs;
    ResetKeystrokes(inputs);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                QuitGame(*args);
                return;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    RemapMenu(*args);
                    return;
                }
                break;

            default:
                break;
        }
    }
    HandleKeystrokes(inputs);
    HandleControllerStrokes(inputs);
    HandleJoystick(inputs);
}






