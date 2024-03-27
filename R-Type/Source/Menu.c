#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"


bool PointInRect(int x, int y, SDL_Rect rect)
{
    return (
        x >= rect.x &&
        x <= rect.x + rect.w &&
        y >= rect.y &&
        y <= rect.y + rect.h
        );
}

void DrawButton(SDL_Renderer* renderer, Button button) {
    SDL_SetRenderDrawColor(renderer, button.Color.r, button.Color.g, button.Color.b, 255);
    SDL_RenderFillRect(renderer, &button.Rect);
}

SDL_Scancode GetKeyPressed() {
    SDL_Event event;
    while (1)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            return event.key.keysym.scancode;
        }
    }
}