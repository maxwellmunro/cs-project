#include "../include/windowing.h"

int main(void) {
    Windowing windowing = Windowing_init();
    Windowing_destroy(&windowing);

    return 0;
}
