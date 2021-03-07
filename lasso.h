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
    double magnet_start_time;

    // frenzy state keeper
    bool frenzy;
    // total time that frenzy will remain
    const double frenzy_time_sec = 10.0;
    double frenzy_start_time;

    int lives;

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
        lives = 3;

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

    int get_lives() const;

    bool get_magnetic() const;

    bool coin_present(Coin *coin);

    bool get_frenzy() const;
}; // End class Lasso

#endif
