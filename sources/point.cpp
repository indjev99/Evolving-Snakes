#include "../headers/point.h"
#include "../headers/field_radius.h"
#include<stdlib.h>

void point::operator+=(int dir)
{
    if (dir%4==0) y+=dir/4+1;
    if (dir%4==1) x+=dir/4+1;
    if (dir%4==2) y-=dir/4+1;
    if (dir%4==3) x-=dir/4+1;
    if (x>=FIELD_RADIUS) x-=2*FIELD_RADIUS;
    if (y>=FIELD_RADIUS) y-=2*FIELD_RADIUS;
    if (x<-FIELD_RADIUS) x+=2*FIELD_RADIUS;
    if (y<-FIELD_RADIUS) y+=2*FIELD_RADIUS;
}
void point::operator-=(int dir)
{
    if (dir%4==0) y-=dir/4+1;
    if (dir%4==1) x-=dir/4+1;
    if (dir%4==2) y+=dir/4+1;
    if (dir%4==3) x+=dir/4+1;
    if (x>=FIELD_RADIUS) x-=2*FIELD_RADIUS;
    if (y>=FIELD_RADIUS) y-=2*FIELD_RADIUS;
    if (x<-FIELD_RADIUS) x+=2*FIELD_RADIUS;
    if (y<-FIELD_RADIUS) y+=2*FIELD_RADIUS;
}
point point::operator+(int dir)
{
    point p;
    p.x=x;
    p.y=y;
    if (dir%4==0) p.y+=dir/4+1;
    if (dir%4==1) p.x+=dir/4+1;
    if (dir%4==2) p.y-=dir/4+1;
    if (dir%4==3) p.x-=dir/4+1;
    if (p.x>=FIELD_RADIUS) p.x-=2*FIELD_RADIUS;
    if (p.y>=FIELD_RADIUS) p.y-=2*FIELD_RADIUS;
    if (p.x<-FIELD_RADIUS) p.x+=2*FIELD_RADIUS;
    if (p.y<-FIELD_RADIUS) p.y+=2*FIELD_RADIUS;
    return p;
}
point point::operator-(int dir)
{
    point p;
    p.x=x;
    p.y=y;
    if (dir%4==0) p.y-=dir/4+1;
    if (dir%4==1) p.x-=dir/4+1;
    if (dir%4==2) p.y+=dir/4+1;
    if (dir%4==3) p.x+=dir/4+1;
    if (p.x>=FIELD_RADIUS) p.x-=2*FIELD_RADIUS;
    if (p.y>=FIELD_RADIUS) p.y-=2*FIELD_RADIUS;
    if (p.x<-FIELD_RADIUS) p.x+=2*FIELD_RADIUS;
    if (p.y<-FIELD_RADIUS) p.y+=2*FIELD_RADIUS;
    return p;
}
bool point::operator==(point a)
{
    if (x==a.x && y==a.y) return 1;
    return 0;
}
bool point::operator!=(point a)
{
    if (x!=a.x || y!=a.y) return 1;
    return 0;
}
void point::randomise()
{
    x=rand()%(2*FIELD_RADIUS)-FIELD_RADIUS;
    y=rand()%(2*FIELD_RADIUS)-FIELD_RADIUS;
}
point::point()
{
    randomise();
}
point::point(int new_x, int new_y)
{
    x=new_x;
    y=new_y;
}
