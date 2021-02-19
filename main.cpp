#include <simplecpp>
#include <string>
#include "lasso.h"
#include "game.h"
#include "display.h"

using namespace simplecpp;

main_program {
    initCanvas("Lasso - Instructions", WINDOW_X, WINDOW_Y * 1.2);
    display::show_instructions();
    for (;;) {
        XEvent e;
        bool pendingEv = checkEvent(e);
        if (pendingEv) {
            char c = charFromEvent(e);
            if (c == 'n') {
                closeCanvas();
                break;
            } else if (c == 'q') {
                exit(0);
            }
        }
    }

    int game_mode;
    initCanvas("Lasso - Choose Mode", WINDOW_X, WINDOW_Y);
    display::show_modes();
    for (;;) {
        XEvent e;
        bool pendingEv = checkEvent(e);
        if (pendingEv) {
            char c = charFromEvent(e);
            if (c == 'q') {
                exit(0);
            } else if (c >= '1' && c <= '4') {
                game_mode = c - '0';
                closeCanvas();
                break;
            }
        }
    }

    initCanvas("Lasso", WINDOW_X, WINDOW_Y);

    // Set background
    Rectangle bg(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X * 1.2, WINDOW_Y * 1.2);
    bg.setColor(COLOR(CANVAS_BG_COLOR));
    bg.setFill(true);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(LIGHT_BROWN));
    Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
    b2.setColor(COLOR(LIGHT_BROWN));

    Game mygame(game_mode);
    mygame.loop();

    wait(3);
} // End main_program
