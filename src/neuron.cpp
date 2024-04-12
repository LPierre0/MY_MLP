#include "neural/neuron.h"
#include "others/utils.h"


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


void neurons::initWeight(unsigned int dataSize){
    this->weightIn.assign(dataSize, 0.0f);
}

void neurons::init(unsigned int dataSize,float biais, int type){
    this->initWeight(dataSize);
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

void neurons::train(std::vector<data_t> dataLabelled){
    int nbIter = 0;
    int nbNoModif = 0;
    while (nbNoModif < dataLabelled.size() - 1 && nbIter < 100){
        nbNoModif = 0;
        std::vector<unsigned int> indicesTab = shuffle(dataLabelled.size());
        for(unsigned int i = 0; i < indicesTab.size(); i++){

            this->in = dataLabelled[indicesTab[i]].vectorizedImg;
            this->calculateOut();
            if (this->out != dataLabelled[indicesTab[i]].label){
                this->actualiseWeight(dataLabelled[indicesTab[i]].label);
            }else{
                nbNoModif++;
            }
        }
        nbIter++;
    }
}


int neurons::predict(std::vector<float> vecToPred){
    this->in = vecToPred;
    this->calculateOut();
    return this->out;
}