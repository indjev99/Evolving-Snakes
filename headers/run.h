#ifndef RUN_H_INCLUDED
#define RUN_H_INCLUDED

#include "snake.h"
#include "controller.h"
#include "field.h"
#include<vector>
#include<GLFW/glfw3.h>

extern double FOOD_PROBABILITY;
extern double MAX_FOOD_PART;
extern double SNAKE_PROBABILITY;

extern const int SEED;

void generateField(field& field, std::vector<snake>& snakes, std::vector<point>& foods);
controller* selectRandomController();
void saveData();
void loadData();
void run(GLFWwindow* sim, GLFWwindow* net);

#endif // RUN_H_INCLUDED
