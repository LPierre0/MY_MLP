#include "neural/neuron.h"

neurons::neurons(unsigned int valueInSize, float biais, int type, std::function<float(float x)> activation){
    this->setValueInSize(valueInSize);
    this->setBiais(biais);
    this->setNeuronsType(type);
    this->setFunction(activation);
    this->outActivation = 0.0f;
    this->outSum = 0.0f;
}

// TODO: Paralléliser

void neurons::printSelf(){
    std::cout << std::endl << "AFFICHAGE DU NEURONNE" << std::endl;
    std::cout << "Value of biais : " << biais << std::endl;
    std::cout << "Value out : " << outActivation << std::endl;
    std::cout << "Type : " << neuronsType << std::endl;
    std::cout << "Weight in : ";
    printVectorFloat(this->weightIn);
    std::cout << "Value in  : ";
    printVectorFloat(this->valueIn);
    std::cout << std::endl;
}


// SETTERS

void neurons::setOut(int o){
    this->outActivation = o;
}

void neurons::setValueIn(std::vector<float> i){
    this->valueIn = i;
}

void neurons::setWeightIn(std::vector<float> wIn){
    this->weightIn = wIn;
}

void neurons::setNeuronsType(int t){
    this->neuronsType = t;
}

void neurons::setBiais(float b){
    this->biais = b;
}

void neurons::setValueInSize(unsigned int valueInSize){
    if (valueInSize < 1){
        throw std::runtime_error("The Size of value In is lower than 1");
    }
    this->valueInSize = valueInSize;
}

void neurons::setFunction(std::function<float(float x)> function){
    this->activation = function;
}

// GETTERS
float neurons::getOutActivation(){
    return this->outActivation;
}

int neurons::getNeuronsType(){
    return this->neuronsType;
}

float neurons::getBiais(){
    return this->biais;
}

std::vector<float> neurons::getValueIn(){
    return this->valueIn;
}

std::vector<float> neurons::getWeightIn(){
    return this->weightIn;
}

unsigned int neurons::getValueInSize(){
    return this->valueInSize;
}


void neurons::initWeight(int nbInPreviousLayer, int nbOut, int range){
    this->weightIn.assign(nbInPreviousLayer, 0.0f);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-(sqrt(6.0f) / sqrt(nbInPreviousLayer + nbOut)), (sqrt(6.0f) / sqrt(nbInPreviousLayer + nbOut)));
    for (unsigned int i = 0; i < this->weightIn.size(); i++){
        this->weightIn[i] = dis(gen);
    }
}



std::vector<float> neurons::calculateOut(std::vector<float> weights, std::vector<float> values){
    this->outSum = 0;
    for(unsigned int i = 0; i < values.size(); i++){
        this->outSum += values[i] * weights[i];
    }
    this->outActivation = this->activation(this->outSum);
    return {this->outActivation, this->outSum};
}

void neurons::actualiseWeight(int trueLabel){
    if (this->outActivation != trueLabel){
        for(unsigned int i = 0; i < this->valueIn.size(); i++){
            this->weightIn[i] = this->weightIn[i] + trueLabel * valueIn[i];
        }
    }
}