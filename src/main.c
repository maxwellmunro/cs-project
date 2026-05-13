#include "../include/game.h"

int main(void) {
    Game game = Game_init();

    Game_run(game);
    Game_destroy(game);

    return 0;
}
