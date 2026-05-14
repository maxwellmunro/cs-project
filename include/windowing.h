#ifndef WINDOWING_H
#define WINDOWING_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Windowing;

int Windowing_init(Windowing *windowing);
void Windowing_destroy(Windowing windowing);

#endif
