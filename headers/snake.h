#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "block.h"
#include "controller.h"
#include<vector>

struct snake
{
    static const int ENERGY_LOSS_SPEED;
    static const int DECOMPOSITION_SPEED;
    static const int BIRTH_SPEED;

    static const double DEFENCE_MULTIPLYER;
    static const double DEFENCE_ADDER;

    static const int MIN_SPLIT_LENGTH;
    static const int MIN_LENGTH;

    std::vector<block> blocks;
    double colour_r, colour_g, colour_b;
    int direction;
    int to_next_loss;
    double defence,attack;
    int dead;

    controller* ctr;

    void randomise(int food, controller* new_ctr);
    bool moveForward();
    std::pair<int, std::vector<block> > think();
    void eat();
    void eat(int food);
    std::pair<int, std::vector<block> > getBit(int node, double enemy_attack);
    void bite(double enemy_defence);
    void die(bool part);
    void birth();
    void mutate();

    ~snake() =default;
};

#endif // SNAKE_H_INCLUDED
