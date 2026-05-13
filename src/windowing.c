#include "../include/windowing.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

Windowing Windowing_init(void) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

    SDL_Renderer *renderer= SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

    return (Windowing) { window, renderer };
}

void Windowing_destroy(Windowing windowing) {
    SDL_DestroyRenderer(windowing.renderer);
    SDL_DestroyWindow(windowing.window);
    SDL_Quit();
}
