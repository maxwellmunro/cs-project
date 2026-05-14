#include "../include/game.h"
#include "../include/event_handler.h"
#include <SDL2/SDL_stdinc.h>

int Game_init(Game *game) {
    Windowing windowing;
    if (Windowing_init(&windowing)) {
        return -1;
    }

    game->windowing = windowing;
    game->running = false;

    return 0;
}

void Game_destroy(Game game) {
    Windowing_destroy(game.windowing);
}

void Game_run(Game game) {
    game.running = true;

    Uint64 last_tick = SDL_GetTicks64();

    while (game.running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handle_event(event, &game);
        }

        Uint64 now = SDL_GetTicks64();
        float dt = (now - last_tick) / 1000.0;
        last_tick = now;

        Game_tick(game, dt);
        Game_render(game);
    }
}

void Game_tick(Game game, float dt) {}

void Game_render(Game game) {
    SDL_Renderer *renderer = game.windowing.renderer;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}
