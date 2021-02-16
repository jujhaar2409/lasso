#include "coin.h"
#include "lasso.h"
#include <random>

namespace my_vector_utils {
    int sum(const vector<int>& vec) {
        int sum = 0;
        for (int i : vec) sum += i;
        return sum;
    }
}

void Coin::initCoin()
{
  coin_start_x = PLAY_X_START + PLAY_X_WIDTH * 0.2 + (rand() % 20) / 20.0 * PLAY_X_WIDTH * 0.7;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);

  set_coin_color();

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

  //* making types work
  init_type();
  set_coin_color();

  // randomize position of coin
  coin_start_x = PLAY_X_START + PLAY_X_WIDTH * 0.2 + (rand() % 20) / 20.0 * PLAY_X_WIDTH * 0.7;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::set_acc(double ax, double ay)
{
  set_ax(ax);
  set_ay(ay);
}

void Coin::attract(MovingObject *obj, double scale)
{
  double disX = obj->getXPos() - getXPos();
  double disY = obj->getYPos() - getYPos();
  // double dist = sqrt(disX * disX + disY * disY);
  set_acc(scale * disX * COIN_G, COIN_G + 0.5 * scale * disY * COIN_G);
}

int Coin::get_coin_reward() const
{
  return coin_reward;
}

int Coin::makes_magnetic() const
{
    // type of magnetic coin is 2
    return coin_type == 2;
}

void Coin::init_type_prob()
{
  if (game_mode == 1)
  {
    //* arcade mode
    coin_types.push_back(0);
    coin_type_prob.push_back(2);
    coin_types.push_back(1);
    coin_type_prob.push_back(8);
  }
  else if (game_mode == 2)
  {
    //* magnet mode
    coin_types.push_back(0);
    coin_type_prob.push_back(2);
    coin_types.push_back(1);
    coin_type_prob.push_back(12);
    coin_types.push_back(2);
    coin_type_prob.push_back(6);
  }
  else if (game_mode == 3)
  {
    //* bomb mode
    coin_types.push_back(0);
    coin_type_prob.push_back(2);
    coin_types.push_back(1);
    coin_type_prob.push_back(12);
    coin_types.push_back(3);
    coin_type_prob.push_back(6);
  }
  else if (game_mode == 4)
  {
    //* rajni mode
    coin_types.push_back(0);
    coin_type_prob.push_back(2);
    coin_types.push_back(1);
    coin_type_prob.push_back(12);
    coin_types.push_back(2);
    coin_type_prob.push_back(6);
    coin_types.push_back(3);
    coin_type_prob.push_back(6);
  }
}

void Coin::init_type() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, my_vector_utils::sum(coin_type_prob));
    int val = dist(mt);

    int sum = 0;
    for (int  i = 0 ; i < coin_type_prob.size(); i++) {
        if (val <= sum + coin_type_prob[i]){
            coin_type = coin_types[i];
            coin_reward = 2 - coin_type;
            return;
        }
        sum += coin_type_prob[i];
    }
}

void Coin::set_coin_color() {
    if (coin_type == 0) {
        //* Bonus Coin
        coin_circle.setColor(COLOR(255,0,0));
    }
    else if (coin_type == 1) {
        //* Regular Coin
        coin_circle.setColor(COLOR(0,0,255));
    }
    else if (coin_type == 2) {
        //* Magnet Coin
        coin_circle.setColor(COLOR(0,255,0));
    }
    else if (coin_type == 3) {
        //* Magnet Coin
        coin_circle.setColor(COLOR(255,255,0));
    }
}