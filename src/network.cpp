#include "neural/network.h"


void network::addLayer(int inSize, int nbNeurons, int type, std::function<float(float x)> activationFunction){
    std::vector<neurons> layer;
    // inSize + 1 for the biais
    std::vector<std::vector<float>> tempLayer(nbNeurons, std::vector<float>(inSize + 1, 0.0f));
    std::vector<float> tempOut(nbNeurons, 0.0f);
    for(int i = 0; i < nbNeurons; i++){
        neurons temp(inSize, 0.0f, type, activationFunction);
        layer.push_back(temp);
    }
    this->inValues.push_back(tempLayer);
    this->weights.push_back(tempLayer);
    this->outValuesActivated.push_back(tempOut);
    this->outValuesNotActivated.push_back(tempOut);
    this->neuronsMatrix.push_back(layer);
}


void network::initWeights(int range){
    for (unsigned int i = 0; i < this->weights.size(); i++){
        // For each layers
        unsigned int nbInPreviousLayer = this->neuronsMatrix[i][0].getValueInSize();
        unsigned int nbOut = this->neuronsMatrix[i].size();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-(sqrt(6.0f) / sqrt(nbInPreviousLayer + nbOut)), (sqrt(6.0f) / sqrt(nbInPreviousLayer + nbOut)));
        for(unsigned int j = 0; j < this->weights[i].size(); j++){
            for (unsigned k = 0; k < this->weights[i][j].size(); k++){
                this->weights[i][j][k] = dis(gen);
            }
        }
    }
}


std::vector<std::vector<neurons>> network::getNeuronsMatrix(){
    return this->neuronsMatrix;
}


void network::createMlp(){
    this->addLayer(160000, 200, PERCEPTRON, tanhFunc);
    this->addLayer(200, 151, PERCEPTRON, tanhFunc);
    this->initWeights(1000);
}




void network::initInValue(std::vector<float> valueIn, int layerPosition){
    for (unsigned int j = 0; j < this->inValues[layerPosition].size(); j++){
        for(unsigned int k = 0; k < valueIn.size(); k++){
            this->inValues[layerPosition][j][k] = valueIn[k];
        }
        this->inValues[layerPosition][j][valueIn.size()] = 1; // Biais
    }
}

void network::forward(std::vector<float> valueIn){
    this->initInValue(valueIn, 0);
    for(unsigned int i = 0; i < neuronsMatrix.size(); i++){
        for(unsigned int j = 0; j < neuronsMatrix[i].size(); j++){
            std::vector<float> temp = neuronsMatrix[i][j].calculateOut(this->weights[i][j], this->inValues[i][j]);
            outValuesActivated[i][j] = temp[0];
            outValuesNotActivated[i][j] = temp[1];
        }
        if (i < neuronsMatrix.size() - 1){
            this->initInValue(outValuesActivated[i], i + 1);
        }
    }
    this->calculateSoftmax();
}





void network::calculateSoftmax(){
    unsigned int lastLayer = this->outValuesActivated.size() - 1;
    for (unsigned int i = 0; i < this->outValuesActivated[lastLayer].size(); i++){
        this->outSoftmaxed.push_back(softmax(this->outValuesActivated[lastLayer], i));
    }
}

std::vector<std::vector<std::vector<float>>> initDeltaWeight(std::vector<std::vector<std::vector<float>>> weights){
    std::vector<std::vector<std::vector<float>>> deltaWeights;
    for (const auto& layer : weights) {
        std::vector<std::vector<float>> deltaLayer;
        for (const auto& row : layer) {
            std::vector<float> deltaRow(row.size(), 0.0f);
            deltaLayer.push_back(deltaRow);
        }
        deltaWeights.push_back(deltaLayer);
    }

    return deltaWeights;
}


float network::softmaxDerivate(unsigned int neuronIndex){
    float softmax_neuron = outSoftmaxed[neuronIndex];
    return softmax_neuron * (1.0f - softmax_neuron);
}


float network::calculateDeltaWeight(int i, int j){
    if (i == this->neuronsMatrix.size() - 1){
        float temp = crossEntropyLossDerivate(this->outSoftmaxed[i], ytrue[i]);
        temp = temp * tanhFuncDerivate(this->outValuesNotActivated[i][j]);
        temp = temp * this->softmaxDerivate(j);
        for(unsigned int k = 0; k < this->weights[i][j].size(); k++){
            this->deltaWeights[i][j][k] = temp * inValues[i][j][k];
        }
        return temp;
    }else{
        float sum = 0.0f;
        for (unsigned int LayerNextPos = 0;  LayerNextPos < neuronsMatrix[i + 1].size(); LayerNextPos++){
            sum += weights[i + 1][LayerNextPos][j] * tanhFuncDerivate(outValuesNotActivated[i + 1][LayerNextPos]) * calculateDeltaWeight(i + 1, LayerNextPos);
        }
        for(unsigned int k = 0; k < weights[i][j].size(); k++){
            deltaWeights[i][j][k] = inValues[i][j][k] * tanhFuncDerivate(outValuesNotActivated[i][j]) * sum;
        }
        return sum;
    }
}

void displayDeltaWeights(const std::vector<std::vector<std::vector<float>>>& deltaWeights) {
    // Parcourir chaque couche de poids
    for (size_t i = 0; i < deltaWeights.size(); ++i) {
        std::cout << "Layer " << i << ":\n";

        // Parcourir chaque ligne dans une couche de poids
        for (size_t j = 0; j < deltaWeights[i].size(); ++j) {
            // Afficher la ligne
            std::cout << "Row " << j << ": [";
            for (size_t k = 0; k < deltaWeights[i][j].size(); ++k) {
                std::cout << deltaWeights[i][j][k];
                if (k != deltaWeights[i][j].size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]\n";
        }
        std::cout << "\n";
    }
}
void network::backward(std::vector<float> ytrue){
    this->ytrue = ytrue;
    unsigned int lastLayerPos = this->neuronsMatrix.size() - 1;
    this->deltaWeights = initDeltaWeight(this->weights);
    for (unsigned int j = 0; j < this->neuronsMatrix[0].size(); j++){
        this->calculateDeltaWeight(0, j);
    }
}



void network::printSelf(){
    std::cout << "Number of layers" << this->neuronsMatrix.size() << std::endl;
    std::cout << "Affichage des poids" << std::endl;
    for(unsigned int i = 0; i < weights.size(); i++){
        for (unsigned int j = 0; j < weights[i].size(); j++){
            for (unsigned int k = 0; k < weights[i][j].size(); k++){
                std::cout << this->weights[i][j][k] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Affichage des valeurs d'entrées" << std::endl;
    for(unsigned int i = 0; i < inValues.size(); i++){
        for (unsigned int j = 0; j < inValues[i].size(); j++){
            for (unsigned int k = 0; k < inValues[i][j].size(); k++){
                std::cout << this->inValues[i][j][k] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Affichage des valeurs de sortie activé" << std::endl;
    for(unsigned int i = 0; i < outValuesActivated.size(); i++){
        for (unsigned int j = 0; j < outValuesActivated[i].size(); j++){
            std::cout << this->outValuesActivated[i][j] << ", ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}