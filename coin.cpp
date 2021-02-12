#include "coin.h"
#include "lasso.h"

void Coin::initCoin()
{
  coin_start_x = PLAY_X_START + PLAY_X_WIDTH * 0.2 + (rand() % 20) / 20.0 * PLAY_X_WIDTH * 0.7;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  // coin_circle.setColor(COLOR(coin_color));
  coin_circle.setColor(COLOR(((coin_type == 1) ? "gold" : "red")));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin()
{
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  // randomize position of coin
  coin_start_x = PLAY_X_START + PLAY_X_WIDTH * 0.2 + (rand() % 20) / 20.0 * PLAY_X_WIDTH * 0.7;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::set_acc(int ax, int ay)
{
  set_ax(ax);
  set_ay(ay);
}

void Coin::attract(MovingObject obj)
{
  double disX = obj.getXPos() - getXPos();
  double disY = obj.getYPos() - getYPos();
  double dist = sqrt(disX * disX + disY * disY);
  set_acc((disX / dist) * COIN_G, COIN_G + (2 * disY / dist) * COIN_G);
}

int Coin::get_coin_reward()
{
  return coin_reward;
}