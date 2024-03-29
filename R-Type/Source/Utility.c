#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/HandleSDL.h"

int RdmInt(int min, int max, bool nonZero)
{
    int rdm;
    do
    {
        rdm = min + rand() % (max - min + 1);
    } while (nonZero && rdm == 0);

    return rdm;
}

void Swap(void* element1, void* element2)
{
    void* tempElement = element1;
    element1 = element2;
    element2 = tempElement;
}

void CheckPointerKill(void* pointer, char* errorMessage, SDL sdl)
{
    if (pointer == NULL) {
        ErrorHandling(errorMessage, sdl);
    }
}

bool CheckPointer(void* pointer)
{
    return pointer != NULL;
}

//int ControllerAxisToInt(SDL_GameController* controller, int axis) {
//    int rawAxis = SDL_GameControllerGetAxis(controller, axis);
//    if (abs(rawAxis) > JOY_POS * .5)
//    >  / JOY_POS);
//}

int ControllerAxisToInt(SDL_GameController* controller, int axis) {

    float rawAxis = SDL_GameControllerGetAxis(controller, axis);

    if (abs(rawAxis) > ACTIVATION_THRESHOLD) return rawAxis > 0 ? 1 : -1;
    else return 0;
    
}