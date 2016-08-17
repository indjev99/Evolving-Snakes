#include "../headers/draw_neural_net.h"
#include "../headers/draw.h"
#include "../headers/colours.h"
#include "../headers/window_size.h"
#include "../headers/ctrNeuralNetwork.h"

void drawNet(GLFWwindow* w, std::vector<double>& values, bool mode)
{
    if (values.empty()) return;
    ctrNeuralNetwork nn;
    nn.setValues(values);
    double dx,dy,dy2,x,y,y2;
    double weight;
    double over;
    double one=1.0*WINDOWS_WIDTH/WINDOWS_HEIGHT;
    double radius;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_LINES);

    dx=one*2.0/nn.topology.size();
    x=-one+dx/2;
    for (int i=1;i<nn.topology.size();++i)
    {
        dy=2.0/nn.topology[i];
        y=1+dy/2;
        x+=dx;
        for (int j=0;j<nn.topology[i];++j)
        {
            dy2=2.0/nn.topology[i-1];
            y2=+1+dy2/2;
            y-=dy;
            for (int k=0;k<nn.topology[i-1];++k)
            {
                y2-=dy2;
                weight=nn.weights[i][j][k]*(mode?nn.neurons[i-1][k]:1);
                if (weight>=0)
                {
                    over=weight-1;
                    if (over<0) over=0;
                    glColor4f(1,over,BACKGROUND_COLOUR_B,weight);
                }
                else
                {
                    over=-weight-1;
                    if (over<0) over=0;
                    glColor4f(BACKGROUND_COLOUR_R,over,1,-weight);
                }
                glVertex2d(x-dx,y2);
                glVertex2d(x,y);
            }
        }
    }

    glEnd();

    glDisable(GL_BLEND);

    dx=one*2.0/nn.topology.size();
    x=-one-dx/2;
    for (int i=0;i<nn.topology.size();++i)
    {
        dy=2.0/nn.topology[i];
        y=1+dy/2;
        x+=dx;
        for (int j=0;j<nn.topology[i];++j)
        {
            y-=dy;
            glColor3f(nn.neurons[i][j],nn.neurons[i][j],nn.neurons[i][j]);
            radius=dy/4;
            if (dx/4<radius) radius=dx/4;
            drawPartEllipse(x,y,radius,radius,0,360);
        }
    }
}
void drawNetWindow(GLFWwindow* w, std::vector<double>& values, bool mode)
{
    glfwSetWindowShouldClose(w,0);

    float ratio;
    int width, height;

    glfwMakeContextCurrent(w);
    glfwGetFramebufferSize(w,&width,&height);
    ratio=width/(float)height;
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio,ratio,-1.f,1.f,1.f,-1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(BACKGROUND_COLOUR_R,BACKGROUND_COLOUR_G,BACKGROUND_COLOUR_B);

    glBegin(GL_QUADS);

    glVertex2f(-1.0,-1.0);
    glVertex2f(1.0,-1.0);
    glVertex2f(1.0,1.0);
    glVertex2f(-1.0,1.0);

    glEnd();

    drawNet(w,values,mode);

    glfwSwapBuffers(w);
}
