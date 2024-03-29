#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "../Include/HandleSDL.h"
#include "../Include/Structs.h"
#include "../Include/Utility.h"


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

SDL_Texture** CreateAnimationTexture(SDL sdl, char* path, int nbrFrames)
{
    SDL_Texture** animation = malloc(nbrFrames * sizeof(SDL_Texture*));
    CheckPointer(animation, "Error Allocating memory for animation", sdl);

    for (int frame = 0; frame < nbrFrames; frame++) {
        char finalPath[256]; // Make sure path buffer is large enough
        snprintf(finalPath, sizeof(finalPath), path, frame + 1);
        animation[frame] = CreateTexture(sdl, finalPath);
    }

    return animation;
}

static void DestroyAnime(int size, SDL_Texture** animation)
{
    for (int index = 0; index < size; index++)
    {
        SDL_DestroyTexture(animation[index]);
    }

    free(animation);
}

void DestroyTextures(Textures Tex)
{
    if (Tex.Background != NULL) SDL_DestroyTexture(Tex.Background);
    if (Tex.Player1 != NULL) SDL_DestroyTexture(Tex.Player1);
    if (Tex.Player1Hurt != NULL) SDL_DestroyTexture(Tex.Player1Hurt); // 69 :) Nice
    if (Tex.Player2 != NULL) SDL_DestroyTexture(Tex.Player2);
    if (Tex.EnemyType1 != NULL) SDL_DestroyTexture(Tex.EnemyType1);
    if (Tex.Boss1 != NULL) SDL_DestroyTexture(Tex.Boss1);
    if (Tex.Projectiles != NULL) SDL_DestroyTexture(Tex.Projectiles); // 69 :) Nice
    if (Tex.Boom != NULL) DestroyAnime(10, Tex.Boom);
}