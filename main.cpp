#include <simplecpp>
#include <string>
#include "lasso.h"
#include "game.h"
#include "display.h"

using namespace simplecpp;

main_program {
    display::show_info();

    for (;;) {
        Game mygame;
        int score = mygame.loop();

        initCanvas("Lasso - Score", WINDOW_X, WINDOW_Y * 1.2);
        char cmd = display::show_score(score);
        if (cmd == 'q') exit(0);
        if (cmd == 'n') closeCanvas();
        if (cmd == 'i') {
            closeCanvas();
            display::show_info();
        }
    }
} // End main_program
