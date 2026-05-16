#ifndef TEXTURE_HANDLER_H
#define TEXTURE_HANDLER_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Surface *surf;
    SDL_Texture *tex;
    int w;
    int h;
} Texture;

typedef struct {
    Texture pieces;
    Texture board;
    Texture promotion_buttons;
} Textures;

int load_texture(Texture *texture, SDL_Renderer *renderer, const char *filepath);
int Textures_init(Textures *textures, SDL_Renderer *renderer);

#endif
