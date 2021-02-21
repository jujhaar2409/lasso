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

    // magnetic state keeper
    bool magnetic;
    // total time that the lasso will remain magnetised in seconds
    const double magnet_time_sec = 5.0;
    const double magnet_time_val = magnet_time_sec / (4 * SCALE_FACTOR); // 5 / SCALE_FACTOR ~ 20 seconds
    double magnet_start_time;

    // frenzy state keeper
    bool frenzy;
    // total time that frenzy will remain
    const double frenzy_time_sec = 10.0;
    const double frenzy_time_val = frenzy_time_sec / (4 * SCALE_FACTOR); // 5 / SCALE_FACTOR ~ 20 seconds
    double frenzy_start_time;
    // number of steps corresponding to the above time
//    double magnet_num_steps = (500.0 / 17.0) * magnet_time_sec_approx; // 500 steps corresponds to 17 sec

    // count of steps taken by the lasso while magnetised
//    int magnet_step_count;

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
        frenzy = false;
        // set counter to 0
//        magnet_step_count = 0;
        magnet_start_time = -1;
        frenzy_start_time = -1;

        initLasso();
    }

    void draw_lasso_band();

    void yank(double);

    void loopit();

    void addAngle(double angle_deg);

    void addSpeed(double speed);

    void nextStep(double t, double ct);

    void check_for_coin(Coin *coin);

    int getNumCoins() const { return num_coins; }

    bool get_magnetic() const;

    bool coin_present(Coin *coin);

    bool get_frenzy() const;
}; // End class Lasso

#endif
