//Evolving Snakes
#include<iostream>
#include<vector>
#include<queue>
#include<math.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<GLFW/glfw3.h>
using namespace std;

queue<int> presses;

const double DEG2RAD=3.14159/180.0;
const int ORIGINAL_WINDOWS_WIDTH=1000;
const int ORIGINAL_WINDOWS_HEIGHT=1000;
int WINDOWS_WIDTH=ORIGINAL_WINDOWS_WIDTH;
int WINDOWS_HEIGHT=ORIGINAL_WINDOWS_HEIGHT;
const double BACKGROUND_COLOUR_R=0;
const double BACKGROUND_COLOUR_G=0;
const double BACKGROUND_COLOUR_B=0;
double FOOD_COLOUR_R=0.1;
double FOOD_COLOUR_G=1;
double FOOD_COLOUR_B=0.05;
const int FIELD_RADIUS=20;
int ENERGY_LOSS_SPEED=100;

int pressed;
double mxpos=0,mypos=0;
struct point
{
    int x;
    int y;
    void operator+= (int dir)
    {
        if (dir%4==0) y+=dir/4+1;
        if (dir%4==1) x+=dir/4+1;
        if (dir%4==2) y-=dir/4+1;
        if (dir%4==3) x-=dir/4+1;
    }
    bool operator== (point a)
    {
        if (x==a.x && y==a.y) return 1;
        return 0;
    }
    void randomise()
    {
        x=rand()%(2*FIELD_RADIUS)-FIELD_RADIUS;
        y=rand()%(2*FIELD_RADIUS)-FIELD_RADIUS;
    }
};
struct block:point
{
    int food;
};
struct snake
{
    vector<block> blocks;
    double colour_r, colour_g, colour_b;
    int direction;
    int to_next_loss;
    double defence,attack;
    bool dead;
    snake()
    {
        dead=0;
        blocks.resize(1);
        blocks[0].x=0;
        blocks[0].y=0;
        direction=0;
        attack=0.5;
        defence=1-attack;
        colour_r=attack;
        colour_g=1;
        colour_b=1;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    snake(int food)
    {
        dead=0;
        blocks.resize(1);
        blocks[0].x=0;
        blocks[0].y=0;
        blocks[0].food=food;
        direction=0;
        attack=0.5;
        defence=1-attack;
        colour_r=attack;
        colour_g=1;
        colour_b=1;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    snake(double new_attack, int food)
    {
        dead=0;
        blocks.resize(1);
        blocks[0].x=0;
        blocks[0].y=0;
        blocks[0].food=food;
        direction=0;
        attack=new_attack;
        defence=1-attack;
        colour_r=attack;
        colour_g=1;
        colour_b=1;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    snake(double new_attack, double new_green, double new_blue, int food)
    {
        dead=0;
        blocks.resize(1);
        blocks[0].x=0;
        blocks[0].y=0;
        blocks[0].food=food;
        direction=0;
        attack=new_attack;
        defence=1-attack;
        colour_r=attack;
        colour_g=new_green;
        colour_b=new_blue;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    snake(int new_x, int new_y, int new_dir, double new_attack, double new_green, double new_blue)
    {
        dead=0;
        blocks.resize(1);
        blocks[0].x=new_x;
        blocks[0].y=new_y;
        direction=new_dir;
        attack=new_attack;
        defence=1-attack;
        colour_r=attack;
        colour_g=new_green;
        colour_b=new_blue;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    snake(int new_x, int new_y, int new_dir, double new_attack, double new_green, double new_blue, int food)
    {
        dead=0;
        blocks.resize(1);
        blocks[0].x=new_x;
        blocks[0].y=new_y;
        blocks[0].food=food;
        direction=new_dir;
        attack=new_attack;
        defence=1-attack;
        colour_r=attack;
        colour_g=new_green;
        colour_b=new_blue;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    void randomise()
    {
        dead=0;
        blocks.resize(1);
        blocks[0].randomise();
        blocks[0].food=0;
        direction=rand()%4;
        attack=rand()%1001/1000.0;
        defence=1-attack;
        colour_r=attack;
        colour_g=rand()%1001/1000.0;
        colour_b=rand()%1001/1000.0;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    void randomise(int food)
    {
        dead=0;
        blocks.resize(1);
        blocks[0].randomise();
        blocks[0].food=food;
        direction=rand()%4;
        attack=rand()%1001/1000.0;
        defence=1-attack;
        colour_r=attack;
        colour_g=rand()%1001/1000.0;
        colour_b=rand()%1001/1000.0;
        to_next_loss=ENERGY_LOSS_SPEED;
    }
    bool moveForward()
    {
        if (dead) return 0;
        block new_pos=blocks[blocks.size()-1];
        for (int i=blocks.size()-1;i>0;--i)
        {
            blocks[i]=blocks[i-1];
        }
        blocks[0].food=0;
        blocks[0]+=direction;
        --to_next_loss;
        if (to_next_loss==0)
        {
            --blocks[0].food;
            to_next_loss=ENERGY_LOSS_SPEED;
        }
        if (blocks[0].x>=FIELD_RADIUS) blocks[0].x=-FIELD_RADIUS;
        if (blocks[0].y>=FIELD_RADIUS) blocks[0].y=-FIELD_RADIUS;
        if (blocks[0].x<-FIELD_RADIUS) blocks[0].x=FIELD_RADIUS-1;
        if (blocks[0].y<-FIELD_RADIUS) blocks[0].y=FIELD_RADIUS-1;
        if (new_pos.food>0)
        {
            --new_pos.food;
            blocks.push_back(new_pos);
        }
        if (blocks[blocks.size()-1].food<0)
        {
            if (blocks.size()>1)
            {
                blocks[blocks.size()-2].food+=blocks[blocks.size()-1].food+1;
                blocks.resize(blocks.size()-1);
            }
            else
            {
                dead=1;
                blocks.resize(0);
                return 1;
            }
        }
        return 0;
    }
    void eat()
    {
        ++blocks[0].food;
    }
    bool getBit(int node, double enemy_attack)
    {
        if (node!=0)
        {
            if (enemy_attack>defence)
            {
                blocks.resize(node);
            }
        }
        else
        {
            if (enemy_attack>defence)
            {
                dead=1;
                blocks.resize(0);
                return 1;
            }
        }
        return 0;
    }
    void bite(double enemy_defence)
    {
        cout<<enemy_defence<<" "<<attack<<endl;
        if (enemy_defence>=attack)
        {
            dead=1;
        }
        else
        {
            eat();
        }
    }
};

//Graphics related functions
GLFWwindow* window;
void errorCallback(int error, const char* description)
{
    cout<<error<<": "<<description<<endl;
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS) glfwSetWindowShouldClose(window,1);
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
string setCallbacks(GLFWwindow* w)
{
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(w,keyCallback);
    glfwSetMouseButtonCallback(w,mouseButtonCallback);
    glfwSetWindowSizeCallback(w,windowSizeCallback);
    return "Callbacks set successfully.";
}
string initializeGLFW()
{
    if (!glfwInit())
        return "Unable to initialize GLFW.";
    return "GLFW initialized successfully.";
}
string createWindow(GLFWwindow*& w)
{
    w=glfwCreateWindow(WINDOWS_WIDTH,WINDOWS_HEIGHT,"Evolving Snakes",NULL,NULL);
    if (!w)
    {
        glfwTerminate();
        return "Unable to open window.";
    }
    return "Window created successfully.";
}
void stopGraphics()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

//Draw functions
void drawPartEllipse(float x, float y, float radiusX, float radiusY, double alpha, double beta)
{
    alpha=round(alpha*2);
    beta=round(beta*2);
    glBegin(GL_TRIANGLES);
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
    glEnd();
}
void drawSnake(snake& s)
{
    if (s.blocks.empty()) return;

    point bl;
    double x,y,x2,y2;

    glColor3f(s.colour_r*0.75,s.colour_g*0.75,s.colour_b*0.75);

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

    glColor3f(s.colour_r,s.colour_g,s.colour_b);

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
void drawFood(point& f)
{
    point bl;
    double x,y,x2,y2;

    glColor3f(FOOD_COLOUR_R, FOOD_COLOUR_G, FOOD_COLOUR_B);

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
void drawWindow(GLFWwindow* w, vector<snake>& snakes, vector<point>& foods)
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

    for (int i=0;i<snakes.size();++i)
    {
        drawSnake(snakes[i]);
    }
    for (int i=0;i<foods.size();++i)
    {
        drawFood(foods[i]);
    }

    glfwSwapBuffers(w);
}
typedef vector<pair<int, int> > field[2*FIELD_RADIUS][2*FIELD_RADIUS];
void generateField(field& field, vector<snake>& snakes, vector<point>& foods)
{
    pair<int, int> curr;
    for (int i=0;i<2*FIELD_RADIUS;++i)
    {
        for (int j=0;j<2*FIELD_RADIUS;++j)
        {
            field[i][j].resize(0);
        }
    }
    for (int i=0;i<foods.size();++i)
    {
        curr.first=i;
        curr.second=-1;
        field[foods[i].x+FIELD_RADIUS][foods[i].y+FIELD_RADIUS].push_back(curr);
    }
    for (int i=0;i<snakes.size();++i)
    {
        for (int j=0;j<snakes[i].blocks.size()-1;++j)
        {
            curr.first=i;
            curr.second=j+1;
            field[snakes[i].blocks[j].x+FIELD_RADIUS][snakes[i].blocks[j].y+FIELD_RADIUS].push_back(curr);
        }
    }
}
double attack,blue,green;
void run(GLFWwindow* w)
{
    srand(time(NULL));
    vector<snake> snakes;
    vector<point> foods;
    field field;
    int x,y;
    pair<int, int> curr_square;
    point curr_food;

    cout<<"Enter attack (0-1): ";
    cin>>attack;
    cout<<"Enter blue (0-1): ";
    cin>>blue;
    cout<<"Enter green (0-1): ";
    cin>>green;

    snake s(attack,green,blue,3);
    cout<<s.attack<<" "<<s.defence<<endl;
    snakes.push_back(s);
    for (int i=0;i<5;++i)
    {
        s.randomise(3);
        snakes.push_back(s);
    }
    clock_t start_time,curr_time;
    while (!glfwWindowShouldClose(w))
    {
        start_time=clock();
        drawWindow(w,snakes,foods);
        if (rand()*rand()%100000<=double(100000)*FIELD_RADIUS*FIELD_RADIUS/6000)
        {
            curr_food.randomise();
            foods.push_back(curr_food);
        }
        if (rand()*rand()%100000<=double(100000)*FIELD_RADIUS*FIELD_RADIUS/60000)
        {
            s.randomise(3);
            snakes.push_back(s);
        }
        if (!presses.empty() && !snakes.empty())
        {
            if ((snakes[0].direction+presses.front())%2)
                snakes[0].direction=presses.front();
            presses.pop();
        }
        generateField(field,snakes,foods);
        for (int i=0;i<snakes.size();++i)
        {
            if (i!=0 && rand()%8==0)
            {
                if (rand()%2) ++snakes[i].direction;
                else  ++snakes[i].direction;
                snakes[i].direction+=4;
                snakes[i].direction%=4;
            }
            if (snakes[i].moveForward())
            {
                snakes.erase(snakes.begin()+i);
            }
        }
        for (int i=0;i<snakes.size();++i)
        {
            x=snakes[i].blocks[0].x;
            y=snakes[i].blocks[0].y;
            for (int j=0;j<field[x+FIELD_RADIUS][y+FIELD_RADIUS].size();++j)
            {
                curr_square=field[x+FIELD_RADIUS][y+FIELD_RADIUS][j];
                if (curr_square.second==-1)
                {
                    foods.erase(foods.begin()+curr_square.first);
                    field[x+FIELD_RADIUS][y+FIELD_RADIUS].erase(field[x+FIELD_RADIUS][y+FIELD_RADIUS].begin()+j);
                    snakes[i].eat();
                }
                else if (curr_square.second==-2)
                {
                    snakes[i].bite(10);
                }
                else if (curr_square.second!=0)
                {
                    cout<<i<<" "<<curr_square.first<<" "<<curr_square.second<<" "<<snakes[i].attack<<endl;
                    if (snakes[curr_square.first].getBit(curr_square.second,snakes[i].attack))
                    {
                        ///TODO create a destroy vector and also remove the eaten part of the snake
                        snakes.erase(snakes.begin()+i);
                        break;
                    }
                    snakes[i].bite(snakes[curr_square.first].defence);
                }
                else
                {
                    if (curr_square.first!=i)
                    {
                        x=curr_square.first;
                        y=i;
                        if (snakes[x].attack<snakes[y].attack)
                        {
                            swap(x,y);
                        }
                        if (snakes[y].getBit(0,snakes[x].attack))
                        {
                            ///TODO create a destroy vector and also remove the eaten part of the snake
                            snakes.erase(snakes.begin()+i);
                            break;
                        }
                        snakes[x].bite(snakes[y].defence);
                    }
                }
            }
        }
        do
        {
            glfwPollEvents();
            curr_time=clock();
        }
        while(!glfwWindowShouldClose(w) && double(curr_time-start_time)/CLOCKS_PER_SEC<0.1);
    }
}
int main()
{
    system("cls");

    string message;
    message=initializeGLFW();
    //cout<<message<<endl;
    if (message!="GLFW initialized successfully.") return -1;

    message=createWindow(window);
    //cout<<message<<endl;
    if (message!="Window created successfully.") return -1;

    message=setCallbacks(window);
    //cout<<message<<endl;
    if (message!="Callbacks set successfully.") return -1;

    //system("cls");
    run(window);

    stopGraphics();
    return 0;
}
