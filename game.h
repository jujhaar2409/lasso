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

    bool magnetic;
    bool frenzy;
    bool already_frenzy;

    char coinScoreStr[256];
    Text *coinScore;

    void check_command();

    void make_frenzy();

    void unmake_frenzy();

    void nextStep();

public:
    explicit Game(int mode) {
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
        game_mode = mode;
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
        endFrame();

        sprintf(coinScoreStr, "Score: %d", lasso->getNumCoins());
        coinScore = new Text(PLAY_X_START + 75, PLAY_Y_HEIGHT + 50, coinScoreStr);
        coinScore->setColor(COLOR(BROWN));
    }

    void loop();
};


#endif //LASSO_GAME_H