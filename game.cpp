//
// Created by Jujhaar Singh on 20/02/21.
//

#include "game.h"

void Game::loop() {
    for (;;) {
        // learnt from: https://www.cse.iitb.ac.in/~ranade/simplecpp/raagmalaa/car.cpp
        // stops rendering after each change
        beginFrame();

        if ((runTime > 0) && (currTime > runTime)) {
            break;
        }

        check_command();

        nextStep();

        sprintf(coinScoreStr, "Score: %d", lasso->getNumCoins());
        coinScore->setMessage(coinScoreStr);

        stepCount++;
        currTime += stepTime;
        wait(stepTime);

        // renders changes all at once
        endFrame();
    } // End for(;;)
}

void Game::check_command() {
    XEvent e;
    bool pendingEv = checkEvent(e);
    if (pendingEv) {
        char c = charFromEvent(e);
        //                  msg[msg.length() - 1] = c;
        //                  charPressed.setMessage(msg);
        switch (c) {
            case 't':
                lasso->unpause();
                break;
            case 'y':
                lasso->yank(currTime);
                break;
            case 'l':
                lasso->loopit();
                for (int i = 0; i < active_coins; i++) {
                    lasso->check_for_coin(coins[i]);
                }
                wait(STEP_TIME * 5);
                break;
            case '[':
                if (lasso->isPaused()) {
                    lasso->addAngle(-RELEASE_ANGLE_STEP_DEG);
                }
                break;
            case ']':
                if (lasso->isPaused()) {
                    lasso->addAngle(+RELEASE_ANGLE_STEP_DEG);
                }
                break;
            case '-':
                if (lasso->isPaused()) {
                    lasso->addSpeed(-RELEASE_SPEED_STEP);
                }
                break;
            case '=':
                if (lasso->isPaused()) {
                    lasso->addSpeed(+RELEASE_SPEED_STEP);
                }
                break;
            case 'q':
                exit(0);
            default:
                break;
        }
    }
}

void Game::nextStep() {
    lasso->nextStep(stepTime, currTime);

    magnetic = lasso->get_magnetic();
    frenzy = lasso->get_frenzy();
    if (magnetic) {
        for (int i = 0; i < active_coins; i++) {
            if (!lasso->coin_present(coins[i]))
                coins[i]->attract(lasso, 0.02);
        }
    }

    if (frenzy && !already_frenzy) make_frenzy();
    if (!frenzy && already_frenzy) unmake_frenzy();

    for (int i = 0; i < active_coins; i++) {
        Coin *coin = coins[i];
        coin->nextStep(stepTime);
        if (coin->isPaused()) {
            if ((currTime - last_coin_jump_ends[i]) >= COIN_GAP) {
                coin->unpause();
            }
        }

        if (coin->getYPos() > PLAY_Y_START + PLAY_Y_HEIGHT || coin->getXPos() > PLAY_X_START + PLAY_X_WIDTH ||
            coin->getYPos() < PLAY_Y_START || coin->getXPos() < PLAY_X_START) {
            coin->resetCoin(magnetic, frenzy);
            last_coin_jump_ends[i] = currTime;
        }
    }
}

void Game::make_frenzy() {
    for (int i = normal_active_coins; i < MAX_COINS; i++) {
        coins[i]->show();
    }
    active_coins = MAX_COINS;
    already_frenzy = true;
}

void Game::unmake_frenzy() {
    for (int i = normal_active_coins; i < MAX_COINS; i++) {
        coins[i]->resetCoin(magnetic, true);
        coins[i]->hide();
    }
    active_coins = normal_active_coins;
    already_frenzy = false;
}