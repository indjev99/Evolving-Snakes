#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "point.h"

struct food:point
{
    static const double DEFAULT_COLOUR_R;
    static const double DEFAULT_COLOUR_G;
    static const double DEFAULT_COLOUR_B;
    double colour_r;
    double colour_g;
    double colour_b;
    int used_energy;
    bool ex_snake;
    food();
    food(int new_x, int new_y);
    food(int new_x, int new_y, double red, double green, double blue, int new_used_energy);

    ~food() =default;
};

#endif // FOOD_H_INCLUDED
