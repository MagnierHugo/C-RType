#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "../Include/HandleSDL.h"
#include "../Include/Structs.h"


SDL_Texture* CreateTexture(SDL sdlStruct, char* path)
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

void DestroyTextures(Textures Tex)
{
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.Background);
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.Player1);
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.Player1Hurt); // 69 :) Nice
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.Player2);
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.EnemyType1);
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.Boss1);
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.Projectiles); // 69 :) Nice
}