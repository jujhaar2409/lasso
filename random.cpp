#include "random.h"

double my_random::get_random_in_range(double a, double b)
{
    std::random_device rd;
    std::default_random_engine e(rd());
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(a, b);
    int val = dist(mt);
    return val;
}