#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Menu.h"
#include "../Include/Text.h"

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

static void DrawRemapMenu(GameArgs args,
    Button lBtns[5], Button rBtns[5])
{
    SDL_SetRenderDrawColor(args.SDL.renderer, 255, 255, 255, 255);
    SDL_RenderClear(args.SDL.renderer);

    InputMap leftInputMap = args.State.Inputs.InputMap[0];
    SDL_Scancode leftCodes[] = { leftInputMap.Up, leftInputMap.Left,
        leftInputMap.Down, leftInputMap.Right, leftInputMap.Shoot };
    InputMap rightInputMap = args.State.Inputs.InputMap[1];
    SDL_Scancode rightCodes[] = { rightInputMap.Up, rightInputMap.Left,
        rightInputMap.Down, rightInputMap.Right, rightInputMap.Shoot };

    for (int i = 0; i < 5; i++) {
        DrawButton(args.SDL.renderer, lBtns[i]);
        char* lKeyName = SDL_GetKeyName(SDL_GetKeyFromScancode(leftCodes[i]));
        RenderText(args.SDL, lKeyName, DONT_RENDER_FLAG,
            lBtns[i].Rect.x + lBtns[i].Rect.w / 2,
            lBtns[i].Rect.y + lBtns[i].Rect.h / 2);
        DrawButton(args.SDL.renderer, rBtns[i]);
        char* rKeyName = SDL_GetKeyName(SDL_GetKeyFromScancode(rightCodes[i]));
        RenderText(args.SDL, rKeyName, DONT_RENDER_FLAG,
            rBtns[i].Rect.x + rBtns[i].Rect.w / 2,
            rBtns[i].Rect.y + rBtns[i].Rect.h / 2);
    }

    SDL_RenderPresent(args.SDL.renderer);
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
            break;
        case 1:
            printf("Left\n");
            relevantInputMap->Left = GetKeyPressed();
            break;
        case 2:
            printf("Down\n");
            relevantInputMap->Down = GetKeyPressed();
            break;
        case 3:
            printf("Right\n");
            relevantInputMap->Right = GetKeyPressed();
            break;
        case 4:
            printf("Shoot\n");
            relevantInputMap->Shoot = GetKeyPressed();
            break;
    }
    printf("Remapped succesfully\n");
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
        DrawRemapMenu(gameArgs, leftButtons, rightButtons);
    }
}