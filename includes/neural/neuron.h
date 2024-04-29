#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <functional>
#include "others/utils.h"
#include <random>
#include <math.h>


#define PERCEPTRON 1

class neurons {

    public : 
        
        neurons(unsigned int dataSize, float biais, int type, std::function<float(float x)> activation);
        void train(std::vector<data_t> dataLabelled);
        int predict(std::vector<float> vecToPred);
        void printSelf();

        void setOut(int outToSet);
        void setValueIn(std::vector<float> valueInToSet);
        void setWeightIn(std::vector<float> wIn); 
        void setNeuronsType(int type);
        void setBiais(float biaisToSet);
        void setValueInSize(unsigned int valueInSize);
        void setFunction(std::function<float(float x)> activation);

        float getOut();
        int getNeuronsType();
        float getBiais();
        std::vector<float> getValueIn();
        std::vector<float> getWeightIn();
        unsigned int getValueInSize();
        void initWeight(int n, int m, int range);
        float calculateOut();

    private :

        float out;
        int neuronsType; 
        unsigned int valueInSize;
        float biais;
        std::function<float(float x)> activation;
        std::vector<float> valueIn;
        std::vector<float> weightIn;
        void actualiseWeight(int trueLabel);
};

#endif
