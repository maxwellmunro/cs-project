#ifndef WINDOWING_H
#define WINDOWING_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Windowing;

Windowing Windowing_init();
void Windowing_destroy(Windowing *windowing);

#endif
