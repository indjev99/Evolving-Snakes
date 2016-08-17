#ifndef SIGHT_H_INCLUDED
#define SIGHT_H_INCLUDED

#include "field.h"
#include "point.h"
#include "snake.h"

std::pair<int, bool> seeOne(field& field, point p, int dir);
void seeAll(field& field, snake& s);

#endif // SIGHT_H_INCLUDED
