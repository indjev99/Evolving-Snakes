#ifndef WINDOW_FUNCTIONS_H_INCLUDED
#define WINDOW_FUNCTIONS_H_INCLUDED

#include<string>
#include<queue>
#include<vector>
#include<GLFW/glfw3.h>

extern std::queue<int> presses;
extern int pressed;
extern double mxpos,mypos;
extern bool paused;
extern bool new_neural_network;
extern bool change_settings;
extern bool draw_sim;
extern bool draw_neural_net;
extern bool draw_neural_net_mode;
extern bool save_data;
extern bool load_data;

void errorCallback(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void windowSizeCallback(GLFWwindow* window, int width, int height);
std::string setCallbacks(GLFWwindow* w, bool net);
std::string initializeGLFW();
std::string createWindow(GLFWwindow*& w, bool net);
void stopGraphics(std::vector<GLFWwindow*> w);

#endif // WINDOW_FUNCTIONS_H_INCLUDED
