#include "../headers/food.h"

const double food::DEFAULT_COLOUR_R=0.15;
const double food::DEFAULT_COLOUR_G=1;
const double food::DEFAULT_COLOUR_B=0.05;

food::food()
{
    colour_r=DEFAULT_COLOUR_R;
    colour_g=DEFAULT_COLOUR_G;
    colour_b=DEFAULT_COLOUR_B;
    used_energy=0;
    ex_snake=0;
}
food::food(int new_x, int new_y)
{
    x=new_x;
    y=new_y;
    colour_r=DEFAULT_COLOUR_R;
    colour_g=DEFAULT_COLOUR_G;
    colour_b=DEFAULT_COLOUR_B;
    used_energy=0;
    ex_snake=0;
}
food::food(int new_x, int new_y, double red, double green, double blue, int new_used_energy)
{
    x=new_x;
    y=new_y;
    colour_r=red;
    colour_g=green;
    colour_b=blue;
    used_energy=new_used_energy;
    ex_snake=1;
}
