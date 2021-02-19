#ifndef __LASSO_H__
#define __LASSO_H__

#include "MovingObject.h"
#include "coin.h"
#include "random.h"
#include "constants.h"

class Lasso : public MovingObject {
    double lasso_start_x;
    double lasso_start_y;
    double release_speed;
    double release_angle_deg;
    double lasso_ax;
    double lasso_ay;

    // Moving parts
    Circle lasso_circle;
    Circle lasso_loop;

    // Non-moving parts
    Line lasso_line;
    Line lasso_band;

    // State info
    bool lasso_looped;
    Coin *the_coins[MAX_COINS];
    int the_coins_len;
    int num_coins;
    bool magnetic;

    // total time that the lasso will remain magnetised in seconds
    double magnet_time_sec_approx = 5;
    // number of steps corresponding to the above time
    double magnet_num_steps = (500.0 / 17.0) * magnet_time_sec_approx; // 500 steps corresponds to 17 sec

    // count of steps taken by the lasso while magnetised
    int magnet_step_count;

    void initLasso();

public:
    Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed,
                                                                                                                  angle_deg,
                                                                                                                  argax,
                                                                                                                  argay,
                                                                                                                  argpaused,
                                                                                                                  rtheta) {
        release_speed = speed;
        release_angle_deg = angle_deg;
        lasso_ax = argax;
        lasso_ay = argay;

        //    magnetic = true;
        magnetic = false;
        // set counter to 0
        magnet_step_count = 0;

        initLasso();
    }

    void draw_lasso_band();

    void yank();

    void loopit();

    void addAngle(double angle_deg);

    void addSpeed(double speed);

    void nextStep(double t);

    void check_for_coin(Coin *coin);

    int getNumCoins() const { return num_coins; }

    bool get_magnetic();

    void set_magnetic(bool);

    bool coin_present(Coin *coin);
}; // End class Lasso

#endif
