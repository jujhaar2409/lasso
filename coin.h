#ifndef __COIN_H__
#define __COIN_H__

#include "MovingObject.h"

class Coin : public MovingObject {
    double coin_start_x;
    double coin_start_y;
    double release_speed;
    double release_angle_deg;
    double coin_ax;
    double coin_ay;

    // values of coin type may be:
    // 0: bonus
    // 1: normal
    // 2: magnetic
    // 3: bomb
    int coin_type;

    // values of coin_reward depend on the coin type:
    // bonus: 2
    // normal: 1
    // magnetic: 0
    // bomb: -1
    int coin_reward;

    // values of game mode may be:
    // 1: arcade
    // 2: magnetic
    // 3: bomb
    // 4: rajni
    int game_mode;

    vector<int> coin_type_prob;

    // Moving parts
    Circle coin_circle;

    void set_random_x();

    void init_type_prob();

    void init_type();

    void set_coin_color();

public:
    Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, int gamemode)
            : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
        release_speed = speed;
        release_angle_deg = angle_deg;
        coin_ax = argax;
        coin_ay = argay;

        // coin_reward = 1;
        game_mode = gamemode;
        init_type_prob();
        init_type();

        initCoin();
    }

    void initCoin();

    void resetCoin();

    void attract(MovingObject *obj, double scale);

    void set_acc(double ax, double ay);

    int get_coin_reward() const;

    int makes_magnetic() const;
}; // End class Coin

#endif
