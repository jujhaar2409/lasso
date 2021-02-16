#ifndef __COIN_H__
#define __COIN_H__

#include "MovingObject.h"

class Coin : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  int coin_type;
  int coin_reward;

  // Moving parts
  Circle coin_circle;

public:
  Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, int type) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;

    coin_reward = 1;
    coin_type = type;
    initCoin();
  }

  void initCoin();
  void resetCoin();

  void attract(MovingObject obj, double scale);
  void set_acc(double ax, double ay);
  int get_coin_reward();
}; // End class Coin

#endif
