#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "snake.h"
#include "food.h"
#include<vector>
#include<GLFW/glfw3.h>

void drawPartEllipse(float x, float y, float radiusX, float radiusY, double alpha, double beta);
void drawGridSquare(int x, int y, double colour_r, double colour_g, double colour_b, double thickness);
void drawGrid(double colour_r, double colour_g, double colour_b, double thickness);
void drawSnake(snake& s);
void drawFood(food& f);
void drawWindow(GLFWwindow* w, std::vector<snake>& snakes, std::vector<food>& foods);
#endif // DRAW_H_INCLUDED
