#ifndef CTRNEURALNETWORK_H_INCLUDED
#define CTRNEURALNETWORK_H_INCLUDED

#include "controller.h"
#include<vector>

struct ctrNeuralNetwork:controller
{
    double body_length_curve;
    double sight_distance_curve;
    double action_treshhold;

    int memory_neurons;
    std::vector<int> topology;
    std::vector<std::vector<std::vector<double> > > weights;
    std::vector<std::vector<double> > neurons;
    std::vector<std::vector<double> > importance;

    ctrNeuralNetwork();
    ctrNeuralNetwork(std::vector<int> new_topology);
    std::string getType();
    std::vector<double> getValues();
    void setValues(std::vector<double>& values);
    ctrNeuralNetwork* clone();
    void randomise();
    void mutate();
    void calcImportance(int mode);
    void calcImportancePartial(int mode);
    decision think();
    void loadInputs();
    void forwardPropagate();
    decision decodeOutputs();

    ~ctrNeuralNetwork() =default;
};

#endif // CTRNEURALNETWORK_H_INCLUDED
