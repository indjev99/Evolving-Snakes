#ifndef DRAW_NEURAL_NET_H_INCLUDED
#define DRAW_NEURAL_NET_H_INCLUDED

#include<vector>
#include<GLFW/glfw3.h>

void drawNet(GLFWwindow* w, std::vector<double>& values, int mode);
void drawNetWindow(GLFWwindow* w, std::vector<double>& values, int mode);

#endif // DRAW_NEURAL_NET_H_INCLUDED
