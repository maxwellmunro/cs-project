#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "game.h"
#include <SDL2/SDL_events.h>

void handle_event(SDL_Event event, Game *game);
void handle_key_event(SDL_KeyCode key, bool pressed, Game *game);

#endif
