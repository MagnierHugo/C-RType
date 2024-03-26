#include <SDL.h>
#include <stdio.h>
#include "Constants.h"

struct Button {
    SDL_Rect Rect ;  // Rectangle representing button's position and size
    SDL_Color Color; // Color of the button
    bool Clicked;
};

bool PointInRect(int x, int y, SDL_Rect rect)
{
    return (
        x >= rect.x &&
        x <= rect.x + rect.w &&
        y >= rect.y &&
        y <= rect.y + rect.h
        );
}

void DrawButton(SDL_Renderer* renderer, struct Button button) {
    SDL_SetRenderDrawColor(renderer, button.Color.r, button.Color.g, button.Color.b, 255);
    SDL_RenderFillRect(renderer, &button.Rect);
}

void StartMenu(struct GameArgs gameArgs)
{
    SDL_Color buttonColor = { 100, 100, 100, 255 };

    int buttonX = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
    int buttonSpacing = BUTTON_HEIGHT + 20;
    int buttonY = (SCREEN_HEIGHT - (3 * BUTTON_HEIGHT + 2 * 20)) / 2;

    struct Button playButton = {
        {buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor };
    struct Button remapButton = {
        {buttonX, buttonY + buttonSpacing, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor };
    struct Button difficultyButton = {
        {buttonX, buttonY + 2 * buttonSpacing, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor };
    struct Button quitButton = {
        {buttonX, buttonY + 3 * buttonSpacing, BUTTON_WIDTH, BUTTON_HEIGHT},
        buttonColor };

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

                playButton.Clicked = PointInRect(mouseX, mouseY, playButton.Rect);
                remapButton.Clicked = PointInRect(mouseX, mouseY, remapButton.Rect);
                difficultyButton.Clicked = PointInRect(mouseX, mouseY, difficultyButton.Rect);
                quitButton.Clicked = PointInRect(mouseX, mouseY, quitButton.Rect);
            }
        }

        SDL_SetRenderDrawColor(gameArgs.SDL.renderer, 255, 255, 255, 255);
        SDL_RenderClear(gameArgs.SDL.renderer);
    
        DrawButton(gameArgs.SDL.renderer, playButton);
        DrawButton(gameArgs.SDL.renderer, remapButton);
        DrawButton(gameArgs.SDL.renderer, difficultyButton);
        DrawButton(gameArgs.SDL.renderer, quitButton);


        SDL_RenderPresent(gameArgs.SDL.renderer);

        if (playButton.Clicked)
        {
            printf("Play\n");
            playButton.Clicked = false;
            continue_ = false;
        }
        else if (remapButton.Clicked)
        {
            printf("Remap\n");
            remapButton.Clicked = false;
        }
        else if (difficultyButton.Clicked)
        {
            printf("Difficulty\n");
            difficultyButton.Clicked = false;
        }
        else if (quitButton.Clicked)
        {
            printf("Quit\n");
            quitButton.Clicked = false;
            // add the cleanup logic
        }
    }
}


void RemapMenu(struct GameArgs gameArgs) // add a go back button
{
   
    SDL_Color buttonColor = { 100, 100, 100, 255 };
    struct Button leftButtons[5];
    leftButtons[0].Rect.x = SCREEN_WIDTH / 4 - BUTTON_SIZE / 2;
    leftButtons[1].Rect.x = SCREEN_WIDTH / 4 - 3 * BUTTON_SPACING - BUTTON_SIZE;
    leftButtons[2].Rect.x = SCREEN_WIDTH / 4 - BUTTON_SIZE / 2;
    leftButtons[3].Rect.x = SCREEN_WIDTH / 4 + BUTTON_SIZE - BUTTON_SPACING;
    leftButtons[4].Rect.x = SCREEN_WIDTH / 4 - 3 * BUTTON_SPACING - BUTTON_SIZE;

    leftButtons[0].Rect.y = SCREEN_HEIGHT / 4 - BUTTON_SIZE;
    leftButtons[1].Rect.y = SCREEN_HEIGHT / 4 + BUTTON_SPACING;
    leftButtons[2].Rect.y = SCREEN_HEIGHT / 4 + BUTTON_SPACING;
    leftButtons[3].Rect.y = SCREEN_HEIGHT / 4 + BUTTON_SPACING;
    leftButtons[4].Rect.y = SCREEN_HEIGHT / 4 + 2 * BUTTON_SPACING + BUTTON_SIZE;

    for (int i = 0; i < 5; i++)
    {
        leftButtons[i].Rect.w = BUTTON_SIZE;
        leftButtons[i].Rect.h = BUTTON_SIZE;
        leftButtons[i].Color = buttonColor;
        leftButtons[i].Clicked = false;
    }
    leftButtons[4].Rect.w = leftButtons[3].Rect.x - leftButtons[1].Rect.x + BUTTON_SIZE;

    struct Button rightButtons[5]; // now that the ugly layout is done: port it to the other side
    for (int i = 0; i < 5; i++) {
        rightButtons[i].Rect.x = SCREEN_WIDTH - leftButtons[i].Rect.w - leftButtons[i].Rect.x;
        rightButtons[i].Rect.y = leftButtons[i].Rect.y;
        rightButtons[i].Rect.w = leftButtons[i].Rect.w;
        rightButtons[i].Rect.h = leftButtons[i].Rect.h;
        rightButtons[i].Color = buttonColor;
        rightButtons[i].Clicked = false;
    }

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
                    leftButtons[i].Clicked = PointInRect(mouseX, mouseY, leftButtons[i].Rect);
                }

                for (int i = 0; i < 5; i++)
                {
                    rightButtons[i].Clicked = PointInRect(mouseX, mouseY, rightButtons[i].Rect);
                }

            }
        }

        SDL_SetRenderDrawColor(gameArgs.SDL.renderer, 255, 255, 255, 255);
        SDL_RenderClear(gameArgs.SDL.renderer);

        for (int i = 0; i < 5; i++) {
            DrawButton(gameArgs.SDL.renderer, leftButtons[i]);
        }

        for (int i = 0; i < 5; i++) {
            DrawButton(gameArgs.SDL.renderer, rightButtons[i]);
        }

        SDL_RenderPresent(gameArgs.SDL.renderer);

    }
}


void HandleMenuEvent(struct Button* buttons)
{
    // could take care of the repeatedswitch case
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