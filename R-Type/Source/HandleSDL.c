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
#include "../Include/Utility.h"


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
        //Mix_CloseAudio();
        SDL_Quit();
    }
    exit(EXIT_FAILURE);
}

static void InitSDL( SDL sdl)
{
    // Initialisation SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorHandling("Erreur SDL Init failed", sdl);
    }

    if (TTF_Init() != 0) {
        ErrorHandling("Erreur SDL_ttf failed", sdl);
    }

    // Initialisation SDL Audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        ErrorHandling("Erreur initialisation de SDL Audio", sdl);
    }

    // Open Audio Channels
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, NUMBER_OF_CHANNELS, 2048) < 0)
    {
        ErrorHandling("Erreur initialisation de SDL Mixer", sdl);
    }
    Mix_Volume(0, 7);

    if (TTF_Init() < 0) {
        ErrorHandling("Erreur initialisation de SDL TTF", sdl);
    }
}

SDL StartSDL()
{
    SDL sdl;

    InitSDL(sdl);

    //creer une fenetre avec SDL
    sdl.window = SDL_CreateWindow("Ship game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );
    CheckPointer(sdl.window, "Erreur creation fen�tre SDL", sdl);

    //Creer rendu SDL
    sdl.renderer = SDL_CreateRenderer(
        sdl.window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    CheckPointer(sdl.renderer, "Erreur creation rendu SDL", sdl);

    sdl.Font = TTF_OpenFont("..\\Font\\font.fon", 24);// Load font
    CheckPointer(sdl.Font, "Erreur chargement de la police", sdl);

    sdl.Tex = InitTextures(sdl);
    sdl.nbrAnimation = 0;

    return sdl;
}

void CloseSDL(GameArgs gameArgs)
{
    TTF_CloseFont(gameArgs.SDL.Font);
    DestroyTextures(gameArgs.SDL.Tex);
    SDL_DestroyRenderer(gameArgs.SDL.renderer);
    SDL_DestroyWindow(gameArgs.SDL.window);

    SDL_Quit();
}

void WindowClear(SDL_Renderer* renderer, SDL_Texture* background)
{
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderClear(renderer); // more of a fill
    SDL_RenderCopy(
        renderer, background, NULL,
        &(SDL_Rect){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }
    );
}