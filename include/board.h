#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "windowing.h"
typedef struct {
    Piece pieces[64];
} Board;

Board Board_init();
void Board_render(Board *board, Textures textures, Windowing windowing);

#endif
