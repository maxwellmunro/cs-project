#include "../include/event_handler.h"
#include "../include/constants.h"
#include "../include/math.h"
#include <stdio.h>

void handle_event(SDL_Event event, Game *game) {
    switch (event.type) {
    case SDL_QUIT:
        game->running = false;
        break;
    case SDL_KEYDOWN:
        handle_key_event(event.key.keysym.sym, true, game);
        break;
    case SDL_KEYUP:
        handle_key_event(event.key.keysym.sym, false, game);
        break;
    case SDL_MOUSEBUTTONDOWN:
        handle_mouse_event(event.button.button, true, event.button.x,
                           event.button.y, game);
        break;
    case SDL_MOUSEBUTTONUP:
        handle_mouse_event(event.button.button, false, event.button.x,
                           event.button.y, game);
        break;
    }
}

void handle_key_event(SDL_KeyCode key, bool pressed, Game *game) {
    printf("Key %s %s\n", SDL_GetKeyName(key),
           pressed ? "pressed" : "released");
}

void handle_mouse_event(int button, bool pressed, int x, int y, Game *game) {
    if (game->promoting)
        handle_promoting_buttons(button, pressed, x, y, game);
    else
        handle_board_piece_move(button, pressed, x, y, game);
}

void handle_board_piece_move(int button, bool pressed, int x, int y,
                             Game *game) {
    SDL_Point ml = {x, y};
    int width, height;
    SDL_GetWindowSize(game->windowing.window, &width, &height);

    int scale = min(width / (BOARD_PIXELS_LENGTH + 2 * BOARD_HORIZONTAL_MARGIN),
                    height / (BOARD_PIXELS_LENGTH + 2 * BOARD_VERTICAL_MARGIN));

    int dx = (width - scale * BOARD_PIXELS_LENGTH) / 2;
    int dy = (height - scale * BOARD_PIXELS_LENGTH) / 2;

    if (pressed) {
        game->selected_x = BOARD_UNSELECTED_X_SENTINEL;
    } else if (game->selected_x == BOARD_UNSELECTED_X_SENTINEL) {
        return;
    }

    for (int cx = 0; cx < 8; ++cx) {
        for (int cy = 0; cy < 8; ++cy) {
#if 0
            int x = dx + cx * BOARD_CELL_LENGTH * scale +
                    (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH) * (scale / 2);
            int y = dy + cy * BOARD_CELL_LENGTH * scale +
                    (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH -
                     PIECE_TEXTURE_HEIGHT) *
                        (scale / 2);
#endif

            int x = dx + cx * BOARD_CELL_LENGTH * scale;
            int y = dy + cy * BOARD_CELL_LENGTH * scale;

            SDL_Rect dst = {x, y, BOARD_CELL_LENGTH * scale,
                            BOARD_CELL_LENGTH * scale};

            if (SDL_PointInRect(&ml, &dst)) {
                if (pressed) {
                    game->selected_x = cx;
                    game->selected_y = cy;
                } else {
                    if (!Board_move_piece(&game->board, game->selected_x,
                                          game->selected_y, cx, cy)) {
                        game->promoting =
                            (cy == 0 || cy == 7) &&
                            (Board_get_piece(&game->board, cx, cy)->type ==
                                 B_PAWN ||
                             Board_get_piece(&game->board, cx, cy)->type ==
                                 W_PAWN);
                    }
                    game->selected_x = BOARD_UNSELECTED_X_SENTINEL;
                }

                return;
            }
        }
    }
}

PieceType get_type_from_button_index(int idx, bool white) {
    switch (idx) {
    case 0:
        return white ? W_ROOK : B_ROOK;
    case 1:
        return white ? W_BISHOP : B_BISHOP;
    case 2:
        return white ? W_KNIGHT : B_KNIGHT;
    case 3:
        return white ? W_QUEEN : B_QUEEN;
    }

    return EMPTY;
}

void handle_promoting_buttons(int button, bool pressed, int x, int y,
                              Game *game) {
    SDL_Point ml = {x, y};
    int width, height;
    SDL_GetWindowSize(game->windowing.window, &width, &height);

    int scale = min(width / (BOARD_PIXELS_LENGTH + 2 * BOARD_HORIZONTAL_MARGIN),
                    height / (BOARD_PIXELS_LENGTH + 2 * BOARD_VERTICAL_MARGIN));

    int dx = (width - scale * BOARD_PIXELS_LENGTH) / 2;
    int dy = (height - scale * BOARD_PIXELS_LENGTH) / 2;

    int total_width = 4 * PROMOTION_BUTTON_WIDTH + 3 * PROMOTION_BUTTON_SPACING;

    int button_x = dx + (BOARD_PIXELS_LENGTH - total_width) * scale / 2;

    for (int i = 0; i < 4; ++i) {
        Texture buttons = game->textures.promotion_buttons;
        
        SDL_Rect rect = {
            button_x +
                i * scale * (PROMOTION_BUTTON_WIDTH + PROMOTION_BUTTON_SPACING),
            dy - scale * (PROMOTION_BUTTON_SPACING + buttons.h),
            PROMOTION_BUTTON_WIDTH * scale, buttons.h * scale};

        if (SDL_PointInRect(&ml, &rect)) {
            Board_set_piece(&game->board,
                            Piece_init(get_type_from_button_index(
                                i, game->board.white_to_move)),
                            game->board.promoting_x, game->board.promoting_y);

            game->board.white_to_move ^= 1;
            game->promoting = false;

            return;
        }
    }
}
