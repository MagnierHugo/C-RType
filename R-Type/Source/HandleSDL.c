#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Include/Structs.h"
#include "../Include/Constants.h"
#include "../Include/Textures.h"
#include "../Include/Init.h"
#include "../Include/Music.h"


void ErrorHandling(char* message,  SDL sdl)
{
    printf("%s\n", message);
    if (&sdl != &(SDL) { NULL, NULL, NULL, NULL, NULL, NULL }) {

        if (sdl.window != NULL) {

            if (sdl.renderer != NULL) {
                if (sdl.Font != NULL) {
                    TTF_CloseFont(sdl.Font);
                }
                DestroyTextures(sdl.Tex);
                SDL_DestroyRenderer(sdl.renderer);
            }
            SDL_DestroyWindow(sdl.window);
        }
        SDL_Quit();
    }
    exit(EXIT_FAILURE);
}

static void InitSDL(SDL sdl)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorHandling("Erreur SDL Init failed", sdl);
    }

    if (TTF_Init() != 0) {
        ErrorHandling("Erreur SDL_ttf failed", sdl);
    }

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        ErrorHandling("Erreur initialisation de SDL Audio", sdl);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, NUMBER_OF_CHANNELS, 2048) < 0)
    {
        ErrorHandling("Erreur initialisation de SDL Mixer", sdl);
    }
    Mix_Volume(0, 7);

    if (TTF_Init() < 0) {
        ErrorHandling("Erreur initialisation de SDL TTF", sdl);
    }

    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        ErrorHandling("Erreur Joystick Init failed", sdl);
    }
}

 SDL StartSDL()
{
    srand(time(NULL));
    SDL sdl;

    InitSDL(sdl);

    sdl.window = SDL_CreateWindow("Ship game", //creer une fenetre avec SDL
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    if (sdl.window == NULL) {
        ErrorHandling("Erreur creation fen�tre SDL", sdl);
    }

    sdl.renderer = SDL_CreateRenderer(//Creer rendu SDL
        sdl.window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (sdl.renderer == NULL) {
        ErrorHandling("Erreur creation rendu SDL", sdl);
    }

    sdl.Font = TTF_OpenFont("../Font/font.fon", 24);// Load font
    if (sdl.Font == NULL) {
        ErrorHandling("Erreur chargement de la police", sdl);
    }

    sdl.Tex = InitTextures(sdl);
    sdl.nbrAnimation = 0;

    return sdl;
}

void CloseSDL(GameArgs gameArgs)
{
    for (int i = 0; i < PLAYER_CNT; i++) {
        SDL_GameController* controller = SDL_GameControllerOpen(i);
        if (CheckPointer(controller)) SDL_GameControllerClose(controller);
    }
    TTF_CloseFont(gameArgs.SDL.Font);
    DestroyTextures(gameArgs.SDL.Tex);
    SDL_DestroyRenderer(gameArgs.SDL.renderer);
    SDL_DestroyWindow(gameArgs.SDL.window);

    SDL_Quit();
}

void WindowClear(SDL_Renderer* renderer, SDL_Texture* background)
{
    SDL_RenderCopy(
        renderer, background, NULL,
        &(SDL_Rect){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }
    );
}