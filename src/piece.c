#include "../include/piece.h"
#include "../include/constants.h"

Piece Piece_init(PieceType type) { return (Piece){type}; }

void Piece_render(Piece piece, Textures textures, Windowing windowing, int cx, int cy, int scale) {
    int width, height;
    SDL_GetWindowSize(windowing.window, &width, &height);

    int dx = (width - scale * BOARD_PIXELS_LENGTH) / 2;
    int dy = (height - scale * BOARD_PIXELS_LENGTH) / 2;

    int x = dx + cx * BOARD_CELL_LENGTH * scale + (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH) * (scale / 2);
    int y = dy + cy * BOARD_CELL_LENGTH * scale + (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH - PIECE_TEXTURE_HEIGHT) * (scale / 2);

    SDL_Rect dst = { x, y, PIECE_TEXTURE_WIDTH * scale, PIECE_TEXTURE_HEIGHT * scale };
    SDL_Rect src = { piece.type * PIECE_TEXTURE_WIDTH, 0, PIECE_TEXTURE_WIDTH, PIECE_TEXTURE_HEIGHT };

    SDL_RenderCopy(windowing.renderer, textures.pieces.tex, &src, &dst);
}

bool Piece_is_white(Piece piece) {
    switch (piece.type) {
    case EMPTY:
    case B_PAWN:
    case B_ROOK:
    case B_BISHOP:
    case B_KNIGHT:
    case B_QUEEN:
    case B_KING:
        return false;
    case W_PAWN:
    case W_ROOK:
    case W_BISHOP:
    case W_KNIGHT:
    case W_QUEEN:
    case W_KING:
        return true;
    }
}
