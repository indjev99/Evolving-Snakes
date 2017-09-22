#include "../headers/snake.h"
#include "../headers/field_radius.h"
#include "../headers/randomisation.h"
#include "../headers/names.h"
#include<stdlib.h>

int snake::MAX_ENERGY=50;
int snake::DECOMPOSITION_TIME=10;
int snake::BIRTH_TIME=20;

double snake::DEFENCE_MULTIPLIER=1;
double snake::DEFENCE_ADDER=0;
double snake::DEFENCE_BOOST=1;

int snake::MIN_SPLIT_LENGTH=10;
int snake::MIN_LENGTH=4;

void snake::randomise(int food, controller* new_ctr)
{
    name=createNewName();
    time_alive=0;
    dead=0;
    blocks.resize(1);
    blocks[0].randomise();
    blocks[0].food=food;
    direction=rand()%4;
    randomiseVariable(attack,0,1);
    defence=(1-attack)*DEFENCE_MULTIPLIER+DEFENCE_ADDER;
    colour_r=attack;
    randomiseVariable(colour_g,0,1);
    randomiseVariable(colour_b,0,1);
    ctr=new_ctr;
    ctr->randomise();
    energy=MAX_ENERGY;
    speed_boost=0;
    defence_boost=0;
}
bool snake::moveForward()
{
    if (dead)
    {
        if (dead<-1)
        {
            ++dead;
            defence-=defence/(-dead);
            colour_g+=(1-colour_g)/(-dead);
            return 0;
        }
        else if (dead>0)
        {
            --dead;
            return 0;
        }
        return 1;
    }
    block new_pos=blocks[blocks.size()-1];
    for (int i=blocks.size()-1;i>0;--i)
    {
        blocks[i]=blocks[i-1];
    }
    blocks[0].food=0;
    blocks[0]+=direction;
    --energy;
    while (energy<=0)
    {
        --blocks[0].food;
        energy+=MAX_ENERGY;
    }
    if (new_pos.food>0)
    {
        --new_pos.food;
        blocks.push_back(new_pos);
    }
    if (blocks[blocks.size()-1].food<0)
    {
        if (blocks.size()>1)
        {
            blocks[blocks.size()-2].food+=blocks[blocks.size()-1].food+1;
            blocks.resize(blocks.size()-1);
        }
        else
        {
            die(0);
            blocks.resize(0);
        }
    }
    return 0;
}
std::pair<int, std::vector<block> > snake::think()
{
    std::vector<block> new_snake;
    int dir;

    if (dead) return make_pair(dir,new_snake);

    ctr->body_length=blocks.size();
    ctr->food_in_body=0;

    for (int i=0;i<blocks.size();++i)
    {
        ctr->food_in_body+=blocks[i].food;
    }

    decision decision=ctr->think();

    if (decision.turn_right) ++direction;
    if (decision.turn_left) --direction;
    direction+=4;
    direction%=4;

    speed_boost=decision.boost_speed;

    /*if (defence_boost)
    {
        defence_boost=0;
        defence-=DEFENCE_BOOST;
    }
    if (decision.boost_defence)
    {
        --energy;
        defence_boost=1;
        defence+=DEFENCE_BOOST;
    }*/

    int x1,y1,x2,y2;
    if (decision.split)
    {
        //--energy;
    }
    if (decision.split && blocks.size()>=MIN_SPLIT_LENGTH && decision.split_length>=MIN_LENGTH && blocks.size()-decision.split_length>=MIN_LENGTH)
    {
        x1=blocks[blocks.size()-1].x;
        y1=blocks[blocks.size()-1].y;
        x2=blocks[blocks.size()-2].x;
        y2=blocks[blocks.size()-2].y;
        if (x1==x2)
        {
            if ((abs(y1-y2)==1)==(y1>y2))
            {
                dir=0;
            }
            else
            {
                dir=2;
            }
        }
        else
        {
            if ((abs(x1-x2)==1)==(x1>x2))
            {
                dir=1;
            }
            else
            {
                dir=3;
            }
        }
        for (int i=blocks.size()-1;i>blocks.size()-1-decision.split_length;--i)
        {
            new_snake.push_back(blocks[i]);
        }
        blocks.resize(blocks.size()-decision.split_length);
    }
    return make_pair(dir,new_snake);
}
void snake::eat()
{
    if (blocks.empty()) return;
    ++blocks[0].food;
}
void snake::eat(int food)
{
    if (!food || blocks.empty()) return;
    blocks[0].food+=food;
}
std::pair<int, std::vector<block> > snake::getBit(int node, double enemy_attack)
{
    int food_given=0;
    std::vector<block> left;
    if (node!=0 || dead)
    {
        if (enemy_attack>defence)
        {
            food_given=blocks[node].food;
            for (int i=blocks.size()-1;i>node;--i)
            {
                left.push_back(blocks[i]);
            }
            blocks.resize(node);
            if (dead>0 && node==0) die(0);
        }
    }
    else
    {
        if (enemy_attack>attack)
        {
            die(0);
            food_given=blocks[node].food;
            for (int i=blocks.size()-1;i>node;--i)
            {
                left.push_back(blocks[i]);
            }
            blocks.resize(0);
        }
        else if (enemy_attack==attack)
        {
            die(0);
        }
        else
        {
            eat();
        }
    }
    return {food_given,left};
}
void snake::bite(double enemy_defence)
{
    if (enemy_defence>=attack)
    {
        die(0);
    }
    else
    {
        eat();
    }
}
void snake::die(bool part)
{
    dead=-DECOMPOSITION_TIME;
    if (!part) delete ctr;
}
void snake::birth()
{
    dead=BIRTH_TIME;
    energy=MAX_ENERGY;
    speed_boost=0;
    defence_boost=0;

    direction=rand()%4;
    ctr=ctr->clone();
    mutate();
}
void snake::mutate()
{
    name=mutateName(name);
    mutateVariable(attack,0,1);
    defence=(1-attack)*DEFENCE_MULTIPLIER+DEFENCE_ADDER;
    colour_r=attack;
    mutateVariable(colour_g,0,1);
    mutateVariable(colour_b,0,1);
    ctr->mutate();
}
