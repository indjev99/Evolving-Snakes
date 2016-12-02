#include "../headers/ctrRandom.h"
#include "../headers/decision.h"
#include<stdlib.h>

std::string ctrRandom::getType()
{
    return "random";
}
std::vector<double> ctrRandom::getValues()
{
    return {};
}

void ctrRandom::setValues(std::vector<double>& values) {}
ctrRandom* ctrRandom::clone()
{
    return new ctrRandom(*this);
}
void ctrRandom::randomise() {}
void ctrRandom::mutate() {}
decision ctrRandom::think()
{
    decision decision;
    decision.turn_right=!(rand()%8);
    decision.turn_left=!(rand()%8);
    if (body_length>0)
    {
        decision.split=!(rand()%150);
        decision.split_length=rand()%body_length;
    }
    else
    {
        decision.split=0;
    }
    return decision;
}
