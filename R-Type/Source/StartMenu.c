#include <SDL.h>
#include <stdio.h>

#include "../Include/Constants.h"
#include "../Include/Structs.h"
#include "../Include/Menu.h"
#include "../Include/Text.h"
#include "../Include/RemapMenu.h"


static void CreateButtons(Button buttons[4], SDL sdl)
{
    SDL_Color buttonColor = { 100, 100, 100, 255 };

    int buttonX = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
    int buttonSpacing = BUTTON_HEIGHT + 20;
    int buttonY = (SCREEN_HEIGHT - (3 * BUTTON_HEIGHT + 2 * 20)) / 2;

    buttons[0] = (Button){
        {buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor, false }; 
    buttons[1] = (Button){
        {buttonX, buttonY + buttonSpacing, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor, false };
    buttons[2] = (Button){
        {buttonX, buttonY + 2 * buttonSpacing, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor, false };
    buttons[3] = (Button){
        {buttonX, buttonY + 3 * buttonSpacing, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor, false };
}

static void DrawStartMenu(SDL sdl, Button buttons[4])
{

    char* Ti[] = { "SOLO", "DUO", "REBIND", "QUIT" };
    SDL_RenderCopy(sdl.renderer, sdl.Tex.TitleScreen, NULL, NULL);

    for (int i = 0; i < 4; i++) {
        DrawButton(sdl.renderer, buttons[i]);
        RenderText(sdl, Ti[i], DONT_RENDER_FLAG,
            buttons[i].Rect.x + buttons[i].Rect.w / 2,
            buttons[i].Rect.y + buttons[i].Rect.h / 2);
    }

    SDL_RenderPresent(sdl.renderer);
}

static bool HandleStartMenu(GameArgs gameArgs, Button buttons[4], int* pCount)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) return false;
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            for (int i = 0; i < 4; i++) {
                if (PointInRect(mouseX, mouseY, buttons[i].Rect)) {
                    switch (i) {
                        case 0:
                            *pCount = 1;
                            return false;
                        case 1:
                            *pCount = 2;
                            return false;
                        case 2:
                            RemapMenu(gameArgs);
                            break;
                        case 3:
                            SDL_Quit();
                            break;
                    }
                }
            }
        }
    }
    return true;
}

int StartMenu(GameArgs gameArgs)
{
    Button buttons[4];
    CreateButtons(buttons, gameArgs.SDL);

    int playerCount = 0;
    bool continue_ = true;
    while (continue_)
    {
        DrawStartMenu(gameArgs.SDL, buttons);
        continue_ = HandleStartMenu(gameArgs, buttons, &playerCount);
    }
    return playerCount;
}

