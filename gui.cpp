#include <simplecpp>
#include "constants.h"
#include "gui.h"

void GUI::show_instructions() {
    vector<string> commands;
    commands.emplace_back("+/= and -");
    commands.emplace_back("[ and ]");
    commands.emplace_back("t");
    commands.emplace_back("l");
    commands.emplace_back("y");
    commands.emplace_back("q");

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
    text.setMessage("press N to go to next screen and choose game mode");
    text.imprint();
};

void GUI::show_modes() {
    vector<string> modes;
    modes.emplace_back("Press 1: Arcade Mode");
    modes.emplace_back("Press 2: Magnet Mode");
    modes.emplace_back("Press 3: Bomb Mode");
    modes.emplace_back("Press 4: Rajni Mode");

    vector<string> rules;
    rules.emplace_back("Collect the most number of coins that you can");
    rules.emplace_back("Collect magnets to attract more coins");
    rules.emplace_back("Beware of the bombs as they provide a score reduction");
    rules.emplace_back(
            "Only a true braveheart should choose this mode, with both bombs and magnets, things can get dicey very fast ;)");

    Text text(WINDOW_X / 2.0, 50, "Lasso - Choose Mode");

    text.setColor(COLOR(BLACK));
    text.imprint();

    text.move(0, 50);

    text.setMessage("Choose one of the following modes");
    text.imprint();

    show_list_on_canvas(modes, rules, text);
};

void GUI::show_list_on_canvas(vector<string> headings, vector<string> content, Text &text) {
    for (int i = 0; i < headings.size(); i++) {
        text.move(0, 50);

        text.setMessage(headings[i]);
        text.imprint();

        text.move(0, 25);

        wrap_text(content[i], 60, 25, text);
    }
}

void GUI::wrap_text(string str, int maxlen, int linespace, Text &text) {
    if (str.length() > maxlen) {
        int ind = str.substr(0, maxlen).find_last_of(' ');

        text.setMessage(str.substr(0, ind));
        text.imprint();

        text.move(0, linespace);

        text.setMessage(str.substr(ind, str.size() - ind));
        text.imprint();
    } else {
        text.setMessage(str);
        text.imprint();
    }
}