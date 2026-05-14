#ifndef PIECE_H
#define PIECE_H

#include "texture_handler.h"
#include "windowing.h"
#include <SDL2/SDL.h>

typedef enum {
    EMPTY = -1,

    B_PAWN,
    B_ROOK,
    B_BISHOP,
    B_KNIGHT,
    B_QUEEN,
    B_KING,

    W_PAWN,
    W_ROOK,
    W_BISHOP,
    W_KNIGHT,
    W_QUEEN,
    W_KING,
} PieceType;

typedef struct {
    PieceType type;
} Piece;

Piece Piece_init(PieceType type);
void Piece_render(Piece piece, Textures textures, Windowing windowing, int cx, int cy);

#endif
