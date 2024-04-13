#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include "others/utils.h"

#define PERCEPTRON 1

class neurons {

    public : 
        
        neurons(unsigned int dataSize, float biais, int type);
        void train(std::vector<data_t> dataLabelled);
        int predict(std::vector<float> vecToPred);
        void printSelf();

        void setOut(int outToSet);
        void setValueIn(std::vector<float> valueInToSet);
        void setWeightIn(std::vector<float> wIn); 
        void setNeuronsType(int type);
        void setBiais(float biaisToSet);
        void setValueInSize(int valueInSize);

        int getOut();
        int getNeuronsType();
        float getBiais();
        std::vector<float> getValueIn();
        std::vector<float> getWeightIn();
        int getValueInSize();

    private :

        int out;
        int neuronsType; 
        int valueInSize;
        float biais;
        std::vector<float> valueIn;
        std::vector<float> weightIn;
        void initWeight(unsigned int dataSize);
        void calculateOut();
        void actualiseWeight(int trueLabel);
};

#endif
