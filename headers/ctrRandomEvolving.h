#ifndef CTRRANDOMEVOLVING_H_INCLUDED
#define CTRRANDOMEVOLVING_H_INCLUDED

#include "controller.h"
#include<vector>

struct ctrRandomEvolving:controller
{
    double turn_left_probability,turn_right_probability;
    double boost_speed_probability,boost_defence_probability;
    double split_probability;

    std::string getType();
    std::vector<double> getValues();
    void setValues(std::vector<double>& values);
    ctrRandomEvolving* clone();
    void randomise();
    void mutate();
    decision think();

    ~ctrRandomEvolving() =default;
};

#endif // CTRRANDOMEVOLVING_H_INCLUDED
