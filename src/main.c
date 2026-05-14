#include "../include/game.h"

int main(void) {
    Game game;

    if (Game_init(&game)) {
        return -1;
    }

    Game_run(game);
    Game_destroy(game);

    return 0;
}
