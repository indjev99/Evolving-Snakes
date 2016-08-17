#ifndef CTR_RANDOM_H_INCLUDED
#define CTR_RANDOM_H_INCLUDED

#include "controller.h"
#include<vector>

struct ctrRandom:controller
{
    std::string getType();
    std::vector<double> getValues();
    ctrRandom* clone();
    void randomise();
    void mutate();
    decision think();

    ~ctrRandom() =default;
};

#endif // CTR_RANDOM_H_INCLUDED
