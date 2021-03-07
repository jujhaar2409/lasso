#include <simplecpp>
#include "constants.h"
#include "display.h"

char display::show_instructions() {
    beginFrame();
    vector<string> commands;
    commands.emplace_back("'+/=' and '-'");
    commands.emplace_back("'[' and ']'");
    commands.emplace_back("'t'");
    commands.emplace_back("'l'");
    commands.emplace_back("'y'");
    commands.emplace_back("'q'");

    vector<string> instructions;
    instructions.emplace_back("Increase and decrease the speed of the lasso respectively");
    instructions.emplace_back("Change the angle of the lasso");
    instructions.emplace_back("Throws the lasso");
    instructions.emplace_back(
            "'loops' the lasso, which means that the coin can be caught at this moment, if it is within range");
    instructions.emplace_back("'yanks' the lasso, brings lasso back to starting position");
    instructions.emplace_back("press q any time to quit game");

    Text text(WINDOW_X / 2.0, 50, "Lasso - Instructions");

    text.setColor(COLOR(BLACK));
    text.imprint();

    text.move(0, 50);

    text.setMessage("The following are the controls of the game:");
    text.imprint();

    show_list_on_canvas(commands, instructions, text);

    text.move(0, 50);
    text.setMessage("press N to go to next screen and see coin types!");
    text.imprint();

    endFrame();

    char c;
    for (;;) {
        XEvent e;
        bool pendingEv = checkEvent(e);
        if (pendingEv) {
            c = charFromEvent(e);
            if (c == 'n' || c == 'q') {
                return c;
            }
        }
    }
};

char display::show_modes() {
    beginFrame();
    vector<string> modes;
    modes.emplace_back("Press 1: Arcade Mode");
    modes.emplace_back("Press 2: Magnet Mode");
    modes.emplace_back("Press 3: Bomb Mode");
    modes.emplace_back("Press 4: Mega Mode");

    vector<string> rules;
    rules.emplace_back(
            "Collect the most number of coins that you can, remember to collect frenzy coins to win big! types of coins: regular, bonus and frenzy");
    rules.emplace_back("Collect magnets to attract more coins! types of coins: regular, bonus, magnet");
    rules.emplace_back(
            "Beware of the bombs as they provide a score reduction and take away a life! types of coins: regular, bonus, bomb");
    rules.emplace_back(
            "Only a true braveheart should choose this mode, with both bombs and magnets, things can get dicey very fast! types of coins: ALL!!");

    Text text(WINDOW_X / 2.0, 50, "Lasso - Choose Mode");

    text.setColor(COLOR(BLACK));
    text.imprint();

    text.move(0, 50);

    text.setMessage("Choose one of the following modes");
    text.imprint();

    show_list_on_canvas(modes, rules, text);
    endFrame();

    char c;
    for (;;) {
        XEvent e;
        bool pendingEv = checkEvent(e);
        if (pendingEv) {
            c = charFromEvent(e);
            if (c == 'q' || (c >= '1' && c <= '4')) {
                return c;
            }
        }
    }
};


char display::show_coin_types() {
    beginFrame();
    vector<string> types;
    types.emplace_back("Bonus: +2");
    types.emplace_back("Regular: +1");
    types.emplace_back("Magnet: +0");
    types.emplace_back("Bomb: -1");
    types.emplace_back("Frenzy: +0");

    vector<string> description;
    description.emplace_back("Gives a bonus point!");
    description.emplace_back("Regular old coin");
    description.emplace_back("Magnetizes your lasso for ~5s");
    description.emplace_back("Gives a negative point and takes away a life too, stay away!");
    description.emplace_back("More number of coins to catch for ~10s!");

    Text text(WINDOW_X / 2.0, 50, "Lasso - Coin Types");

    text.setColor(COLOR(BLACK));
    text.imprint();

    text.move(0, 50);

    text.setMessage("The following are the coin types in the game:");
    text.imprint();

    text.setColor(COLOR(BONUS_COIN_COLOR));
    print_pair(types[0], description[0], text);

    text.setColor(COLOR(REGULAR_COIN_COLOR));
    print_pair(types[1], description[1], text);

    text.setColor(COLOR(MAGNET_COIN_COLOR));
    print_pair(types[2], description[2], text);

    text.setColor(COLOR(BOMB_COIN_COLOR));
    print_pair(types[3], description[3], text);

    text.setColor(COLOR(FRENZY_COIN_COLOR));
    print_pair(types[4], description[4], text);

    text.setColor(COLOR(BLACK));
    text.move(0, 50);
    text.setMessage("press N to go to next screen and choose game mode!");
    text.imprint();

    endFrame();

    for (;;) {
        XEvent e;
        bool pendingEv = checkEvent(e);
        if (pendingEv) {
            char c = charFromEvent(e);
            if (c == 'n' || c == 'q') {
                return c;
            }
        }
    }
};

void display::show_list_on_canvas(vector<string> headings, vector<string> content, Text &text) {
    for (int i = 0; i < headings.size(); i++) {
        print_pair(headings[i], content[i], text);
    }
}

void display::print_pair(string &heading, string &content, Text &text) {
    text.move(0, 50);

    text.setMessage(heading);
    text.imprint();

    text.move(0, 25);

    wrap_text(content, 60, 25, text);
}

void display::wrap_text(string &str, int maxlen, int linespace, Text &text) {
    if (str.length() > maxlen) {
        int ind = str.substr(0, maxlen).find_last_of(' ');

        text.setMessage(str.substr(0, ind));
        text.imprint();

        text.move(0, linespace);

//        text.setMessage(str.substr(ind, str.size() - ind));
//        text.imprint();
        string substr = str.substr(ind, str.size() - ind);
        wrap_text(substr, maxlen, linespace, text);
    } else {
        text.setMessage(str);
        text.imprint();
    }
}

char display::show_score(int score) {

    Text text(WINDOW_X / 2.0, 50, "Score");

    text.setColor(COLOR(BLACK));
    text.imprint();

    text.move(0, 200);

    char score_display[256];
    sprintf(score_display, "Your final score is: %d", score);
    text.setMessage(score_display);
    text.imprint();

    text.move(0, 200);
    text.setMessage("press N to play again! or press Q to quit");
    text.imprint();

    text.move(0, 100);
    text.setMessage("press I to see coin types and instructions again");
    text.imprint();

    for (;;) {
        XEvent e;
        bool pendingEv = checkEvent(e);
        if (pendingEv) {
            char c = charFromEvent(e);
            if (c == 'n' || c == 'q' || c == 'i') {
                return c;
            }
        }
    }
}

void display::show_info() {
    initCanvas("Lasso - Instructions", WINDOW_X, WINDOW_Y * 1.2);
    char show_instructions_cmd = display::show_instructions();
    if (show_instructions_cmd == 'q') exit(0);
    closeCanvas();

    initCanvas("Lasso - Coin Types", WINDOW_X, WINDOW_Y * 1.2);
    char coin_type_command = display::show_coin_types();
    if (coin_type_command == 'q') exit(0);
    closeCanvas();
}
