#ifndef GAME_H
#define GAME_H

#include "windowing.h"
#include <stdbool.h>

typedef struct Game {
    Windowing windowing;
    bool running;
} Game;

int Game_init(Game *game);
void Game_destroy(Game game);

void Game_run(Game game);
void Game_tick(Game game, float dt);
void Game_render(Game game);

#endif
