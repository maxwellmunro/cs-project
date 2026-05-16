#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "game.h"
#include <SDL2/SDL_events.h>

void handle_event(SDL_Event event, Game *game);
void handle_key_event(SDL_KeyCode key, bool pressed, Game *game);
void handle_mouse_event(int button, bool pressed, int x, int y, Game *game);

void handle_board_piece_move(int button, bool pressed, int x, int y, Game *game);
void handle_promoting_buttons(int button, bool pressed, int x, int y, Game *game);

PieceType get_type_from_button_index(int idx, bool white);

#endif
