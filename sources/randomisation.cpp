#include "../headers/randomisation.h"
#include<stdlib.h>

int MAX_MUTATION=30;

void mutateVariable(double& variable, double low, double high)
{
    if (rand()%100) variable+=rand()%(MAX_MUTATION*2+1)/1000.0-MAX_MUTATION/1000.0;
    else if (rand()%10) variable+=rand()%(MAX_MUTATION*2+1)/50.0-MAX_MUTATION/50.0;
    else randomiseVariable(variable,low,high);
    if (variable<low) variable=low;
    if (variable>high) variable=high;
}
void randomiseVariable(double& variable, double low, double high)
{
    variable=rand()%(int(high-low)*1000+1)/1000.0+low;
}
