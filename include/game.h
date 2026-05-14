#ifndef GAME_H
#define GAME_H

#include "texture_handler.h"
#include "windowing.h"
#include "board.h"
#include <stdbool.h>

typedef struct Game {
    Windowing windowing;
    Textures textures;
    Board board;

    bool running;

    int selected_x;
    int selected_y;
} Game;

int Game_init(Game *game);
void Game_destroy(Game game);

void Game_run(Game game);
void Game_tick(Game game, float dt);
void Game_render(Game game);

#endif
