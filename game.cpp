//
// Created by Jujhaar Singh on 20/02/21.
//

#include "game.h"
#include "display.h"

int Game::loop() {
    for (;;) {
        // learnt from: https://www.cse.iitb.ac.in/~ranade/simplecpp/raagmalaa/car.cpp
        // stops rendering after each change
        beginFrame();
        auto t_start = std::chrono::high_resolution_clock::now();

        if ((runTime > 0) && (currTime > runTime)) {
            break;
        }

        check_command();

        nextStep();

        sprintf(coinScoreStr, "Score: %d", lasso->getNumCoins());
        coinScore->setMessage(coinScoreStr);
        sprintf(game_clock_str, "Time: %ds / %ds", int(currTime), int(gameTime));
        game_clock->setMessage(game_clock_str);

        // renders changes all at once
        endFrame();

        stepCount++;
        wait(stepTime);
        auto t_end = std::chrono::high_resolution_clock::now();
        auto time_passed = std::chrono::duration<double, std::milli>(t_end - t_start).count();
        currTime += float(time_passed) / 1000;

        if (currTime > (float(gameTime) + float(time_passed) / 1000))break;
    } // End for(;;)

    showGameOver();

    closeCanvas();

    return lasso->getNumCoins();
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


void Game::showGameOver() {
    Text text(WINDOW_X / 2.0, WINDOW_Y / 2.0, "GAME OVER");
    wait(3);
}

void Game::getGameMode() {
    initCanvas("Lasso - Choose Mode", WINDOW_X, WINDOW_Y * 1.2);
    char res = display::show_modes();
    closeCanvas();
    if (res == 'q') exit(0);
    else if (res <= '4' && res >= '1') game_mode = res - '0';
}

void Game::initGameWindow() {
    // Set background
    beginFrame();
    Rectangle bg(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X * 1.2, WINDOW_Y * 1.2);
    bg.setColor(COLOR(CANVAS_BG_COLOR));
    bg.setFill(true);
    bg.imprint();

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(LIGHT_BROWN));
    b1.imprint();
    Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
    b2.setColor(COLOR(LIGHT_BROWN));
    b2.imprint();
    endFrame();
}
