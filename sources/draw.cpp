#include "../headers/draw.h"
#include "../headers/window_size.h"
#include "../headers/field_radius.h"
#include "../headers/colours.h"
#include "../headers/window_functions.h"
#include<math.h>

const double DEG2RAD=3.14159/180.0;

void drawPartEllipse(float x, float y, float radiusX, float radiusY, double alpha, double beta)
{
    alpha=round(alpha*2);
    beta=round(beta*2);
    for(int i=alpha;i<beta;++i)
    {
        float rad=i*0.5*DEG2RAD;
        float rad2=(i+1)*0.5;
        while (rad2>=360) rad2-=360;
        rad2*=DEG2RAD;
        glVertex2f(cos(rad)*radiusX+x,sin(rad)*radiusY+y);
        glVertex2f(cos(rad2)*radiusX+x,sin(rad2)*radiusY+y);
        glVertex2f(x,y);
    }
}
void drawGridSquare(int x, int y, double colour_r, double colour_g, double colour_b, double thickness)
{
    double x1=double(x)/FIELD_RADIUS;
    double y1=double(y)/FIELD_RADIUS;
    double x2=x1+1.0/FIELD_RADIUS;
    double y2=y1+1.0/FIELD_RADIUS;

    glColor3f(colour_r,colour_g,colour_b);

    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);

    glColor3f(BACKGROUND_COLOUR_R,BACKGROUND_COLOUR_G,BACKGROUND_COLOUR_B);

    x1+=thickness/FIELD_RADIUS;
    y1+=thickness/FIELD_RADIUS;
    x2-=thickness/FIELD_RADIUS;
    y2-=thickness/FIELD_RADIUS;

    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
}
void drawGrid(double colour_r, double colour_g, double colour_b, double thickness)
{
    glBegin(GL_QUADS);

    for (int i=-FIELD_RADIUS;i<FIELD_RADIUS;++i)
    {
        for (int j=-FIELD_RADIUS;j<FIELD_RADIUS;++j)
        {
            drawGridSquare(i,j,colour_r,colour_g,colour_b,thickness);
        }
    }

    glEnd();
}
void drawSnake(snake& s, bool selected)
{
    if (s.blocks.empty()) return;

    point bl;
    double x,y,x2,y2;
    double r,g,b;
    r=s.colour_r;
    g=s.colour_g;
    b=s.colour_b;

    if (selected)
    {
        if (r>0.5) r-=0.5;
        else r+=0.5;
        if (g>0.5) g-=0.5;
        else g+=0.5;
        if (b>0.5) b-=0.5;
        else b+=0.5;
    }

    if (!s.dead) glColor3f(r*0.75,g*0.75,b*0.75);
    else glColor3f(r,g,b);

    glBegin(GL_QUADS);

    bl=s.blocks[0];
    x=bl.x;
    y=bl.y;
    x/=FIELD_RADIUS;
    y/=FIELD_RADIUS;
    x2=x+1.0/FIELD_RADIUS;
    y2=y+1.0/FIELD_RADIUS;
    glVertex2f(x,y);
    glVertex2f(x2,y);
    glVertex2f(x2,y2);
    glVertex2f(x,y2);

    glEnd();

    glColor3f(r,g,b);

    glBegin(GL_QUADS);

    for (int i=1;i<s.blocks.size();++i)
    {
        bl=s.blocks[i];
        x=bl.x;
        y=bl.y;
        x/=FIELD_RADIUS;
        y/=FIELD_RADIUS;
        x2=x+1.0/FIELD_RADIUS;
        y2=y+1.0/FIELD_RADIUS;
        glVertex2f(x,y);
        glVertex2f(x2,y);
        glVertex2f(x2,y2);
        glVertex2f(x,y2);
    }

    glEnd();
}
void drawFood(food& f)
{
    double x,y,x2,y2;

    glColor3f(f.colour_r,f.colour_g,f.colour_b);

    glBegin(GL_QUADS);

    x=f.x;
    y=f.y;
    x/=FIELD_RADIUS;
    y/=FIELD_RADIUS;
    x2=x+1.0/FIELD_RADIUS;
    y2=y+1.0/FIELD_RADIUS;
    glVertex2f(x,y);
    glVertex2f(x2,y);
    glVertex2f(x2,y2);
    glVertex2f(x,y2);

    glEnd();
}
void drawWindow(GLFWwindow* w, std::vector<snake>& snakes, std::vector<food>& foods, int mode, int selected)
{
    glfwSetWindowShouldClose(w,0);
    pressed=-1;

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

    //drawGrid(0.1,0.1,0.1,0.1);
    for (int i=0;i<snakes.size();++i)
    {
        if (mode==0 || (mode==1 && snakes[i].dead==0) || (mode==2 && snakes[i].dead>0) || (mode==3 && snakes[i].dead<0)) drawSnake(snakes[i],selected==i);
    }
    for (int i=0;i<foods.size();++i)
    {
        if (mode==0) drawFood(foods[i]);
    }

    glfwSwapBuffers(w);
}
