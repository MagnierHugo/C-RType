#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "HandleSDL.h"
#include "Structs.h"
#include "Constants.h"


SDL_Texture* CreateTexture(struct SDL sdlStruct, char* path)
{
    // Chargement de l'image
    SDL_Surface* image = IMG_Load(path);
    if (!image) {
        ErrorHandling("Failed to load image", sdlStruct);
    }

    // Création de la texture à partir de l'image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        sdlStruct.renderer, image
    );

    SDL_FreeSurface(image); // Libération de la surface, la texture contient maintenant l'image

    if (!texture) {
        ErrorHandling("Failed to create texture", sdlStruct);
    }

    return texture;
}

void DestroyTextures(struct Textures Tex)
{
    //SDL_DestroyTexture(Tex.background);

}