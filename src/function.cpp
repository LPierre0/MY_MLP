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

float tanhFunc(float x){
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
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
