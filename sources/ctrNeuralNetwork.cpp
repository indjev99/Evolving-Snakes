#include "../headers/ctrNeuralNetwork.h"
#include "../headers/decision.h"
#include "../headers/randomisation.h"
#include<math.h>

ctrNeuralNetwork::ctrNeuralNetwork() {}
ctrNeuralNetwork::ctrNeuralNetwork(std::vector<int> new_topology)
{
    topology=new_topology;
    if (topology.empty())
    {
        memory_neurons=0;
        topology.push_back(inputs);
    }
    else
    {
        memory_neurons=topology[0];
        topology[0]=inputs+memory_neurons;
    }
    topology.push_back(outputs+memory_neurons);
    neurons.resize(topology.size());
    weights.resize(topology.size());
    for (int i=0;i<topology.size();++i)
    {
        neurons[i].resize(topology[i]);
        weights[i].resize(topology[i]);
        if (i)
        {
            for (int j=0;j<topology[i];++j)
            {
                weights[i][j].resize(topology[i-1]);
            }
        }
    }
}
std::string ctrNeuralNetwork::getType()
{
    return "neuralNetwork";
}
std::vector<double> ctrNeuralNetwork::getValues()
{
    std::vector<double> values;

    values.push_back(body_length_curve);
    values.push_back(sight_distance_curve);
    values.push_back(action_treshhold);

    values.push_back(topology.size());
    for (int i=0;i<topology.size();++i)
    {
        values.push_back(topology[i]);
        for (int j=0;j<topology[i];++j)
        {
            values.push_back(neurons[i][j]);
            if (i)
            {
                for (int k=0;k<topology[i-1];++k)
                {
                    values.push_back(weights[i][j][k]);
                }
            }
        }
    }
    return values;
}
void ctrNeuralNetwork::setValues(std::vector<double>& values)
{
    int curr=0;

    body_length_curve=values[curr++];
    sight_distance_curve=values[curr++];
    action_treshhold=values[curr++];

    topology.resize(round(values[curr++]));
    neurons.resize(topology.size());
    weights.resize(topology.size());

    //cout<<topology.size()<<": "<<"\n";

    for (int i=0;i<topology.size();++i)
    {
        topology[i]=round(values[curr++]);
        //cout<<i<<". "<<topology[i]<<": "<<"\n";
        neurons[i].resize(topology[i]);
        weights[i].resize(topology[i]);
        for (int j=0;j<topology[i];++j)
        {
            neurons[i][j]=values[curr++];
            //cout<<" "<<j<<". "<<neurons[i][j]<<"\n";
            if (i)
            {
                weights[i][j].resize(topology[i-1]);
                for (int k=0;k<topology[i-1];++k)
                {
                    weights[i][j][k]=values[curr++];
                }
            }
       }
    }
    memory_neurons=topology[0]-inputs;
}
ctrNeuralNetwork* ctrNeuralNetwork::clone()
{
    return new ctrNeuralNetwork(*this);
}
void ctrNeuralNetwork::randomise()
{
    randomiseVariable(body_length_curve,0,1);
    randomiseVariable(sight_distance_curve,0,1);
    randomiseVariable(action_treshhold,0,1);
    for (int i=1;i<topology.size();++i)
    {
        for (int j=0;j<topology[i];++j)
        {
            for (int k=0;k<topology[i-1];++k)
            {
                randomiseVariable(weights[i][j][k],-2,2);
            }
        }
    }
}
void ctrNeuralNetwork::mutate()
{
    mutateVariable(body_length_curve,0,1);
    mutateVariable(sight_distance_curve,0,1);
    mutateVariable(action_treshhold,0,1);
    for (int i=1;i<topology.size();++i)
    {
        for (int j=0;j<topology[i];++j)
        {
            for (int k=0;k<topology[i-1];++k)
            {
                mutateVariable(weights[i][j][k],-2,2);
            }
        }
    }
}
decision ctrNeuralNetwork::think()
{
    decision decision;
    loadInputs();
    forwardPropagate();
    decision=decodeOutputs();
    return decision;
}
decision ctrNeuralNetwork::decodeOutputs()
{
    int curr=0;
    decision decision;
    if (neurons[topology.size()-1][curr++]>=action_treshhold) decision.turn_right=1;
    else decision.turn_right=0;
    if (neurons[topology.size()-1][curr++]>=action_treshhold) decision.turn_left=1;
    else decision.turn_left=0;
    if (neurons[topology.size()-1][curr++]>=action_treshhold) decision.split=1;
    else decision.split=0;
    decision.split_length=round(body_length*neurons[topology.size()-1][curr++]);
    return decision;
}
void ctrNeuralNetwork::forwardPropagate()
{
    for (int i=1;i<topology.size();++i)
    {
        for (int j=0;j<topology[i];++j)
        {
            neurons[i][j]=0;
            for (int k=0;k<topology[i-1];++k)
            {
                neurons[i][j]+=neurons[i-1][k]*weights[i][j][k];
            }
            if (neurons[i][j]<0) neurons[i][j]=0;
            if (neurons[i][j]>1) neurons[i][j]=1;
        }
    }
}
void ctrNeuralNetwork::loadInputs()
{
    int curr=0;
    neurons[0][curr++]=1;
    neurons[0][curr++]=1-pow(1-body_length_curve,body_length);
    neurons[0][curr++]=(energy>=0?1:-1)*(1-pow(1-body_length_curve,fabs(energy)));
    for (int i=0;i<=2*VF_RADIUS;++i)
    {
        if (VF_dist[i]>=0) neurons[0][curr++]=pow(1-sight_distance_curve,VF_dist[i]);
        else neurons[0][curr++]=0;
        neurons[0][curr++]=VF_food[i];
    }
    for (int i=0;i<=2*VS_RADIUS;++i)
    {
        if (VR_dist[i]>=0) neurons[0][curr++]=pow(1-sight_distance_curve,VR_dist[i]);
        else neurons[0][curr++]=0;
        neurons[0][curr++]=VR_food[i];
    }
    for (int i=0;i<=2*VS_RADIUS;++i)
    {
        if (VL_dist[i]>=0) neurons[0][curr++]=pow(1-sight_distance_curve,VL_dist[i]);
        else neurons[0][curr++]=0;
        neurons[0][curr++]=VL_food[i];
    }
    for (int i=0;i<memory_neurons;++i)
    {
        neurons[0][curr++]=neurons[topology.size()-1][outputs+i];
    }
}
