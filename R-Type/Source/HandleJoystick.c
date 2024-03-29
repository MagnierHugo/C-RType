#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/HandleSDL.h"

int GetJoystickCount() {
    return SDL_NumJoysticks();
}

SDL_Joystick** DetectJoystick(int numJoysticks, SDL sdl) {

    SDL_Joystick* joystick1 = NULL;
    SDL_Joystick* joystick2 = NULL;

    for (int i = 0; i < numJoysticks; ++i) {
        if (SDL_IsGameController(i)) {
            if (!joystick1) {
                joystick1 = SDL_JoystickOpen(i);
                if (joystick1) {
                    printf("Joystick %d for player 1\n", i);
                }
            }
            else if (!joystick2) {
                joystick2 = SDL_JoystickOpen(i);
                if (joystick2) {
                    printf("Joystick %d for player 2\n", i);
                }
            }
        }
    }
    SDL_Joystick** joysticks = malloc(2 * sizeof(SDL_Joystick*));
    if (joysticks == NULL) ErrorHandling("Erreur with joysticks", sdl);
    joysticks[0] = joystick1;
    joysticks[1] = joystick2;
    return joysticks;
}

void CheckForJoystick(GameArgs* args) {
    int countBefore = args->State.Inputs.JoysticksAvailable;
    args->State.Inputs.JoysticksAvailable = GetJoystickCount();
    if (args->State.Inputs.JoysticksAvailable != countBefore)
    {
        if (args->State.Joysticks) free(args->State.Joysticks);
        args->State.Joysticks = DetectJoystick(GetJoystickCount(), args->SDL);
    }
}