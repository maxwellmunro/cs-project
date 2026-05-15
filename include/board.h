#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "windowing.h"
#include <stdbool.h>

typedef struct {
    Piece pieces[64];

    int last_two_square_advance_x;
    int last_two_square_advance_y;

    bool white_to_move;
} Board;

Board Board_init();
void Board_render(Board *board, Textures textures, Windowing windowing);

Piece *Board_get_piece(Board *board, int x, int y);
int Board_move_piece(Board *board, int sx, int sy, int dx, int dy);
bool Board_is_valid_move(Board *board, int sx, int sy, int dx, int dy);

#endif
