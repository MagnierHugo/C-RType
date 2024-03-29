#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Menu.h"

static void CreateLeftButtons(Button lB[5], SDL_Color btnColor)
{
    lB[0].Rect.x = SCREEN_WIDTH / 4 - BUTTON_SIZE / 2;
    lB[1].Rect.x = SCREEN_WIDTH / 4 - 3 * BUTTON_SPACING - BUTTON_SIZE;
    lB[2].Rect.x = SCREEN_WIDTH / 4 - BUTTON_SIZE / 2;
    lB[3].Rect.x = SCREEN_WIDTH / 4 + BUTTON_SIZE - BUTTON_SPACING;
    lB[4].Rect.x = SCREEN_WIDTH / 4 - 3 * BUTTON_SPACING - BUTTON_SIZE;

    lB[0].Rect.y = SCREEN_HEIGHT / 4 - BUTTON_SIZE;
    lB[1].Rect.y = SCREEN_HEIGHT / 4 + BUTTON_SPACING;
    lB[2].Rect.y = SCREEN_HEIGHT / 4 + BUTTON_SPACING;
    lB[3].Rect.y = SCREEN_HEIGHT / 4 + BUTTON_SPACING;
    lB[4].Rect.y = SCREEN_HEIGHT / 4 + 2 * BUTTON_SPACING + BUTTON_SIZE;

    for (int i = 0; i < 5; i++) {
        lB[i].Rect.w = BUTTON_SIZE;
        lB[i].Rect.h = BUTTON_SIZE;
        lB[i].Color = btnColor;
        lB[i].Clicked = false;
    }
    lB[4].Rect.w = lB[3].Rect.x - lB[1].Rect.x + BUTTON_SIZE;
}

static void CreateButtons(Button lB[5], Button rB[5]) // left buttons & right buttons
{
    SDL_Color buttonColor = { 100, 100, 100, 255 };
    CreateLeftButtons(lB, buttonColor);

    // now that the ugly layout is done: port it to the other side
    for (int i = 0; i < 5; i++) {
        rB[i].Rect.x = SCREEN_WIDTH - lB[i].Rect.w - lB[i].Rect.x;
        rB[i].Rect.y = lB[i].Rect.y;
        rB[i].Rect.w = lB[i].Rect.w;
        rB[i].Rect.h = lB[i].Rect.h;
        rB[i].Color = buttonColor;
        rB[i].Clicked = false;
    }
}

static void DrawRemapMenu(SDL sdl,
    Button lBtns[5], Button rBtns[5])
{
    SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl.renderer);

    for (int i = 0; i < 5; i++) {
        DrawButton(sdl.renderer, lBtns[i]);
        DrawButton(sdl.renderer, rBtns[i]);
    }

    SDL_RenderPresent(sdl.renderer);
}

static void HandleRemap(InputsSummary input, int rightSide, int whichButton)
{
    InputMap* relevantInputMap = &input.InputMap[rightSide];
    printf("Listening for a key to bind to Player%d ", rightSide + 1);
    switch (whichButton)
    {
        case 0:
            printf("Up\n");
            relevantInputMap->Up = GetKeyPressed();
            printf("Remapped succesfully\n");
            break;
        case 1:
            printf("Left\n");
            relevantInputMap->Left = GetKeyPressed();
            printf("Remapped succesfully\n");
            break;
        case 2:
            printf("Down\n");
            relevantInputMap->Down = GetKeyPressed();
            printf("Remapped succesfully\n");
            break;
        case 3:
            printf("Right\n");
            relevantInputMap->Right = GetKeyPressed();
            printf("Remapped succesfully\n");
            break;
        case 4:
            printf("Shoot\n");
            relevantInputMap->Shoot = GetKeyPressed();
            printf("Remapped succesfully\n");
            break;
        default:
            break;
    }

}

void RemapMenu(GameArgs gameArgs) // add a go back button
{ 
    Button leftButtons[5];
    Button rightButtons[5];

    CreateButtons(leftButtons, rightButtons);

    SDL_Event event;
    bool continue_ = true;
    while (continue_)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) continue_ = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                for (int i = 0; i < 5; i++)
                {
                    if (PointInRect(mouseX, mouseY, leftButtons[i].Rect))
                        HandleRemap(gameArgs.State.Inputs, 0, i);
                    if (PointInRect(mouseX, mouseY, rightButtons[i].Rect))
                        HandleRemap(gameArgs.State.Inputs, 1, i);
                }
            }
        }
        DrawRemapMenu(gameArgs.SDL, leftButtons, rightButtons);
    }
}