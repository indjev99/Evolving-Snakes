#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct point
{
    int x;
    int y;
    void operator+=(int dir);
    void operator-=(int dir);
    point operator+(int dir);
    point operator-(int dir);
    bool operator==(point a);
    bool operator!=(point a);
    void randomise();
    point();
    point(int new_x, int new_y);

    ~point() =default;
};

#endif // POINT_H_INCLUDED
