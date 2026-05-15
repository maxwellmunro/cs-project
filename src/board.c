#include "../include/board.h"
#include "../include/constants.h"
#include "../include/math.h"

Board Board_init() {
    return (Board){
        .pieces =
            {
                B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT,
                B_ROOK, B_PAWN,   B_PAWN,   B_PAWN,  B_PAWN, B_PAWN,   B_PAWN,
                B_PAWN, B_PAWN,   EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,
                EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,
                EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,
                EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    EMPTY,
                EMPTY,  EMPTY,    EMPTY,    EMPTY,   EMPTY,  EMPTY,    W_PAWN,
                W_PAWN, W_PAWN,   W_PAWN,   W_PAWN,  W_PAWN, W_PAWN,   W_PAWN,
                W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT,
                W_ROOK,
            },
        .last_two_square_advance_x = -1,
        .white_to_move = true,
        .white_king_moved = false,
        .black_king_moved = false,
    };
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
    if (!Board_is_valid_move(board, sx, sy, dx, dy))
        return -1;

    if (Piece_is_white(*Board_get_piece(board, sx, sy)) !=
        board->white_to_move) {
        return -2;
    }

    printf("Moving %i, %i to %i, %i\n", sx, sy, dx, dy);

    board->white_to_move = !board->white_to_move;

    board->last_two_square_advance_x = -1;

    if ((sy == 1 || sy == 6) &&
            Board_get_piece(board, sx, sy)->type == W_PAWN ||
        Board_get_piece(board, sx, sy)->type == B_PAWN) {
        board->last_two_square_advance_y = sy;
        board->last_two_square_advance_x = sx;
    }

    if ((Board_get_piece(board, sx, sy)->type == W_PAWN ||
         Board_get_piece(board, sx, sy)->type == B_PAWN) &&
        Board_get_piece(board, dx, dy)->type == EMPTY && sx != dx) {
        Board_set_piece(board, Piece_init(EMPTY), dx, sy);
    }

    //    if (Board_get_piece(board, sx, sy)->type == B_KING)
    //        board->black_king_moved = true;
    //
    //    if (Board_get_piece(board, sx, sy)->type == W_KING)
    //        board->white_king_moved = true;


    Board_set_piece(board, *Board_get_piece(board, sx, sy), dx, dy);
    Board_set_piece(board, Piece_init(EMPTY), sx, sy);

    return 0;
}

bool Board_is_valid_move(Board *board, int sx, int sy, int dx, int dy) {
    if (sx == dx && sy == dy)
        return false;

    Piece *src = Board_get_piece(board, sx, sy);
    Piece *dst = Board_get_piece(board, dx, dy);

    bool s_white = Piece_is_white(*src);
    bool d_white = Piece_is_white(*dst);

    if (s_white == d_white && dst->type != EMPTY)
        return false;

    switch (src->type) {
    case EMPTY:
        return false;
    case B_PAWN:
        return (sx == dx && sy == 1 && dy == 2) ||
               (sx == dx && sy == 1 && dy == 3 &&
                Board_get_piece(board, sx, 2)->type == EMPTY) ||
               (abs(sx - dx) == 1 && dy == sy + 1 &&
                Board_get_piece(board, dx, dy)->type != EMPTY) ||
               (abs(sx - dx) == 1 && dx == board->last_two_square_advance_x &&
                sy == 4 && dy == 5 && board->last_two_square_advance_y == 6) ||
               (sx == dx && dy == sy + 1 && dst->type == EMPTY);
    case W_ROOK:
    case B_ROOK:
        if (sx != dx && sy != dy)
            return false;

        if (sy == dy) {
            for (int x = sx; x != dx; x += (dx > sx ? 1 : -1)) {
                if (x == sx)
                    continue;

                if (Board_get_piece(board, x, sy)->type != EMPTY)
                    return false;
            }
        } else {
            for (int y = sy; y != dy; y += (dy > sy ? 1 : -1)) {
                if (y == sy)
                    continue;

                if (Board_get_piece(board, sx, y)->type != EMPTY)
                    return false;
            }
        }

        return true;
    case W_BISHOP:
    case B_BISHOP:
        if (abs(sx - dx) != abs(sy - dy))
            return false;

        for (int x = sx, y = sy; x != dx && y != dy;
             x += (dx > sx ? 1 : -1), y += (dy > sy ? 1 : -1)) {
            if (x == sx)
                continue;

            if (Board_get_piece(board, x, y)->type != EMPTY)
                return false;
        }

        return true;
    case W_KNIGHT:
    case B_KNIGHT:
        return abs(abs(dx - sx) - (abs(dy - sy))) == 1 && dx != sx && dy != sy;
    case W_QUEEN:
    case B_QUEEN:
        if (sy == dy) {
            for (int x = sx; x != dx; x += (dx > sx ? 1 : -1)) {
                if (x == sx)
                    continue;

                if (Board_get_piece(board, x, sy)->type != EMPTY)
                    return false;
            }

            return true;
        } else if (sx == dx) {
            for (int y = sy; y != dy; y += (dy > sy ? 1 : -1)) {
                if (y == sy)
                    continue;

                if (Board_get_piece(board, sx, y)->type != EMPTY)
                    return false;
            }

            return true;
        }

        if (abs(sx - dx) != abs(sy - dy))
            return false;

        for (int x = sx, y = sy; x != dx && y != dy;
             x += (dx > sx ? 1 : -1), y += (dy > sy ? 1 : -1)) {
            if (x == sx)
                continue;

            if (Board_get_piece(board, x, y)->type != EMPTY)
                return false;
        }

        return true;
    case W_KING:
    case B_KING:
        if (!board->white_to_move && !board->black_king_moved) {
            if (sy == 0 && sx == 4) {
                if (dx == 1) {
                    if (Board_get_piece(board, 0, 0)->type == B_ROOK &&
                        Board_get_piece(board, 1, 0)->type == EMPTY &&
                        Board_get_piece(board, 2, 0)->type == EMPTY &&
                        Board_get_piece(board, 3, 0)->type == EMPTY) {
                        Board_set_piece(board, *Board_get_piece(board, 0, 0), 2, 0);
                        Board_set_piece(board, Piece_init(EMPTY), 0, 0);
                        return true;
                    }
                } else if (dx == 6) {
                    if (Board_get_piece(board, 5, 0)->type == EMPTY &&
                        Board_get_piece(board, 6, 0)->type == EMPTY &&
                        Board_get_piece(board, 7, 0)->type == B_ROOK) {
                        Board_set_piece(board, *Board_get_piece(board, 7, 0), 5, 0);
                        Board_set_piece(board, Piece_init(EMPTY), 7, 0);
                        return true;
                    }
                }
            }
        }
        if (board->white_to_move && !board->white_king_moved) {
            if (sy == 7 && sx == 4) {
                if (dx == 1) {
                    if (Board_get_piece(board, 0, 7)->type == W_ROOK &&
                        Board_get_piece(board, 1, 7)->type == EMPTY &&
                        Board_get_piece(board, 2, 7)->type == EMPTY &&
                        Board_get_piece(board, 3, 7)->type == EMPTY) {
                        Board_set_piece(board, *Board_get_piece(board, 0, 7), 2, 7);
                        Board_set_piece(board, Piece_init(EMPTY), 0, 7);
                        return true;
                    }
                } else if (dx == 6) {
                    if (Board_get_piece(board, 5, 7)->type == EMPTY &&
                        Board_get_piece(board, 6, 7)->type == EMPTY &&
                        Board_get_piece(board, 7, 7)->type == W_ROOK) {
                        Board_set_piece(board, *Board_get_piece(board, 7, 7), 5, 7);
                        Board_set_piece(board, Piece_init(EMPTY), 7, 7);
                        printf("Returning true\n");
                        return true;
                    }

                    printf("Did not return true\n");
                }
            }
        }
        return abs(sx - dx) <= 1 && abs(sy - dy) <= 1;
    case W_PAWN:
        return (sx == dx && sy == 6 && dy == 5) ||
               (sx == dx && sy == 6 && dy == 4 &&
                Board_get_piece(board, sx, 5)->type == EMPTY) ||
               (abs(sx - dx) == 1 && dy == sy - 1 &&
                Board_get_piece(board, dx, dy)->type != EMPTY) ||
               (abs(sx - dx) == 1 && dx == board->last_two_square_advance_x &&
                sy == 3 && dy == 2 && board->last_two_square_advance_y == 1) ||
               (sx == dx && dy == sy - 1 && dst->type == EMPTY);
    }
}
