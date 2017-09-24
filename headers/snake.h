#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "block.h"
#include "controller.h"
#include<vector>

struct snake
{
    static int MAX_ENERGY;
    static int DECOMPOSITION_TIME;
    static int BIRTH_TIME;

    static double DEFENCE_MULTIPLIER;
    static double DEFENCE_ADDER;
    static double DEFENCE_BOOST;

    static int MIN_SPLIT_LENGTH;
    static int MIN_LENGTH;

    std::string name;
    int time_alive;

    double defence,attack;
    double colour_r, colour_g, colour_b;
    int dead;
    int energy;
    int direction;
    bool speed_boost;
    bool defence_boost;
    std::vector<block> blocks;

    controller* ctr;

    void randomise(int food, controller* new_ctr);
    bool moveForward();
    std::pair<int, std::vector<block> > think();
    void eat(int food=1);
    std::pair<int, std::vector<block> > getBit(int node, double enemy_attack);
    void die(bool part);
    void birth();
    void mutate();

    ~snake() =default;
};

#endif // SNAKE_H_INCLUDED
