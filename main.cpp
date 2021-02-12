#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "gui.h"
#include <vector>

using namespace simplecpp;

main_program
{
      initCanvas("Lasso - Instructions", WINDOW_X, WINDOW_Y);
      show_instructions();
      for (;;)
      {
            XEvent e;
            bool pendingEv = checkEvent(e);
            if (pendingEv)
            {
                  char c = charFromEvent(e);
                  if (c == 'n')
                  {
                        closeCanvas();
                        break;
                  }
                  else if (c == 'q')
                  {
                        exit(0);
                  }
            }
      }

      initCanvas("Lasso - Choose mode", WINDOW_X, WINDOW_Y);
      show_modes();
      for (;;)
      {
            XEvent e;
            bool pendingEv = checkEvent(e);
            if (pendingEv)
            {
                  char c = charFromEvent(e);
                  if (c == 'n')
                  {
                        closeCanvas();
                        break;
                  }
                  else if (c == 'q')
                  {
                        exit(0);
                  }
            }
      }

      initCanvas("Lasso", WINDOW_X, WINDOW_Y);
      int stepCount = 0;
      float stepTime = STEP_TIME;
      float runTime = -1; // sec; -ve means infinite
      float currTime = 0;

      // Draw lasso at start position
      double release_speed = INIT_RELEASE_SPEED;         // m/s
      double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
      double lasso_ax = 0;
      double lasso_ay = LASSO_G;
      bool paused = true;
      bool rtheta = true;
      Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

      Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
      b1.setColor(COLOR("blue"));
      Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
      b2.setColor(COLOR("blue"));

      string msg("Cmd: _");
      Text charPressed(PLAY_X_START + 50, PLAY_Y_HEIGHT + 20, msg);
      char coinScoreStr[256];
      sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
      Text coinScore(PLAY_X_START + 50, PLAY_Y_HEIGHT + 50, coinScoreStr);

      paused = true;
      rtheta = true;
      double coin_speed = COIN_SPEED;
      double coin_angle_deg = COIN_ANGLE_DEG;
      double coin_ax = 0;
      double coin_ay = COIN_G;

      int num_coins = 4;
      Coin coin1(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 1);
      Coin coin2(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 1);
      Coin coin3(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 1);
      Coin coin4(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 1);
      vector<Coin *> coins;
      coins.push_back(&coin1);
      coins.push_back(&coin2);
      coins.push_back(&coin3);
      coins.push_back(&coin4);

      // After every COIN_GAP sec, make the coin jump
      // double last_coin_jump_end = 0;
      double last_coin_jump_ends[num_coins];
      for (int i = 0; i < num_coins; i++)
      {
            last_coin_jump_ends[i] = 0;
      }

      // When t is pressed, throw lasso
      // If lasso within range, make coin stick
      // When y is pressed, yank lasso
      // When l is pressed, loop lasso
      // When q is pressed, quit

      for (;;)
      {
            if ((runTime > 0) && (currTime > runTime))
            {
                  break;
            }

            XEvent e;
            bool pendingEv = checkEvent(e);
            if (pendingEv)
            {
                  char c = charFromEvent(e);
                  msg[msg.length() - 1] = c;
                  charPressed.setMessage(msg);
                  switch (c)
                  {
                  case 't':
                        lasso.unpause();
                        break;
                  case 'y':
                        lasso.yank();
                        break;
                  case 'l':
                        lasso.loopit();
                        for (Coin *coin : coins)
                        {
                              lasso.check_for_coin(coin);
                        }
                        wait(STEP_TIME * 5);
                        break;
                  case '[':
                        if (lasso.isPaused())
                        {
                              lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);
                        }
                        break;
                  case ']':
                        if (lasso.isPaused())
                        {
                              lasso.addAngle(+RELEASE_ANGLE_STEP_DEG);
                        }
                        break;
                  case '-':
                        if (lasso.isPaused())
                        {
                              lasso.addSpeed(-RELEASE_SPEED_STEP);
                        }
                        break;
                  case '=':
                        if (lasso.isPaused())
                        {
                              lasso.addSpeed(+RELEASE_SPEED_STEP);
                        }
                        break;
                  case 'q':
                        exit(0);
                  default:
                        break;
                  }
            }

            lasso.nextStep(stepTime);

            //* testing magnetic attraction
            // if (!lasso.coin_present())
            //       coin.attract((MovingObject)lasso);

            for (int i = 0; i < num_coins; i++)
            {
                  Coin *coin = coins[i];
                  coin->nextStep(stepTime);
                  if (coin->isPaused())
                  {
                        if ((currTime - last_coin_jump_ends[i]) >= COIN_GAP)
                        {
                              coin->unpause();
                        }
                  }

                  if (coin->getYPos() > PLAY_Y_HEIGHT || coin->getXPos() > PLAY_X_WIDTH || coin->getYPos() < PLAY_Y_START || coin->getXPos() < PLAY_X_START)
                  {
                        coin->resetCoin();
                        last_coin_jump_ends[i] = currTime;
                  }
            }

            sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
            coinScore.setMessage(coinScoreStr);

            stepCount++;
            currTime += stepTime;
            wait(stepTime);
      } // End for(;;)

      wait(3);
} // End main_program
