#ifndef CTRRANDOM_H_INCLUDED
#define CTRRANDOM_H_INCLUDED

#include "controller.h"
#include<vector>

struct ctrRandom:controller
{
    std::string getType();
    std::vector<double> getValues();
    void setValues(std::vector<double>& values);
    ctrRandom* clone();
    void randomise();
    void mutate();
    decision think();

    ~ctrRandom() =default;
};

#endif // CTRRANDOM_H_INCLUDED
