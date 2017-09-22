#ifndef DECISION_H_INCLUDED
#define DECISION_H_INCLUDED

struct decision
{
    bool turn_right;
    bool turn_left;
    bool boost_speed;
    bool boost_defence;
    bool split;
    int split_length;

    ~decision() =default;
};

#endif // DECISION_H_INCLUDED
