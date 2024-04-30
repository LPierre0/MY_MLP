#include "others/function.h"


float relu(float x){
    if (x > 0){
        return x;
    }
    return 0;
}


float sigmoide(float x){
    return 1 / (1 + exp((-x)));
}

float sigmoideDerivate(float x){
    return sigmoide(x) * (1 - sigmoide(x));
}

float tanhFunc(float x){
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

float tanhFuncDerivate(float x){
    return 1 - (tanhFunc(x) * tanhFunc(x));
}

float softmax(std::vector<float> out, int i){
    if (i > out.size()){
        std::cerr << "Error out of range in function softmax" << std::endl;
    }
    float sum = 0.0f;
    for(unsigned j = 0; j < out.size(); j++){
        sum += exp(out[j]);
    }
    return exp(out[i])/sum;
}


float crossEntropyLoss(std::vector<float> predictionSoftmax, std::vector<float> yTrue){
    if (predictionSoftmax.size() != yTrue.size()){
        std::cerr << "Prediction and True Labels don't have the same size " << predictionSoftmax.size() << " vs " << yTrue.size() << std::endl; 
        return 0;
    }
    float loss;
    for(unsigned int i = 0; i < predictionSoftmax.size(); i++){
        loss += predictionSoftmax[i] * yTrue[i];
    }
    loss = loss * (-1);
    return loss;
}

float crossEntropyLossDerivate(float predictionSoftmax, float ypred){
    return (-ypred) * (1 - predictionSoftmax);
}