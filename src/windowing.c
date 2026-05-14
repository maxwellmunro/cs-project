#include "../include/windowing.h"
#include "../include/constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int Windowing_init(Windowing *windowing) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
       printf("Error initialising SDL2: %s\n", SDL_GetError()); 
       return -1;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("Error initialising SDL2_image: %s\n", SDL_GetError());
        return -2;
    }

    SDL_Window *window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

    if (!window) {
        printf("Error initialising window: %s\n", SDL_GetError());
        return -2;
    }

    SDL_Renderer *renderer= SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

    if (!renderer) {
        printf("Error initialising renderer: %s\n", SDL_GetError());
        return -3;
    }

    windowing->window = window;
    windowing->renderer = renderer;

    return 0;
}

void Windowing_destroy(Windowing windowing) {
    SDL_DestroyRenderer(windowing.renderer);
    SDL_DestroyWindow(windowing.window);
    SDL_Quit();
}
