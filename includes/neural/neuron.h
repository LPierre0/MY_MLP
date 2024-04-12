#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include "others/utils.h"

#define PERCEPTRON 1

class neurons {
    public : 
        float biais;
        std::vector<float> in;
        int out;
        std::vector<float> weightIn;
        int type; 
        void setOut(int o);
        void setIn(std::vector<float> i);
        void setWeightIn(std::vector<float> wIn); 
        void setType(int t);
        void setBiais(float b);
        void init(std::vector<float> inValue, std::vector<float> weightIn, float biais, int type);
        void calculateOut();
        void printSelf();
        void actualiseWeight(int yTrain);
};

#endif