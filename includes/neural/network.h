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
        void addLayer(int inSize, int nbNeurons, int type, std::function<float(float x)> activationFunction);
        void initWeights(int range);

        void forward(std::vector<float> valueIn);
        void backward(std::vector<float> ytrue);
        void backwardNeurons(int i, int j);
        std::vector<std::vector<neurons>> getNeuronsMatrix();
        void calculateSoftmax();
        float softmaxDerivate(unsigned int neuronIndex);
        void createMlp();
        void printSelf();
    private :
        void initInValue(std::vector<float> valueIn, int layerPosition);
        float calculateDeltaWeight(int i, int j);
        std::vector<std::vector<neurons>> neuronsMatrix;
        // neuronsMatrix : Objet neurons J for the Layer I 

        std::vector<std::vector<std::vector<float>>> weights;
        std::vector<std::vector<std::vector<float>>> deltaWeights;
        std::vector<float> ytrue;
        // Weights : I = layer, J = neurons, K = K weights in of neuron.

        std::vector<std::vector<std::vector<float>>> inValues;
        // inValues : I = Layer, J = neurons, K = value in For the weight k

        std::vector<std::vector<float>> outValuesActivated;
        std::vector<std::vector<float>> outValuesNotActivated;
        // outValues : I = Layer, J = neurons
        std::vector<float> outSoftmaxed;
};



#endif