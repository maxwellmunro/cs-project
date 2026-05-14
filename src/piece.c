#include "../include/piece.h"
#include "../include/constants.h"
#include "../include/math.h"

Piece Piece_init(PieceType type) { return (Piece){type}; }

void Piece_render(Piece piece, Textures textures, Windowing windowing, int cx, int cy) {
    int width, height;
    SDL_GetWindowSize(windowing.window, &width, &height);

    int scale = min(width / BOARD_PIXELS_LENGTH, (height - BOARD_VERTICAL_MARGIN) / BOARD_PIXELS_LENGTH);

    int dx = (width - scale * BOARD_PIXELS_LENGTH) / 2;
    int dy = (height - scale * BOARD_PIXELS_LENGTH) / 2;

    int x = dx + cx * BOARD_CELL_LENGTH * scale + (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH) * (scale / 2);
    int y = dy + cy * BOARD_CELL_LENGTH * scale + (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH - PIECE_TEXTURE_HEIGHT) * (scale / 2);

    SDL_Rect dst = { x, y, PIECE_TEXTURE_WIDTH * scale, PIECE_TEXTURE_HEIGHT * scale };
    SDL_Rect src = { piece.type * PIECE_TEXTURE_WIDTH, 0, PIECE_TEXTURE_WIDTH, PIECE_TEXTURE_HEIGHT };

    SDL_RenderCopy(windowing.renderer, textures.pieces.tex, &src, &dst);
}
