#include <simplecpp>
#include "MovingObject.h"
#include "lasso.h"

using namespace simplecpp;

void Lasso::draw_lasso_band()
{
  double len = (release_speed / MAX_RELEASE_SPEED) * LASSO_BAND_LENGTH;
  double arad = release_angle_deg * PI / 180.0;
  double xlen = len * cos(arad);
  double ylen = len * sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x - xlen), (lasso_start_y + ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso()
{
  lasso_start_x = (PLAY_X_START + LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT - LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR(RED));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE / 2);
  lasso_loop.setColor(COLOR(BROWN));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  // the_coins;
  the_coins_len = 0;
  num_coins = 0;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR(BROWN));

  lasso_band.setColor(COLOR(BLUE_VIOLET));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank()
{
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE / 2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if (the_coins_len != 0)
  {
    for (int i = 0; i < the_coins_len; i++)
    {
      Coin *the_coin = the_coins[i];
      num_coins += the_coin->get_coin_reward();
      if (the_coin->makes_magnetic())
        magnetic = true;
      the_coin->resetCoin();
      the_coins[i] = nullptr;
    }
    the_coins_len = 0;
  }
} // End Lasso::yank()

void Lasso::loopit()
{
  if (lasso_looped)
  {
    return;
  } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg)
{
  release_angle_deg += angle_deg;
  if (release_angle_deg < MIN_RELEASE_ANGLE_DEG)
  {
    release_angle_deg = MIN_RELEASE_ANGLE_DEG;
  }
  if (release_angle_deg > MAX_RELEASE_ANGLE_DEG)
  {
    release_angle_deg = MAX_RELEASE_ANGLE_DEG;
  }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed)
{
  release_speed += speed;
  if (release_speed < MIN_RELEASE_SPEED)
  {
    release_speed = MIN_RELEASE_SPEED;
  }
  if (release_speed > MAX_RELEASE_SPEED)
  {
    release_speed = MAX_RELEASE_SPEED;
  }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime)
{
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if (getYPos() > PLAY_Y_START + PLAY_Y_HEIGHT || getXPos() > PLAY_X_START + PLAY_X_WIDTH)
  {
    yank();
  }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr)
{
  if (isPaused())
    return;
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff * xdiff) + (ydiff * ydiff));
  if (distance <= LASSO_RADIUS)
  {
    if (coin_present(coinPtr))
      return;
    the_coins[the_coins_len] = coinPtr;
    the_coins_len++;
    coinPtr->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()

bool Lasso::coin_present(Coin *coin)
{
  for (int i = 0; i < the_coins_len; i++)
  {
    if (coin == the_coins[i])
      return true;
  }
  return false;
}

bool Lasso::get_magnetic()
{
  return magnetic;
}

void Lasso::set_magnetic(bool magnetic_val)
{
  magnetic = magnetic_val;
}