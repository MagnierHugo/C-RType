#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "Constants.h"
#include "Structs.h"
#include  "textures.h"
#include  "Init.h"







int ErrorHandling(char* message, struct SDL sdl)
{
    printf("%s\n", message);
    if (&sdl != &(struct SDL) { NULL, NULL }) {

        if (sdl.Font != NULL) {
            if (sdl.window != NULL) {
                if (sdl.renderer != NULL) {
                    SDL_DestroyRenderer(sdl.renderer);
                }
                TTF_CloseFont(sdl.Font);
                SDL_DestroyWindow(sdl.window);
            }
            TTF_Quit();
        }
        //Mix_CloseAudio();
        SDL_Quit();
    }
    exit(EXIT_FAILURE);
}


void InitSDL(struct SDL sdl)
{
    // Initialisation SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorHandling("Erreur SDL Init failed", sdl);
    }

     //Initialisation SDL Audio
    //if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    //    ErrorHandling("Erreur initialisation de SDL Audio", sdl);
    //}

    //// Open Audio Channels
    //if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, NUMBER_OF_CHANNELS, 2048) < 0)
    //{
    //    ErrorHandling("Erreur initialisation de SDL Mixer", sdl);
    //}

    if (TTF_Init() < 0) {
        ErrorHandling("Erreur initialisation de SDL TTF", sdl);
    }
    Mix_Volume(0, 7);

}

struct SDL StartSDL()
{
    struct SDL sdl = { NULL, NULL };

    InitSDL(sdl);

    //creer une fenetre avec SDL
    sdl.window = SDL_CreateWindow("Ship game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    if (sdl.window == NULL) {
        ErrorHandling("Erreur creation fen�tre SDL", sdl);
    }

    //Creer rendu SDL
    sdl.renderer = SDL_CreateRenderer(
        sdl.window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (sdl.renderer == NULL) {
        ErrorHandling("Erreur creation rendu SDL", sdl);
    }

    sdl.Font = TTF_OpenFont("..\\Font\\font.fon", 24);// Load font
    if (sdl.Font == NULL) {
        ErrorHandling("Erreur chargement de la police", sdl);
        ;
    }


    sdl.Tex = InitTextures();
    return sdl;
}

void CloseSDL(struct GameArgs gameArgs)
{
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

void TempWindowClear(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // more of a fill
}