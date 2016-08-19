#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "decision.h"
#include<string>
#include<vector>

extern const int inputs;
extern const int outputs;

struct controller
{
    static const int VF_RADIUS=1;
    static const int VS_RADIUS=0;

    int VF_dist[1+2*VF_RADIUS];
    bool VF_food[1+2*VF_RADIUS];
    int VL_dist[1+2*VS_RADIUS];
    bool VL_food[1+2*VS_RADIUS];
    int VR_dist[1+2*VS_RADIUS];
    bool VR_food[1+2*VS_RADIUS];

    int body_length;
    int energy;

    virtual std::string getType() =0;
    virtual std::vector<double> getValues() =0;
    virtual controller* clone() =0;
    virtual void randomise() =0;
    virtual void mutate() =0;
    virtual decision think() =0;

    virtual ~controller() =default;
};

#endif // CONTROLLER_H_INCLUDED
