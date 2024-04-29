#include "neural/network.h"


void network::addLayer(int insize, int size, int type, std::function<float(float x)> activationFunction){
    std::vector<neurons> layer;
    for(int i = 0; i < size; i++){
        neurons temp(insize, 0.0f, type, activationFunction);
        layer.push_back(temp);
    }
    layers.push_back(layer);
}


// This weight initialization came from the Normalized Xavier Weight Initialization.
void network::initWeights(int range){
    for (unsigned int i = 0; i < this->layers.size(); i++){
        unsigned int n = layers[i][0].getValueInSize();
        unsigned int m = layers[i].size();
        for(unsigned int j = 0; j < this->layers[i].size(); j++){
            this->layers[i][j].initWeight(n, m, range);
        }
    }
}

std::vector<std::vector<neurons>> network::getLayers(){
    return this->layers;
}


void network::createMlp(){
    this->addLayer(2, 3, PERCEPTRON, tanhFunc);
    this->addLayer(3, 3, PERCEPTRON, tanhFunc);
    this->initWeights(1000);
}


std::vector<float> network::forward(std::vector<float> valueIn){
    std::vector<std::vector<float>> outVector;
    for(auto layer: layers){
        std::vector<float> temp;
        for(auto neuron : layer){
            neuron.setValueIn(valueIn);
            float out = neuron.calculateOut();
            temp.push_back(out);
        }
        valueIn = temp;
        outVector.push_back(temp);
    }
    return outVector[outVector.size() - 1];
}