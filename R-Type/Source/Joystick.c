#include <SDL.h>
#include <stdio.h>

#include "../Include/HandleSDL.h"

int NumJoystick() {

    int numJoysticks = SDL_NumJoysticks();
    return numJoysticks;
}

SDL_Joystick* DetectJoystick(int numJoysticks) {

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
    return (SDL_Joystick*[2]) { joystick1, joystick2 };
}

static ActionJoystick(SDL_Event event, int numJoysticks) {

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            break;
        case SDL_JOYBUTTONDOWN:
            if (event.jbutton.button == 0) {
                // action
            }
            break;
        case SDL_JOYAXISMOTION:
            if (event.jaxis.axis == 0) {
                if (abs(event.jaxis.value) > 8000) {
                    /*J1.x += event.jaxis.value / 32767.0f * 5;*/
                }
            }
            else if (event.jaxis.axis == 1) {
                if (abs(event.jaxis.value) > 8000) {
                    /*J1.y += event.jaxis.value / 32767.0f * 5;*/
                }
            }
            // Contrôles pour le deuxième cube avec le deuxième joystick
            else if (event.jaxis.axis == 2) {
                if (abs(event.jaxis.value) > 8000) {
                    /*J2.x += event.jaxis.value / 32767.0f * 5;*/
                }
            }
            else if (event.jaxis.axis == 3) {
                if (abs(event.jaxis.value) > 8000) {
                    /*J2.y += event.jaxis.value / 32767.0f * 5;*/
                }
            }
            break;
        }
    }
    return 0;
}
