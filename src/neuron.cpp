#include "neural/neuron.h"



void neurons::actualiseWeight(int yTrain){
    if (this->out != yTrain){
        for(unsigned int i = 0; i < this->in.size(); i++){
            this->weightIn[i] = this->weightIn[i] + yTrain * in[i];
        }
    }
}

void neurons::calculateOut(){
    this->out = 0;
    float sum = 0;
    for(unsigned int i = 0; i < this->in.size(); i++){
        sum += in[i] * weightIn[i];
    }
    sum += biais;
    if (sum > 0) this->out = 1;
    else this->out = -1;
}

void neurons::init(std::vector<float> inValue, std::vector<float> weightIn, float biais, int type){
    this->setIn(inValue);
    this->setWeightIn(weightIn);
    this->setBiais(biais);
    this->setType(type);
    this->out = 0.0f;
}


void neurons::setType(int t){
    this->type = t;
}

void neurons::setBiais(float b){
    this->biais = b;
}

void neurons::setOut(int o){
    this->out = o;
}

void neurons::setIn(std::vector<float> i){
    this->in = i;
}

void neurons::setWeightIn(std::vector<float> wIn){
    this->weightIn = wIn;
}

void neurons::printSelf(){
    std::cout << std::endl << "AFFICHAGE DU NEURONNE" << std::endl;
    std::cout << "Value of biais : " << biais << std::endl;
    std::cout << "Value out : " << out << std::endl;
    std::cout << "Type : " << type << std::endl;
    std::cout << "Weight in : ";
    printVectorFloat(this->weightIn);
    std::cout << "Value in  : ";
    printVectorFloat(this->in);
    std::cout << std::endl;
}