#include "../include/texture_handler.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

int load_texture(Texture *texture, SDL_Renderer *renderer,
                 const char *filepath) {
    SDL_Surface *surf = IMG_Load(filepath);

    if (!surf) {
        printf("Error loading image: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (!tex) {
        printf("Error creating texture: %s\n", SDL_GetError());
        return -2;
    }

    texture->surf = surf;
    texture->tex = tex;
    texture->w = surf->w;
    texture->h = surf->h;

    return 0;
}

#define init_texture(id, path)                                                 \
    if (!load_texture(&texture, renderer, path)) {                             \
        textures->id = texture;                                                \
    } else {                                                                   \
        return -1;                                                             \
    }

int Textures_init(Textures *textures, SDL_Renderer *renderer) {
    Texture texture;
    
    init_texture(pieces, "res/pieces.png")

    return 0;
}
