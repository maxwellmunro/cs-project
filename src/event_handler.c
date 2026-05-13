#include "../include/event_handler.h"
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
    }
}

void handle_key_event(SDL_KeyCode key, bool pressed, Game *game) {
    printf("Key %s %s\n", SDL_GetKeyName(key), pressed ? "pressed" : "released");
}
