//
// Created by Jujhaar Singh on 20/02/21.
//

#ifndef LASSO_GAME_H
#define LASSO_GAME_H

#include "coin.h"
#include "lasso.h"
#include "constants.h"

class Game {
    Lasso *lasso;
    vector<Coin *> coins;

    int active_coins;
    const int normal_active_coins = 4;

    int stepCount;
    float stepTime;
    float runTime; // sec; -ve means infinite
    float currTime;

    // Draw lasso at start position
    double release_speed;        // m/s
    double release_angle_deg;// degrees
    double lasso_ax;
    double lasso_ay;
    bool paused;
    bool rtheta;

    double coin_speed;
    double coin_ax;
    double coin_ay;

    double last_coin_jump_ends[MAX_COINS];

    int game_mode;
    bool lives_matter;

    bool magnetic;
    bool frenzy;
    bool already_frenzy;

    const float gameTime = 30;

    char coinScoreStr[256];
    Text *coinScore;

    char game_clock_str[256];
    Text *game_clock;

    char lives_str[256];
    Text *lives;

    void check_command();

    void make_frenzy();

    void unmake_frenzy();

    void nextStep();

    static void showGameOver();

    void getGameMode();

    static void initGameWindow();

public:
    explicit Game() {
        getGameMode();
        initCanvas("Lasso", WINDOW_X, WINDOW_Y);
        initGameWindow();

        stepCount = 0;
        stepTime = STEP_TIME;
        runTime = -1; // sec; -ve means infinite
        currTime = 0;

        // Draw lasso at start position
        release_speed = INIT_RELEASE_SPEED;         // m/s
        release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
        lasso_ax = 0;
        lasso_ay = LASSO_G;
        paused = true;
        rtheta = true;
        lasso = new Lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

        magnetic = false;
        frenzy = false;
        already_frenzy = false;

        active_coins = 4;

        paused = true;
        rtheta = true;
        coin_speed = COIN_SPEED;
        coin_ax = 0;
        coin_ay = COIN_G;

        beginFrame();
        for (int i = 0; i < MAX_COINS; i++) {
            coins.push_back(new Coin(coin_speed, COIN_ANGLE_DEG, coin_ax, coin_ay, paused, rtheta, game_mode));
        }
        for (int i = normal_active_coins; i < MAX_COINS; i++) {
            coins[i]->hide();
        }

        for (int i = 0; i < MAX_COINS; i++) {
            last_coin_jump_ends[i] = 0;
        }

        sprintf(coinScoreStr, "Score: %d", lasso->getNumCoins());
        coinScore = new Text(PLAY_X_START + 75, PLAY_Y_HEIGHT + 50, coinScoreStr);
        coinScore->setColor(COLOR(BROWN));

        sprintf(game_clock_str, "Time: %d / 30", (int) currTime);
        game_clock = new Text(PLAY_X_START + PLAY_X_WIDTH - 150, PLAY_Y_HEIGHT + 50, coinScoreStr);
        game_clock->setColor(COLOR(BROWN));

        if (lives_matter) {
            sprintf(lives_str, "Lives: %d / 3", lasso->get_lives());
            lives = new Text(PLAY_X_START + PLAY_X_WIDTH - 300, PLAY_Y_HEIGHT + 50, coinScoreStr);
            lives->setColor(COLOR(BROWN));
        }

        endFrame();
    }

    int loop();
};


#endif //LASSO_GAME_H
