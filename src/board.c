#include "../include/board.h"
#include "../include/constants.h"
#include "../include/math.h"

Board Board_init() {
    return (Board){{
        B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK,
        B_PAWN, B_PAWN,   B_PAWN,   B_PAWN,  B_PAWN, B_PAWN,   B_PAWN,   B_PAWN,
        EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,    EMPTY,
        EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,    EMPTY,
        EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,    EMPTY,
        EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,    EMPTY,
        W_PAWN, W_PAWN,   W_PAWN,   W_PAWN,  W_PAWN, W_PAWN,   W_PAWN,   W_PAWN,
        W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK,
    }};
}

void Board_render(Board *board, Textures textures, Windowing windowing) {
    int width, height;
    SDL_GetWindowSize(windowing.window, &width, &height);

    int scale = min(width / BOARD_PIXELS_LENGTH,
                    (height - BOARD_VERTICAL_MARGIN) / BOARD_PIXELS_LENGTH);

    int dx = (width - scale * BOARD_PIXELS_LENGTH) / 2;
    int dy = (height - scale * BOARD_PIXELS_LENGTH) / 2;

    SDL_Rect rect = {dx, dy, scale * BOARD_PIXELS_LENGTH,
                     scale * BOARD_PIXELS_LENGTH};
    SDL_RenderCopy(windowing.renderer, textures.board.tex, NULL, &rect);

    for (int i = 0; i < 64; ++i) {
        if (board->pieces[i].type == EMPTY)
            continue;

        int cx = i % 8;
        int cy = i / 8;

        Piece_render(board->pieces[i], textures, windowing, cx, cy);
    }
}
