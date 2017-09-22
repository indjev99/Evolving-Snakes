#include "../headers/ctrRandomEvolving.h"
#include "../headers/decision.h"
#include "../headers/randomisation.h"
#include<stdlib.h>

std::string ctrRandomEvolving::getType()
{
    return "randomEvolving";
}
std::vector<double> ctrRandomEvolving::getValues()
{
    return {turn_left_probability,turn_right_probability,boost_speed_probability,boost_defence_probability,split_probability};
}

void ctrRandomEvolving::setValues(std::vector<double>& values)
{
    turn_left_probability=values[0];
    turn_right_probability=values[1];
    boost_speed_probability=values[2];
    boost_defence_probability=values[3];
    split_probability=values[4];
}
ctrRandomEvolving* ctrRandomEvolving::clone()
{
    return new ctrRandomEvolving(*this);
}
void ctrRandomEvolving::randomise()
{
    randomiseVariable(turn_left_probability,0,1);
    randomiseVariable(turn_right_probability,0,1);
    randomiseVariable(split_probability,0,1);
}
void ctrRandomEvolving::mutate()
{
    mutateVariable(turn_left_probability,0,1);
    mutateVariable(turn_right_probability,0,1);
    mutateVariable(split_probability,0,1);
}
decision ctrRandomEvolving::think()
{
    decision decision;
    decision.turn_right=(rand()%1000)/1000.0<turn_left_probability;
    decision.turn_left=(rand()%1000)/1000.0<turn_right_probability;
    decision.turn_right=(rand()%1000)/1000.0<boost_speed_probability;
    decision.turn_left=(rand()%1000)/1000.0<boost_defence_probability;
    if (body_length>0)
    {
        decision.split=(rand()%1000)/1000.0<split_probability;
        decision.split_length=rand()%body_length;
    }
    else
    {
        decision.split=0;
    }
    return decision;
}
