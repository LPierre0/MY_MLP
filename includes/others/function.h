#ifndef FUNCTION_H
#define FUNCITON_H

#include <vector>
#include <iostream>
#include <math.h>


float relu(float x);
float sigmoide(float x);
float tanhFunc(float x);
float softmax(std::vector<float> out, int i);
float crossEntropyLossDerivate(float predictionSoftmax, float ypred);
float crossEntropyLoss(std::vector<float> predictionSoftmax, std::vector<float> yTrue);
float tanhFuncDerivate(float x);
float sigmoideDerivate(float x);

#endif