#include "../headers/run.h"
#include "../headers/snake.h"
#include "../headers/ctrRandom.h"
#include "../headers/ctrBasic.h"
#include "../headers/ctrNeuralNetwork.h"
#include "../headers/sight.h"
#include "../headers/draw.h"
#include "../headers/draw_neural_net.h"
#include "../headers/window_functions.h"
#include "../headers/randomisation.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<conio.h>
#include<chrono>

using namespace std;
using namespace chrono;

double FOOD_PROBABILITY=0.000067;
double MAX_FOOD_PART=32;
double SNAKE_PROBABILITY=0.000002;

const int SEED=2;

void generateField(field& field, vector<snake>& snakes, vector<food>& foods)
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
        for (int j=0;j<snakes[i].blocks.size();++j)
        {
            curr.first=i;
            curr.second=j;
            field[snakes[i].blocks[j].x+FIELD_RADIUS][snakes[i].blocks[j].y+FIELD_RADIUS].push_back(curr);
        }
    }
}
controller* selectRandomController()
{
    //int res=rand()%2;
    //if (res<4) return new ctrRandom();
    //if (res) return new ctrNeuralNetwork({0});
    return new ctrNeuralNetwork({2,15,15});
    //return new ctrBasic();
}
vector<snake> snakes[2];
vector<food> foods[2];
vector<pair<int, int> > curr;
pair<int, vector<block> > res;
vector<int> removed_snakes;
vector<int> removed_foods;
bool cv; //current vector
int snakes_alive;
vector<double> values;
void saveData()
{
    string filename;
    cin>>filename;
    ofstream file(filename.c_str());
    file<<FIELD_RADIUS<<' ';
    file<<controller::VF_RADIUS<<' ';
    file<<controller::VS_RADIUS<<' ';
    file<<FOOD_PROBABILITY<<' ';
    file<<MAX_FOOD_PART<<' ';
    file<<SNAKE_PROBABILITY<<' ';
    file<<snake::ENERGY_LOSS_SPEED<<' ';
    file<<snake::DECOMPOSITION_SPEED<<' ';
    file<<snake::BIRTH_SPEED<<' ';
    file<<snake::DEFENCE_MULTIPLIER<<' ';
    file<<snake::DEFENCE_ADDER<<' ';
    file<<snake::MIN_SPLIT_LENGTH<<' ';
    file<<snake::MIN_LENGTH<<' ';
    file<<MAX_MUTATION<<' ';
    file<<foods[cv].size()<<' ';
    for (int i=0;i<foods[cv].size();++i)
    {
        file<<foods[cv][i].colour_r<<' '<<foods[cv][i].colour_g<<' '<<foods[cv][i].colour_b<<' '<<foods[cv][i].x<<' '<<foods[cv][i].y<<' ';
    }
    file<<snakes[cv].size()<<' ';
    for (int i=0;i<snakes[cv].size();++i)
    {
        file<<snakes[cv][i].attack<<' '<<snakes[cv][i].defence<<' '<<snakes[cv][i].colour_r<<' '<<snakes[cv][i].colour_g<<' '<<snakes[cv][i].colour_b<<' '<<snakes[cv][i].dead<<' '<<snakes[cv][i].to_next_loss<<' ';
        file<<snakes[cv][i].blocks.size()<<' ';
        for (int j=0;j<snakes[cv][i].blocks.size();++j)
        {
            file<<snakes[cv][i].blocks[j].x<<' '<<snakes[cv][i].blocks[j].y<<' '<<snakes[cv][i].blocks[j].food<<' ';
        }
        if (snakes[cv][i].dead<0) continue;
        file<<snakes[cv][i].ctr->getType()<<' ';
        values=snakes[cv][i].ctr->getValues();
        for (int j=0;j<values.size();++j)
        {
            file<<values[j]<<' ';
        }
        file<<"end"<<' ';
    }
}
void resetData()
{
    foods[cv].resize(0);
    snakes[cv].resize(0);
    char answer;
    cout<<"Change settings? (Y/N): ";
    cin>>answer;
    if (answer!='y' && answer!='Y') return;
    cout<<"Probability of food appearing ("<<FOOD_PROBABILITY<<"): ";
    cin>>FOOD_PROBABILITY;
    cout<<"Maximum food concentration (1/x) ("<<MAX_FOOD_PART<<"): ";
    cin>>MAX_FOOD_PART;
    cout<<"Probability of snake appearing ("<<SNAKE_PROBABILITY<<"): ";
    cin>>SNAKE_PROBABILITY;
    cout<<"Energy loss speed (1/x) ("<<snake::ENERGY_LOSS_SPEED<<"): ";
    cin>>snake::ENERGY_LOSS_SPEED;
    cout<<"Decomposition speed (1/x) ("<<snake::DECOMPOSITION_SPEED<<"): ";
    cin>>snake::DECOMPOSITION_SPEED;
    cout<<"Birth speed (1/x) ("<<snake::BIRTH_SPEED<<"): ";
    cin>>snake::BIRTH_SPEED;
    cout<<"Defence multiplier ("<<snake::DEFENCE_MULTIPLIER<<"): ";
    cin>>snake::DEFENCE_MULTIPLIER;
    cout<<"Defence adder ("<<snake::DEFENCE_ADDER<<"): ";
    cin>>snake::DEFENCE_ADDER;
    cout<<"Minimum length to split ("<<snake::MIN_SPLIT_LENGTH<<"): ";
    cin>>snake::MIN_SPLIT_LENGTH;
    cout<<"Minimum length of split part ("<<snake::MIN_LENGTH<<"): ";
    cin>>snake::MIN_LENGTH;
    cout<<"Maximum mutation ("<<MAX_MUTATION<<"): ";
    cin>>MAX_MUTATION;
}
void loadData(string filename="", bool first=1)
{
    bool only_settings=0;
    bool no_settings=0;
    if (filename=="") cin>>filename;
    if (filename=="") return;
    if (filename[0]=='/')
    {
        filename=filename.substr(1);
    }
    else if (filename[0]=='-')
    {
        only_settings=1;
        filename=filename.substr(1);
        if (filename!="" && filename[0]=='+')
        {
            only_settings=0;
            no_settings=1;
            filename=filename.substr(1);
        }
    }
    for (int i=0;i<filename.size();++i)
    {
        if (filename[i]=='+')
        {
            first=0;
            if (i<filename.size()-1) loadData(filename.substr(i+1),i);
            filename=filename.substr(0,i);
            break;
        }
    }
    ifstream file(filename.c_str());
    if (!file) return;
    int s;
    double s2;
    string type;
    string in="";
    file>>s;
    if (s!=FIELD_RADIUS) return;
    file>>s;
    if (s!=controller::VF_RADIUS) return;
    file>>s;
    if (s!=controller::VS_RADIUS) return;
    if (no_settings)
    {
        file>>s2;
        file>>s2;
        file>>s2;
        file>>s;
        file>>s;
        file>>s;
        file>>s2;
        file>>s2;
        file>>s;
        file>>s;
        file>>s2;
    }
    else
    {
        file>>FOOD_PROBABILITY;
        file>>MAX_FOOD_PART;
        file>>SNAKE_PROBABILITY;
        file>>snake::ENERGY_LOSS_SPEED;
        file>>snake::DECOMPOSITION_SPEED;
        file>>snake::BIRTH_SPEED;
        file>>snake::DEFENCE_MULTIPLIER;
        file>>snake::DEFENCE_ADDER;
        file>>snake::MIN_SPLIT_LENGTH;
        file>>snake::MIN_LENGTH;
        file>>MAX_MUTATION;
    }
    if (only_settings)
    {
        if (first)
        {
            foods[cv].resize(0);
            snakes[cv].resize(0);
        }
        return;
    }
    int start;
    start=0;
    file>>s;
    if (first) foods[cv].resize(s);
    else
    {
        start=foods[cv].size();
        foods[cv].resize(start+s);
    }
    for (int i=start;i<foods[cv].size();++i)
    {
        file>>foods[cv][i].colour_r>>foods[cv][i].colour_g>>foods[cv][i].colour_b>>foods[cv][i].x>>foods[cv][i].y;
    }
    file>>s;
    start=0;
    if (first) snakes[cv].resize(s);
    else
    {
        start=snakes[cv].size();
        snakes[cv].resize(start+s);
    }
    for (int i=start;i<snakes[cv].size();++i)
    {
        file>>snakes[cv][i].attack>>snakes[cv][i].defence>>snakes[cv][i].colour_r>>snakes[cv][i].colour_g>>snakes[cv][i].colour_b>>snakes[cv][i].dead>>snakes[cv][i].to_next_loss;
        file>>s;
        snakes[cv][i].blocks.resize(s);
        for (int j=0;j<snakes[cv][i].blocks.size();++j)
        {
            file>>snakes[cv][i].blocks[j].x>>snakes[cv][i].blocks[j].y>>snakes[cv][i].blocks[j].food;
        }
        if (snakes[cv][i].dead<0) continue;
        file>>type;
        file>>in;
        values.resize(0);
        while (in!="end")
        {
            values.push_back(atof(in.c_str()));
            file>>in;
        }
        if (type=="random") snakes[cv][i].ctr=new ctrRandom();
        else if (type=="basic") snakes[cv][i].ctr=new ctrBasic();
        else if (type=="neuralNetwork") snakes[cv][i].ctr=new ctrNeuralNetwork();
        else snakes[cv][i].ctr=new ctrRandom();
        snakes[cv][i].ctr->setValues(values);
    }
}
void run(GLFWwindow* sim, GLFWwindow* net)
{
    srand(SEED);
    field field;
    int x,y;
    point p;
    food curr_food;
    int food_gained;
    double speed=0.03;
    int player=-1;
    int curr_net=-1;
    double attack,blue,green;
    int flashing=0;
    int benchmark_counter=0;

    /*cout<<"Enter attack (0-1): ";
    cin>>attack;
    cout<<"Enter blue (0-1): ";
    cin>>blue;
    cout<<"Enter green (0-1): ";
    cin>>green;*/

    //snake s(attack,green,blue,3);
    //snake s(0,1,1,3);
    //snakes.push_back(s);

    snake s;
    for (int i=0;i<5;++i)
    {
        s.randomise(3,selectRandomController());
        snakes[cv].push_back(s);
    }
    high_resolution_clock::time_point start_time,curr_time,benchmark_start_time;
    start_time=high_resolution_clock::now();
    benchmark_start_time=start_time;
    while (!glfwWindowShouldClose(sim) && !glfwWindowShouldClose(net))
    {
        ++benchmark_counter;
        if (benchmark_counter==1000)
        {
            curr_time=high_resolution_clock::now();
            cout<<"Time for last 1000 steps: "<<duration_cast<duration<double>>(curr_time-benchmark_start_time).count()<<'\n';
            benchmark_start_time=curr_time;
            benchmark_counter=0;
        }
        flashing=(flashing+1)%10;
        if (curr_net>=snakes[cv].size()) curr_net=-1;
        if (new_neural_network || curr_net==-1 || snakes[cv][curr_net].dead || snakes[cv][curr_net].ctr->getType()!="neuralNetwork")
        {
            int start_net=curr_net;
            ++curr_net;
            bool success=0;
            for (;curr_net<snakes[cv].size();++curr_net)
            {
                if (!snakes[cv][curr_net].dead && snakes[cv][curr_net].ctr->getType()=="neuralNetwork")
                {
                    success=1;
                    break;
                }
            }
            if (!success)
            {
                for (curr_net=0;curr_net<=start_net;++curr_net)
                {
                    if (!snakes[cv][curr_net].dead && snakes[cv][curr_net].ctr->getType()=="neuralNetwork")
                    {
                        success=1;
                        break;
                    }
                }
            }
            if (!success)
            {
                curr_net=-1;
            }
            new_neural_network=0;
        }
        if (curr_net!=-1) values=snakes[cv][curr_net].ctr->getValues();
        else values={};
        if (draw_neural_net) drawNetWindow(net,values,draw_neural_net_mode);
        if (draw_sim) drawWindow(sim,snakes[cv],foods[cv],flashing<5 && draw_neural_net?curr_net:-1);
        do
        {
            glfwPollEvents();
            curr_time=high_resolution_clock::now();
        }
        while(!glfwWindowShouldClose(sim) && !glfwWindowShouldClose(net) && duration_cast<duration<double>>(curr_time-start_time).count()<speed);
        if (change_settings)
        {
            cin>>speed;
            glfwPollEvents();
            change_settings=0;
            save_data=0;
            load_data=0;
            reset=0;
        }
        if (save_data)
        {
            saveData();
            glfwPollEvents();
            change_settings=0;
            save_data=0;
            load_data=0;
            reset=0;
        }
        if (load_data)
        {
            loadData();
            glfwPollEvents();
            change_settings=0;
            save_data=0;
            load_data=0;
            reset=0;
        }
        if (reset)
        {
            resetData();
            glfwPollEvents();
            change_settings=0;
            save_data=0;
            load_data=0;
            reset=0;
        }
        if (paused) continue;
        start_time=high_resolution_clock::now();
        generateField(field,snakes[cv],foods[cv]);
        for (int i=0;i<2*FIELD_RADIUS;++i)
        {
            for (int j=0;j<2*FIELD_RADIUS;++j)
            {
                if (field[i][j].empty())
                {
                    if (((1LL*RAND_MAX*rand()+rand())*RAND_MAX+rand())%10000000LL/double(10000000)<FOOD_PROBABILITY*(1-MAX_FOOD_PART*double(foods[cv].size())/4/FIELD_RADIUS/FIELD_RADIUS))
                    {
                        curr_food=food(i-FIELD_RADIUS,j-FIELD_RADIUS);
                        field[i][j].push_back(make_pair(foods[cv].size(),-1));
                        foods[cv].push_back(curr_food);
                    }
                }
            }
        }
        for (int i=0;i<2*FIELD_RADIUS;++i)
        {
            for (int j=0;j<2*FIELD_RADIUS;++j)
            {
                if (field[i][j].empty())
                {
                    if (((1LL*RAND_MAX*rand()+rand())*RAND_MAX+rand())%10000000LL/double(10000000)<SNAKE_PROBABILITY)
                    {
                        s.randomise(3,selectRandomController());
                        s.blocks[0].x=i-FIELD_RADIUS;
                        s.blocks[0].y=j-FIELD_RADIUS;
                        field[i][j].push_back(make_pair(snakes[cv].size(),0));
                        snakes[cv].push_back(s);
                    }
                }
            }
        }
        player=-1;
        if (control)
        {
            for (int i=0;i<snakes[cv].size();++i)
            {
                if (!snakes[cv][i].dead)
                {
                    player=i;
                    break;
                }
            }
        }
        if (!presses.empty())
        {
            if (player>=0 && (snakes[cv][player].direction+presses.front())%2)
            {
                snakes[cv][player].direction=presses.front();
            }
            presses.pop();
        }
        for (int i=0;i<snakes[cv].size();++i)
        {
            if (snakes[cv][i].blocks.empty())
            {
                removed_snakes.push_back(i);
                continue;
            }
            if (snakes[cv][i].dead) continue;
            seeAll(field,snakes[cv][i]);
            if (i!=player)
            {
                res=snakes[cv][i].think();
                if (!res.second.empty())
                {
                    s=snakes[cv][i];
                    s.birth();
                    s.blocks=res.second;
                    s.direction=res.first;
                    snakes[cv].push_back(s);
                    for (int j=0;j<res.second.size();++j)
                    {
                        x=res.second[j].x;
                        y=res.second[j].y;
                        for (int k=0;k<field[x+FIELD_RADIUS][y+FIELD_RADIUS].size();++k)
                        {
                            if (field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].first==i && field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].second!=-1)
                            {
                                field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].first=snakes[cv].size()-1;
                                field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].second=j;
                            }
                        }
                    }
                }
            }
            p=snakes[cv][i].blocks[0];
            p+=snakes[cv][i].direction;
            x=p.x;
            y=p.y;
            for (int j=0;j<field[x+FIELD_RADIUS][y+FIELD_RADIUS].size();++j)
            {
                if (field[x+FIELD_RADIUS][y+FIELD_RADIUS][j].second!=-1)
                {
                    int curr_snake=field[x+FIELD_RADIUS][y+FIELD_RADIUS][j].first;
                    if (field[x+FIELD_RADIUS][y+FIELD_RADIUS][j].second!=0 || snakes[cv][curr_snake].dead)
                    {
                        if (snakes[cv][i].attack<=snakes[cv][curr_snake].defence)
                        {
                            snakes[cv][i].die(0);
                            break;
                        }
                    }
                    else
                    {
                        if (snakes[cv][i].attack==snakes[cv][curr_snake].attack ||
                        (snakes[cv][i].attack<snakes[cv][curr_snake].attack && (4+snakes[cv][i].direction-2)%4!=snakes[cv][curr_snake].direction && curr_snake>i))
                        {
                            if (snakes[cv][i].attack==snakes[cv][curr_snake].attack && (4+snakes[cv][i].direction-2)%4==snakes[cv][curr_snake].direction)
                            {
                                snakes[cv][curr_snake].die(0);
                            }
                            snakes[cv][i].die(0);
                            break;
                        }
                    }
                }
            }
            if (snakes[cv][i].dead) continue;
            for (int j=0;j<snakes[cv][i].blocks.size();++j)
            {
                x=snakes[cv][i].blocks[j].x;
                y=snakes[cv][i].blocks[j].y;
                for (int k=0;k<field[x+FIELD_RADIUS][y+FIELD_RADIUS].size();++k)
                {
                    if (field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].first==i && field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].second==j)
                    {
                        field[x+FIELD_RADIUS][y+FIELD_RADIUS].erase(field[x+FIELD_RADIUS][y+FIELD_RADIUS].begin()+k);
                        --k;
                    }
                }
            }
            snakes[cv][i].moveForward();
            if (snakes[cv][i].blocks.empty())
            {
                removed_snakes.push_back(i);
                continue;
            }
            for (int j=0;j<snakes[cv][i].blocks.size();++j)
            {
                x=snakes[cv][i].blocks[j].x;
                y=snakes[cv][i].blocks[j].y;
                field[x+FIELD_RADIUS][y+FIELD_RADIUS].push_back(make_pair(i,j));
            }
            p=snakes[cv][i].blocks[0];
            x=p.x;
            y=p.y;
            for (int j=0;j<field[x+FIELD_RADIUS][y+FIELD_RADIUS].size();++j)
            {
                if (field[x+FIELD_RADIUS][y+FIELD_RADIUS][j].second==-1)
                {
                    int f=field[x+FIELD_RADIUS][y+FIELD_RADIUS][j].first;
                    removed_foods.push_back(f);
                    snakes[cv][i].eat();
                    field[x+FIELD_RADIUS][y+FIELD_RADIUS].erase(field[x+FIELD_RADIUS][y+FIELD_RADIUS].begin()+j);
                    --j;
                }
                else
                {
                    int curr_snake=field[x+FIELD_RADIUS][y+FIELD_RADIUS][j].first;
                    int curr_node=field[x+FIELD_RADIUS][y+FIELD_RADIUS][j].second;
                    if (curr_node!=0 || snakes[cv][curr_snake].dead)
                    {
                        res=snakes[cv][curr_snake].getBit(curr_node,snakes[cv][i].attack);
                        food_gained=res.first;
                        if (!res.second.empty())
                        {
                            s=snakes[cv][curr_snake];
                            s.blocks=res.second;
                            if (s.dead>=0) s.die(1);
                            snakes[cv].push_back(s);
                            for (int k=0;k<s.blocks.size();++k)
                            {
                                int x2=s.blocks[k].x;
                                int y2=s.blocks[k].y;
                                for (int kk=0;kk<field[x2+FIELD_RADIUS][y2+FIELD_RADIUS].size();++kk)
                                {
                                    if (field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].first==curr_snake && field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].second!=-1)
                                    {
                                        field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].first=snakes[cv].size()-1;
                                        field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].second=k;
                                    }
                                }
                            }
                        }
                        snakes[cv][i].bite(snakes[cv][curr_snake].defence);
                        snakes[cv][i].eat(food_gained);
                        if (!snakes[cv][i].dead)
                        {
                            field[x+FIELD_RADIUS][y+FIELD_RADIUS].erase(field[x+FIELD_RADIUS][y+FIELD_RADIUS].begin()+j);
                            --j;
                        }
                    }
                    else if (curr_snake!=i)
                    {
                        res=snakes[cv][curr_snake].getBit(curr_node,snakes[cv][i].attack);
                        food_gained=res.first;
                        if (!res.second.empty())
                        {
                            s=snakes[cv][curr_snake];
                            s.blocks=res.second;
                            if (s.dead>=0) s.die(1);
                            snakes[cv].push_back(s);
                            for (int k=0;k<s.blocks.size();++k)
                            {
                                int x2=s.blocks[k].x;
                                int y2=s.blocks[k].y;
                                for (int kk=0;kk<field[x2+FIELD_RADIUS][y2+FIELD_RADIUS].size();++kk)
                                {
                                    if (field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].first==curr_snake && field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].second!=-1)
                                    {
                                        field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].first=snakes[cv].size()-1;
                                        field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].second=k;
                                    }
                                }
                            }
                        }
                        snakes[cv][i].eat(food_gained);
                        res=snakes[cv][i].getBit(curr_node,snakes[cv][curr_snake].attack);
                        food_gained=res.first;
                        if (!res.second.empty())
                        {
                            s=snakes[cv][i];
                            s.blocks=res.second;
                            if (s.dead>=0) s.die(1);
                            snakes[cv].push_back(s);
                            for (int k=0;k<s.blocks.size();++k)
                            {
                                int x2=s.blocks[k].x;
                                int y2=s.blocks[k].y;
                                for (int kk=0;kk<field[x2+FIELD_RADIUS][y2+FIELD_RADIUS].size();++kk)
                                {
                                    if (field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].first==i && field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].second!=-1)
                                    {
                                        field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].first=snakes[cv].size()-1;
                                        field[x2+FIELD_RADIUS][y2+FIELD_RADIUS][kk].second=k;
                                    }
                                }
                            }
                        }
                        snakes[cv][curr_snake].eat(food_gained);
                        if (!snakes[cv][i].dead)
                        {
                            field[x+FIELD_RADIUS][y+FIELD_RADIUS].erase(field[x+FIELD_RADIUS][y+FIELD_RADIUS].begin()+j);
                            --j;
                        }
                        else
                        {
                            for (int k=0;k<field[x+FIELD_RADIUS][y+FIELD_RADIUS].size();++k)
                            {
                                if (field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].first==i && field[x+FIELD_RADIUS][y+FIELD_RADIUS][k].second!=-1)
                                {
                                    field[x+FIELD_RADIUS][y+FIELD_RADIUS].erase(field[x+FIELD_RADIUS][y+FIELD_RADIUS].begin()+j);
                                    if (k<=j) --j;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        int snakes_alive=0;
        int mass_alive=0;
        int mass_dead=0;
        for (int i=0;i<snakes[cv].size();++i)
        {
            if (snakes[cv][i].dead)
            {
                if (snakes[cv][i].moveForward())
                {
                    for (int j=0;j<snakes[cv][i].blocks.size();++j)
                    {
                        curr_food=food(snakes[cv][i].blocks[j].x,snakes[cv][i].blocks[j].y,snakes[cv][i].colour_r,snakes[cv][i].colour_g,snakes[cv][i].colour_b);
                        foods[cv].push_back(curr_food);
                    }
                    removed_snakes.push_back(i);
                }
                else mass_dead+=snakes[cv][i].blocks.size();
            }
            else
            {
                ++snakes_alive;
                mass_alive+=snakes[cv][i].blocks.size();
            }
        }
        snakes[!cv].resize(0);
        sort(removed_snakes.begin(),removed_snakes.end());
        int rem_ind=0;
        for (int i=0;i<snakes[cv].size();++i)
        {
            if (rem_ind>=removed_snakes.size() || i<removed_snakes[rem_ind]) snakes[!cv].push_back(snakes[cv][i]);
            else
            {
                if (snakes[cv][i].dead>=0)
                {
                    snakes[cv][i].die(0);
                    //cerr<<"WARNING: Snake "<<i<<" not killed but removed."<<endl;
                }
                ++rem_ind;
            }
        }
        removed_snakes.resize(0);
        foods[!cv].resize(0);
        sort(removed_foods.begin(),removed_foods.end());
        rem_ind=0;
        for (int i=0;i<foods[cv].size();++i)
        {
            if (rem_ind>=removed_foods.size() || i<removed_foods[rem_ind]) foods[!cv].push_back(foods[cv][i]);
            else ++rem_ind;
        }
        removed_foods.resize(0);
        cv=!cv;
        //cout<<snakes_alive<<' '<<mass_alive<<' '<<double(mass_alive)/snakes_alive<<' '<<mass_dead<<' '<<foods[cv].size()<<' '<<mass_dead+foods[cv].size()<<'\n';
    }
}
