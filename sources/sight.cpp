#include "../headers/sight.h"

std::pair<int, bool> seeOne(field& field, point p, int dir)
{
    point o=p;
    int dist=0;
    bool food;
    bool first=1;
    while (field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty() && (p!=o || first))
    {
        first=0;
        ++dist;
        p+=dir;
    }
    if (field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty()) dist=-1;
    if (dist>=0 && field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS][0].second==-1) food=1;
    else food=0;
    return std::make_pair(dist,food);
}
void seeAll(field& field, snake& s)
{
    std::pair<int, bool> res;
    int dir;
    for (int i=0;i<=2*VF_RADIUS;++i)
    {
        s.ctr->VF_dist[i]=-1;
        s.ctr->VF_food[i]=0;
    }
    for (int i=0;i<=2*VS_RADIUS;++i)
    {
        s.ctr->VR_dist[i]=-1;
        s.ctr->VR_food[i]=0;
        s.ctr->VL_dist[i]=-1;
        s.ctr->VL_food[i]=0;
    }
    dir=(s.direction+1)%4;
    point p=s.blocks[0]+s.direction;
    for (int i=0;i<=VF_RADIUS;++i)
    {
        res=seeOne(field,p,s.direction);
        s.ctr->VF_dist[VF_RADIUS+i]=res.first;
        s.ctr->VF_food[VF_RADIUS+i]=res.second;
        if (!field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty()) break;
        p+=dir;
    }
    p=s.blocks[0]+s.direction;
    for (int i=0;i<=VF_RADIUS;++i)
    {
        res=seeOne(field,p,s.direction);
        s.ctr->VF_dist[VF_RADIUS-i]=res.first;
        s.ctr->VF_food[VF_RADIUS-i]=res.second;
        if (!field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty()) break;
        p-=dir;
    }
    p=s.blocks[0]+dir;
    for (int i=0;i<=VS_RADIUS;++i)
    {
        res=seeOne(field,p,dir);
        s.ctr->VR_dist[VS_RADIUS+i]=res.first;
        s.ctr->VR_food[VS_RADIUS+i]=res.second;
        if (!field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty()) break;
        p+=s.direction;
    }
    p=s.blocks[0]+dir;
    for (int i=0;i<=VS_RADIUS;++i)
    {
        res=seeOne(field,p,dir);
        s.ctr->VR_dist[VS_RADIUS-i]=res.first;
        s.ctr->VR_food[VS_RADIUS-i]=res.second;
        if (!field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty()) break;
        p-=s.direction;
    }
    p=s.blocks[0]-dir;
    for (int i=0;i<=VS_RADIUS;++i)
    {
        res=seeOne(field,p,(dir+2)%4);
        s.ctr->VL_dist[VS_RADIUS+i]=res.first;
        s.ctr->VL_food[VS_RADIUS+i]=res.second;
        if (!field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty()) break;
        p+=s.direction;
    }
    p=s.blocks[0]-dir;
    for (int i=0;i<=VS_RADIUS;++i)
    {
        res=seeOne(field,p,(dir+2)%4);
        s.ctr->VL_dist[VS_RADIUS-i]=res.first;
        s.ctr->VL_food[VS_RADIUS-i]=res.second;
        if (!field[p.x+FIELD_RADIUS][p.y+FIELD_RADIUS].empty()) break;
        p-=s.direction;
    }
}
