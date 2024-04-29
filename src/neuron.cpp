#include "neural/neuron.h"

neurons::neurons(unsigned int valueInSize, float biais, int type, std::function<float(float x)> activation){
    this->setValueInSize(valueInSize);
    this->setBiais(biais);
    this->setNeuronsType(type);
    this->setFunction(activation);
    this->out = 0.0f;
}

// TODO: Paralléliser

void neurons::train(std::vector<data_t> dataLabelled){
    int nbIter = 0;
    int goodLabelsCount = 0;
    while (goodLabelsCount < dataLabelled.size() - 1 && nbIter < 100){
        goodLabelsCount = 0;
        std::vector<unsigned int> indicesTab = createShuffledIndices(dataLabelled.size());
        for(unsigned int i = 0; i < indicesTab.size(); i++){
            int indices = indicesTab[i];
            this->valueIn = dataLabelled[indices].vectorizedImg;
            this->calculateOut();
            if (this->out != dataLabelled[indices].label) this->actualiseWeight(dataLabelled[indices].label);
            else goodLabelsCount++;
        }
        nbIter++;
    }
}

int neurons::predict(std::vector<float> vecToPred){
    this->valueIn = vecToPred;
    this->calculateOut();
    return this->out;
}

void neurons::printSelf(){
    std::cout << std::endl << "AFFICHAGE DU NEURONNE" << std::endl;
    std::cout << "Value of biais : " << biais << std::endl;
    std::cout << "Value out : " << out << std::endl;
    std::cout << "Type : " << neuronsType << std::endl;
    std::cout << "Weight in : ";
    printVectorFloat(this->weightIn);
    std::cout << "Value in  : ";
    printVectorFloat(this->valueIn);
    std::cout << std::endl;
}


// SETTERS

void neurons::setOut(int o){
    this->out = o;
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
float neurons::getOut(){
    return this->out;
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



float neurons::calculateOut(){
    float sum = 0;
    for(unsigned int i = 0; i < this->valueIn.size(); i++){
        sum += valueIn[i] * weightIn[i];
    }
    sum += biais;
    this->out = this->activation(sum);
    return out;
}

void neurons::actualiseWeight(int trueLabel){
    if (this->out != trueLabel){
        for(unsigned int i = 0; i < this->valueIn.size(); i++){
            this->weightIn[i] = this->weightIn[i] + trueLabel * valueIn[i];
        }
    }
}