#include "../headers/run.h"
#include "../headers/window_functions.h"
#include<iostream>
#include<stdlib.h>

GLFWwindow *sim,*net;
int main()
{
    system("cls");

    std::string message;
    message=initializeGLFW();
    std::cout<<message<<std::endl;
    if (message!="GLFW initialized successfully.") return -1;

    message=createWindow(sim,0);
    std::cout<<message<<std::endl;
    if (message!="Simulation window created successfully.") return -1;

    message=createWindow(net,1);
    std::cout<<message<<std::endl;
    if (message!="Neural network window created successfully.") return -1;

    message=setCallbacks(sim,0);
    std::cout<<message<<std::endl;
    if (message!="Callbacks for simulation window set successfully.") return -1;

    message=setCallbacks(net,1);
    std::cout<<message<<std::endl;
    if (message!="Callbacks for neural network window set successfully.") return -1;

    system("cls");
    run(sim,net);

    stopGraphics({sim});
    return 0;
}
