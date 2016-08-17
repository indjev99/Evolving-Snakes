#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "point.h"

struct block:point
{
    int food;
    ~block() =default;
};

#endif // BLOCK_H_INCLUDED
