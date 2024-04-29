#ifndef NETWORK_H
#define NETWORK_H

#include "neural/neuron.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include <functional>
#include "others/function.h"

class network {
    public : 
        void addLayer(int insize, int size, int type, std::function<float(float x)> activationFunction);
        void initWeights(int range);
        std::vector<float> forward(std::vector<float> valueIn);
        std::vector<std::vector<neurons>> getLayers();
        void createMlp();
    private :
        std::vector<std::vector<neurons>> layers;
        std::vector<std::vector<float>> weights;
};



#endif