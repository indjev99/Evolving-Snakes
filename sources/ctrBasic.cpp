#include "../headers/ctrBasic.h"
#include "../headers/decision.h"
#include "../headers/randomisation.h"
#include<math.h>
#include<iostream>
#include<conio.h>

std::string ctrBasic::getType()
{
    return "basic";
}
std::vector<double> ctrBasic::getValues()
{
    return {split_treshhold,split_part};
}
void ctrBasic::setValues(std::vector<double>& values)
{
    split_treshhold=values[0];
    split_part=values[1];
}
ctrBasic* ctrBasic::clone()
{
    return new ctrBasic(*this);
}
void ctrBasic::randomise()
{
    randomiseVariable(split_treshhold,2,100);
    randomiseVariable(split_part,1,split_treshhold-1);
}
void ctrBasic::mutate()
{
    mutateVariable(split_treshhold,2,100);
    mutateVariable(split_part,1,split_treshhold-1);
}
decision ctrBasic::think()
{
    decision decision;

    loadInputs();

    std::pair<bool, int> best_score=front_score;
    decision.turn_right=0;
    decision.turn_left=0;

    if (right_score<best_score)
    {
        best_score=right_score;
        decision.turn_right=1;
        decision.turn_left=0;
    }
    if (left_score<best_score)
    {
        best_score=left_score;
        decision.turn_right=0;
        decision.turn_left=1;
    }

    //cerr<<front_score.second<<" "<<right_score.second<<" "<<left_score.second<<"   "<<decision.turn_right<<" "<<decision.turn_left<<endl;
    //if (front_score.second<0 && right_score.second<0 && left_score.second<0) getch();

    if (body_length>=split_treshhold)
    {
        decision.split=1;
        decision.split_length=ceil(split_part);
    }
    else
    {
        decision.split=0;
    }
    return decision;
}
void ctrBasic::loadInputs()
{
    front_score.second=(VF_food[VF_RADIUS]?1:-1)*(VF_dist[VF_RADIUS]+1);
    front_score.first=!VF_food[VF_RADIUS];

    right_score.second=(VR_food[VS_RADIUS]?1:-1)*(VR_dist[VS_RADIUS]+1);
    right_score.first=!VR_food[VS_RADIUS];

    left_score.second=(VL_food[VS_RADIUS]?1:-1)*(VL_dist[VS_RADIUS]+1);
    left_score.first=!VL_food[VS_RADIUS];
}
