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
    handle_board_piece_move(button, pressed, x, y, game);
}

void handle_board_piece_move(int button, bool pressed, int x, int y,
                             Game *game) {
    SDL_Point ml = {x, y};
    int width, height;
    SDL_GetWindowSize(game->windowing.window, &width, &height);

    int scale = min(width / BOARD_PIXELS_LENGTH,
                    (height - BOARD_VERTICAL_MARGIN) / BOARD_PIXELS_LENGTH);

    int dx = (width - scale * BOARD_PIXELS_LENGTH) / 2;
    int dy = (height - scale * BOARD_PIXELS_LENGTH) / 2;

    if (pressed) {
        game->selected_x = BOARD_UNSELECTED_X_SENTINEL;
    } else if (game->selected_x == BOARD_UNSELECTED_X_SENTINEL) {
        return;
    }

    for (int cx = 0; cx < 8; ++cx) {
        for (int cy = 0; cy < 8; ++cy) {
            int x = dx + cx * BOARD_CELL_LENGTH * scale +
                    (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH) * (scale / 2);
            int y = dy + cy * BOARD_CELL_LENGTH * scale +
                    (BOARD_CELL_LENGTH - PIECE_TEXTURE_WIDTH -
                     PIECE_TEXTURE_HEIGHT) *
                        (scale / 2);

            SDL_Rect dst = {x, y, PIECE_TEXTURE_WIDTH * scale,
                            PIECE_TEXTURE_HEIGHT * scale};

            if (SDL_PointInRect(&ml, &dst)) {
                if (pressed) {
                    game->selected_x = cx;
                    game->selected_y = cy;
                } else {
                    Board_move_piece(&game->board, game->selected_x,
                                     game->selected_y, cx, cy);
                    game->selected_x = BOARD_UNSELECTED_X_SENTINEL;
                }

                return;
            }
        }
    }
}
