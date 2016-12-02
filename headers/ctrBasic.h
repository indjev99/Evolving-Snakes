#ifndef CTRBASIC_H_INCLUDED
#define CTRBASIC_H_INCLUDED

#include "controller.h"
#include<vector>

struct ctrBasic:controller
{
    double split_treshhold;
    double split_part;

    std::pair<bool, int> front_score,right_score,left_score;

    std::string getType();
    std::vector<double> getValues();
    void setValues(std::vector<double>& values);
    ctrBasic* clone();
    void randomise();
    void mutate();
    decision think();
    void loadInputs();

    ~ctrBasic() =default;
};

#endif // CTRBASIC_H_INCLUDED
