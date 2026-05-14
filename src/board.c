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

Piece *Board_get_piece(Board *board, int x, int y) {
    if (x < 0 || y < 0 || x > 7 || y > 7)
        return NULL;

    return &board->pieces[y * 8 + x];
}

void Board_set_piece(Board *board, Piece piece, int x, int y) {
    board->pieces[y * 8 + x] = piece;
}

int Board_move_piece(Board *board, int sx, int sy, int dx, int dy) {
    Board_set_piece(board, *Board_get_piece(board, sx, sy), dx, dy);
    Board_set_piece(board, Piece_init(EMPTY), sx, sy);

    return 0; // TODO currently just moves pieces need to implement move validation
}
