#include "coin.h"
#include "constants.h"
#include "random.h"

namespace my_vector_utils {
    int sum(const vector<int> &vec, bool magnetic, bool frenzy) {
        int sum = 0;
        int term;
        for (int i = 0; i < vec.size(); i++){
            term = vec[i];
            if ((magnetic && i == 2) || (frenzy && i == 4)) term = 0;
            sum += term;
        }
        return sum;
    }
} // namespace my_vector_utils

void Coin::initCoin() {
    // randomize position of coin
    set_random_x();

    coin_start_y = PLAY_Y_HEIGHT;
    coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);

    set_coin_color();

    coin_circle.setFill(true);
    addPart(&coin_circle);
}

void Coin::resetCoin(bool magnetic, bool frenzy) {
    double coin_speed = COIN_SPEED;
    double coin_angle_deg = COIN_ANGLE_DEG;
    coin_ax = 0;
    coin_ay = COIN_G;
    bool paused = true, rtheta = true;

    //* making types work
    init_type(magnetic, frenzy);
    set_coin_color();

    // randomize position of coin
    set_random_x();

    reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::set_acc(double ax, double ay) {
    set_ax(ax);
    set_ay(ay);
}

void Coin::attract(MovingObject *obj, double scale) {
    double disX = obj->getXPos() - getXPos();
    double disY = obj->getYPos() - getYPos();
    // double dist = sqrt(disX * disX + disY * disY);
    set_acc(scale * disX * COIN_G, COIN_G + 0.5 * scale * disY * COIN_G);
}

int Coin::get_coin_reward() const {
    return coin_reward;
}

bool Coin::makes_magnetic() const {
    // type of magnetic coin is 2
    return coin_type == 2;
}

bool Coin::makes_frenzy() const {
    return coin_type == 4;
}

void Coin::init_type_prob() {
    if (game_mode == 1) {
        //* arcade mode

        // type 0: bonus
        coin_type_prob.push_back(2);
        // type 1: regular
        coin_type_prob.push_back(8);
        // type 2: magnet
        coin_type_prob.push_back(0);
        // type 3: bomb
        coin_type_prob.push_back(0);
        // type 4: frenzy
        coin_type_prob.push_back(5);
    } else if (game_mode == 2) {
        //* magnet mode

        // type 0: bonus
        coin_type_prob.push_back(2);
        // type 1: regular
        coin_type_prob.push_back(12);
        // type 2: magnet
        coin_type_prob.push_back(6);
        // type 3: bomb
        coin_type_prob.push_back(0);
        // type 4: frenzy
        coin_type_prob.push_back(0);
    } else if (game_mode == 3) {
        //* bomb mode

        // type 0: bonus
        coin_type_prob.push_back(2);
        // type 1: regular
        coin_type_prob.push_back(12);
        // type 2: magnet
        coin_type_prob.push_back(0);
        // type 3: bomb
        coin_type_prob.push_back(6);
        // type 4: frenzy
        coin_type_prob.push_back(0);
    } else if (game_mode == 4) {
        //* rajni mode

        // type 0: bonus
        coin_type_prob.push_back(2);
        // type 1: regular
        coin_type_prob.push_back(12);
        // type 2: magnet
        coin_type_prob.push_back(6);
        // type 3: bomb
        coin_type_prob.push_back(6);
        // type 4: frenzy
        coin_type_prob.push_back(3);
    }
}

void Coin::init_type(bool magnetic, bool frenzy) {
    double val = my_random::get_random_in_range(0.0, my_vector_utils::sum(coin_type_prob, magnetic, frenzy));

    int sum = 0;
    int elem = 0;
    for (int i = 0; i < coin_type_prob.size(); i++) {
        elem = (coin_type_prob[i]);
        if ((magnetic && i == 2) || (frenzy && i == 4))
            elem = 0;

        if (val < sum + elem) {
            coin_type = i;
            coin_reward = coin_rewards[i];
            return;
        }
        sum += elem;
    }
}

void Coin::set_coin_color() {
    if (coin_type == 0) {
        //* Bonus Coin
        coin_circle.setColor(COLOR(BONUS_COIN_COLOR));
    } else if (coin_type == 1) {
        //* Regular Coin
        coin_circle.setColor(COLOR(REGULAR_COIN_COLOR));
    } else if (coin_type == 2) {
        //* Magnet Coin
        coin_circle.setColor(COLOR(MAGNET_COIN_COLOR));
    } else if (coin_type == 3) {
        //* Bomb Coin
        coin_circle.setColor(COLOR(BOMB_COIN_COLOR));
    } else if (coin_type == 4) {
        //* Frenzy Coin
        coin_circle.setColor(COLOR(FRENZY_COIN_COLOR));
    }
}

void Coin::set_random_x() {
    coin_start_x = my_random::get_random_in_range(PLAY_X_START + PLAY_X_WIDTH * 0.2, PLAY_X_START + PLAY_X_WIDTH * 0.9);
}

void Coin::hide() {
    coin_circle.hide();
}
void Coin::show() {
    coin_circle.show();
}

int Coin::get_type() const {
    return coin_type;
}