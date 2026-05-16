#include "../include/game.h"
#include "../include/board.h"
#include "../include/constants.h"
#include "../include/event_handler.h"
#include "../include/math.h"
#include <SDL2/SDL_stdinc.h>

int Game_init(Game *game) {
    Windowing windowing;
    if (Windowing_init(&windowing)) {
        return -1;
    }

    Textures textures;
    if (Textures_init(&textures, windowing.renderer)) {
        return -2;
    }

    game->windowing = windowing;
    game->textures = textures;
    game->board = Board_init();
    game->running = false;

    game->selected_x = BOARD_UNSELECTED_X_SENTINEL;

    game->promoting = false;

    return 0;
}

void Game_destroy(Game game) { Windowing_destroy(game.windowing); }

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

    int width, height;
    SDL_GetWindowSize(game.windowing.window, &width, &height);

    int scale = min(width / (BOARD_PIXELS_LENGTH + 2 * BOARD_HORIZONTAL_MARGIN),
                    height / (BOARD_PIXELS_LENGTH + 2 * BOARD_VERTICAL_MARGIN));

    Board_render(&game.board, game.textures, game.windowing, scale);

    if (game.promoting) {
        int total_width =
            4 * PROMOTION_BUTTON_WIDTH + 3 * PROMOTION_BUTTON_SPACING;

        int dx = (width - scale * BOARD_PIXELS_LENGTH) / 2;
        int dy = (height - scale * BOARD_PIXELS_LENGTH) / 2;

        int x = dx + (BOARD_PIXELS_LENGTH - total_width) * scale / 2;

        for (int i = 0; i < 4; ++i) {
            Texture buttons = game.textures.promotion_buttons;
            SDL_Rect dst = {
                x + i * scale *
                        (PROMOTION_BUTTON_WIDTH + PROMOTION_BUTTON_SPACING),
                dy - scale * (PROMOTION_BUTTON_SPACING + buttons.h),
                PROMOTION_BUTTON_WIDTH * scale, buttons.h * scale};

            SDL_Rect src = {(i + (game.board.white_to_move ? 4 : 0)) *
                                PROMOTION_BUTTON_WIDTH,
                            0, PROMOTION_BUTTON_WIDTH, buttons.h};

            SDL_RenderCopy(renderer, buttons.tex, &src, &dst);
        }
    }

    SDL_RenderPresent(renderer);
}
