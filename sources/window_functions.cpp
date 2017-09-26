#include "../headers/window_functions.h"
#include "../headers/field_radius.h"
#include "../headers/window_size.h"
#include<iostream>
#include<queue>

std::queue<int> presses;
int pressed;
double mxpos=0,mypos=0;
bool paused=0;
bool new_neural_network=0;
bool change_settings=0;
bool draw_sim=1;
int draw_sim_mode=0;
bool draw_neural_net=1;
int draw_neural_net_mode=0;
int draw_neural_net_neuron=-1;
bool draw_neural_net_neuron_increment=0;
bool save_data=0;
bool load_data=0;
bool reset=0;
bool control=0;

void errorCallback(int error, const char* description)
{
    std::cout<<error<<": "<<description<<std::endl;
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS) glfwSetWindowShouldClose(window,1);
    if ((key==GLFW_KEY_W || key==GLFW_KEY_UP) && action==GLFW_PRESS)
    {
        presses.push(0);
    }
    if ((key==GLFW_KEY_D || key==GLFW_KEY_RIGHT) && action==GLFW_PRESS)
    {
        presses.push(1);
    }
    if ((key==GLFW_KEY_S || key==GLFW_KEY_DOWN) && action==GLFW_PRESS)
    {
        presses.push(2);
    }
    if ((key==GLFW_KEY_A || key==GLFW_KEY_LEFT) && action==GLFW_PRESS)
    {
        presses.push(3);
    }
    if ((key==GLFW_KEY_F1) && action==GLFW_PRESS)
    {
        new_neural_network=1;
    }
    if ((key==GLFW_KEY_F2) && action==GLFW_PRESS)
    {
        paused=!paused;
    }
    if ((key==GLFW_KEY_F3) && action==GLFW_PRESS)
    {
        draw_sim=!draw_sim;
    }
    if ((key==GLFW_KEY_F4) && action==GLFW_PRESS)
    {
        draw_sim_mode=(draw_sim_mode+1)%4;
    }
    if ((key==GLFW_KEY_F5) && action==GLFW_PRESS)
    {
        draw_neural_net=!draw_neural_net;
    }

    if ((key==GLFW_KEY_F6) && action==GLFW_PRESS)
    {
        draw_neural_net_mode=(draw_neural_net_mode+1)%4;
    }
    if ((key==GLFW_KEY_F7) && action==GLFW_PRESS)
    {
        ++draw_neural_net_neuron;
        draw_neural_net_neuron_increment=1;
    }
    if ((key==GLFW_KEY_F8) && action==GLFW_PRESS)
    {
        change_settings=1;
    }
    if ((key==GLFW_KEY_F9) && action==GLFW_PRESS)
    {
        save_data=1;
    }
    if ((key==GLFW_KEY_F10) && action==GLFW_PRESS)
    {
        load_data=1;
    }
    if ((key==GLFW_KEY_F11) && action==GLFW_PRESS)
    {
        reset=1;
    }
    if ((key==GLFW_KEY_F12) && action==GLFW_PRESS)
    {
        control=!control;
    }
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action==GLFW_PRESS)
    {
        pressed=button;
        glfwGetCursorPos(window,&mxpos,&mypos);
        mxpos=mxpos*2-WINDOWS_WIDTH;
        mypos=-mypos*2+WINDOWS_HEIGHT;
        mxpos/=ORIGINAL_WINDOWS_HEIGHT;
        mypos/=ORIGINAL_WINDOWS_HEIGHT;
    }
}
void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    WINDOWS_WIDTH=width;
    WINDOWS_HEIGHT=height;
    pressed=-2;
}
std::string setCallbacks(GLFWwindow* w, bool net)
{
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(w,keyCallback);
    if (net)
    {
        glfwSetMouseButtonCallback(w,mouseButtonCallback);
        glfwSetWindowSizeCallback(w,windowSizeCallback);
    }
    if (net) return "Callbacks for neural network window set successfully.";
    else return "Callbacks for simulation window set successfully.";
}
std::string initializeGLFW()
{
    if (!glfwInit())
        return "Unable to initialize GLFW.";
    return "GLFW initialized successfully.";
}
std::string createWindow(GLFWwindow*& w, bool net)
{
    std::string name;
    if (net) name="Neural Network";
    else name="Evolving Snakes";
    w=glfwCreateWindow(WINDOWS_WIDTH,WINDOWS_HEIGHT,name.c_str(),NULL,NULL);
    if (!w)
    {
        glfwTerminate();
        if (net) return "Unable to create neural network window.";
        else return "Unable to create simulation window.";
    }
    if (net) return "Neural network window created successfully.";
    else return "Simulation window created successfully.";
}
void stopGraphics(std::vector<GLFWwindow*> w)
{
    for (int i=0;i<w.size();++i)
    {
        glfwDestroyWindow(w[i]);
    }
    glfwTerminate();
}
