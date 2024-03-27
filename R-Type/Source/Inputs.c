#include "../Include/Constants.h"
#include "../Include/Structs.h"


void HandleInputs(GameState state, Scene scene)
{
    InputsSummary* inputs = &state.Inputs;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            //return ( InputSummary) { false, false };

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                //return ( InputSummary) { false, false };
            }

        default:
            break;
        }
    }
    for (int i = 0; i < PLAYER_CNT; i++)
    {
        PlayerInput* playerInput = &inputs->PlayerInput[i]; // get the player inputs
        InputMap* inputMap = &inputs->InputMap[i]; // retrieve the player key mapping
        playerInput->DirY = keys[inputMap->Down] - keys[inputMap->Up];
        playerInput->DirX = keys[inputMap->Right] - keys[inputMap->Left];
        playerInput->Shooting = keys[inputMap->Shoot];

    }

    /*
    inputs->P[0].DirY = keyState[SDL_SCANCODE_S] - keyState[SDL_SCANCODE_W];
    inputs->P[0].DirX = keyState[SDL_SCANCODE_D] - keyState[SDL_SCANCODE_A];
    inputs->P[0].Shooting = keyState[SDL_SCANCODE_SPACE];
    inputs->P[1].DirY = keyState[SDL_SCANCODE_DOWN] - keyState[SDL_SCANCODE_UP];
    inputs->P[1].DirX = keyState[SDL_SCANCODE_RIGHT] - keyState[SDL_SCANCODE_LEFT];
    inputs->P[1].Shooting = keyState[SDL_SCANCODE_KP_0];
    */
}