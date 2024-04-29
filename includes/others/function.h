#ifndef FUNCTION_H
#define FUNCITON_H

#include <vector>
#include <iostream>
#include <math.h>


float relu(float x);
float sigmoide(float x);
float tanhFunc(float x);
float softmax(std::vector<float> out, int i);

#endif